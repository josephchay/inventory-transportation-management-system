#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <string>

namespace blockchain::enums {
    /**
     * @brief Enum class for BlockType
     */
    enum class BlockType {
        SUPPLIER,
        TRANSPORTER,
        TRANSACTION,
    };

    class BlockTypeUtils {
    public:
        /**
         * Convert a string to a BlockType
         *
         * @param typeString
         * @return
         */
        static BlockType fromString(const std::string& typeString);

        /**
         * Convert a BlockType to a string
         *
         * @param type
         * @return
         */
        static std::string toString(BlockType type);
    };
} // namespace blockchain

#endif // BLOCKTYPE_H
