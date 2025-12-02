#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <cryptopp/modes.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file> <key_hex>" << std::endl;
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];
    std::string key_hex = argv[3];

    // 鍵のチェック（16, 24, 32バイトのみ）
    size_t key_length = key_hex.length() / 2;
    if (key_length != CryptoPP::AES::DEFAULT_KEYLENGTH &&
        key_length != CryptoPP::AES::MAX_KEYLENGTH &&
        key_length != CryptoPP::AES::MIN_KEYLENGTH) {
        std::cerr << "Key must be 16, 24, or 32 bytes (32, 48, or 64 hex)" << std::endl;
        return 1;
    }

    // 16バイトのIV
    byte iv[CryptoPP::AES::BLOCKSIZE] = {0};

    // HEX → バイト配列変換
    CryptoPP::SecByteBlock key(key_length);
    CryptoPP::StringSource ss(key_hex, true,
        new CryptoPP::HexDecoder(
            new CryptoPP::ArraySink(key, key.size())
        )
    );

    try {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption enc;
        enc.SetKeyWithIV(key, key.size(), iv);

        CryptoPP::FileSource fs(input_file.c_str(), true,
            new CryptoPP::StreamTransformationFilter(enc,
                new CryptoPP::FileSink(output_file.c_str())
            )
        );

        std::cout << "Encryption successful!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}