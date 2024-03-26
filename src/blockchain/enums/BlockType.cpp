#include "BlockType.h"
#include <stdexcept>

namespace blockchain::enums {
    /**
     * @brief Convert string to BlockType
     *
     * @param typeString
     * @return
     */
    BlockType BlockTypeUtils::fromString(const std::string& typeString) {
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

    /**
     * @brief Convert BlockType to string
     *
     * @param type
     * @return
     */
    std::string BlockTypeUtils::toString(BlockType type) {
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
