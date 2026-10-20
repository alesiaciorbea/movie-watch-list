#pragma once
#include "FileWatchlist.h"
#include <fstream>
#include <cstdlib>

class HTMLWatchlist : public FileWatchlist
{
public:
    HTMLWatchlist(const std::string& filename) : FileWatchlist(filename) {}

    void writeToFile() const override {
        std::ofstream file(this->filename);
        if (!file.is_open()) return;

        file << "<!DOCTYPE html>\n<html>\n<head>\n<title>Watchlist</title>\n</head>\n<body>\n";
        file << "<table border=\"1\">\n";
        file << "<tr><td>Title</td><td>Genre</td><td>Year</td><td>Likes</td><td>Trailer</td></tr>\n";

        for (const auto& m : this->movies) {
            file << "<tr>\n";
            file << "<td>" << m.getTitle() << "</td>\n";
            file << "<td>" << m.getGenre() << "</td>\n";
            file << "<td>" << m.getYear() << "</td>\n";
            file << "<td>" << m.getLikes() << "</td>\n";
            file << "<td><a href=\"" << m.getTrailer() << "\">Link</a></td>\n";
            file << "</tr>\n";
        }

        file << "</table>\n</body>\n</html>\n";
        file.close();
    }

    void displayWatchlist() const override {
        std::string command = "start \"\" \"" + this->filename + "\"";
        system(command.c_str());
    }
};