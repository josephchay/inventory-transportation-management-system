#include <stdexcept>
#include "BlockAttribute.h"

namespace blockchain::enums {
    std::string BlockAttributeUtils::toString(BlockAttribute attribute) {
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
            default:
                throw std::invalid_argument("Unknown BlockAttribute");
        }
    }
} // namespace blockchain
