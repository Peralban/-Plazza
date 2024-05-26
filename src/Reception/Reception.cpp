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

static void dumpReceiverQueue(MessageQueueIPC<std::string> &_receiverQueue, std::vector<std::string> &_receiverMessages)
{
    while (!_receiverQueue.empty()) {
        std::string message = _receiverQueue.pop();
        _receiverMessages.push_back(message);
    }
}

static bool waitConfirmation(int id, MessageQueueIPC<std::string> &receiverQueue, std::vector<std::string> &receiverMessages)
{
    while (1) {
        dumpReceiverQueue(receiverQueue, receiverMessages);
        for (size_t i = 0; i < receiverMessages.size(); i++) {
            if (receiverMessages[i] == ("SOK" + std::to_string(id))) {
                receiverMessages.erase(receiverMessages.begin() + i);
                return true;
            }
            if (receiverMessages[i] == ("SKO" + std::to_string(id))) {
                receiverMessages.erase(receiverMessages.begin() + i);
                return false;
            }
        }
    }

}

void Plazza::Reception::addOrder(command_t order)
{
    for (int i = 0; i < order.number; i++) {
        std::string pizzaOrder = std::to_string(order.type) + " " + std::to_string(order.size);
        std::cout << "Reception: Adding order " << pizzaOrder << std::endl;
        if (_kitchenQueues.empty()) {
            std::cout << "Reception: Creating kitchen" << std::endl;
            createKitchen();
            sleep(1);
        }
        for (auto &kitchenQueue : _kitchenQueues) {
            kitchenQueue.push(pizzaOrder);
            int id = kitchenQueue.getID();
            if (waitConfirmation(id, _receiverQueue, _receiverMessages)) {
                std::cout << "Reception: Order added to kitchen " << id << std::endl;
                break;
            }
            std::cout << "Reception: Kitchen " << id << " is full" << std::endl;
            std::cout << "Reception: Creating kitchen" << std::endl;
            createKitchen();
            sleep(1);
            _kitchenQueues.back().push(pizzaOrder);
        }
    }
}

void Plazza::Reception::createKitchen()
{
    _kitchenQueues.emplace_back(_kitchenUid);
    _kitchenQueues.back().reset();
    _kitchenUid++;

    int pid = fork();
    if (pid == 0) {
        std::cout << "Kitchen " << _kitchenUid - 1 << ": creation" << std::endl;
        Kitchen kitchen(_args.getCookNumber(), _args.getRestockTime(), _args.getMultiplier(), _kitchenUid - 1);
        kitchen.run();
        exit(0);
    }
}

static void waitStatus(int id, MessageQueueIPC<std::string> &receiverQueue, std::vector<std::string> &receiverMessages)
{
    while (1) {
        dumpReceiverQueue(receiverQueue, receiverMessages);
        for (size_t i = 0; i < receiverMessages.size(); i++) {
            if (receiverMessages[i] == ("SOK" + std::to_string(id))) {
                receiverMessages.erase(receiverMessages.begin() + i);
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
        waitStatus(id, _receiverQueue, _receiverMessages);
    }
}
