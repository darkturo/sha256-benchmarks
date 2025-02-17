#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <folly/Benchmark.h>
#include <gflags/gflags.h>
#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/sha256.h>


DEFINE_string(input, "", "File containing the string to be hashed");

std::string message;

BENCHMARK(woflssl_sha256, n) {
    byte hash[WC_SHA256_DIGEST_SIZE];
    wc_Sha256 sha256;

    wc_InitSha256(&sha256);
    wc_Sha256Update(&sha256, reinterpret_cast<const byte*>(message.c_str()), message.size());
    wc_Sha256Final(&sha256, hash);


    std::cout << "SHA-256 hash of \"" << message << "\": ";
    for (int i = 0; i < WC_SHA256_DIGEST_SIZE; ++i) {
	std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(hash[i]);
    }
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    gflags::SetUsageMessage("WolfSSL SHA256 benchmark");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if (FLAGS_input.empty()) {
	std::cerr << "Please provide a string to be hashed with -c flag" << std::endl;
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
