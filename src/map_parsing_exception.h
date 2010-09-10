#ifndef MAP_PARSING_EXCEPTION_H
#define MAP_PARSING_EXCEPTION_H

#include <exception>
#include <stdexcept>

class MapParsingException : public std::runtime_error
{
    public:
       explicit MapParsingException(const std::string& what)
           : std::runtime_error(what) {}

       virtual ~MapParsingException() throw() {}
};

#endif
