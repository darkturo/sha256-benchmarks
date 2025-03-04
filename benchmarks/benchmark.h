#pragma once

#include <string>
#include <fmt/core.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <folly/Benchmark.h>
#include <gflags/gflags.h>


DEFINE_string(input, "", "File containing the string to be hashed");

namespace benchmark {
    std::string message;

    template <typename T>
    concept ByteType = requires(T a) {
        { a } -> std::convertible_to<char>;
    };

    template <ByteType T, int DigestSize>
    class digest_trait {
    public:
        typedef void hash_fun_type(const std::string &message, T *digest);

        digest_trait(hash_fun_type *fun) : hash(fun) {}

        hash_fun_type *hash;

        void print(T *digest) {
            std::cout << "SHA-256 hash of \"" << message << "\": ";
            for (int i = 0; i < DigestSize; ++i) {
                std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(digest[i]);
            }
            std::cout << std::endl;
        }
    };

    template <ByteType T,
              int DigestSize,
              typename trait = digest_trait<T, DigestSize>>
    void bechmarker(void fun(const std::string &message, T *digest), uint32_t n) {
        T digest[DigestSize];
        auto hasher = trait(fun);
        for (int i = 0; i < n; ++i) {
            hasher.hash(message, digest);
#ifdef ENABLE_STDOUT_DEBUG
            hasher.print(digest);
#else
            folly::doNotOptimizeAway(digest);
#endif
        }
    }


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
}

#define BENCH(digest_func, byte_type, digest_size)                         \
        BENCHMARK(digest_func, n) {                                        \
            benchmark::bechmarker<byte_type, digest_size>(digest_func, n); \
        }

#define MAIN(name) \
    int main(int argc, char **argv) {                        \
        std::string usage = #name;                           \
        usage += " SHA256 benchmark";                        \
        gflags::SetUsageMessage(usage);                      \
        gflags::ParseCommandLineFlags(&argc, &argv, true);   \
        return benchmark::run();                             \
    }

#define BENCH_MAIN(digest_func, byte_type, digest_size) \
        BENCH(digest_func, byte_type, digest_size)      \
        MAIN(digest_func)
