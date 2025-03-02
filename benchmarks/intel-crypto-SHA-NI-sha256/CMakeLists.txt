cmake_minimum_required(VERSION 3.10)

# Don't ask me, couldn't make it work in a better way with find_package :-S
set(IPPCP_LIBRARIES "/usr/local/lib/intel64/libippcp_s_mx.a")

build_benchmark(intel-crypto-SHANI-sha256-bench LIBRARIES ${IPPCP_LIBRARIES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(check_SHA_NI sha_ni_available.cc)
target_link_libraries(check_SHA_NI
        PRIVATE
        ${IPPCP_LIBRARIES})
