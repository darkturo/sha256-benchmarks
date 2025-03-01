#include <string>
#include <openssl/evp.h>

#include "../benchmark.h"


template <benchmark::ByteType T>
void openssl_sha256(const std::string &message, T *digest) {
    unsigned int hash_len;
    EVP_MD_CTX *context = EVP_MD_CTX_new();
    if (context == nullptr) {
        std::cerr << "Failed to create context" << std::endl;
        return;
    }

    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) {
        std::cerr << "Failed to initialize digest" << std::endl;
        EVP_MD_CTX_free(context);
        return;
    }

    if (EVP_DigestUpdate(context, message.c_str(), message.size()) != 1) {
        std::cerr << "Failed to update digest" << std::endl;
        EVP_MD_CTX_free(context);
        return;
    }

    if (EVP_DigestFinal_ex(context, digest, &hash_len) != 1) {
        std::cerr << "Failed to finalize digest" << std::endl;
        EVP_MD_CTX_free(context);
        return;
    }
    EVP_MD_CTX_free(context);
}

BENCH_MAIN(openssl_sha256, unsigned char, EVP_MAX_MD_SIZE)

