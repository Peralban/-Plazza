/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Arguments
*/

#pragma once

#include <iostream>
#include "Errors/ArgumentsErrors.hpp"
#include <map>

namespace Plazza {

    enum PizzaType {
        Regina = 1 ,
        Margarita = 2 ,
        Americana = 4 ,
        Fantasia = 8
    };

    enum PizzaSize {
        S = 1 ,
        M = 2 ,
        L = 4 ,
        XL = 8 ,
        XXL = 16
    };

    static const std::map<std::string, Plazza::PizzaType> pizzaTypesMap = {
            {"regina", Plazza::PizzaType::Regina},
            {"margarita", Plazza::PizzaType::Margarita},
            {"americana", Plazza::PizzaType::Americana},
            {"fantasia", Plazza::PizzaType::Fantasia}
    };

    static const std::map<std::string, Plazza::PizzaSize> pizzaSizesMap = {
            {"S", Plazza::PizzaSize::S},
            {"M", Plazza::PizzaSize::M},
            {"L", Plazza::PizzaSize::L},
            {"XL", Plazza::PizzaSize::XL},
            {"XXL", Plazza::PizzaSize::XXL}
    };

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
         * @brief Copy constructor for the Arguments class.
        */
        Arguments(const Arguments &other);

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
