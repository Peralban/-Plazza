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

class Cook {
    public:
        enum status {
            COOKING,
            WAITING
        };

        Cook(std::shared_ptr<messageQueueThread> messageQueue);
        ~Cook();

        void Cook::cookRoutine(std::shared_ptr<messageQueueThread> messageQueue);

        status getStatus() { return _status; }

        Kitchen::Pizza getPizzaType() { return _pizzaType; }

    protected:
    private:
        std::thread _thread;
        std::shared_ptr<messageQueueThread> _messageQueue;
        status _status;
        Kitchen::Pizza _pizzaType; // will be changed with future enum
};
