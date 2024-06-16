#include "easygl.hpp"

#include <sstream>
#include <fstream>

std::optional<std::string> loadTextFile(const std::string& filename) {

    std::ifstream fin(filename);
    if(!fin.is_open()){
        std::cerr << "Failed to load file " << filename << std::endl;
        return {};
    }

    std::stringstream ss;
    ss << fin.rdbuf();
    return ss.str();
}