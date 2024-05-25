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
#include <memory>
#include "messageQueue/messageQueueThread.hpp"
#include "Arguments/Arguments.hpp"

class Cook {
    public:
        enum status {
            COOKING,
            WAITING
        };

        Cook(std::shared_ptr<MessageQueueThread<std::string>> messageQueue);
        ~Cook();

        void cookRoutine(std::shared_ptr<MessageQueueThread<std::string>> messageQueue);

        status getStatus() { return _status; }

        Plazza::PizzaType getPizzaType() { return _pizzaType; }

    protected:
    private:
        std::shared_ptr<MessageQueueThread<std::string>> _messageQueue;
        std::thread _thread;
        Plazza::PizzaType _pizzaType;
        Plazza::PizzaSize _pizzaSize;
        status _status;
};
