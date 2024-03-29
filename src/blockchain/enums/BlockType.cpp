#include "BlockType.h"
#include <stdexcept>

namespace blockchain::enums {
    BlockType BlockTypeUtils::fromString(const std::string& typeString) {
        // Convert the string to the corresponding BlockType
        // (If else statements are used instead of switch-case because the enum class values are not continuous)
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

    std::string BlockTypeUtils::toString(BlockType type) {
        // Convert the BlockType to the corresponding string
        switch (type) {
            case BlockType::SUPPLIER:
                return "Supplier";
            case BlockType::TRANSPORTER:
                return "Transporter";
            case BlockType::TRANSACTION:
                return "Transaction";
            default:
                throw std::invalid_argument("Unknown BlockType");
        }
    }
}
