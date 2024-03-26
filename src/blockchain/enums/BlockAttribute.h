#ifndef BLOCKATTRIBUTE_H
#define BLOCKATTRIBUTE_H

#include <string>

namespace blockchain::enums {
    enum class BlockAttribute {
        TYPE,
        HEIGHT,
        VERSION,
        NONCE,
        HASH,
        PREV_HASH,
        MERKLE_ROOT,
        TIMESTAMP,
        BITS,
        INFORMATION,
    };

    class BlockAttributeUtils {
    public:
        static BlockAttribute fromString(const std::string& typeString);
        static std::string toString(BlockAttribute type);
    };
} // namespace blockchain

#endif // BLOCKATTRIBUTE_H
