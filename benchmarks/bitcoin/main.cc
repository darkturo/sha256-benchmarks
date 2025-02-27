#include <string>
#include <fstream>
#include <iostream>
#include <folly/Benchmark.h>
#include <gflags/gflags.h>
#include <bitcoin/crypto/sha256.h>


DEFINE_string(input, "", "File containing the string to be hashed");

std::string message;

BENCHMARK(bitcoincore_sha256, n) {
    unsigned char digest[CSHA256::OUTPUT_SIZE];

    for (int i = 0; i < n; ++i) {
	CSHA256()
       		.Write(reinterpret_cast<const unsigned char*>(message.data()), message.size())
	        .Finalize(digest);

        BENCHMARK_SUSPEND {
#ifdef ENABLE_STDOUT_DEBUG
            for (int i = 0; i < CSHA256::OUTPUT_SIZE; i++) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
            }

            std::cout << "SHA-256 digest of \"" << message << "\": " << output << std::endl;
#else
            folly::doNotOptimizeAway(digest);
#endif
        }
    }
}

int main(int argc, char **argv) {
    gflags::SetUsageMessage("Bitcoin core sha256 benchmark");
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
