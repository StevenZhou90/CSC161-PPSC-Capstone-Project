#ifndef IDENTIFIEREXCEPTION
#define IDENTIFIEREXCEPTION

#include <exception>

class invalidID : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "ID not found! Make sure one of the columns (first row) contains string ID.";
        }
};

#endif // IDENTIFIEREXCEPTION