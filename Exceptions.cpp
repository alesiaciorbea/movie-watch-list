#include "Exceptions.h"

RepositoryException::RepositoryException(const std::string& msg) : message(msg) {}

const char* RepositoryException::what() const noexcept {
    return this->message.c_str();
}

ValidationException::ValidationException(const std::string& msg) : message(msg) {}

const char* ValidationException::what() const noexcept {
    return this->message.c_str();
}