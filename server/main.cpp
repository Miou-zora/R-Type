#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>
#include <ctime>

int main(int ac, char *av[])
{
    boost::array<char, 128> test1;

    std::cout << "Hello from server!" << std::endl;
    return 0;
}
