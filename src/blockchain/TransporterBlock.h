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
        TransporterBlock(int blockNumber, const std::string& previousBlockHash, const TransporterInfo& info);

        TransporterInfo getInfo() const;

    private:
        TransporterInfo info;
        static std::string formatTransporterInfo(const TransporterInfo& info);
    };
}
