#include <stdexcept>
#include "BlockAttribute.h"

namespace blockchain::enums {
    BlockAttribute BlockAttributeUtils::fromString(const std::string& attributeString) {
        // Convert the string to the corresponding BlockAttribute
        // (If else statements are used instead of switch-case because the enum class values are not continuous)
        if (attributeString == "Block Type") {
            return BlockAttribute::TYPE;
        } else if (attributeString == "Height") {
            return BlockAttribute::HEIGHT;
        } else if (attributeString == "Version") {
            return BlockAttribute::VERSION;
        } else if (attributeString == "Nonce") {
            return BlockAttribute::NONCE;
        } else if (attributeString == "Current Hash") {
            return BlockAttribute::HASH;
        } else if (attributeString == "Previous Hash") {
            return BlockAttribute::PREV_HASH;
        } else if (attributeString == "Merkle Root") {
            return BlockAttribute::MERKLE_ROOT;
        } else if (attributeString == "Timestamp") {
            return BlockAttribute::TIMESTAMP;
        } else if (attributeString == "Bits") {
            return BlockAttribute::BITS;
        } else if (attributeString == "Information") {
            return BlockAttribute::INFORMATION;
        } else if (attributeString == "Mined") {
            return BlockAttribute::MINED;
        } else if (attributeString == "Visible") {
            return BlockAttribute::VISIBLE;
        } else {
            throw std::invalid_argument("Unknown BlockAttribute");
        }
    }

    std::string BlockAttributeUtils::toString(BlockAttribute attribute) {
        // Convert the BlockAttribute to the corresponding string
        switch (attribute) {
            case BlockAttribute::TYPE:
                return "Block Type";
            case BlockAttribute::HEIGHT:
                return "Height";
            case BlockAttribute::VERSION:
                return "Version";
            case BlockAttribute::NONCE:
                return "Nonce";
            case BlockAttribute::HASH:
                return "Current Hash";
            case BlockAttribute::PREV_HASH:
                return "Previous Hash";
            case BlockAttribute::MERKLE_ROOT:
                return "Merkle Root";
            case BlockAttribute::TIMESTAMP:
                return "Timestamp";
            case BlockAttribute::BITS:
                return "Bits";
            case BlockAttribute::INFORMATION:
                return "Information";
            case BlockAttribute::MINED:
                return "Mined";
            case BlockAttribute::VISIBLE:
                return "Visible";
            default:
                throw std::invalid_argument("Unknown BlockAttribute");
        }
    }
} // namespace blockchain
