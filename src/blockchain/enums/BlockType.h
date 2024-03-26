#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <string>

namespace blockchain::enums {
    enum class BlockType {
        SUPPLIER,
        TRANSPORTER,
        TRANSACTION,
    };

    class BlockTypeUtils {
    public:
        static BlockType fromString(const std::string& typeString);
        static std::string toString(BlockType type);
    };
} // namespace blockchain

#endif // BLOCKTYPE_H
