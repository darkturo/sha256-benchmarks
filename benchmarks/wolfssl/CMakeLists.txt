cmake_minimum_required(VERSION 3.10)

include(${PROJECT_SOURCE_DIR}/cmake/Benchmark.cmake)

build_benchmark(wolfsha256 wolfssl)