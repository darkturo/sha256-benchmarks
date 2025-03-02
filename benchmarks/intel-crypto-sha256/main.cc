#include <string>
#include <vector>
#include <iostream>
#include <ippcp.h>
//#define ENABLE_STDOUT_DEBUG 1

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
    //NOTE: So at the moment in my computer I don't seem to have access in runtime to the SHA-NI extensions
    //      so I'm running this with ippsHashMethod_SHA256(). I could use ippsHashMethod_SHA256_TT() instead
    //      but for this cases I think the best is to duplicate and have two benchmarks one for intel crypto
    //      without the extensions, and another one with the extensions, that may not be available (how to know
    //      before running if I should skip? ... hmmm)
    const IppsHashMethod* hash_method = ippsHashMethod_SHA256();

    int context_size = 0;
    status = ippsHashGetSize_rmf(&context_size);
#ifdef DEBUG
    if (!checkStatus("ippsHashGetSize", ippStsNoErr, status)) {
        return;
    }
#endif

    std::vector<Ipp8u> context_buffer(context_size);
    IppsHashState_rmf* hash_state = reinterpret_cast<IppsHashState_rmf*>(context_buffer.data());
    status = ippsHashInit_rmf(hash_state, hash_method);
#ifdef DEBUG
    if (!checkStatus("ippsHashInit", ippStsNoErr, status)) {
        return;
    }
#endif

    status = ippsHashUpdate_rmf(reinterpret_cast<const Ipp8u *>(message.c_str()), message.size(), hash_state);
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