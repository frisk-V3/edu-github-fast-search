cmake_minimum_required(VERSION 3.10)
project(edu-github-fast-search)

set(CMAKE_CXX_STANDARD 17)

# OpenSSLが必要
find_package(OpenSSL REQUIRED)

include_directories(include)

add_executable(edu-github-fast-search src/main.cpp)

target_link_libraries(edu-github-fast-search OpenSSL::SSL OpenSSL::Crypto)

# Windows環境でのソケットライブラリのリンク
if(WIN32)
    target_link_libraries(edu-github-fast-search ws2_32 crypt32)
endif()
