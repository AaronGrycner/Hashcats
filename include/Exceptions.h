//
// Created by aaron on 3/20/24.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class NoResponse final : public std::exception {
private:
    const char* message;

public:
    explicit NoResponse(const char* msg) : message(msg) {}

    // Override what() method to return custom message
    const char* what() const noexcept override {
        return message;
    }
};


#endif //EXCEPTIONS_H
