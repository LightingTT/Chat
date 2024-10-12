#include <iostream>
#include <boost/algorithm/string.hpp>
#include <winsock2.h>

int main() {
    std::string text = "Hello Boost!";
    boost::to_upper(text);
    std::cout << text << std::endl; // Output: HELLO BOOST!
    return 0;
}

