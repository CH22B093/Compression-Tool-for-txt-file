add_executable(test_compressor test_compressor.cpp)
target_link_libraries(test_compressor PRIVATE compressor)
add_test(NAME CompressorTest COMMAND test_compressor)
