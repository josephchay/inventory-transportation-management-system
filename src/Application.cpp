#include "Application.h"
#include "blockchain/Chain.h"
#include "filesystem/FileReader.h"
#include "../data/Config.h"
#include "authentication/Login.h"
#include "collection/InputCollector.h"
#include "collection/conversion/DataConverter.h"
#include "collection/validator/InputValidator.h"
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

// Static member variable initialization
blockchain::Chain* Application::blockchain = nullptr;
blockchain::Chain* Application::redactedBlockchain = nullptr;
std::vector<authentication::Participant> Application::participants;
std::unique_ptr<authentication::Participant> Application::currentParticipant = nullptr;
std::vector<filesystem::BlockData> Application::blocks;
blockchain::enums::BlockType Application::lastBlockType;

void Application::init() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation
    initDependencies();

    initializeBlockchain();
}

void Application::initDependencies() {
    /**
     * @brief The chain of blocks where all blocks are from the real data blockchain record.
     */
    setBlockchain(new blockchain::Chain(data::Config::RECORDS_BLOCKCHAIN_FILE_PATH, data::Config::VERSION));

    /**
     * @brief The chain of blocks where some blocks are hidden (redacted) from the display view output to the currentParticipant.
     * aka. The temporary storage of the blockchain data.
     */
    setRedactedBlockchain(new blockchain::Chain(data::Config::RECORDS_BLOCKCHAIN_FILE_PATH, data::Config::VERSION));

    /**
     * @brief The list of blocks in the blockchain network.
     */
    filesystem::FileReader fileReaderChain(data::Config::RECORDS_BLOCKCHAIN_FILE_PATH, filesystem::DataType::CHAIN);
    const auto& blocks = fileReaderChain.getBlocks();
    setBlocks(blocks);

    /**
     * @brief The list of participants in the blockchain network.
     */
    filesystem::FileReader fileReaderParticipant(data::Config::PARTICIPANTS_FILE_PATH, filesystem::DataType::PARTICIPANTS);
    const auto& participants = fileReaderParticipant.getParticipants();
    setParticipants(participants);
}

void Application::initializeBlockchain() {
    // Set the last block type to TRANSACTION as default
    setLastBlockType(blockchain::enums::BlockType::TRANSACTION); // Default to Transaction if no blocks were added

    // Check if there are any blocks stored
    if (!blocks.empty()) {
        // Iterate over each BlockData and add the corresponding block to the blockchain
        for (const auto& blockData : blocks) {
            if (blockData.type == blockchain::enums::BlockType::SUPPLIER) {
                // Create a SupplierBlock from BlockData and add it to the blockchain
                auto block = std::make_shared<blockchain::SupplierBlock>(conversion::DataConverter::convertToSupplierBlock(data::Config::VERSION, blockchain->getBits(), blockData.height, blockData.nonce, blockData.currentHash, blockData.previousHash, blockData.information, blockData.visible));
                blockchain->addBlock(block);
                redactedBlockchain->addBlock(block);
            } else if (blockData.type == blockchain::enums::BlockType::TRANSPORTER) {
                // Create a TransporterBlock from BlockData and add it to the blockchain
                auto block = std::make_shared<blockchain::TransporterBlock>(conversion::DataConverter::convertToTransporterBlock(data::Config::VERSION, blockchain->getBits(), blockData.height, blockData.nonce, blockData.currentHash, blockData.previousHash, blockData.information, blockData.visible));
                blockchain->addBlock(block);
                redactedBlockchain->addBlock(block);
            } else if (blockData.type == blockchain::enums::BlockType::TRANSACTION) {
                // Create a TransactionBlock from BlockData and add it to the blockchain
                auto block = std::make_shared<blockchain::TransactionBlock>(conversion::DataConverter::convertToTransactionBlock(data::Config::VERSION, blockchain->getBits(), blockData.height, blockData.nonce, blockData.currentHash, blockData.previousHash, blockData.information, blockData.visible));
                blockchain->addBlock(block);
                redactedBlockchain->addBlock(block);
            }

            setLastBlockType(blockData.type);
        }
    }
}

void Application::authenticateUser() {
    // Authenticate the currentParticipant
    authentication::Login login;
    bool isAuthenticated = false;
    std::string username, password;

    while (!isAuthenticated) {
        std::tie(username, password) = collection::InputCollector::collectLoginDetails();

        for (const auto &participant: participants) {
            if (login.authenticate(username, password, participant)) {
                isAuthenticated = true;
                setCurrentParticipant(std::make_unique<authentication::Participant>(participant));
                break; // Exit the for loop
            }
        }

        if (!isAuthenticated) {
            std::cout << "Invalid username or password. Please try again." << std::endl << std::endl;
        } else {
            break; // Exit the while loop since authentication was successful
        }
    }

    // Proceed with the authenticated currentParticipant.
    std::cout << "Welcome back, " << currentParticipant->getFullName() << "!" << std::endl << std::endl;
}

void Application::displayMenu() {
    // Function vector to cycle through, using the InputCollector class for data collection
    std::vector<std::function<void()>> functions = {
            [&]{
                // Collect information for Supplier block
                auto info = collection::InputCollector::collectSupplierInfo(data::Config::OPTIONS_SUPPLIER_FILE_PATH);
                // Create a SupplierBlock and add it to the blockchain
                auto block = std::make_shared<blockchain::SupplierBlock>(data::Config::VERSION, blockchain->getBits(), blockchain->getNextBlockHeight(), blockchain->getLastBlockHash(), info);
                blockchain->addBlock(block).addToRecord();
                redactedBlockchain->addBlock(block);
            },
            [&]{
                // Collect information for Transporter block
                auto info = collection::InputCollector::collectTransporterInfo(data::Config::OPTIONS_TRANSPORTER_FILE_PATH);
                // Create a TransporterBlock and add it to the blockchain
                auto block = std::make_shared<blockchain::TransporterBlock>(data::Config::VERSION, blockchain->getBits(), blockchain->getNextBlockHeight(), blockchain->getLastBlockHash(), info);
                blockchain->addBlock(block).addToRecord();
                redactedBlockchain->addBlock(block);
            },
            [&]{
                // Collect information for Transaction block
                auto info = collection::InputCollector::collectTransactionInfo(data::Config::OPTIONS_TRANSACTION_FILE_PATH, data::Config::RECORDS_BLOCKCHAIN_FILE_PATH);
                // Create a TransactionBlock and add it to the blockchain
                auto block = std::make_shared<blockchain::TransactionBlock>(data::Config::VERSION, blockchain->getBits(), blockchain->getNextBlockHeight(), blockchain->getLastBlockHash(), info);
                blockchain->addBlock(block).addToRecord();
                redactedBlockchain->addBlock(block);
            }
    };

    // Define options for user actions and block search criteria
    std::vector<std::string> actionOptions = { "Display blockchain", "Search Block", "Add Block", "Manipulate Block" };
    std::vector<std::string> searchOptions = { "Block Type", "Height", "Version", "Nonce", "Current Hash", "Previous Hash", "Merkle Root", "Timestamp", "Bits", "Information" };

    // Determine the index for selecting the next type of block to add
    int index; // Default to Supplier if no blocks were added or if the last block was Transaction
    switch (getLastBlockType()) {
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

    // Get the industry role of the current participant
    auto participantIndustryRole = currentParticipant->getIndustryRole();

    // Loop for user interaction
    do {
        // InputCollector user for action
        int action = collection::validation::InputValidator::validateSelectionInt("an action", actionOptions);

        switch (action) {
            case 1:
                // Display blockchain
                if (redactedBlockchain->isEmpty()) {
                    std::cout << "No blocks found in the blockchain." << std::endl << std::endl;
                } else {
                    redactedBlockchain->displayAll();
                }
                break;
            case 2: {
                // Search block
                auto [searchAttr, searchValue] = collection::InputCollector::collectSearchCriteria(searchOptions);

                blockchain->display(blockchain->searchBlockByAttr(searchAttr, searchValue));
                break;
            }
            case 3:
                // Add block
                if ((participantIndustryRole == "Supplier" && index == 0) ||
                    (participantIndustryRole == "Transporter" && index == 1) ||
                    (participantIndustryRole == "Accountant" && index == 2) ||
                    (participantIndustryRole == "Administrator")) {

                    // Call the function at the current index
                    functions[index]();
                    // Move to the next type of block or loop back to the start
                    index = (index + 1) % functions.size();
                } else {
                    std::cout << "The current block requires intervention from a different industry role." << std::endl << std::endl;
                }
                break;
            case 4:
                // Manipulate block
                collection::InputCollector::collectBlockManipulationCriteria(*blockchain, *redactedBlockchain, searchOptions);
                break;
        }
    } while (true);
}

void Application::run() {
    std::cout << "Enter values based on the given options, custom values or 'q'/'quit' to exit the program anytime." << std::endl << std::endl;

    // Enable user interaction with the application
    authenticateUser();
    displayMenu();
}

// getters
blockchain::Chain* Application::getBlockchain() { return blockchain; }
blockchain::Chain* Application::getRedactedBlockchain() { return redactedBlockchain; }
std::vector<authentication::Participant>& Application::getParticipants() { return participants; }
authentication::Participant* Application::getCurrentParticipant() { return currentParticipant.get(); }
std::vector<filesystem::BlockData>& Application::getBlocks() { return blocks; }
blockchain::enums::BlockType Application::getLastBlockType() { return lastBlockType; }

// setters
void Application::setBlockchain(blockchain::Chain* chain) { blockchain = chain; }
void Application::setRedactedBlockchain(blockchain::Chain* chain) { redactedBlockchain = chain; }
void Application::setParticipants(const std::vector<authentication::Participant>& participants) { Application::participants = participants; }
void Application::setCurrentParticipant(std::unique_ptr<authentication::Participant> user) { currentParticipant = std::move(user); }
void Application::setBlocks(const std::vector<filesystem::BlockData>& blocks) { Application::blocks = blocks; }
void Application::setLastBlockType(blockchain::enums::BlockType type) { lastBlockType = type; }
