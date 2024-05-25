/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include <unistd.h>

Plazza::Reception::Reception(Arguments &args) : _args(args), _receiverQueue(1), _kitchenQueues() {
    _receiverQueue.reset();
}

Plazza::Reception::~Reception()
{
    //must send a message to all kitchens to stop
    _receiverQueue.destroy();
    for (auto &kitchenQueue : _kitchenQueues) {
        kitchenQueue.destroy();
    }
}

static bool waitConfirmation(int id, MessageQueueIPC<std::string> &receiverQueue)
{
    while (1) {
        for (int i = 0; i < receiverQueue.size(); i++) {
            std::string message = receiverQueue[i];
            if (message == ("COK" + std::to_string(id)))
                return true;
            if (message == ("CKO" + std::to_string(id)))
                return false;
        }
    }
}

void Plazza::Reception::addOrder(command_t order)
{
    for (int i = 0; i < order.number; i++) {
        std::string pizzaOrder = std::to_string(order.type) + " " + std::to_string(order.size);
        for (auto &kitchenQueue : _kitchenQueues) {
            kitchenQueue.push(pizzaOrder);
            int id = kitchenQueue.getID();
            if (waitConfirmation(id, _receiverQueue)) {
                continue;
            }
        }
        createKitchen();
        _kitchenQueues.back().push(pizzaOrder);
    }
}

void Plazza::Reception::createKitchen()
{
    _kitchenQueues.emplace_back(_kitchenUid);
    _kitchenQueues.back().reset();
    _kitchenUid++;

    int pid = fork();
    if (pid == 0) {
        //Kitchen kitchen();
        //kitchen.run();
        std::cout << "Kitchen created" << std::endl;
        exit(0);
    }
}
