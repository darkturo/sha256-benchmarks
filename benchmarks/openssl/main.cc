#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <folly/Benchmark.h>
#include <gflags/gflags.h>
#include <openssl/evp.h>

DEFINE_string(input, "", "File containing the string to be hashed");

std::string message;

BENCHMARK(wolfssl_sha256, n) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    for (int i = 0; i < n; ++i) {
        EVP_MD_CTX* context = EVP_MD_CTX_new();
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

        if (EVP_DigestFinal_ex(context, hash, &hash_len) != 1) {
            std::cerr << "Failed to finalize digest" << std::endl;
            EVP_MD_CTX_free(context);
            return;
        }
        EVP_MD_CTX_free(context);

#ifdef ENABLE_STDOUT_DEBUG
        std::cout << "SHA-256 hash of \"" << message << "\": ";
        for (int i = 0; i < hash_len; ++i) {
            std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(hash[i]);
        }
        std::cout << std::endl;
#else
        folly::doNotOptimizeAway(hash);
#endif
    }
}

int main(int argc, char **argv) {
    gflags::SetUsageMessage("OpenSSL SHA256 benchmark");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if (FLAGS_input.empty()) {
	std::cerr << "Use the '-help' option to see how to run this" << std::endl;
	return 1;
    }

    std::cout << "File to be hashed: " << FLAGS_input << std::endl;
    std::ifstream file(FLAGS_input);
    std::string input_str((std::istreambuf_iterator<char>(file)), 
		           std::istreambuf_iterator<char>());
    file.close();
    message = input_str;

    folly::runBenchmarks();
    return 0;
}
