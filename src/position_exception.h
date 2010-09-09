#ifndef POSITION_EXCEPTION_H
#define POSITION_EXCEPTION_H

#include <exception>
#include <stdexcept>

class PositionException : public std::runtime_error
{
    public:
       explicit PositionException(const std::string& what)
           : std::runtime_error(what) {}

       virtual ~PositionException() throw() {}
};

#endif
