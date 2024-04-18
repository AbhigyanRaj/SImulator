#include <iostream>
#include <sstream>
#include <stdexcept>
#include <regex>
#include <vector>
#include <fstream>

typedef enum { R_TYPE, I_TYPE, S_TYPE, B_TYPE, U_TYPE, J_TYPE } InstructionType;

struct InstructionEncoding {
    InstructionType type;
    std::vector<bool> opcode;
    std::vector<bool> funct3;
    std::vector<bool> funct7;
};

struct RegisterEncoding {
    std::string name;
    std::vector<bool> address;
    int id;
};

std::map<std::string, InstructionEncoding> instruction_map = {
    {"add", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}}},
    {"sub", {R_TYPE, {0, 1, 1, 0, 0, 1, 1}, {0, 0, 0}, {0, 1, 0, 0, 0, 0, 0}}},
    
};

std::map<std::string, RegisterEncoding> register_map = {
    {"zero", {"x0", {0, 0, 0, 0, 0}, 2}},
   
};

std::vector<bool> int_to_signed_bin_array(int value, int n) {
    std::vector<bool> bin_array(n);
    for (int i = 0; i < n; i++) {
        bin_array[i] = (value & (1 << (n - 1 - i))) ? 1 : 0;
    }
    return bin_array;
}

std::vector<bool> slice_bool_array(const std::vector<bool> &bool_array, int start_index, int end_index) {
    std::vector<bool> sliced_array;
    for (int i = start_index; i <= end_index; ++i) {
        sliced_array.push_back(bool_array[i]);
    }
    return sliced_array;
}

std::vector<std::string> tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ' ')) {
        token.erase(0, token.find_first_not_of(" \t\r\n"));
        token.erase(token.find_last_not_of(" \t\r\n") + 1);
    }
    return tokens;
}
    while (std::getline(file, line)) {
        std::vector<std::string> tokens = tokenize(line);
        std::vector<bool> decoded = decode(tokens);
        for (int i = 0; i < 32; ++i) {
            std::cout << decoded[i];
        }
        std::cout << std::endl;
    }
    file.close();
}

int main() {
    read_file("src/instruction/text.txt");
    return 0;
}
