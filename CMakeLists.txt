cmake_minimum_required(VERSION 3.26)
project(inventory_transportation_management_system)

set(CMAKE_CXX_STANDARD 17)

add_executable(inventory_transportation_management_system src/main.cpp
        src/blockchain/Block.cpp
        src/blockchain/Block.h
        src/blockchain/Chain.cpp
        src/blockchain/Chain.h
        src/blockchain/SupplierBlock.cpp
        src/blockchain/SupplierBlock.h
        src/blockchain/TransactionBlock.cpp
        src/blockchain/TransactionBlock.h
        src/blockchain/TransporterBlock.cpp
        src/blockchain/TransporterBlock.h
        src/collection/InputCollector.cpp
        src/collection/InputCollector.h
        src/filesystem/FileReader.cpp
        src/filesystem/FileReader.h
        src/filesystem/FileWriter.cpp
        src/filesystem/FileWriter.h
        src/collection/validator/InputValidator.cpp
        src/collection/validator/InputValidator.h
        src/collection/conversion/DataConverter.h
        src/collection/conversion/DataConverter.cpp
        src/utils/Structures.h
        src/utils/Structures.cpp
        src/blockchain/BlockHeader.cpp
        libs/sha256/sha256.cpp
        libs/sha256/sha256.h
        src/utils/Datetime.cpp
        src/blockchain/enums/BlockType.cpp
        src/blockchain/enums/BlockType.h
        src/utils/Math.h
        src/utils/Math.cpp)
