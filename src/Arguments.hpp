/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Arguments
*/

#pragma once

#include <iostream>
#include "Errors/ArgumentsErrors.hpp"

namespace Plazza {
    /**
     * @brief The Arguments class represents the command line arguments passed to the program.
     */
    class Arguments {
    public:
        /**
         * @brief Constructs an Arguments object with the given command line arguments.
         * @param ac The number of command line arguments.
         * @param av The array of command line arguments.
         */
        Arguments(int ac, char **av);

        /**
         * @brief Default destructor for the Arguments class.
         */
        ~Arguments() = default;

        /**
         * @brief Gets the multiplier value.
         * @return The multiplier value.
         */
        double getMultiplier() const;

        /**
         * @brief Gets the number of cooks.
         * @return The number of cooks.
         */
        int getCookNumber() const;

        /**
         * @brief Gets the restock time.
         * @return The restock time.
         */
        double getRestockTime() const;

    private:
        double _multiplier; /**< The multiplier value. */
        int cookNumber; /**< The number of cooks. */
        double restockTime; /**< The restock time. */
    };
}
