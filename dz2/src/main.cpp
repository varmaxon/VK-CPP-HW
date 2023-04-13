#include "utils.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Input example (write the full path for files): ./text_processor 'echo 1 | cat file_1.txt | cat file_2.txt'";
        return EXIT_FAILURE;
    }

    List<std::shared_ptr<IOperation>> list;

    std::shared_ptr<std::vector<std::string>> result(new std::vector<std::string>);

    parsing(list, result, static_cast<std::string>(argv[1]));

    return EXIT_SUCCESS;
}
