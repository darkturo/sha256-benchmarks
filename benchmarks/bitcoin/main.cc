#include <string>
#include <bitcoin/crypto/sha256.h>

#include "../benchmark.h"


template <benchmark::ByteType T>
void bitcoincore_sha256(const std::string &message, T *digest) {
    CSHA256()
            .Write(reinterpret_cast<const unsigned char*>(message.data()), message.size())
            .Finalize(digest);
}

BENCH_MAIN(bitcoincore_sha256, unsigned char, CSHA256::OUTPUT_SIZE)