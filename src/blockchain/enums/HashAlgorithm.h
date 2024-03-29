#ifndef HASHALGORITHM_H
#define HASHALGORITHM_H

#include <string>

namespace blockchain::enums {
    /**
     * @brief Enum class for HashAlgorithm
     */
    enum class HashAlgorithm {
        SHA256,
        SHA384,
        SHA512,
    };
} // namespace blockchain

#endif // HASHALGORITHM_H
