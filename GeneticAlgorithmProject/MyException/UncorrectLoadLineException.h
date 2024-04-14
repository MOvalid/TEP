#ifndef TEP_PROJEKT2_UNCORRECTLOADLINEEXCEPTION_H
#define TEP_PROJEKT2_UNCORRECTLOADLINEEXCEPTION_H


#include <exception>
#include <string>

class UncorrectLoadLineException: public std::exception {

private:
    std::string message;

public:

    explicit UncorrectLoadLineException(const std::string& msg = ""){
        this->message += msg;
    }

    const char* what() const noexcept override {
        return message.c_str();
    }

};


#endif //TEP_PROJEKT2_UNCORRECTLOADLINEEXCEPTION_H
