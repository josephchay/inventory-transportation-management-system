#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include "blockchain/Chain.h"
#include "collection/InputCollector.h"

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    blockchain::Chain blockchain;

    // Function vector to cycle through, using the Prompt class for data collection
    std::vector<std::function<void()>> functions = {
            [&]{
                auto info = collection::Prompt::collectSupplierInfo(R"(../data/options/suppliers.txt)");
                blockchain.addBlock(std::make_unique<blockchain::SupplierBlock>(blockchain.getNextBlockNumber(), blockchain.getLastBlockHash(), info));
            },
            [&]{
                auto info = collection::Prompt::collectTransporterInfo(R"(../data/options/transporters.txt)");
                blockchain.addBlock(std::make_unique<blockchain::TransporterBlock>(blockchain.getNextBlockNumber(), blockchain.getLastBlockHash(), info));
            },
            [&]{
                auto info = collection::Prompt::collectTransactionInfo(R"(../data/options/transactions.txt)");
                blockchain.addBlock(std::make_unique<blockchain::TransactionBlock>(blockchain.getNextBlockNumber(), blockchain.getLastBlockHash(), info));
            }
    };

    int index = 0; // Start with Supplier
    char continueInput;

    do {
        // Call the function corresponding to the current index
        functions[index]();

        // Move to the next type of block or loop back to the start
        index = (index + 1) % functions.size();

        blockchain.displayBlockchain();

        std::cout << "Continue to add next block? (y/n): ";
        std::cin >> continueInput;
        std::cin.ignore();
        std::cout << std::endl;
    } while (continueInput == 'y' || continueInput == 'Y');

    return 0;
}
