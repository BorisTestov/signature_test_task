#include "file.h"
#include "common.h"
#include <boost/filesystem.hpp>

File::File(const std::string &file_path, unsigned long long int block_size) :
        file_path_(file_path),
        block_size_(block_size) {
    if (!boost::filesystem::exists(file_path)) {
        throw std::runtime_error("Can't read file for creating 'File' class: " + file_path);
    }
}

File::File(const File &other_file) {
    this->block_size_ = other_file.block_size_;
    this->file_path_ = other_file.file_path_;
}

File &File::operator=(const File &other_file) = default;


FileIterator File::begin() {
    return FileIterator{file_path_, block_size_};
}

FileIterator File::end() {
    return FileIterator{file_path_,
                        block_size_,
                        GetTotalBlocks(file_path_, block_size_)};
}
