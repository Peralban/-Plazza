/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Arguments
*/

#include "Arguments.hpp"

Plazza::Arguments::Arguments(int ac, char **av)
{
    try {
        if (ac != 4) {
            displayUsage();
            throw Errors::ArgumentNumber("Invalid number of arguments");
        } if (std::stof(av[1]) < 0) {
            displayUsage();
            throw Errors::WrongMultiplier("Invalid multiplier");
        } if (std::stoi(av[2]) <= 0) {
            displayUsage();
            throw Errors::WrongCookNumber("Invalid number of cooks");
        } if (std::stof(av[3]) <= 0) {
            displayUsage();
            throw Errors::WrongRestockTime("Invalid restock time");
        }
    } catch (Errors::ArgumentsErrors &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    _multiplier = std::stof(av[1]);
    cookNumber = std::stoi(av[2]);
    restockTime = std::stof(av[3]);
}

double Plazza::Arguments::getMultiplier() const
{
    return _multiplier;
}

int Plazza::Arguments::getCookNumber() const
{
    return cookNumber;
}

double Plazza::Arguments::getRestockTime() const
{
    return restockTime;
}

void Plazza::Arguments::displayUsage()
{
    std::cout << "USAGE: ./plazza multiplier cooks restock_time" << std::endl;
    std::cout << "\tmultiplier: positive float" << std::endl;
    std::cout << "\tcooks: positive integer" << std::endl;
    std::cout << "\trestock_time: positive float" << std::endl;
}
