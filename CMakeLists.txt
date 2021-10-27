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
    src/Block.cpp
    src/Blockchain.cpp
    src/BlockchainCommand.cpp
    src/BlockchainNetwork.cpp
    "src/Command.cpp"
    src/CreateTransactionCommand.cpp
    src/GetBlockchainCommand.cpp
    src/GetFilesListCommand.cpp
    src/ListFilesCommand.cpp
    src/PeerReceiver.cpp
    src/PeerSender.cpp
    src/PrintBlockchainCommand.cpp
    src/ReadFileCommand.cpp
    src/ReceiveFileCommand.cpp
    src/ReplaceBlockchainCommand.cpp
    src/StringHelper.cpp
    src/main.cpp
)

add_executable(${This} ${Sources})
add_custom_command(TARGET ${This} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shared ${CMAKE_BINARY_DIR}/shared)
target_link_libraries(${This} OpenSSL::SSL)
