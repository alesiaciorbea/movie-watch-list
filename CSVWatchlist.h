#pragma once
#include "FileWatchlist.h"
#include <fstream>
#include <cstdlib>

class CSVWatchlist : public FileWatchlist
{
public:
    CSVWatchlist(const std::string& filename) : FileWatchlist(filename) {}

    void writeToFile() const override {
        std::ofstream file(this->filename);
        if (!file.is_open()) return;

        for (const auto& m : this->movies) {
            file << m << "\n";
        }
        file.close();
    }

    void displayWatchlist() const override {
        std::string command = "notepad \"" + this->filename + "\"";
        system(command.c_str());
    }
};