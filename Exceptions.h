#pragma once
#include <exception>
#include <string>

class RepositoryException : public std::exception
{
protected:
    std::string message;
public:
    RepositoryException(const std::string& msg);
    const char* what() const noexcept override;
};


class ValidationException : public std::exception
{
protected:
    std::string message;
public:
    ValidationException(const std::string& msg);
    const char* what() const noexcept override;
};