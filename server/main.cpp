#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>

int main(int ac, char* av[])
{
    boost::array<char, 128> test1;

    std::cout << "Hello from server!" << std::endl;
    return 0;
}
