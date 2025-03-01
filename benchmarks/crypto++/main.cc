#include <string>
#include <cryptopp/sha.h>

#ifdef ENABLE_STDOUT_DEBUG
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#endif

#include "../benchmark.h"


CryptoPP::SHA256 hash;

template <benchmark::ByteType T>
void cryptopp_sha256(const std::string &message, T *digest) {
    hash.CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte*>(message.c_str()), message.size());
}

BENCH_MAIN(cryptopp_sha256, CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE)
