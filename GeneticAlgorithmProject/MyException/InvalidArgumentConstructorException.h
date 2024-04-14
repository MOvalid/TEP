#ifndef TEP_PROJEKT2_INVALIDARGUMENTCONSTRUCTOREXCEPTION_H
#define TEP_PROJEKT2_INVALIDARGUMENTCONSTRUCTOREXCEPTION_H

#include <exception>
#include <string>

class InvalidArgumentConstructorException: public std::exception {

private:
    std::string message;

public:

    explicit InvalidArgumentConstructorException(const std::string& msg = ""){
        this->message += msg;
    }

    const char* what() const noexcept override  {
        return message.c_str();
    }

};
#endif //TEP_PROJEKT2_INVALIDARGUMENTCONSTRUCTOREXCEPTION_H
