#pragma once

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

using Blocktype = unsigned long long int;

/**
 * @brief Struct with input parameters
 */
struct Arguments {
    boost::filesystem::path input_file;
    boost::filesystem::path output_file;
    Blocktype block_size;
};

/**
 * @brief Class for parsing input parameters
 */
class ArgumentParser {
public:
    ArgumentParser() = default;

    /**
     * @brief parse input parameters
     * @param argc - argument count
     * @param argv - argument values
     * @param arguments - pointer to struct, where parameters will be saved. @see Arguments
     * @return true if parameters parsed successfully, false otherwise
     */
    static bool ParseArguments(int argc, char *argv[], const std::shared_ptr<Arguments> &arguments);
};


