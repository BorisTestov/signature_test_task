#include <gtest/gtest.h>
#include <fstream>
#include "../src/file.h"
#include "common.h"


TEST(CreateFileInstance, ExistedFile) {
    CreateTestFile();
    EXPECT_NO_THROW(
            {
                File test_file("test_file", 10);
            }
    );
    RemoveTestFile();
}

TEST(CreateFileInstance, NonExistedFile) {
    EXPECT_THROW({
                     try {
                         File test_file("test_fail", 10);
                     }
                     catch (const std::runtime_error &e) {
                         EXPECT_STREQ("Can't read file for creating 'File' class: test_fail", e.what());
                         throw;
                     }
                 }, std::runtime_error);
}