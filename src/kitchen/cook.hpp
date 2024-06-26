/*
** EPITECH PROJECT, 2024
** cook.hpp
** File description:
** DESCRIPTION
*/

#pragma once

#include <thread>
#include <iostream>
#include <chrono>
#include "messageQueue/messageQueueThread.hpp"
#include "Arguments/Arguments.hpp"

/**
 * @class Cook
 * @brief This class represents a Cook in the kitchen.
 *
 * A Cook can have two statuses: COOKING and WAITING.
 * The Cook class also contains a reference to a message queue for communication.
 */
class Cook {
    public:
        /**
         * @enum status
         * @brief The status of the Cook.
         *
         * The Cook can be either COOKING or WAITING.
         */
        enum status {
            COOKING, ///< The Cook is currently cooking a pizza.
            WAITING, ///< The Cook is waiting for a new pizza order.
            UNEMPLOYED ///< The Cook is unemployed.
        };

        /**
         * @brief Construct a new Cook object.
         *
         * @param messageQueue The message queue for communication.
         * @param timeToCookMultiplier The time multiplier for cooking.
         */
        Cook(MessageQueueThread<std::string> &messageQueue, double timeToCookMultiplier);

        /**
         * @brief Destroy the Cook object.
         */
        ~Cook();

        /**
         * @brief The routine that the Cook follows when cooking.
         *
         * @param messageQueue The message queue for communication.
         */
        void cookRoutine(MessageQueueThread<std::string> &messageQueue);

        /**
         * @brief Get the status of the Cook.
         *
         * @return The current status of the Cook.
         */
        status getStatus() { return _status; }

        /**
         * @brief Set the status of the Cook.
         *
         * @param status The new status of the Cook.
         */
        void setStatus(status newStatus) { _status = newStatus; }

        /**
         * @brief Get the type of the pizza that the Cook is currently cooking.
         *
         * @return The type of the pizza.
         */
        Plazza::PizzaType getPizzaType() { return _pizzaType; }

        /**
         * @brief Get the size of the pizza that the Cook is currently cooking.
         *
         * @return The size of the pizza.
         */
        Plazza::PizzaSize getPizzaSize() { return _pizzaSize; }

    protected:
    private:
        std::thread _thread; ///< The thread on which the Cook is running.
        Plazza::PizzaType _pizzaType; ///< The type of the pizza that the Cook is currently cooking.
        Plazza::PizzaSize _pizzaSize; ///< The size of the pizza that the Cook is currently cooking.
        status _status; ///< The current status of the Cook.
        double _timeToCookMultiplier; ///< The time multiplier for cooking.
};
