#include "MovieValidator.h"
#include "Exceptions.h"

void MovieValidator::validate(const Movie& m)
{
    std::string errors = "";

    if (m.getTitle().empty()) {
        errors += "Title cannot be empty!\n";
    }
    if (m.getYear() < 1888) { 
        errors += "Year must be a valid positive number (>= 1888)!\n";
    }
    if (m.getLikes() < 0) {
        errors += "Number of likes cannot be negative!\n";
    }
    if (m.getTrailer().find("http") != 0) { 
        errors += "Trailer link must start with 'http'!\n";
    }

    if (!errors.empty()) {
        throw ValidationException(errors);
    }
}