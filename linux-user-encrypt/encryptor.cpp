#include "encryptor.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <fstream>
#include <vector>

void aes256_cbc_encrypt(const std::string &file, const std::vector<unsigned char> &key, const std::vector<unsigned char> &iv) {
    // Read file
    std::ifstream in_file(file, std::ios::binary);
    std::vector<unsigned char> input_data((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
    in_file.close();

    
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key.data(), iv.data());

    std::vector<unsigned char> ciphertext(input_data.size() + EVP_MAX_BLOCK_LENGTH);
    int len = 0, ciphertext_len = 0;

    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, input_data.data(), input_data.size());
    ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    // Write to file
    std::ofstream out_file(file, std::ios::binary);
    out_file.write(reinterpret_cast<const char*>(ciphertext.data()), ciphertext_len);
    out_file.close();
}

void aes192_ecb_encrypt(const std::string &file, const std::vector<unsigned char> &key) {
    std::ifstream in_file(file, std::ios::binary);
    std::vector<unsigned char> input_data((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
    in_file.close();

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_192_ecb(), nullptr, key.data(), nullptr);

    std::vector<unsigned char> ciphertext(input_data.size() + EVP_MAX_BLOCK_LENGTH);
    int len = 0, ciphertext_len = 0;

    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, input_data.data(), input_data.size());
    ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    std::ofstream out_file(file, std::ios::binary);
    out_file.write(reinterpret_cast<const char*>(ciphertext.data()), ciphertext_len);
    out_file.close();
}
