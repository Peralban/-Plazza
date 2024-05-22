/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** DESCRIPTION
*/

#include <iostream>
#include "shell/shellParser.hpp"
#include "Arguments/Arguments.hpp"

static void displayUsage()
{
    std::cout << "USAGE: ./plazza multiplier cooks restock_time" << std::endl;
    std::cout << "\tmultiplier: positive float" << std::endl;
    std::cout << "\tcooks: positive integer" << std::endl;
    std::cout << "\trestock_time: positive float" << std::endl;
}

int main(int ac, char **av)
{
    try {
        Plazza::Arguments args(ac, av);
        Shell::run(args);
    } catch (const Errors::ArgumentsErrors &e) {
        std::cerr << e.what() << std::endl;
        displayUsage();
        return 84;
    }
    return 0;
}
