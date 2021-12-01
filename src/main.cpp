#include <iostream>
#include "arguments.h"
#include "signature.h"

// TODO add unit tests with gtest
// TODO add dockerfile for running
// TODO add CI/CD

int main(int argc, char *argv[]) {
    try {
        std::shared_ptr<Arguments> arguments = std::make_shared<Arguments>();

        bool parsed = ArgumentParser::ParseArguments(argc, argv, arguments);
        if (!parsed) {
            return 0;
        }

        SignatureCalculator signature_calculator(arguments);
        signature_calculator.Calculate();

        std::cout << std::endl
                  << "SignatureCalculator file written to:" << std::endl
                  << arguments->output_file << std::endl;
        return 0;
    }
    catch (const boost::program_options::error &exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
}
