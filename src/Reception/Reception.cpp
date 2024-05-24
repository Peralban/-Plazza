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

void Plazza::Reception::addOrder(const std::string &order)
{
    for (auto &kitchenQueue : _kitchenQueues) {
        if (kitchenQueue.size() < _args.getCookNumber() * 2) {
            kitchenQueue.push(order);
            return;
        }
    }
    createKitchen();
    _kitchenQueues.back().push(order);
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

void Plazza::Reception::getStatus()
{
    //for (auto &kitchenQueue : _kitchenQueues) {
    //    std::cout << "Kitchen " << kitchenQueue.getID() - 1 << ": " << kitchenQueue.size() << " orders" << std::endl;
    //}
}
