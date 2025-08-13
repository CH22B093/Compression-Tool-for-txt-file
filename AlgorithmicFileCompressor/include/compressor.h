#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <cstddef>

using Byte = unsigned char;
class Compressor {
public:
    struct Node{
        char ch;
        uint32_t freq;
        Node* left;
        Node* right;
        Node(char c,uint32_t f);
        Node(char c,uint32_t f,Node* l,Node* r);
    };

    std::vector<Byte> compress(const std::string& input);
    std::string decompress(const std::vector<Byte>& inputData);

private:
    void buildFrequencyMap(const std::string& input,std::unordered_map<char,uint32_t>& freqMap);
    Node* buildHuffmanTree(const std::unordered_map<char,uint32_t>& freqMap);
    void buildCodes(Node* node,const std::string& prefix,std::unordered_map<char,std::string>& codes);
    void deleteTree(Node* node);
    void writeUint32(std::vector<Byte>& out,uint32_t value);
    uint32_t readUint32(const std::vector<Byte>& data,std::size_t& idx);
};