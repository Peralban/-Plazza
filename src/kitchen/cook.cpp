/*
** EPITECH PROJECT, 2024
** cook.cpp
** File description:
** DESCRIPTION
*/

#include "cook.hpp"
#include "kitchen.hpp"
#include <string>
#include <unistd.h>

Cook::Cook(MessageQueueThread<std::string> &messageQueue, double timeToCookMultiplier) : _thread(&Cook::cookRoutine, this, std::ref(messageQueue)), _pizzaType(Plazza::NONE), _status(WAITING), _timeToCookMultiplier(timeToCookMultiplier) {}

void Cook::cookRoutine(MessageQueueThread<std::string> &messageQueue)
{
    while (true) {
        if (messageQueue.empty()) {
            usleep(1000);
            continue;
        }
        std::string message = messageQueue.pop();
        Plazza::PizzaType pizzaType = static_cast<Plazza::PizzaType>(std::stoi(message.substr(0, message.find(' '))));
        Plazza::PizzaSize pizzaSize = static_cast<Plazza::PizzaSize>(std::stoi(message.substr(message.find(' ') + 1)));
        if (pizzaType == Plazza::Margarita || pizzaType == Plazza::Regina || pizzaType == Plazza::Americana || pizzaType == Plazza::Fantasia) {
            std::cout << "Cook is cooking a pizza of type " << Plazza::DisplayPizzaName.at(pizzaType) << " and size " << Plazza::DisplayPizzaSize.at(pizzaSize) <<  "." << std::endl;
            _status = COOKING;
            _pizzaType = pizzaType;
            _pizzaSize = pizzaSize;
            std::this_thread::sleep_for(std::chrono::duration<double>(pizzaType * _timeToCookMultiplier));
            if (_status == UNEMPLOYED) {
                return;
            }
            std::cout << "Pizza : " << Plazza::DisplayPizzaName.at(pizzaType) << " is ready !" << std::endl;
            _status = WAITING;
            _pizzaType = Plazza::NONE;
        }
    }
}

Cook::~Cook()
{
    _thread.join();
}
