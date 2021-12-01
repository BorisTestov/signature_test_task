#pragma once

#include <string>
#include "fileiterator.h"

/**
 * @brief Class for iterating over a file with blocks of data
 */
class File {
public:
    /**
     * @brief Constructor
     * @param file_path - path to file for reading
     * @param block_size - size of one block of data in bytes
     */
    File(std::string file_path, unsigned long long block_size);

    /**
     * @brief Copy constructor
     * @param other_file From where to copy
     */
    File(const File &other_file);

    /**
     * @brief Copy assignment
     * @param other_file From where to copy
     * @return Result of copy
     */
    File &operator=(const File &other_file);

    /**
     * @brief Get iterator pointed to first block of data in file
     * @return iterator pointed to first block of data in file
     */
    FileIterator begin();

    /**
     * @brief Get iterator pointed to end of data
     * @return iterator pointed to end of data
     */
    FileIterator end();

private:
    unsigned long long int block_size_;
    std::string file_path_;
};