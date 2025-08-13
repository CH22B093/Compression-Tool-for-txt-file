#include "compressor.h"
#include <iostream>
#include <fstream>

int main(int argc,char* argv[]) {
    if(argc <4){
        std::cout<<"Usage: compress_tool [compress|decompress] <input_file> <output_file>\n";
        return 1;
    }

    std::string mode = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    Compressor comp;
    if(mode == "compress"){
        std::ifstream in(inputFile);
        std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        auto compressed = comp.compress(content);
        std::ofstream out(outputFile, std::ios::binary);
        out.write(reinterpret_cast<const char*>(compressed.data()),compressed.size());
    } else if(mode == "decompress"){
        std::ifstream in(inputFile, std::ios::binary);
        std::vector<Byte> data((std::istreambuf_iterator<char>(in)),std::istreambuf_iterator<char>());
        auto decompressed = comp.decompress(data);
        std::ofstream out(outputFile);
        out << decompressed;
    } else {
        std::cout<<"Invalid mode"<<std::endl;
        return 1;
    }
    return 0;
}
