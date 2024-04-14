#ifndef TEP_PROJEKT2_UNCORRECTFUNCTIONPARAMETEREXCEPTION_H
#define TEP_PROJEKT2_UNCORRECTFUNCTIONPARAMETEREXCEPTION_H

#include <exception>
#include <string>

class UncorrectFunctionParameterException: public std::exception {

private:
    std::string message;

public:

    explicit UncorrectFunctionParameterException(const std::string& msg = ""){
        message += msg;
    }

    const char* what() const noexcept override  {
        return message.c_str();
    }

};
#endif //TEP_PROJEKT2_UNCORRECTFUNCTIONPARAMETEREXCEPTION_H
