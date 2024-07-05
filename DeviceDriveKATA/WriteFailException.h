#pragma once
#include <exception>

class WriteFailException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom Exception: Read operation failed";
    }
};