#pragma once

#include <fstream>
#include <boost/uuid/detail/md5.hpp>

/**
 * @brief Get file size in bytes
 * @param filename - path to file
 * @return file size in bytes
 */
unsigned long long GetFilesize(const std::string &filename);


/**
 * @brief Get total amount of blocks in file
 * @param file - path to file
 * @param blocksize - size of one block in bytes
 * @return total amount of blocks in file
 */
unsigned long long int GetTotalBlocks(const std::string &filename, unsigned long long int blocksize);

/**
 * @brief convert hash digest to string
 * @param digest - hash digest
 * @return representation of hash digest as std::string
 */
std::string HashToString(const boost::uuids::detail::md5::digest_type &digest);