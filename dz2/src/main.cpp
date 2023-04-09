#include "utils.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Input example: ./text_processor 'echo 1 | cat file_1.txt | cat file_2.txt'";
        return 0;
    }

    List<std::shared_ptr<IOperation>> list;

    std::vector<std::string>* result = new std::vector<std::string>;

    parsing(list, result, argv[1]);

    delete result;

    return 0;
}
