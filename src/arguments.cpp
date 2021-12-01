#include "arguments.h"
#include <iostream>

bool ArgumentParser::ParseArguments(int argc, char *argv[], const std::shared_ptr<Arguments> &arguments) {
    boost::program_options::options_description description{"Possible options"};
    description.add_options()("help,h",
                              "Print help message");

    description.add_options()("input,i",
                              boost::program_options::value<boost::filesystem::path>(
                                      &arguments->input_file)->required(),
                              "File for signature calculation");

    description.add_options()("output,o",
                              boost::program_options::value<boost::filesystem::path>(
                                      &arguments->output_file)->required(),
                              "File with signature. Overwritten if exists");

    description.add_options()("blocksize,b",
                              boost::program_options::value<Blocktype>(&arguments->block_size)->default_value(
                                      1024 * 1024),
                              "Block size in bytes. Default is 1Mb");

    boost::program_options::variables_map variables;
    boost::program_options::store(parse_command_line(argc, argv, description), variables);

    if (variables.count("help")) {
        std::cout << description << std::endl;
        return false;
    }

    boost::program_options::notify(variables);

    auto canonical_input_path = boost::filesystem::canonical(arguments->input_file, ".");
    auto canonical_output_path = boost::filesystem::weakly_canonical(arguments->output_file);

    std::cout << "Input file: " << canonical_input_path << std::endl
              << "Output file: " << canonical_output_path << std::endl
              << "Block size: " << arguments->block_size << std::endl;

    if (!boost::filesystem::exists(arguments->input_file) ||
        !boost::filesystem::is_regular_file(arguments->input_file)) {
        throw std::invalid_argument("Input file doesn't exists");
    }

    if (!canonical_output_path.has_root_directory()) {
        throw std::invalid_argument("Output directory doesn't exists");
    }

    return true;
}
