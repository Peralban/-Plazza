/*
** EPITECH PROJECT, 2024
** cook.cpp
** File description:
** DESCRIPTION
*/

#include "cook.hpp"
#include "kitchen.hpp"
#include <string>

void Cook::cookRoutine(std::shared_ptr<messageQueueThread> messageQueue)
{
    while (true) {
        int pizzaType =  std::stoi(messageQueue->pop());
        if (pizzaType == Kitchen::Margarita || pizzaType == Kitchen::Regina || pizzaType == Kitchen::Americana || pizzaType == Kitchen::Fantasia) {
            _status = COOKING;
            _pizzaType = static_cast<Kitchen::Pizza>(pizzaType);
            std::cout << "Cooking pizza" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(pizzaType));
            std::cout << "Pizza : " << pizzaType << " is ready" << std::endl;
            _status = WAITING;
            _pizzaType = Kitchen::NONE;
        }
    }
}

Cook::Cook(std::shared_ptr<messageQueueThread> messageQueue) :
    _messageQueue(messageQueue), _status(WAITING), _pizzaType(Kitchen::NONE), _thread(&Cook::cookRoutine, this, messageQueue)
{}

Cook::~Cook()
{
    _thread.join();
}

