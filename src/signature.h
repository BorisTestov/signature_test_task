#pragma once

#include "arguments.h"
#include "file.h"
#include <boost/uuid/detail/md5.hpp>
#include <future>

using HashType = boost::uuids::detail::md5;

class SignatureCalculator {
public:
    /**
     * @brief Constructor
     * @param arguments - input arguments. @see Arguments
     */
    explicit SignatureCalculator(const std::shared_ptr<Arguments> &arguments);

    /**
     * @brief Calculate hash of input file and write it to output file
     */
    void Calculate();

private:
    /**
     * @brief get hashed buffer data
     * @param buffer - value to hash
     * @return string representation of hashed data
     */
    static std::string GetHashBlock(const char *buffer);

    /**
     * @brief write hash block to file
     * @param hash_block block to write
     */
    void WriteHashBlock(std::string hash_block);

    boost::filesystem::path output_path_;
    std::unique_ptr<File> input_file_;
    std::vector<std::future<std::string>> tasks_pool_;
};
