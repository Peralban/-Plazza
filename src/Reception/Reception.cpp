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

static void wait_status(int id, MessageQueueIPC<std::string> &receiverQueue)
{
    while (1) {
        for (int i = 0; i < receiverQueue.size(); i++) {
            std::string message = receiverQueue[i];
            if (message == ("SOK" + std::to_string(id))) {
                return;
            }
        }
    }
}

void Plazza::Reception::getStatus()
{
    for (auto &kitchenQueue : _kitchenQueues) {
        kitchenQueue.push("status");
        int id = kitchenQueue.getID();
        wait_status(id, _receiverQueue);
    }
}
