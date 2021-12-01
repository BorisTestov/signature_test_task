#include "common.h"
#include <fstream>

void CreateTestFile() {
    std::ofstream test_file("test_file");
    test_file << "1234567890";
    test_file.close();
}

void RemoveTestFile() {
    remove("test_file");
}