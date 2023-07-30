#ifndef NODE_HPP
#define NODE_HPP

#include <string>

class Node {
public:
    // Constructor for node (obj to hold both value and index)
    Node(double v = 0.0, std::string i = "") {
        value = v;
        index = i;
    };

    // Getters

    double getValue() const {
        return value;
    };

    std::string getIndex() const {
        return index;
    };

private:
    double value;
    std::string index;
};

#endif // NODE_HPP
