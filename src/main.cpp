#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "utils.hpp"


int main(int argc, char** argv)
{
    uint8_t flag = 0;
    std::string character = "";
    std::string file_name = "";
    for (int i = 1; i < argc; ++i) {
        file_name += argv[i];
        if (flag >= 3) {
            character.size() == 0 ? character += argv[i] : character += (" " + file_name);
        }
        else {
            if ((file_name == "title.principals.tsv") || (file_name == "title.basics.tsv") || (file_name == "title.akas.tsv")) {
                flag++;
            }
        }
        file_name.clear();
    }

    if ((flag >= 3) && (character.size() > 0)) {
        std::string path = "/home/max/VK/CPP/DZ1/data/";
        File_tsv title_principals(path + "title.principals.tsv");  // поиск фильмов с данным персонажем
        File_tsv title_basics(path + "title.basics.tsv");  // оставим из них фильмы НЕ для взрослых
        File_tsv title_akas(path + "title.akas.tsv");  // поиск их русских названий

        std::vector<std::string> characters = search_character(title_principals, character);
        std::vector<std::string> not_adults = isAdult(title_basics, characters);
        search_movies(title_akas, not_adults);
    }
    else {
        std::cerr << "Incorrect data entry" << std::endl;
    }
    
}
