// BlockType.h
#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <string>

namespace blockchain::enums {
    enum class BlockType {
        SUPPLIER,
        TRANSPORTER,
        TRANSACTION,
    };

    static BlockType fromString(const std::string& typeString);
} // namespace blockchain

#endif // BLOCKTYPE_H
