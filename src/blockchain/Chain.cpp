#include "Chain.h"
#include "../filesystem/FileWriter.h"
#include "enums/BlockAttribute.h"
#include <iostream>

namespace blockchain {
    Chain::Chain(const std::string dataFilePath, const int version, const std::string& bits) : dataFilePath(dataFilePath), version(version), bits(bits) {}

    Chain& Chain::addBlock(std::shared_ptr<Block> block) {
        // Set the genesis flag for the block
        block->setGenesis(block->getHeight() == 0);
        blocks.push_back(std::move(block));

        return *this;
    }

    Chain& Chain::hideBlock(std::shared_ptr<Block> block) {
        // The lambda captures block by value since it's a shared_ptr
        auto it = std::remove_if(blocks.begin(), blocks.end(),
                                 [block](const std::shared_ptr<Block>& itBlock) {
                                     return itBlock == block;
                                 });

        blocks.erase(it, blocks.end()); // Erase the specified block

        return *this;
    }

    Chain& Chain::removeBlock(std::shared_ptr<Block> blockToHide) {
        // The lambda captures blockToHide by value since it's a shared_ptr
        auto it = std::find(blocks.begin(), blocks.end(), blockToHide);

        if (it != blocks.end()) {
            (*it)->setVisible(false);
        }

        filesystem::FileWriter::clearFile(dataFilePath); // Clear the file before writing the updated data
        for (const auto& block : blocks) {
            logBlockDetails(*block, dataFilePath);
        }

        return *this;
    }

    bool Chain::isEmpty() const {
        return blocks.empty();
    }

    void Chain::displayAll() const {
        if (hasVisibleBlocks(blocks)) {
            std::cout << std::endl << "------------------------------------ BLOCKCHAIN ------------------------------------" << std::endl << std::endl;
            for (const auto& block : blocks) {
                if (block->isVisible()) {
                    displayBlockDetails(block);
                }
            }
            std::cout << "------------------------------------------------------------------------------------" << std::endl << std::endl;
        } else {
            std::cout << "No blocks found in the blockchain." << std::endl << std::endl;
        }
    }

    void Chain::display(const std::vector<std::shared_ptr<Block>>& selectedBlocks) const {
        if (!selectedBlocks.empty() && hasVisibleBlocks(selectedBlocks)) {
            std::cout << "------------------------------------ SELECTED BLOCKS ------------------------------------" << std::endl << std::endl;

            for (const auto& block : selectedBlocks) {
                if (block->isVisible()) {
                    displayBlockDetails(block);
                }
            }

            std::cout << "------------------------------------------------------------------------------------" << std::endl << std::endl;
        } else {
            std::cout << "No blocks found matching the criteria." << std::endl << std::endl;
        }
    }

    bool Chain::hasVisibleBlocks(const std::vector<std::shared_ptr<Block>>& blocks) const {
        return std::any_of(blocks.begin(), blocks.end(), [](const std::shared_ptr<Block>& block) {
            return block->isVisible();
        });
    }

    std::vector<std::shared_ptr<Block>> Chain::searchBlockByAttr(blockchain::enums::BlockAttribute attribute, const std::string& value) const {
        std::vector<std::shared_ptr<Block>> foundBlocks; // Store shared pointers to the found blocks

        for (const auto& block : blocks) {
            bool found = false;
            std::string attrValue;

            switch (attribute) {
                case blockchain::enums::BlockAttribute::TYPE:
                    attrValue = blockchain::enums::BlockTypeUtils::toString(block->getType());
                    found = attrValue == value;
                    break;
                case blockchain::enums::BlockAttribute::HEIGHT:
                    attrValue = std::to_string(block->getHeight());
                    found = attrValue == value;
                    break;
                case blockchain::enums::BlockAttribute::VERSION:
                    attrValue = std::to_string(version);
                    found = attrValue == value;
                    break;
                case blockchain::enums::BlockAttribute::NONCE:
                    attrValue = std::to_string(block->getNonce());
                    found = attrValue == value;
                    break;
                case blockchain::enums::BlockAttribute::HASH:
                    attrValue = block->getHash();
                    found = attrValue == value;
                    break;
                case blockchain::enums::BlockAttribute::PREV_HASH:
                    attrValue = block->getPrevHash();
                    found = attrValue == value;
                    break;
                case blockchain::enums::BlockAttribute::MERKLE_ROOT:
                    attrValue = block->getMerkleRoot();
                    found = attrValue == value;
                    break;
                case blockchain::enums::BlockAttribute::TIMESTAMP:
                    attrValue = std::to_string(block->getTimestamp());
                    found = attrValue == value;

                    if (!found) {
                        attrValue = block->getFormattedTimestamp();
                        found = (attrValue == value);
                    }
                    break;
                case blockchain::enums::BlockAttribute::BITS:
                    attrValue = bits;
                    found = attrValue == value;
                    break;
                case blockchain::enums::BlockAttribute::INFORMATION:
                    attrValue = block->getInformationString();
                    found = attrValue == value;
                    break;
                case enums::BlockAttribute::VISIBLE:
                    // Visibility not needed to be shown to the users
                    break;
            }

            if (found) {
                foundBlocks.push_back(block); // Directly use the shared_ptr from the blocks vector
            }
        }

        return foundBlocks;
    }

    void Chain::displayBlockDetails(const std::shared_ptr<Block> &block) const {
        std::cout << enums::BlockAttributeUtils::toString(enums::BlockAttribute::TYPE) << " --> " << enums::BlockTypeUtils ::toString(block->getType()) << std::endl
                  << enums::BlockAttributeUtils::toString(enums::BlockAttribute::HEIGHT) << " --> " << block->getHeight() << (block->isGenesis() ? " (Genesis Block)" : "") << std::endl
                  << enums::BlockAttributeUtils::toString(enums::BlockAttribute::VERSION) << " --> " << version << std::endl
                  << enums::BlockAttributeUtils::toString(enums::BlockAttribute::NONCE) << " --> " << block->getNonce() << std::endl
                  << enums::BlockAttributeUtils::toString(enums::BlockAttribute::HASH) << " --> " << block->getHash() << std::endl
                  << enums::BlockAttributeUtils::toString(enums::BlockAttribute::PREV_HASH) << " --> " << block->getPrevHash() << std::endl
                  << enums::BlockAttributeUtils::toString(enums::BlockAttribute::MERKLE_ROOT) << " --> " << block->getMerkleRoot() << std::endl
                  << enums::BlockAttributeUtils::toString(enums::BlockAttribute::TIMESTAMP) << " --> " << block->getTimestamp() << " (" + block->getFormattedTimestamp() + ")" << std::endl
                  << enums::BlockAttributeUtils::toString(enums::BlockAttribute::BITS) << " --> " << bits << std::endl
                  << enums::BlockAttributeUtils::toString(enums::BlockAttribute::INFORMATION) << " --> " << "[ " << block->getInformationString() << " ]" << std::endl << std::endl;
    }

    /**
     * @brief Get the height of the next block in the chain.
     *
     * @return int The height of the next block in the chain.
     */
    int Chain::getNextBlockHeight() const {
        return static_cast<int>(blocks.size());
    }

    /**
     * @brief Get the hash of the last block in the chain.
     *
     * @return std::string The hash of the last block in the chain.
     */
    std::string Chain::getLastBlockHash() const {
        if (!blocks.empty()) {
            return blocks.back()->getHash();
        }
        return "0"; // Return a default hash for the genesis block
    }

    /**
     * @brief Log the details of a block to a file.
     *
     * @param block The block to log.
     * @param filename The name of the file to write (log) to.
     */
    void Chain::logBlockDetails(const Block& block, const std::string& filename) {
        using namespace blockchain::enums; // Use the entire namespace

        filesystem::FileWriter writer(filename);

        writer.writeLine(BlockAttributeUtils::toString(BlockAttribute::TYPE) + ": " + blockchain::enums::BlockTypeUtils::toString(block.getType()));
        writer.writeLine(BlockAttributeUtils::toString(BlockAttribute::HEIGHT) + ": " + std::to_string(block.getHeight()));
        writer.writeLine(BlockAttributeUtils::toString(BlockAttribute::VERSION) + ": " + std::to_string(version));
        writer.writeLine(BlockAttributeUtils::toString(BlockAttribute::NONCE) + ": " + std::to_string(block.getNonce()));
        writer.writeLine(BlockAttributeUtils::toString(BlockAttribute::HASH) + ": " + block.getHash());
        writer.writeLine(BlockAttributeUtils::toString(BlockAttribute::PREV_HASH) + ": " + block.getPrevHash());
        writer.writeLine(BlockAttributeUtils::toString(BlockAttribute::MERKLE_ROOT) + ": " + block.getMerkleRoot());
        writer.writeLine(BlockAttributeUtils::toString(BlockAttribute::TIMESTAMP) + ": " + std::to_string(block.getTimestamp()));
        writer.writeLine(BlockAttributeUtils::toString(BlockAttribute::BITS) + ": " + bits);
        writer.writeLine(BlockAttributeUtils::toString(BlockAttribute::INFORMATION) + ": " + block.getInformationString());
        writer.writeLine(BlockAttributeUtils::toString(BlockAttribute::VISIBLE) + ": " + (block.isVisible() ? "true" : "false"));
        writer.writeLine(""); // Add an empty line for readability
    }

    void Chain::addToRecord() {
        if (!blocks.empty()) {
            const auto& block = blocks.back();
            logBlockDetails(*block, dataFilePath);
        }
    }
}
