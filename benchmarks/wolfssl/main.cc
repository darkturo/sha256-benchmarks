#include <string>
#include <wolfssl/wolfcrypt/sha256.h>

#include "../benchmark.h"

template <benchmark::ByteType T>
void wolfssl_sha256(const std::string &message, T *digest) {
    wc_Sha256 sha256;

    wc_InitSha256(&sha256);
    wc_Sha256Update(&sha256, reinterpret_cast<const byte *>(message.c_str()), message.size());
    wc_Sha256Final(&sha256, digest);
}

BENCH_MAIN(wolfssl_sha256, byte, WC_SHA256_DIGEST_SIZE)