#include <gtest/gtest.h>
#include "dir.h"
#include <stdio.h>
#include <string>

using namespace reality::common;

TEST(dir_test, Sum)
{
    Dir dir("./");
    ASSERT_EQ(dir.exist(), true);
    if (dir.exist())
    {
        printf("/home/bot dir exist!\n");
    }

    auto sub_dirs = dir.sub_dirs();
    ASSERT_EQ(sub_dirs.size(), 1);
    ASSERT_EQ(sub_dirs[0], std::string("CMakeFiles"));

    auto sub_files = dir.sub_files();
    ASSERT_EQ(sub_files.size(), 6);

    auto sub_files_and_dirs = dir.sub_dirs_and_files();
    ASSERT_EQ(sub_files_and_dirs.size(), 7);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
