#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <string>

namespace blockchain::enums {
    enum class BlockType {
        SUPPLIER,
        TRANSPORTER,
        TRANSACTION,
    };

    BlockType fromString(const std::string& typeString);
    std::string toString(BlockType type);
} // namespace blockchain

#endif // BLOCKTYPE_H
