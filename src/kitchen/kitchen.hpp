/*
** EPITECH PROJECT, 2024
** kitchen.hpp
** File description:
** DESCRIPTION
*/

#pragma once

#include <iostream>
#include <list>
#include <thread>
#include <map>
#include <unordered_map>
#include <functional>
#include <queue>
#include <chrono>
#include "messageQueue/messageQueueIPC.hpp"


/**
 * @class Kitchen
 * @brief Main class for managing the kitchen operations.
 */
class Kitchen {
    public:

        /**
         * @brief Constructor for the Kitchen class.
         * @param nbCooks The number of cooks.
         * @param time The time to restock ingredients.
        */
        Kitchen(size_t nbCooks, size_t time);

        /**
         * @brief Destructor for the Kitchen class.
         */
        ~Kitchen();

        /**
         * @brief Runs the kitchen.
         */
        void run();

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
             * @enum Pizza
             * @brief Enum for the different types of pizzas.
             */
            enum Pizza {
                Regina,
                Margarita,
                Americana,
                Fantasia
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
            bool hasEnoughIngredient(Pizza pizza);

            /**
             * @brief Takes the ingredients for a specific pizza.
             * @param pizza The type of pizza to take ingredients for.
             */
            void takeIngredient(Pizza pizza);

            size_t dough; ///< Amount of dough in stock.
            size_t tomato; ///< Amount of tomato in stock.
            size_t gruyere; ///< Amount of gruyere in stock.
            size_t ham; ///< Amount of ham in stock.
            size_t mushroom; ///< Amount of mushroom in stock.
            size_t steak; ///< Amount of steak in stock.
            size_t eggplant; ///< Amount of eggplant in stock.
            size_t goatCheese; ///< Amount of goat cheese in stock.
            size_t chiefLove; ///< Amount of chief love in stock.

        private:
            /**
             * @brief Map for storing the ingredients required for each type of pizza.
             */
            std::map<Kitchen::Stock::Pizza, std::map<Ingredients, size_t>> _pizzaIngredients = {
                {Regina, {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}, {Ham, 1}, {Mushroom, 1}}},
                {Margarita, {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}}},
                {Americana, {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}, {Steak, 1}}},
                {Fantasia, {{Dough, 1}, {Tomato, 1}, {Eggplant, 1}, {Goatcheese, 1}, {ChiefLove, 1}}}
            };
        };

        size_t _nbCooks; ///< Number of cooks.
        std::vector<std::thread> _cooks; ///< List of cook threads.
        Stock _stock; ///< Stock of ingredients.

        size_t _id; ///< ID of the kitchen.
        std::vector<std::string> _waitingCommands; ///< List of waiting commands.
        std::vector<std::string> _inProgressCommands; ///< List of commands in progress.

        std::chrono::system_clock::time_point _lastRestock; ///< Time of the last restock.
        size_t _timeToRestock; ///< Time to restock ingredients.

        /**
         * @brief Message queue for receiving commands.
         */
        MessageQueueIPC<std::string> _kitchenQueue;

        /**
         * @brief Thread for receiving commands.
         */
        MessageQueueIPC<std::string> _receptionQueue;

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
         * @brief Handles the commands.
         * @note This method transfers the commands from the message queue to the command buffer.
         */
        void handleCommands();

        /**
         * @brief Manage the cook threads.
         */
        void manageCooks();

        /**
         * @brief Conveys the status of the kitchen to the reception.
         */
        void status();
};
