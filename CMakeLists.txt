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
        libs/sha384/sha384.h
        libs/sha384/sha384.cpp
        src/blockchain/enums/HashAlgorithm.h
        libs/sha512/sha512.h
        libs/sha512/sha512.cpp
        src/blockchain/enums/BlockAttribute.h
        src/blockchain/enums/BlockAttribute.cpp
        data/Config.h
        data/Config.cpp
        src/authentication/Participant.cpp
        src/authentication/Participant.h
        src/authentication/Login.cpp
        src/authentication/Login.h
        src/Application.cpp
        src/Application.h)
