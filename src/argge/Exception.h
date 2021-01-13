#ifndef ARGGE_EXCEPTION_H
#define ARGGE_EXCEPTION_H

#include <exception>
#include <string>

namespace argge
{
    struct Exception : public std::exception
    {
        ///
        ///Custom exception to called if there is an error.
        ///
        Exception(const std::string& message);
        virtual ~Exception() throw();
        virtual const char* what() const throw();

    private:
        std::string message;
    };
}
#endif