#include "gtest/gtest.h"
#include "config_parser.h"

class NginxConfigTest : public ::testing::Test {
protected:

    NginxConfigParser parser_;
    NginxConfig config_;

    bool ParseString(const std::string& config_string) {

        std::stringstream config_stream(config_string);
        return parser_.Parse(&config_stream, &config_);

    }

};

/* Tests that it is able to parse a simple config file. */
TEST(NginxConfigParserTest, SimpleConfig) {

    NginxConfigParser parser;
    NginxConfig out_config;

    bool success = parser.Parse("example_config", &out_config);

    EXPECT_TRUE(success);

}

/* Checks the output of a parsing of a simple config file. */
TEST_F(NginxConfigTest, SimpleParse) {

    bool success = ParseString("foo bar;");

    EXPECT_TRUE(success) << "Could not parse simple config";

    EXPECT_EQ(1, config_.statements_.size()) << "Did not get the correct "
                                                    "number of statements";

    EXPECT_EQ("foo", config_.statements_.at(0)->tokens_.at(0)) <<
        "Did not get the correct parse value";

    EXPECT_EQ("bar", config_.statements_.at(0)->tokens_.at(1)) <<
        "Did not get the correct parse value";

}

/* Checks that it can parse a nested config file. */
TEST_F(NginxConfigTest, NestParse) {

    EXPECT_TRUE(ParseString("foo { bar 100; }"));

}

/* Checks that it can parse a nested config file. */
TEST_F(NginxConfigTest, DoubleNestParse) {

    EXPECT_TRUE(ParseString("foo { bar 100; foo2 { bar2 200; } }"));

}
