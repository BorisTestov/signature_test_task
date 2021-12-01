#include <gtest/gtest.h>
#include <fstream>
#include "../src/fileiterator.h"
#include "../src/file.h"
#include "common.h"

TEST(CreateFileIterator, ExistedFile) {
    CreateTestFile();
    EXPECT_NO_THROW(
            {
                FileIterator iterator("test_file", 10);
                FileIterator iterator_block("test_file", 5, 1);
            });
    RemoveTestFile();
}

TEST(CreateFileIterator, NonExistedFile) {
    EXPECT_THROW({
                     try {
                         FileIterator iterator("test_fail", 10);
                     }
                     catch (const std::runtime_error &e) {
                         EXPECT_STREQ("Can't read file for creating 'FileIterator' class: test_fail", e.what());
                         throw;
                     }
                 }, std::runtime_error);
}

TEST(Iterate, SampleFile) {
    CreateTestFile();
    File test_file("test_file", 1);
    size_t iteration_counter = 1;
    for (FileIterator i = test_file.begin(); i != test_file.end(); ++i) {
        ASSERT_EQ(*i, std::to_string(iteration_counter % 10));
        ++iteration_counter;
    }
    RemoveTestFile();
}