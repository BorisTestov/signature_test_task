#include <iterator>
#include <fstream>
#include <memory>
#include <mutex>
#include <iostream>
#include <cstring>
#include "fileiterator.h"
#include "common.h"

FileIterator::FileIterator(const std::string &file_path,
                           unsigned long long int block_size,
                           unsigned long long int start_block) {
    block_size_ = block_size;
    file_handle_.open(file_path, std::ifstream::binary);
    file_size_ = GetFilesize(file_path);
    total_blocks_ = GetTotalBlocks(file_path, block_size_);
    current_block_ = start_block;
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
    std::lock_guard<std::mutex> lck(mutex_);
    unsigned long long int amount_to_read = block_size_;
    if (current_block_ + 1 == total_blocks_) {
        amount_to_read = file_size_ - (current_block_) * block_size_;
    }
    std::string buffer(amount_to_read, '\0');
    file_handle_.read((char *) buffer.data(), amount_to_read);
    data_ = buffer;
    current_block_++;
}