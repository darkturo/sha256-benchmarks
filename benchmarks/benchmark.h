#pragma once

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <folly/Benchmark.h>
#include <gflags/gflags.h>

namespace benchmark {
    std::string message;

    DEFINE_string(input, "", "File containing the string to be hashed");

    int run() {
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

    concept ByteType = requires(T a) {
        { a } -> std::convertible_to<char>;
    };

    template <typename digest_trait, typename print_digest_trait, class ByteType, int DigestSize>
    void digest_benchmark(uint32_t n) {
        ByteType digest[DigestSize];
        for (int i = 0; i < n; ++i) {
            digest_trait(message, digest);
#ifdef ENABLE_STDOUT_DEBUG
            print_digest_trait(digest);
#else
            folly::doNotOptimizeAway(digest);
#endif
            }
    }

    template <class ByteType, int DigestSize>
    void print_digest_default(ByteType *digest) {
        std::cout << "SHA-256 hash of \"" << message << "\": ";
        for (int i = 0; i < DigestSize; ++i) {
            std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(digest[i]);
        }
        std::cout << std::endl;
    }
}