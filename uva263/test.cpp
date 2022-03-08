#include <gmock/gmock.h>
#include <stdint.h>
#include "uva263.h"

TEST(mapping_str_order_to_int, acending_125634) {
        std::string input_str = std::to_string(125634);
            EXPECT_EQ (mapping_str_order_to_int(input_str, ASCENDING), 123456);
}

TEST(mapping_str_order_to_int, descending_125634) {
        std::string input_str = std::to_string(125634);
            EXPECT_EQ (mapping_str_order_to_int(input_str, DESCENDING), 654321);
}

