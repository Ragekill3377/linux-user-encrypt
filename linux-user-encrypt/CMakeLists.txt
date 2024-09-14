cmake_minimum_required(VERSION 3.10)

# Project Name
project(Encryptor)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Include OpenSSL
find_package(OpenSSL REQUIRED)

# Add executable
add_executable(encryptor main.cpp encryptor.cpp utils.cpp)

# Link OpenSSL libraries
target_link_libraries(encryptor OpenSSL::SSL OpenSSL::Crypto)