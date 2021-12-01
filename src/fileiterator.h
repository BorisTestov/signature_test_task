#pragma once

#include <fstream>

class FileIterator {
public:
    /**
     * @brief Iterator over file content with blocks of data
     * @details Possible operations:
     * - Preincrement
     * - Not equal compare with other FileIterator
     * - Dereference
     * @param file_path - path of input file
     * @param block_size - size of one block in bytes
     * @param start_block - block number from where to start
     */
    FileIterator(const std::string &file_path,
                 unsigned long long int block_size,
                 unsigned long long int start_block = 0);

    ~FileIterator();

    const std::string &operator*() const;

    FileIterator &operator++();

    friend bool operator!=(const FileIterator &a, const FileIterator &b);

private:
    /**
     * @brief get next part of data from file
     */
    void next();

    unsigned long long int file_size_;
    std::ifstream file_handle_;
    unsigned long long int block_size_;
    unsigned long long int total_blocks_;
    unsigned long long int current_block_;
    std::string data_;
};