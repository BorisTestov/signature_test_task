#include <gtest/gtest.h>
#include <fstream>
#include "../src/signature.h"
#include "common.h"

TEST(CalculateSignature, Correct) {
    CreateTestFile();
    auto arguments = std::make_shared<Arguments>();
    arguments->input_file = boost::filesystem::path("test_file");
    arguments->output_file = boost::filesystem::path("test.sig");
    arguments->block_size = 5;
    SignatureCalculator signature_calculator(arguments);
    signature_calculator.Calculate();
    std::ifstream signature("test.sig");
    std::string result;
    signature >> result;
    ASSERT_EQ(result, "0ECB7C826C708AEA68A1344C7B4EF8913EBA011ECB48AC0728D3B2DAFAD01D4D");
    signature.close();
    remove("test.sig");
    RemoveTestFile();
}

