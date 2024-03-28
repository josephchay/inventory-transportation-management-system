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
#include "authentication/Login.h"

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    /**
     * @brief The chain of blocks where all blocks are from the real data blockchain record.
     */
    blockchain::Chain blockchain(data::Config::RECORDS_BLOCKCHAIN_FILE_PATH, data::Config::VERSION);

    /**
     * @brief The chain of blocks where some blocks are hidden (redacted) from the display view output to the user.
     * aka. The temporary storage of the blockchain data.
     */
    blockchain::Chain redactedBlockchain(data::Config::RECORDS_BLOCKCHAIN_FILE_PATH, data::Config::VERSION);

    // Read the block data
    filesystem::FileReader fileReaderChain(data::Config::RECORDS_BLOCKCHAIN_FILE_PATH, filesystem::DataType::CHAIN);
    const auto& blocks = fileReaderChain.getBlocks();

    blockchain::enums::BlockType lastBlockType = blockchain::enums::BlockType::TRANSACTION; // Default to Transaction if no blocks were added

    if (!blocks.empty()) {
        // Iterate over each BlockData and add the corresponding block to the blockchain
        for (const auto& blockData : blocks) {
            if (blockData.type == blockchain::enums::BlockType::SUPPLIER) {
                auto block = std::make_shared<blockchain::SupplierBlock>(conversion::DataConverter::convertToSupplierBlock(data::Config::VERSION, blockchain.getBits(), blockData.height, blockData.nonce, blockData.currentHash, blockData.previousHash, blockData.information, blockData.visible));
                blockchain.addBlock(block);
                redactedBlockchain.addBlock(block);
            } else if (blockData.type == blockchain::enums::BlockType::TRANSPORTER) {
                auto block = std::make_shared<blockchain::TransporterBlock>(conversion::DataConverter::convertToTransporterBlock(data::Config::VERSION, blockchain.getBits(), blockData.height, blockData.nonce, blockData.currentHash, blockData.previousHash, blockData.information, blockData.visible));
                blockchain.addBlock(block);
                redactedBlockchain.addBlock(block);
            } else if (blockData.type == blockchain::enums::BlockType::TRANSACTION) {
                auto block = std::make_shared<blockchain::TransactionBlock>(conversion::DataConverter::convertToTransactionBlock(data::Config::VERSION, blockchain.getBits(), blockData.height, blockData.nonce, blockData.currentHash, blockData.previousHash, blockData.information, blockData.visible));
                blockchain.addBlock(block);
                redactedBlockchain.addBlock(block);
            }

            lastBlockType = blockData.type;
        }
    }

    // Function vector to cycle through, using the Prompt class for data collection
    std::vector<std::function<void()>> functions = {
            [&]{
                auto info = collection::Prompt::collectSupplierInfo(data::Config::OPTIONS_SUPPLIER_FILE_PATH);
                auto block = std::make_shared<blockchain::SupplierBlock>(data::Config::VERSION, blockchain.getBits(), blockchain.getNextBlockHeight(), blockchain.getLastBlockHash(), info);
                blockchain.addBlock(block).addToRecord();
                redactedBlockchain.addBlock(block);
            },
            [&]{
                auto info = collection::Prompt::collectTransporterInfo(data::Config::OPTIONS_TRANSPORTER_FILE_PATH);
                auto block = std::make_shared<blockchain::TransporterBlock>(data::Config::VERSION, blockchain.getBits(), blockchain.getNextBlockHeight(), blockchain.getLastBlockHash(), info);
                blockchain.addBlock(block).addToRecord();
                redactedBlockchain.addBlock(block);
            },
            [&]{
                auto info = collection::Prompt::collectTransactionInfo(data::Config::OPTIONS_TRANSACTION_FILE_PATH, data::Config::RECORDS_BLOCKCHAIN_FILE_PATH);
                auto block = std::make_shared<blockchain::TransactionBlock>(data::Config::VERSION, blockchain.getBits(), blockchain.getNextBlockHeight(), blockchain.getLastBlockHash(), info);
                blockchain.addBlock(block).addToRecord();
                redactedBlockchain.addBlock(block);
            }
    };

    std::cout << "Enter values based on the given options, custom values or 'q'/'quit' to exit the program anytime." << std::endl << std::endl;

    // Read the participants data
    filesystem::FileReader fileReaderParticipant(data::Config::PARTICIPANTS_FILE_PATH, filesystem::DataType::PARTICIPANTS);
    const auto& participants = fileReaderParticipant.getParticipants();

    // Authenticate the user
    authentication::Login login;
    bool isAuthenticated = false;
    std::unique_ptr<authentication::Participant> authenticatedUser;
    std::string username, password;

    while (!isAuthenticated) {
        std::tie(username, password) = collection::Prompt::collectLoginDetails();

        for (const auto& participant : participants) {
            if (login.authenticate(username, password, participant)) {
                isAuthenticated = true;
                authenticatedUser = std::make_unique<authentication::Participant>(participant);
                break; // Exit the for loop
            }
        }

        if (!isAuthenticated) {
            std::cout << "Invalid username or password. Please try again." << std::endl << std::endl;
        } else {
            break; // Exit the while loop since authentication was successful
        }
    }

    // Proceed with the authenticated user.
    std::cout << "Welcome back, " << authenticatedUser->getFullName() << "!" << std::endl << std::endl;

    std::vector<std::string> actionOptions = { "Display blockchain", "Search Block", "Add Block", "Manipulate Block" };
    std::vector<std::string> searchOptions = { "Block Type", "Height", "Version", "Nonce", "Current Hash", "Previous Hash", "Merkle Root", "Timestamp", "Bits", "Information" };

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

    std::string participantIndustryRole = authenticatedUser->getIndustryRole();

    do {
        int action = collection::validation::InputValidator::validateSelectionInt("an action", actionOptions);

        switch (action) {
            case 1:
                if (redactedBlockchain.isEmpty()) {
                    std::cout << "No blocks found in the blockchain." << std::endl << std::endl;
                } else {
                    redactedBlockchain.displayAll();
                }
                break;
            case 2: {
                auto [searchAttr, searchValue] = collection::Prompt::collectSearchCriteria(searchOptions);

                blockchain.display(blockchain.searchBlockByAttr(searchAttr, searchValue));
                break;
            }
            case 3:
                if ((participantIndustryRole == "Supplier" && index == 0) ||
                    (participantIndustryRole == "Transporter" && index == 1) ||
                    (participantIndustryRole == "Accountant" && index == 2)) {

                    // Call the function at the current index
                    functions[index]();
                    // Move to the next type of block or loop back to the start
                    index = (index + 1) % functions.size();
                } else {
                    std::cout << "The current block requires intervention from a different industry role." << std::endl << std::endl;
                }
                break;
            case 4:
                collection::Prompt::collectBlockManipulationCriteria(blockchain, redactedBlockchain, searchOptions);
                break;
        }
    } while (true);
}
