/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ArgumentsErrors
*/

#include "ArgumentsErrors.hpp"

Errors::ArgumentNumber::ArgumentNumber(std::string message)
{
    _message = message;
}

Errors::WrongMultiplier::WrongMultiplier(std::string message)
{
    _message = message;
}

Errors::WrongCookNumber::WrongCookNumber(std::string message)
{
    _message = message;
}

Errors::WrongRestockTime::WrongRestockTime(std::string message)
{
    _message = message;
}
