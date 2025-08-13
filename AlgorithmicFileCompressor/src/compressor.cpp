#include "compressor.h"

#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>
#include <cstddef>

using Node = Compressor::Node;

struct Compare{
    bool operator()(Node* a,Node* b) const{
        return a->freq > b->freq;
    }
};

Compressor::Node::Node(char c,uint32_t f)
  : ch(c),freq(f),left(nullptr),right(nullptr){}

Compressor::Node::Node(char c,uint32_t f,Node* l,Node* r)
  : ch(c),freq(f),left(l),right(r){}

void Compressor::buildFrequencyMap(const std::string& input,std::unordered_map<char,uint32_t>& freqMap)
{
    for (char c:input)freqMap[c]++;
}

Compressor::Node* Compressor::buildHuffmanTree(
    const std::unordered_map<char, uint32_t>& freqMap)
{
    std::priority_queue<Node*,std::vector<Node*>,Compare> pq;
    for (auto& p:freqMap)
        pq.push(new Node(p.first,p.second));
    if (pq.size() == 1) {
        Node* only = pq.top();pq.pop();
        return new Node('\0',only->freq,only,nullptr);
    }

    while (pq.size() > 1){
        Node* l = pq.top();pq.pop();
        Node* r = pq.top();pq.pop();
        pq.push(new Node('\0',l->freq + r->freq,l,r));
    }
    return pq.top();
}

void Compressor::buildCodes(Node* node,const std::string& prefix,std::unordered_map<char,std::string>& codes)
{
    if (!node) return;
    if (!node->left && !node->right){
        codes[node->ch] = prefix.empty()?"0":prefix;
    } else{
        buildCodes(node->left,prefix + "0",codes);
        buildCodes(node->right,prefix + "1",codes);
    }
}
void Compressor::deleteTree(Node* node)
{
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
void Compressor::writeUint32(std::vector<Byte>& out,uint32_t value)
{
    for (int i = 0;i<4;++i)
        out.push_back(static_cast<Byte>((value>>(i*8)) & 0xFF));
}

uint32_t Compressor::readUint32(const std::vector<Byte>& data,size_t& idx)
{
    uint32_t v = 0;
    for (int i = 0;i<4;++i)
        v |= static_cast<uint32_t>(data[idx++])<<(i*8);
    return v;
}

std::vector<Byte> Compressor::compress(const std::string& input)
{
    std::unordered_map<char,uint32_t> freq;
    buildFrequencyMap(input, freq);

    Node* root = buildHuffmanTree(freq);
    std::unordered_map<char,std::string> codes;
    buildCodes(root, "", codes);

    std::vector<Byte> out;
    writeUint32(out,static_cast<uint32_t>(freq.size()));
    for (auto& p:freq){
        out.push_back(static_cast<Byte>(p.first));
        writeUint32(out,p.second);
    }
    std::string bits;
    bits.reserve(input.size()*8);
    for (char c:input)
        bits += codes[c];

    writeUint32(out,static_cast<uint32_t>(bits.size()));
    Byte curr = 0;int count=0;
    for (char b:bits){
        curr = (curr<<1) | (b=='1');
        if (++count==8){out.push_back(curr);curr=0;count=0;}
    }
    if (count>0) {curr<<=(8-count);out.push_back(curr);}

    deleteTree(root);
    return out;
}

std::string Compressor::decompress(const std::vector<Byte>& inputData)
{
    size_t idx=0;
    uint32_t mapSz = readUint32(inputData,idx);
    std::unordered_map<char,uint32_t> freq;
    for (uint32_t i=0;i<mapSz;++i){
        char c = static_cast<char>(inputData[idx++]);
        freq[c] = readUint32(inputData,idx);
    }
    Node* root = buildHuffmanTree(freq);
    uint32_t bitLen = readUint32(inputData,idx);

    std::vector<bool> bits;
    bits.reserve(bitLen);
    while (idx < inputData.size() && bits.size()<bitLen){
        Byte b = inputData[idx++];
        for (int i=7; i>=0 && bits.size()<bitLen;--i)
            bits.push_back((b>>i)&1);
    }

    std::string result;
    result.reserve(bitLen);
    Node* cur = root;
    for (bool bit:bits){
        cur = bit?cur->right:cur->left;
        if (!cur->left && !cur->right){
            result += cur->ch;
            cur = root;
        }
    }

    deleteTree(root);
    return result;
}