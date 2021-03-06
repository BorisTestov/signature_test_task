#include <iterator>
#include <fstream>
#include <memory>
#include <boost/filesystem.hpp>
#include "fileiterator.h"
#include "common.h"

FileIterator::FileIterator(const std::string &file_path,
                           unsigned long long int block_size,
                           unsigned long long int start_block) {
    if (!boost::filesystem::exists(file_path)) {
        throw std::runtime_error("Can't read file for creating 'FileIterator' class: " + file_path);
    }
    block_size_ = block_size;
    file_handle_.open(file_path, std::ifstream::binary);
    file_size_ = GetFilesize(file_path);
    total_blocks_ = GetTotalBlocks(file_path, block_size_);
    current_block_ = start_block;
    next();
}

FileIterator::~FileIterator() {
    file_handle_.close();
}

const std::string &FileIterator::operator*() const {
    return data_;
}

FileIterator &FileIterator::operator++() {
    next();
    return *this;
}

bool operator!=(const FileIterator &a, const FileIterator &b) {
    return a.current_block_ != b.current_block_;
}

void FileIterator::next() {
    unsigned long long int amount_to_read = block_size_;
    if (current_block_ + 1 == total_blocks_) {
        amount_to_read = file_size_ - (current_block_) * block_size_;
    }
    data_ = std::string(amount_to_read, '\0');
    file_handle_.read((char *) data_.data(), amount_to_read);
    current_block_++;
}