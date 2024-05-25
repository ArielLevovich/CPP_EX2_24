#include <iostream>
#include <exception>

// Define a custom exception class that inherits from std::exception
class NegativeCycleException : public std::exception {
private:
    const char* message;

public:
    NegativeCycleException(const char* msg) : message(msg) {}

    const char* what() const noexcept override {
        return message;
    }
};