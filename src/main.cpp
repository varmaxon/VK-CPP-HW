#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "utils.hpp"


int main(int argc, char** argv)
{
    u_int8_t flag = 0;
    std::string character = "";
    std::string file_name = "";
    for (int i = 1; i < argc; i++) {
        file_name += argv[i];
        if (flag >= 3) {
            character.size() == 0 ? character += argv[i] : character += (" " + file_name);
        }
        else {
            if (file_name == "title.principals.tsv") {
                flag++;
                File_tsv title_principals("title.principals.tsv");
            }
            if (file_name == "title.basics.tsv") {
                flag++;
                File_tsv title_basics("title.basics.tsv");
            }
            if (file_name == "title.akas.tsv") {
                flag++;
                File_tsv title_akas("title.akas.tsv");
            }
        }
        file_name.clear();
    }

    if ((flag >= 3) && (character.size() > 0)) {
        File_tsv title_principals("title.principals.tsv");  // поиск фильмов с данным персонажем
        File_tsv title_basics("title.basics.tsv");  // оставим из них фильмы НЕ для взрослых
        File_tsv title_akas("title.akas.tsv");  // поиск их русских названий

        std::vector<std::string> characters = search_character(title_principals, character);
        std::vector<std::string> not_adults = is_adult(title_basics, characters);
        search_movies(title_akas, not_adults);
    }
    else {
        std::cout << "ERROR: Введены не все необходимые данные." << std::endl;
    }
    
}
