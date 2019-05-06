#include <jbr/reg/config.hpp>
#include <jbr/reg/factorial.hpp>
#include <jbr/reg/HelloWorld.hpp>

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    jbr::reg::HelloWorld helloWorld;
    
    if (argc == 2 && std::string{ argv[1] } == "--version")
    {
        std::cout << "Project Name version " << VERSION << "\n";
        std::cout << "Copyright information here\n";
        std::cout << "More copyright details.\n\n";
    }
    else
    {
        std::cout << helloWorld.hello() << ", " << helloWorld.world() << "!\n";
        std::cout << "Random number = " << helloWorld.generateRandomNumber() << "\n";
        std::cout << "Factorial(5) = " << factorial(5) << "\n";
        while (true);
    }
}
