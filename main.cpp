#include <iostream>
#include <fstream>
#include <string>

#define ErrCountCMDArgs "count args error"
#define ErrOpenFile "open file error"

void run(std::ifstream *in, std::ostream *out) {
    std::cout<<"Hello world";
}

int main(int argc, char **argv) {
    if (argc < 2) // no arguments were passed
    {
        std::cout << ErrCountCMDArgs << std::endl;
        return -1;
    }

    std::string inFileName = argv[1];
    std::string outFileName = argv[2];

    std::ifstream in(inFileName);
    std::ofstream out(outFileName);

    if (!in.is_open() || !out.is_open())
    {
        std::cout << ErrOpenFile << std::endl;
        return -1;
    }

    run(&in, &out);
    return 0;
}
