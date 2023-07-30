#ifndef CSVEXCEPTION
#define CSVEXCEPTION

#include <exception>

class invalidCSV : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "CSV not found or can't open!";
        }
};

#endif // CSVEXCEPTION