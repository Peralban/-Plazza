/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** AError
*/

#include "AError.hpp"

const char *Errors::AError::what() const noexcept
{
    return _message.c_str();
}
