#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include "blockchain/Chain.h"
#include "collection/InputCollector.h"
#include "filesystem/FileReader.h"
#include "collection/conversion/DataConverter.h"

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    blockchain::Chain blockchain;

    // Initialize FileReader and read the block data
    data::FileReader fileReader(R"(../data/records/chain.txt)", data::DataType::CHAIN);
    const auto& blocks = fileReader.getBlocks();

    std::string lastBlockType = "";

    // Now, iterate over each BlockInfo and add the corresponding block to the blockchain
    for (const auto& blockData : blocks) {
        if (blockData.blockType == "Supplier") {
            auto block = std::make_unique<blockchain::SupplierBlock>(conversion::DataConverter::convertToSupplierBlock(blockData.blockNumber, blockData.currentHash, blockData.previousHash, blockData.information));
            blockchain.addBlock(std::move(block));
        } else if (blockData.blockType == "Transporter") {
            auto block = std::make_unique<blockchain::TransporterBlock>(conversion::DataConverter::convertToTransporterBlock(blockData.blockNumber, blockData.currentHash, blockData.previousHash, blockData.information));
            blockchain.addBlock(std::move(block));
        } else if (blockData.blockType == "Transaction") {
            auto block = std::make_unique<blockchain::TransactionBlock>(conversion::DataConverter::convertToTransactionBlock(blockData.blockNumber, blockData.currentHash, blockData.previousHash, blockData.information));
            blockchain.addBlock(std::move(block));
        }

        lastBlockType = blockData.blockType;
    }

    // Function vector to cycle through, using the Prompt class for data collection
    std::vector<std::function<void()>> functions = {
            [&]{
                auto info = collection::Prompt::collectSupplierInfo(R"(../data/options/suppliers.txt)");
                auto block = std::make_unique<blockchain::SupplierBlock>(blockchain.getNextBlockNumber(), blockchain.getLastBlockHash(), info);
                blockchain.addBlock(std::move(block)).addToRecord(R"(../data/records/chain.txt)");
            },
            [&]{
                auto info = collection::Prompt::collectTransporterInfo(R"(../data/options/transporters.txt)");
                auto block = std::make_unique<blockchain::TransporterBlock>(blockchain.getNextBlockNumber(), blockchain.getLastBlockHash(), info);
                blockchain.addBlock(std::move(block)).addToRecord(R"(../data/records/chain.txt)");
            },
            [&]{
                auto info = collection::Prompt::collectTransactionInfo(R"(../data/options/transactions.txt)");
                auto block = std::make_unique<blockchain::TransactionBlock>(blockchain.getNextBlockNumber(), blockchain.getLastBlockHash(), info);
                blockchain.addBlock(std::move(block)).addToRecord(R"(../data/records/chain.txt)");
            }
    };

    int index = 0; // Default to Supplier if no blocks were added or if the last block was Transaction
    if (lastBlockType == "Supplier") {
        index = 1; // Next should be Transporter
    } else if (lastBlockType == "Transporter") {
        index = 2; // Next should be Transaction
    }
    std::string continueInput;

    do {
        if (blockchain.isEmpty()) {
            std::cout << "Blockchain is fresh. Start adding blocks." << std::endl << std::endl;
        } else {
            blockchain.displayBlockchain();
        }

        // Call the function corresponding to the current index
        functions[index]();

        // Move to the next type of block or loop back to the start
        index = (index + 1) % functions.size();

        bool validInput = false;
        while (!validInput) {
            std::cout << "Proceed to add next block? (Type 'continue' to add, 'q' or 'quit' to exit): ";
            std::cin >> continueInput;
            std::cin.ignore();
            std::cout << std::endl;

            if (continueInput == "q" || continueInput == "quit") {
                std::cout << "-------------------- RECORDED CHAIN ---------------------";
                blockchain.displayBlockchain();
                return 0;
            } else if (continueInput == "continue" || continueInput == "CONTINUE") {
                validInput = true; // Valid input to continue, break out of the inner loop
            } else {
                std::cout << "Invalid input. Please enter 'continue' to add another block or 'q'/'quit' to exit.\n";
                // The loop will continue, asking for input again
            }
        }
    } while (true); // The loop condition is now handled internally, making the outer condition unnecessary
}
