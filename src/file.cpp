#include "file.h"

#include <utility>

#include "common.h"

File::File(std::string file_path, unsigned long long int block_size) :
        file_path_(std::move(file_path)),
        block_size_(block_size) {}

File::File(const File &other_file) {
    this->block_size_ = other_file.block_size_;
    this->file_path_ = other_file.file_path_;
}

File &File::operator=(const File &other_file) {
    this->block_size_ = other_file.block_size_;
    this->file_path_ = other_file.file_path_;
    return *this;
}


FileIterator File::begin() {
    return FileIterator{file_path_, block_size_};
}

FileIterator File::end() {
    return FileIterator{file_path_,
                        block_size_,
                        GetTotalBlocks(file_path_, block_size_) + 1};
}
