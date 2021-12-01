#include <gtest/gtest.h>
#include <boost/uuid/detail/md5.hpp>
#include "../src/common.h"
#include "common.h"

TEST(GetFileSize, ExsistedFile) {
    CreateTestFile();
    ASSERT_EQ(GetFilesize("test_file"), 10);
    RemoveTestFile();
}

TEST(GetFileSize, NonExsistedFile) {
    EXPECT_THROW({
                     try {
                         GetFilesize("test_fail");
                     }
                     catch (const std::runtime_error &e) {
                         EXPECT_STREQ("Can't read file for getting size: test_fail", e.what());
                         throw;
                     }
                 }, std::runtime_error);
}


TEST(GetTotalBlocks, ExistedFile) {
    CreateTestFile();
    for (size_t block_size = 1; block_size < 20; ++block_size) {
        ASSERT_EQ(GetTotalBlocks("test_file", block_size),
                  (GetFilesize("test_file") + block_size - 1) / block_size);
    }
    RemoveTestFile();
}

TEST(GetTotalBlocks, NonExistedFile) {
    EXPECT_THROW({
                     try {
                         GetTotalBlocks("test_fail", 1);
                     }
                     catch (const std::runtime_error &e) {
                         EXPECT_STREQ("Can't read file for getting total amount of blocks: test_fail", e.what());
                         throw;
                     }
                 }, std::runtime_error);
}

TEST(HashToString, Naive) {
    char buffer[] = "1234567890";
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;
    hash.process_bytes(buffer, strlen(buffer));
    hash.get_digest(digest);
    ASSERT_EQ(HashToString(digest), "FCF107E82F132DF8CA18B09B9FA13867");
}