#include <iostream>
#include <ippcp.h>

int main() {
    const IppsHashMethod* hash_method = ippsHashMethod_SHA256_NI();
    if (hash_method == nullptr) {
        std::cerr << "SHA-NI not available in runtime" << std::endl;
        return 1;
    }
    return 0;
}