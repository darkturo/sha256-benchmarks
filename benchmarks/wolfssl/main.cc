#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <folly/Benchmark.h>
#include <gflags/gflags.h>
#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/sha256.h>

#include "../benchmark.h"

template <benchmark::ByteType T>
void wolfssl_sha256(const std::string &message, T *digest) {
    wc_Sha256 sha256;

    wc_InitSha256(&sha256);
    wc_Sha256Update(&sha256, reinterpret_cast<const byte *>(message.c_str()), message.size());
    wc_Sha256Final(&sha256, digest);
}

BENCHMARK(digest_bench, n) {
    benchmark::bechmarker<byte, WC_SHA256_DIGEST_SIZE>(wolfssl_sha256, n);
}

int main(int argc, char **argv) {
    gflags::SetUsageMessage("WolfSSL SHA256 benchmark");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    return benchmark::run();
}
