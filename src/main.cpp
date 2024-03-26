#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include "blockchain/Chain.h"
#include "collection/InputCollector.h"
#include "filesystem/FileReader.h"
#include "collection/conversion/DataConverter.h"
#include "collection/validator/InputValidator.h"
#include "../data/Config.h"

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    blockchain::Chain blockchain(data::Config::VERSION);

    // Initialize FileReader and read the block data
    filesystem::FileReader fileReader(R"(../data/records/chain.txt)", filesystem::DataType::CHAIN);
    const auto& blocks = fileReader.getBlocks();

    blockchain::enums::BlockType lastBlockType = blockchain::enums::BlockType::TRANSACTION; // Default to Transaction if no blocks were added

    if (!blocks.empty()) {
        // Now, iterate over each BlockInfo and add the corresponding block to the blockchain
        for (const auto& blockData : blocks) {
            if (blockData.type == blockchain::enums::BlockType::SUPPLIER) {
                auto block = std::make_unique<blockchain::SupplierBlock>(conversion::DataConverter::convertToSupplierBlock(data::Config::VERSION, blockchain.getBits(), blockData.height, blockData.nonce, blockData.currentHash, blockData.previousHash, blockData.information));
                blockchain.addBlock(std::move(block));
            } else if (blockData.type == blockchain::enums::BlockType::TRANSPORTER) {
                auto block = std::make_unique<blockchain::TransporterBlock>(conversion::DataConverter::convertToTransporterBlock(data::Config::VERSION, blockchain.getBits(), blockData.height, blockData.nonce, blockData.currentHash, blockData.previousHash, blockData.information));
                blockchain.addBlock(std::move(block));
            } else if (blockData.type == blockchain::enums::BlockType::TRANSACTION) {
                auto block = std::make_unique<blockchain::TransactionBlock>(conversion::DataConverter::convertToTransactionBlock(data::Config::VERSION, blockchain.getBits(), blockData.height, blockData.nonce, blockData.currentHash, blockData.previousHash, blockData.information));
                blockchain.addBlock(std::move(block));
            }

            lastBlockType = blockData.type;
        }
    }

    // Function vector to cycle through, using the Prompt class for data collection
    std::vector<std::function<void()>> functions = {
            [&]{
                auto info = collection::Prompt::collectSupplierInfo(R"(../data/options/suppliers.txt)");
                auto block = std::make_unique<blockchain::SupplierBlock>(data::Config::VERSION, blockchain.getBits(), blockchain.getNextBlockHeight(), blockchain.getLastBlockHash(), info);
                blockchain.addBlock(std::move(block)).addToRecord(R"(../data/records/chain.txt)");
            },
            [&]{
                auto info = collection::Prompt::collectTransporterInfo(R"(../data/options/transporters.txt)");
                auto block = std::make_unique<blockchain::TransporterBlock>(data::Config::VERSION, blockchain.getBits(), blockchain.getNextBlockHeight(), blockchain.getLastBlockHash(), info);
                blockchain.addBlock(std::move(block)).addToRecord(R"(../data/records/chain.txt)");
            },
            [&]{
                auto info = collection::Prompt::collectTransactionInfo(R"(../data/options/transactions.txt)", R"(../data/records/chain.txt)");
                auto block = std::make_unique<blockchain::TransactionBlock>(data::Config::VERSION, blockchain.getBits(), blockchain.getNextBlockHeight(), blockchain.getLastBlockHash(), info);
                blockchain.addBlock(std::move(block)).addToRecord(R"(../data/records/chain.txt)");
            }
    };

    std::string continueInput;
    std::vector<std::string> actionOptions = { "Display blockchain", "Search Block", "Add Block" };
    std::vector<std::string> searchOptions = { "Block Type", "Height", "Version", "Nonce", "Current Hash", "Previous Hash", "Merkle Root", "Timestamp", "Bits", "Information" };

    std::cout << "Enter values based on the given options or 'q'/'quit' to exit the program anytime." << std::endl << std::endl;

    int index; // Default to Supplier if no blocks were added or if the last block was Transaction
    switch (lastBlockType) {
        case blockchain::enums::BlockType::SUPPLIER:
            index = 1; // Next should be Transporter
            break;
        case blockchain::enums::BlockType::TRANSPORTER:
            index = 2; // Next should be Transaction
            break;
        case blockchain::enums::BlockType::TRANSACTION:
        default:
            index = 0; // Default to Supplier if the last block was Transaction or no blocks were added
            break;
    }

    do {
        int action = collection::validation::InputValidator::validateSelectionInt("an action", actionOptions);

        if (action == 1) {
            if (blockchain.isEmpty()) {
                std::cout << "No blocks found in the blockchain." << std::endl << std::endl;
            } else {
                blockchain.display();
            }
        } else if (action == 2) {
            int searchByAttr = collection::validation::InputValidator::validateSelectionInt("a attribute to search by", searchOptions);
            std::string searchValue = collection::validation::InputValidator::validateString("a value to search for");

            blockchain.searchBlockByAttr(static_cast<blockchain::enums::BlockAttribute>(searchByAttr - 1), searchValue);
        } else if (action == 3) {
            // Call the function at the current index
            functions[index]();

            // Move to the next type of block or loop back to the start
            index = (index + 1) % functions.size();
        }
    } while (true);
}
