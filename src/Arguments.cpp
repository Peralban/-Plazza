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
            throw Errors::ArgumentNumber("Invalid number of arguments");
        } if (std::stof(av[1]) < 0) {
            throw Errors::WrongMultiplier("Invalid multiplier");
        } if (std::stoi(av[2]) <= 0) {
            throw Errors::WrongCookNumber("Invalid number of cooks");
        } if (std::stof(av[3]) <= 0) {
            throw Errors::WrongRestockTime("Invalid restock time");
        }
    } catch (const std::exception &e) {
        throw Errors::InvalidArgument(e.what());
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
