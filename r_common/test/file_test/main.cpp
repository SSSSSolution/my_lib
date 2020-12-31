//#include <gtest/gtest.h>
#include "file.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <assert.h>
using namespace reality::common;

//TEST(dir_test, Sum)
//{
//    File file("./test");
//    ASSERT_EQ(dir.exist(), true);
//    if (dir.exist())
//    {
//        printf("/home/bot dir exist!\n");
//    }

//    auto sub_dirs = dir.sub_dirs();
//    ASSERT_EQ(sub_dirs.size(), 1);
//    ASSERT_EQ(sub_dirs[0], std::string("CMakeFiles"));

//    auto sub_files = dir.sub_files();
//    ASSERT_EQ(sub_files.size(), 6);

//    auto sub_files_and_dirs = dir.sub_dirs_and_files();
//    ASSERT_EQ(sub_files_and_dirs.size(), 7);
//}

int main(int argc, char **argv)
{
//    ::testing::InitGoogleTest(&argc, argv);

//    return RUN_ALL_TESTS();
    if (argc < 3)
    {
        printf("usage: %s src dst\n", argv[0]);
        exit(0);
    }
    File file(argv[1]);
//    for (int i = 0; i < 100000; i++)
        if (file.exist()) {
            std::cout << "file exist\n";
        } else {
            std::cout << "file not exist\n";
        }
    if (file.copy(argv[2]))
    {
        std::cout << "copy successfully\n";
    }
    else {
        std::cout << "copy failed\n";
    }

    std::string empty;
    File f(empty);
    assert(!f.exist());
    std::cout << "empty name file's absPath: " << f.absolute_path() << std::endl;
    assert(f.absolute_path().empty());
    assert(!f.copy(""));
//    std::cout << "./test exist() = " << file.exist() << std::endl;
}
