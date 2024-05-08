#include "src/Car.h"
#include "src/RemoteControl.h"
#include "stdafx.h"

int main()
{
    Car car;

    RemoteControl remoteControl(car, std::cin, std::cout);

    while (!std::cin.eof() && !std::cin.fail())
    {
        std::cout << MENU << std::endl;
        std::cout << "> ";
        if (!remoteControl.HandleCommand())
        {
            std::cout << "Unknown command!" << std::endl;
        }
    }

    return 0;
}