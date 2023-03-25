#include "utils.hpp"

// #include <iostream>
// #include <vector>
// #include <fstream>
// #include <string>

File_tsv::File_tsv(const std::string & fname) {
    file.open(fname);
    if (!file.is_open()) {
        std::cout << "ERROR - File not found" << std::endl;
    }
}

std::vector<std::string> is_adult(File_tsv& file_titles, std::vector<std::string>& movies_id) {
    file_titles.file.seekg(0);
    std::string line, str;
    std::vector<std::string> result_id, vec;
    while (getline(file_titles.file, line)) {
        str = "";
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == '\t') {
                vec.push_back(str);
                str = "";
            }
            else
                str += line[i];
        }
        vec.push_back(str);

        for (unsigned int i = 0; i < movies_id.size(); i++) {
            if ((vec.at(1) == "movie") && (vec.at(4) == "0") && (vec.at(0) == movies_id.at(i))) {
                result_id.push_back(vec.at(0));
                break;
            }
        }
        vec.clear();
    }
    return result_id;
}

void search_movies(File_tsv& file_movies, std::vector<std::string>& movies_id) {
    file_movies.file.seekg(0);
    std::string line, str;
    std::vector<std::string> vec;
    bool flag = false;
    while (getline(file_movies.file, line)) {
        str = "";
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == '\t') {
                vec.push_back(str);
                str = "";
            }
            else
                str += line[i];
        }
        vec.push_back(str);

        for (unsigned int i = 0; i < movies_id.size(); i++) {
            if (((vec.at(4) == "ru") || (vec.at(3) == "RU")) && (vec.at(0) == movies_id.at(i))) {
                std::cout << vec.at(2) << std::endl;
                flag = true;
                break;
            }
        }
        vec.clear();
    }
    if (!flag) { std::cout << "NOT FOUND" << std::endl; }
    return;
}

std::vector<std::string> search_character(File_tsv& file_characters, std::string character) {
    file_characters.file.seekg(0);
    std::string line, str;
    std::vector<std::string> result_id, vec;
    while (getline(file_characters.file, line)) {
        str = "";
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == '\t') {
                vec.push_back(str);
                str = "";
            }
            else
                str += line[i];
        }
        vec.push_back(str);

        if (((vec.at(5).find('"' + character + '"')) != std::string::npos) && (vec.at(3) == "actor")) {
            result_id.push_back(vec.at(0));
        }
        vec.clear();
    }
    return result_id;
}
