#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class File_tsv
{
public:
    std::ifstream file;

    File_tsv() {}

    File_tsv(const std::string & fname);

    File_tsv( const File_tsv & ) = delete;
    File_tsv& operator=( const File_tsv & ) = delete;

    ~File_tsv() { file.close(); }
};

std::vector<std::string> isAdult(File_tsv& file_titles, const std::vector<std::string>& movies_id);

void search_movies(File_tsv& file_movies, const std::vector<std::string>& movies_id);

std::vector<std::string> search_character(File_tsv& file_characters, const std::string character);
