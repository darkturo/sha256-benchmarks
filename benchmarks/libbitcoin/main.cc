#include <string>
#include <bitcoin/system.hpp>

#include "../benchmark.h"

template <benchmark::ByteType T>
void bitcoincore_sha256(const std::string &message, T *digest) {
    bc::system::data_chunk data(message.begin(), message.end());
    bc::system::hash_digest digest = bc::system::sha256_hash(data);
}


BENCH_MAIN(bitcoincore_sha256, unsigned char, CSHA256::OUTPUT_SIZE)