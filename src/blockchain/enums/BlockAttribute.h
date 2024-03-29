#ifndef BLOCKATTRIBUTE_H
#define BLOCKATTRIBUTE_H

#include <string>

namespace blockchain::enums {
    /**
     * @brief Enum class for BlockAttribute
     */
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
        MINED,
        VISIBLE,
    };

    class BlockAttributeUtils {
    public:
        /**
         * Convert a string to a BlockAttribute
         *
         * @param typeString
         * @return
         */
        static BlockAttribute fromString(const std::string& typeString);

        /**
         * Convert a BlockAttribute to a string
         *
         * @param type
         * @return
         */
        static std::string toString(BlockAttribute type);
    };
} // namespace blockchain

#endif // BLOCKATTRIBUTE_H
