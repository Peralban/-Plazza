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
    for (auto &kitchenQueue : _kitchenQueues) {
        kitchenQueue.push("closing");
    }
    usleep(1000);
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

static bool isKitchenAlive(int id, MessageQueueIPC<std::string> &receiverQueue, std::vector<std::string> &receiverMessages)
{
    dumpReceiverQueue(receiverQueue, receiverMessages);
    for (size_t i = 0; i < receiverMessages.size(); i++) {
        if (receiverMessages[i] == ("closing" + std::to_string(id))) {
            receiverMessages.erase(receiverMessages.begin() + i);
            return false;
        }
    }
    return true;
}

static bool waitConfirmation(int id, MessageQueueIPC<std::string> &receiverQueue, std::vector<std::string> &receiverMessages)
{
    while (1) {
        dumpReceiverQueue(receiverQueue, receiverMessages);
        if (!isKitchenAlive(id, receiverQueue, receiverMessages)) {
            return false;
        }
        for (size_t i = 0; i < receiverMessages.size(); i++) {
            if (receiverMessages[i] == ("COK" + std::to_string(id))) {
                receiverMessages.erase(receiverMessages.begin() + i);
                return true;
            }
            if (receiverMessages[i] == ("CKO" + std::to_string(id))) {
                receiverMessages.erase(receiverMessages.begin() + i);
                return false;
            }
        }
        usleep(1000);
    }
}

void Plazza::Reception::addOrder(command_t order)
{
    std::cout << "--" << std::endl;

    for (int i = 0; i < order.number; i++) {

        for (int i = 0; i < _kitchenQueues.size(); i++) {
            if (!isKitchenAlive(_kitchenQueues[i].getID(), _receiverQueue, _receiverMessages)) {
                removeKitchen(_kitchenQueues[i].getID());
                i--;
            }
        }

        bool needNewKitchen = true;
        std::string pizzaOrder = std::to_string(order.type) + " " + std::to_string(order.size);
        std::string displayPizzaName = Plazza::DisplayPizzaName.at((Plazza::PizzaType)order.type);
        std::string displayPizzaSize = Plazza::DisplayPizzaSize.at((Plazza::PizzaSize)order.size);
        std::cout << "Reception: Adding order " << displayPizzaName << " " << displayPizzaSize <<  "." << std::endl;
        for (auto &kitchenQueue : _kitchenQueues) {
            kitchenQueue.push(pizzaOrder);
            int id = kitchenQueue.getID();
            if (waitConfirmation(id, _receiverQueue, _receiverMessages)) {
                std::cout << "Reception: Order added to kitchen " << id - 1 << "." << std::endl;
                needNewKitchen = false;
                break;
            }
            std::cout << "Reception: Kitchen " << id - 1 << " is full." << std::endl;
        }
        if (needNewKitchen) {
            createKitchen();
            usleep(1000);
            _kitchenQueues.back().push(pizzaOrder);
            waitConfirmation(_kitchenQueues.back().getID(), _receiverQueue, _receiverMessages);
            std::cout << "Reception: Order added to the new kitchen." << std::endl;
        }
    }
}

void Plazza::Reception::removeKitchen(int id)
{
    for (size_t i = 0; i < _kitchenQueues.size(); i++) {
        if (_kitchenQueues[i].getID() == id) {
            _kitchenQueues[i].push("closing");
            _kitchenQueues.erase(_kitchenQueues.begin() + i);
            std::cout << "Reception: Removing kitchen " << id - 1 << "." << std::endl;
            return;
        }
    }
}

static int getSmallestAvailableId(std::vector<MessageQueueIPC<std::string>> &kitchenQueues)
{
    int id = 2;
    for (auto &kitchenQueue : kitchenQueues) {
        if (id < kitchenQueue.getID()) {
            continue;
        } else {
            id = kitchenQueue.getID() + 1;
        }
    }
    return id;
}

void Plazza::Reception::createKitchen()
{
    int id = getSmallestAvailableId(_kitchenQueues);
    _kitchenQueues.emplace_back(id);
    _kitchenQueues.back().reset();

    std::cout << "Reception: Creating kitchen " << id - 1 << "." << std::endl;
    int pid = fork();
    if (pid == 0) {
        Kitchen kitchen(_args.getCookNumber(), _args.getRestockTime(), _args.getMultiplier(), id);
        kitchen.run();
        exit(84);
    }
}

static void waitStatus(int id, MessageQueueIPC<std::string> &receiverQueue, std::vector<std::string> &receiverMessages)
{
    while (1) {
        dumpReceiverQueue(receiverQueue, receiverMessages);
        if (!isKitchenAlive(id, receiverQueue, receiverMessages)) {
            return;
        }
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
