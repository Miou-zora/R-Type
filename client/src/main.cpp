#include <iostream>
namespace raylib {
    #include <raylib.h>
}
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>
#include <ctime>

int main(int ac, char *av[])
{
    boost::array<char, 128> test1;

    std::cout << "Hello from client!" << std::endl;
    raylib::InitWindow(800, 600, "raylib [core] example - basic window");
    return 0;
}
