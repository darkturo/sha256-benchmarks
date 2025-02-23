#include <string>
#include <fstream>
#include <iostream>
#include <folly/Benchmark.h>
#include <gflags/gflags.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>


DEFINE_string(input, "", "File containing the string to be hashed");

std::string message;

BENCHMARK(openssl_sha256, n) {
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SHA256 hash;

    for (int i = 0; i < n; ++i) {
        hash.CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte*>(message.c_str()), message.size());

        BENCHMARK_SUSPEND {
#ifdef ENABLE_STDOUT_DEBUG
            CryptoPP::HexEncoder encoder;
            std::string output;
            encoder.Attach(new CryptoPP::StringSink(output));
            encoder.Put(digest, sizeof(digest));
            encoder.MessageEnd();

            std::cout << "SHA-256 digest of \"" << message << "\": " << output << std::endl;
#else
            folly::doNotOptimizeAway(digest);
#endif
        }
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
