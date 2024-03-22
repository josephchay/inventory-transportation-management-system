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
                blockchain.addBlock(std::make_unique<blockchain::SupplierBlock>(blockchain.getNextBlockNumber(), blockchain.getLastBlockHash(), info), R"(../data/records/chain.txt)");
            },
            [&]{
                auto info = collection::Prompt::collectTransporterInfo(R"(../data/options/transporters.txt)");
                blockchain.addBlock(std::make_unique<blockchain::TransporterBlock>(blockchain.getNextBlockNumber(), blockchain.getLastBlockHash(), info), R"(../data/records/chain.txt)");
            },
            [&]{
                auto info = collection::Prompt::collectTransactionInfo(R"(../data/options/transactions.txt)");
                blockchain.addBlock(std::make_unique<blockchain::TransactionBlock>(blockchain.getNextBlockNumber(), blockchain.getLastBlockHash(), info), R"(../data/records/chain.txt)");
            }
    };

    int index = 0; // Start with Supplier
    std::string continueInput;

    do {
        // Call the function corresponding to the current index
        functions[index]();

        // Move to the next type of block or loop back to the start
        index = (index + 1) % functions.size();

        blockchain.displayBlockchain();

        bool validInput = false;
        while (!validInput) {
            std::cout << "Proceed to add next block? (Type 'continue' to add, 'q' or 'quit' to exit): ";
            std::cin >> continueInput;
            std::cin.ignore();
            std::cout << std::endl;

            if (continueInput == "q" || continueInput == "quit") {
                return 0; // Exit program if user inputs 'q' or 'quit'
            } else if (continueInput == "continue" || continueInput == "CONTINUE") {
                validInput = true; // Valid input to continue, break out of the inner loop
            } else {
                std::cout << "Invalid input. Please enter 'continue' to add another block or 'q'/'quit' to exit.\n";
                // The loop will continue, asking for input again
            }
        }
    } while (true); // The loop condition is now handled internally, making the outer condition unnecessary
}
