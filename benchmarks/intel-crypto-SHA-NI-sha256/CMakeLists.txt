cmake_minimum_required(VERSION 3.10)

# Don't ask me, couldn't make it work in a better way with find_package :-S
set(IPPCP_LIBRARIES "/usr/local/lib/intel64/libippcp_s_mx.a")

build_benchmark(intel-crypto-SHANI-sha256-bench LIBRARIES ${IPPCP_LIBRARIES})