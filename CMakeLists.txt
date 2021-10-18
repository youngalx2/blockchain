cmake_minimum_required(VERSION 3.17.0)

set (This ChainPeer)

project(${This})

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(OPENSSL_INCLUDE_DIR /usr/local/opt/openssl@1.1/include)
set(OPENSSL_CRYPTO_LIBRARY /usr/local/opt/openssl@1.1/lib)
set(CRYPTO_INCLUDE_DIR /usr/local/opt/openssl@1.1/include)
set(OPENSSL_LIBRARIES /usr/local/opt/openssl@1.1/lib)
set(OPENSSL_USE_STATIC_LIBS TRUE)
set(CMAKE_REQUIRED_LIBRARIES socket crypto openssl)
find_package(OpenSSL REQUIRED)

set(Headers
    "include/Block.h"
    "include/Blockchain.h"
    "include/Color.h"
    "include/PeerReceiver.h"
    "include/PeerSender.h"
    "include/TransactionData.h"
)

set(Sources
    Block.cpp
    Blockchain.cpp
    PeerReceiver.cpp
    PeerSender.cpp
    main.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})