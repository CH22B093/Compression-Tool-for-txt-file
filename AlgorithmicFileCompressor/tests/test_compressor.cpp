#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "compressor.h"

TEST_CASE("Compression and Decompression","[compressor]"){
    Compressor comp;
    std::string text = "aaabbc";
    auto compressed = comp.compress(text);
    auto decompressed = comp.decompress(compressed);
    REQUIRE(decompressed == text);
}
