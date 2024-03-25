// BlockType.cpp
#include "BlockType.h"
#include <stdexcept>

namespace blockchain::enums {
    // Function definition
    BlockType fromString(const std::string& typeString) {
        if (typeString == "Supplier") {
            return BlockType::SUPPLIER;
        } else if (typeString == "Transporter") {
            return BlockType::TRANSPORTER;
        } else if (typeString == "Transaction") {
            return BlockType::TRANSACTION;
        } else {
            throw std::invalid_argument("Unknown BlockType string: " + typeString);
        }
    }
}
