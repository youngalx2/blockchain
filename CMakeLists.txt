cmake_minimum_required(VERSION 3.17.0)

set (This ChainPeer)

project(${This})

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(OPENSSL_ROOT_DIR /usr/local/opt/openssl@1.1)
set(OPENSSL_USE_STATIC_LIBS TRUE)
set(CMAKE_REQUIRED_LIBRARIES socket crypto openssl)
find_package(OpenSSL REQUIRED)

set(Headers
    "include/Block.h"
    "include/Blockchain.h"
    "include/BlockchainCommand.h"
    "include/BlockchainNetwork.h"
    "include/Color.h"
    "include/Command.h"
    "include/GetFilesListCommand.h"
    "include/commands/CreateTransactionCommand.h"
    "include/commands/GetBlockchainCommand.h"
    "include/commands/ListFilesCommand.h"
    "include/commands/PrintBlockchainCommand.h"
    "include/commands/ReadFileCommand.h"
    "include/commands/ReceiveFileCommand.h"
    "include/commands/ReplaceBlockchainCommand.h"
    "include/domain/Peer.h"
    "include/PeerReceiver.h"
    "include/PeerSender.h"
    "include/StringHelper.h"
    "include/TransactionData.h"
)

set(Sources
    Block.cpp
    Blockchain.cpp
    BlockchainCommand.cpp
    BlockchainNetwork.cpp
    "Command.cpp"
    CreateTransactionCommand.cpp
    GetBlockchainCommand.cpp
    GetFilesListCommand.cpp
    ListFilesCommand.cpp
    PeerReceiver.cpp
    PeerSender.cpp
    PrintBlockchainCommand.cpp
    ReadFileCommand.cpp
    ReceiveFileCommand.cpp
    ReplaceBlockchainCommand.cpp
    StringHelper.cpp
    main.cpp
)

add_executable(${This} MACOSX_BUNDLE ${Sources})
target_link_libraries(${This} OpenSSL::SSL)
