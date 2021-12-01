#include "common.h"
#include "signature.h"
#include <iostream>


SignatureCalculator::SignatureCalculator(const std::shared_ptr<Arguments> &arguments) {
    output_path_ = arguments->output_file;
    input_file_ = std::make_unique<File>(arguments->input_file.string(), arguments->block_size);
    std::ofstream output_file(arguments->output_file);
    output_file.close();
}

void SignatureCalculator::Calculate() {
    for (auto file_iterator = input_file_->begin(); file_iterator != input_file_->end(); ++file_iterator) {
        auto data = *file_iterator;
        if (data.empty()) continue;
        tasks_pool_.push_back(std::async(
                [](const std::string &data) {
                    return GetHashBlock(data.c_str());
                }, std::move(data)));
    }
    for (auto &task: tasks_pool_) {
        task.wait();
        WriteHashBlock(task.get());
    }
}

std::string SignatureCalculator::GetHashBlock(const char *buffer) {
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;
    hash.process_bytes(buffer, strlen(buffer));
    hash.get_digest(digest);
    return HashToString(digest);
}

void SignatureCalculator::WriteHashBlock(const std::string &hash_block) {
    std::ofstream result(output_path_, std::ifstream::app);
    result << hash_block;
    result.close();
}
