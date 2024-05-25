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
#include "Arguments/Arguments.hpp"
#include "messageQueue/messageQueueIPC.hpp"
#include "messageQueue/messageQueueThread.hpp"

/**
 * @brief Represents a pair of values, where the first value is of type Plazza::PizzaType and the second value is of type Plazza::PizzaSize.
 */
typedef std::pair<Plazza::PizzaType, Plazza::PizzaSize> Pizza;

class Kitchen {
public:
    /**
     * @brief Constructor for the Kitchen class.
     * @param nbCooks The number of cooks.
     * @param time The time to restock ingredients.
     * @param multiplier The multiplier for cooking time.
     * @param id The ID of the kitchen.
     */
    Kitchen(size_t nbCooks, size_t time, double multiplier, size_t id);

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

        /**
         * @brief Converts a string representation of a pizza to a Pizza object.
         * @param pizza The string representation of the pizza.
         * @return The Pizza object.
         */
        Pizza getPizzaFromString(const std::string &pizza);

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
        std::map<Plazza::PizzaType, std::map<Ingredients, size_t>> _pizzaIngredients = {
            {Plazza::PizzaType::Regina, {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}, {Ham, 1}, {Mushroom, 1}}},
            {Plazza::PizzaType::Margarita, {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}}},
            {Plazza::PizzaType::Americana, {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}, {Steak, 1}}},
            {Plazza::PizzaType::Fantasia, {{Dough, 1}, {Tomato, 1}, {Eggplant, 1}, {Goatcheese, 1}, {ChiefLove, 1}}}
        };
    };

    // Arguments
    size_t _nbCooks; ///< Number of cooks.
    size_t _timeToRestock; ///< Time to restock ingredients.
    double _multiplier; ///< Multiplier for cooking time.
    size_t _id; ///< ID of the kitchen.

    // Cook management
    std::chrono::system_clock::time_point _lastRestock; ///< Time of the last restock.
    Stock _stock; ///< Stock of ingredients.

    // Command management
    std::vector<std::string> _waitingCommands; ///< List of waiting commands.

    /**
     * @brief Message queue for receiving commands.
     */
    MessageQueueIPC<std::string> _kitchenQueue;

    /**
     * @brief Message queue for sending commands.
     */
    MessageQueueIPC<std::string> _receptionQueue;

    /**
     * @brief Message queues for sending commands to the cooks.
     */
    std::vector<MessageQueueThread<std::string>> _cooksQueue;

    /**
     * @brief Checks if there are available commands.
     * @return true if commands are available, false otherwise.
     */
    bool commandAreAvailable();

    /**
     * @brief Handles the commands.
     * @note This method transfers the commands from the message queue to the command buffer.
     */
    void handleCommands();

    /**
     * @brief Conveys the status of the kitchen to the reception.
     */
    void status();

    /**
     * @brief Manages the waiting commands.
     * @note If there are available cooks, the waiting commands are sent to them.
     */
    void manageWaitingCommands();

    /**
     * @brief Gets the number of cooks currently working.
     * @return The number of cooks working.
     */
    size_t getNbCooksWorking() const;
};
