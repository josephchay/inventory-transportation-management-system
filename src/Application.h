#ifndef APPLICATION_H
#define APPLICATION_H

#include "blockchain/Chain.h"
#include "authentication/Participant.h"
#include "filesystem/FileReader.h"

/**
 * @brief The Application class manages the initialization and execution of the application.
 */
class Application {
public:
    /**
     * @brief Initializes the application.
     */
    static void init();

    /**
     * @brief Runs the application.
     */
    static void run();

    /**
     * @brief Sets the blockchain instance.
     * @param blockchain Pointer to the blockchain.
     */
    static void setBlockchain(blockchain::Chain* blockchain);

    /**
     * @brief Sets the redacted blockchain instance.
     * @param redactedBlockchain Pointer to the redacted blockchain.
     */
    static void setRedactedBlockchain(blockchain::Chain* redactedBlockchain);

    /**
     * @brief Sets the list of participants.
     * @param participants List of participants.
     */
    static void setParticipants(const std::vector<authentication::Participant>& participants);

    /**
     * @brief Sets the current participant.
     * @param user Pointer to the current participant.
     */
    static void setCurrentParticipant(std::unique_ptr<authentication::Participant> user);

    /**
     * @brief Sets the list of blocks.
     * @param blocks List of block data.
     */
    static void setBlocks(const std::vector<filesystem::BlockData>& blocks);

    /**
     * @brief Sets the type of the last block.
     * @param type Type of the last block.
     */
    static void setLastBlockType(blockchain::enums::BlockType type);

    /**
     * @brief Gets the blockchain instance.
     */
    static blockchain::Chain* getBlockchain();

    /**
     * @brief Gets the redacted blockchain instance.
     */
    static blockchain::Chain* getRedactedBlockchain();

    /**
     * @brief Gets the list of participants.
     */
    static std::vector<authentication::Participant>& getParticipants();

    /**
     * @brief Gets the current participant.
     */
    static authentication::Participant* getCurrentParticipant();

    /**
     * @brief Gets the list of blocks.
     */
    static std::vector<filesystem::BlockData>& getBlocks();

    /**
     * @brief Gets the type of the last block.
     */
    static blockchain::enums::BlockType getLastBlockType();

private:
    static blockchain::Chain* blockchain; /**< Pointer to the blockchain instance. */
    static blockchain::Chain* redactedBlockchain; /**< Pointer to the redacted blockchain instance. */
    static std::vector<authentication::Participant> participants; /**< List of participants. */
    static std::unique_ptr<authentication::Participant> currentParticipant; /**< Pointer to the current participant. */
    static std::vector<filesystem::BlockData> blocks; /**< List of block data. */
    static blockchain::enums::BlockType lastBlockType; /**< Type of the last block. */

    /**
     * @brief Initializes the blockchain.
     */
    static void initializeBlockchain();

    /**
     * @brief Authenticates the user.
     */
    static void authenticateUser();

    /**
     * @brief Displays the application menu.
     */
    static void displayMenu();

    /**
     * @brief Initializes dependencies required by the application.
     */
    static void initDependencies();
};

#endif // APPLICATION_H
