/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ArgumentsErrors
*/

#pragma once

#include "AError.hpp"

namespace Errors {
    /**
     * @class ArgumentsErrors
     * @brief Base class for argument-related errors.
     */
    class ArgumentsErrors : public AError {};

    /**
     * @class ArgumentNumber
     * @brief Error class for invalid argument number.
     */
    class ArgumentNumber : public ArgumentsErrors {
    public:
        /**
         * @brief Constructor for ArgumentNumber.
         * @param message The error message.
         */
        ArgumentNumber(std::string message) { _message = message; }
    };

    /**
     * @class WrongMultiplier
     * @brief Error class for invalid multiplier argument.
     */
    class WrongMultiplier : public ArgumentsErrors {
    public:
        /**
         * @brief Constructor for WrongMultiplier.
         * @param message The error message.
         */
        WrongMultiplier(std::string message) { _message = message; }
    };

    /**
     * @class WrongCookNumber
     * @brief Error class for invalid cook number argument.
     */
    class WrongCookNumber : public ArgumentsErrors {
    public:
        /**
         * @brief Constructor for WrongCookNumber.
         * @param message The error message.
         */
        WrongCookNumber(std::string message) { _message = message; }
    };

    /**
     * @class WrongRestockTime
     * @brief Error class for invalid restock time argument.
     */
    class WrongRestockTime : public ArgumentsErrors {
    public:
        /**
         * @brief Constructor for WrongRestockTime.
         * @param message The error message.
         */
        WrongRestockTime(std::string message) { _message = message; }
    };

    /**
     * @class InvalidArgument
     * @brief Error class for invalid argument.
     */
    class InvalidArgument : public ArgumentsErrors {
    public:
        /**
         * @brief Constructor for InvalidArgument.
         * @param message The error message.
         */
        InvalidArgument(std::string message) { _message = message; }
    };
}
