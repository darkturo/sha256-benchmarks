#include <string>
#include <vector>
#include <iostream>
#include <ippcp.h>

#include "../benchmark.h"

#define DEBUG 1
inline int checkStatus(const char* funcName, IppStatus expectedStatus, IppStatus status)
{
    if (expectedStatus != status) {
        std::cerr << funcName << ": unexpected return status" << std::endl;
        std::cerr << "Expected: " << ippcpGetStatusString(expectedStatus) << std::endl;
        std::cerr << "Received: " << ippcpGetStatusString(status) << std::endl;
        return 0;
    }
    return 1;
}

template <benchmark::ByteType T>
void intel_crypto_sha256(const std::string &message, T *digest) {
    IppStatus status = ippStsNoErr;
    const IppsHashMethod* hash_method = ippsHashMethod_SHA256_NI();

    int context_size = 0;
    status = ippsHashGetSize_rmf(&context_size);
#ifdef DEBUG
    if (!checkStatus("ippsHashGetSize", ippStsNoErr, status)) {
        return;
    }
#endif

    std::vector<Ipp8u> context_buffer(context_size);
    IppsHashState_rmf* hash_state = (IppsHashState_rmf*)(context_buffer.data());
    status = ippsHashInit_rmf(hash_state, hash_method);
#ifdef DEBUG
    if (!checkStatus("ippsHashInit", ippStsNoErr, status)) {
        return;
    }
#endif

    status = ippsHashUpdate_rmf(reinterpret_cast<const Ipp8u *>(message.c_str()), message.size() - 1, hash_state);
#ifdef DEBUG
    if (!checkStatus("ippsHashUpdate", ippStsNoErr, status)) {
        return;
    }
#endif

    status = ippsHashFinal_rmf(digest, hash_state);
#ifdef DEBUG
    if (!checkStatus("ippsHashFinal", ippStsNoErr, status)) {
        return;
    }
#endif

}

BENCH_MAIN(intel_crypto_sha256, Ipp8u, IPP_SM3_DIGEST_BYTESIZE)