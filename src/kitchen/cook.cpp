/*
** EPITECH PROJECT, 2024
** cook.cpp
** File description:
** DESCRIPTION
*/

#include "cook.hpp"
#include "kitchen.hpp"
#include <string>

Cook::Cook(std::shared_ptr<MessageQueueThread<std::string>> messageQueue, double timeToCookMultiplier) :
    _messageQueue(messageQueue), _thread(&Cook::cookRoutine, this, messageQueue), _pizzaType(Plazza::NONE), _status(WAITING), _timeToCookMultiplier(timeToCookMultiplier) {}

void Cook::cookRoutine(std::shared_ptr<MessageQueueThread<std::string>> messageQueue)
{
    while (true) {
        if (messageQueue->empty())
            continue;
        std::string message = messageQueue->pop();
        Plazza::PizzaType pizzaType = static_cast<Plazza::PizzaType>(std::stoi(message.substr(0, message.find(' '))));
        Plazza::PizzaSize pizzaSize = static_cast<Plazza::PizzaSize>(std::stoi(message.substr(message.find(' ') + 1)));
        if (pizzaType == Plazza::Margarita || pizzaType == Plazza::Regina || pizzaType == Plazza::Americana || pizzaType == Plazza::Fantasia) {
            _status = COOKING;
            _pizzaType = pizzaType;
            _pizzaSize = pizzaSize;
            std::cout << "Cooking pizza" << std::endl;
            std::this_thread::sleep_for(std::chrono::duration<double>(pizzaType * _timeToCookMultiplier));
            std::cout << "Pizza : " << pizzaType << " is ready" << std::endl;
            _status = WAITING;
            _pizzaType = Plazza::NONE;
        }
    }
}

Cook::~Cook()
{
    _thread.join();
}
