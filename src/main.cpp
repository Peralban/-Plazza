/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** DESCRIPTION
*/

#include "shellParser.hpp"
#include "Arguments.hpp"

int main(int ac, char **av)
{
    try {
        Plazza::Arguments args(ac, av);
        Shell::run(args);
    } catch (const Errors::ArgumentsErrors &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
