#include "common.h"
#include <iostream>
#include <boost/algorithm/hex.hpp>

unsigned long long GetFilesize(const std::string &filename) {
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    unsigned long long file_size = in.tellg();
    in.close();
    return file_size;

}

unsigned long long int GetTotalBlocks(const std::string &file, unsigned long long int blocksize) {
    auto total_blocks = (GetFilesize(file) + blocksize - 1) / blocksize;
    return total_blocks;
}

std::string HashToString(const boost::uuids::detail::md5::digest_type &digest) {
    const auto charDigest = reinterpret_cast<const char *>(&digest);
    std::string result;
    boost::algorithm::hex(charDigest, charDigest + sizeof(boost::uuids::detail::md5::digest_type),
                          std::back_inserter(result));
    return result;
}