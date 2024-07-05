#pragma once
#include <exception>

class ReadFailException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom Exception: Read operation failed";
    }
};