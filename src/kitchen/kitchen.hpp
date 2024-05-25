/*
** EPITECH PROJECT, 2024
** kitchen.hpp
** File description:
** DESCRIPTION
*/

#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <map>
#include <chrono>
#include "messageQueue/messageQueueIPC.hpp"
#include "messageQueue/messageQueueThread.hpp"
#include "Arguments/Arguments.hpp"
#include "cook.hpp"


/**
 * @class Kitchen
 * @brief Main class for managing the kitchen operations.
 */
class Kitchen {
    public:

        /**
         * @brief Constructor for the Kitchen class.
         */
        Kitchen(size_t nbCooks, size_t timeToRestock, double multi, std::shared_ptr<MessageQueueIPC<std::string>> kitchenQueue, std::shared_ptr<MessageQueueIPC<std::string>> receptionQueue);

        /**
         * @brief Destructor for the Kitchen class.
         */
        ~Kitchen();

        /**
         * @brief Checks if there are available commands.
         * @return true if commands are available, false otherwise.
         */
        bool commandAreAvailable();

        /**
         * @brief Creates a new cook.
         */
        void createCook();

        /**
         * @brief Starts the kitchen.
         * @return true if the kitchen is running, false if the kitchen has to be closed.
         */
         bool update();

    private:
        /**
         * @class Stock
         * @brief Inner class for managing the stock of ingredients.
         */
        class Stock {
        public:
            /**
             * @brief Constructor for the Stock class.
             */
            Stock();

            /**
             * @brief Destructor for the Stock class.
             */
            ~Stock();

            /**
             * @enum Ingredients
             * @brief Enum for the different types of ingredients.
             */
            enum Ingredients {
                Dough,
                Tomato,
                Gruyere,
                Ham,
                Mushroom,
                Steak,
                Eggplant,
                Goatcheese,
                ChiefLove
            };


            /**
             * @brief Restocks the ingredients.
             */
            void restock();

            /**
             * @brief Checks if there are enough ingredients for a specific pizza.
             * @param pizza The type of pizza to check for.
             * @return true if there are enough ingredients, false otherwise.
             */
            bool hasEnoughIngredient(Plazza::PizzaType pizza);

            /**
             * @brief Takes the ingredients for a specific pizza.
             * @param pizza The type of pizza to take ingredients for.
             */
            void takeIngredient(Plazza::PizzaType pizza);

        private:
            size_t _dough; ///< Amount of dough in stock.
            size_t _tomato; ///< Amount of tomato in stock.
            size_t _gruyere; ///< Amount of gruyere in stock.
            size_t _ham; ///< Amount of ham in stock.
            size_t _mushroom; ///< Amount of mushroom in stock.
            size_t _steak; ///< Amount of steak in stock.
            size_t _eggplant; ///< Amount of eggplant in stock.
            size_t _goatCheese; ///< Amount of goat cheese in stock.
            size_t _chiefLove; ///< Amount of chief love in stock.

            /**
             * @brief Map for storing the ingredients required for each type of pizza.
             */
            std::map<Plazza::PizzaType, std::map<Ingredients, size_t>> _pizzaIngredients = {
                {Plazza::Regina, {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}, {Ham, 1}, {Mushroom, 1}}},
                {Plazza::Margarita, {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}}},
                {Plazza::Americana, {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}, {Steak, 1}}},
                {Plazza::Fantasia, {{Dough, 1}, {Tomato, 1}, {Eggplant, 1}, {Goatcheese, 1}, {ChiefLove, 1}}}
            };
        };
        size_t _nbCooks; ///< Number of cooks.
        size_t _commandNumber; ///< Number of commands.
        std::vector<std::shared_ptr<Cook>> _cooks; ///< Vector of cooks.
        size_t _timeToRestock; ///< Time to restock ingredients.
        double _multi; ///< Multiplier for cooking time.
        Stock _stock; ///< Stock of ingredients.
        bool _clockIsRunning; ///< Flag for the clock status.
        std::chrono::system_clock::time_point _startClock; ///< Start time of the clock.

        /**
         * @brief Message queue for receiving commands.
         */
        std::shared_ptr<MessageQueueIPC<std::string>> _kitchenQueue;

        /**
         * @brief Thread for receiving commands.
         */
        std::shared_ptr<MessageQueueIPC<std::string>> _receptionQueue;

        /**
         * @brief Thread for receiving commands.
         */
        std::shared_ptr<MessageQueueThread<std::string>> _messageQueue;
};
