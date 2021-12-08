#include "common.h"
#include "signature.h"
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>

SignatureCalculator::SignatureCalculator(const std::shared_ptr<Arguments> &arguments) {
    output_path_ = arguments->output_file;
    input_file_ = std::make_unique<File>(arguments->input_file.string(), arguments->block_size);
    total_blocks_ = GetTotalBlocks(arguments->input_file.string(), arguments->block_size);
    std::ofstream output_file(arguments->output_file);
    output_file.close();
}

void SignatureCalculator::Calculate() {

    size_t max_threads = std::max((int) std::thread::hardware_concurrency(), 1);

    boost::asio::thread_pool pool(max_threads);
    for (auto file_iterator = input_file_->begin(); file_iterator != input_file_->end(); ++file_iterator) {
        auto data = *file_iterator;
        if (data.empty()) continue;
        std::packaged_task<std::string()> task([data = std::move(data)]() {
            return GetHashBlock(data);
        });
        futures_.push_back(task.get_future());
        boost::asio::post(pool, std::move(task));
    }

    boost::asio::post(pool, [this] {
        size_t completed_threads = 0;
        while (completed_threads != this->total_blocks_) {
            if (!this->futures_.empty()) {
                WriteHashBlock(this->futures_.at(0).get());
                this->futures_.erase(this->futures_.begin());
                ++completed_threads;
            }
        }
    });

    pool.join();
}

std::string SignatureCalculator::GetHashBlock(const std::string &buffer) {
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;
    hash.process_bytes(buffer.data(), buffer.length());
    hash.get_digest(digest);
    return HashToString(digest);
}

void SignatureCalculator::WriteHashBlock(const std::string &hash_block) {
    std::ofstream result(output_path_, std::ifstream::app);
    result << hash_block;
    result.close();
}
