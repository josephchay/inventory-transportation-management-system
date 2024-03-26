#pragma once

#include "Block.h"
#include <string>

namespace blockchain {
    struct TransporterInfo {
        int transporterId;
        std::string transporterName;
        std::string productType;
        std::string transportationType;
        std::string orderingType;
        double orderingAmount;

        TransporterInfo() = default;
        TransporterInfo(const int& id, const std::string& name, const std::string& productType, const std::string& transportationType, const std::string& orderingType, const double& orderingAmount)
                : transporterId(id), transporterName(name), productType(productType), transportationType(transportationType), orderingType(orderingType), orderingAmount(orderingAmount) {}
    };

    class TransporterBlock : public Block {
    public:
        TransporterBlock(const int version, const std::string bits, int height, const std::string& previousHash, const TransporterInfo& info, int nonce = 0, const std::string& currentHash = "", bool visible = true);

        TransporterInfo getInfo() const;

    private:
        TransporterInfo info;
        static std::string formatTransporterInfo(const TransporterInfo& info);
    };
}
