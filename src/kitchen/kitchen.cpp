/*
** EPITECH PROJECT, 2024
** kitchen.cpp
** File description:
** DESCRIPTION
*/

#include "kitchen.hpp"
#include <regex>

Kitchen::Kitchen(size_t nbCooks, size_t time) : _nbCooks(nbCooks), _timeToRestock(time)
{
    _stock = Stock();
    _lastRestock = std::chrono::system_clock::now();
}

Kitchen::~Kitchen() {}

void Kitchen::run()
{
    while (1) {
        std::chrono::system_clock::time_point actualRestock = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(actualRestock - _lastRestock).count() >= _timeToRestock) {
            _stock.restock();
            _lastRestock = actualRestock;
        }
        if (!_kitchenQueue.empty())
            this->handleCommands();
        manageCooks();
    }
}

/* ----------------- Stock ----------------- */

Kitchen::Stock::Stock()
    : dough(5), tomato(5), gruyere(5), ham(5), mushroom(5), steak(5), eggplant(5), goatCheese(5) {}

Kitchen::Stock::~Stock() {}

void Kitchen::Stock::restock()
{
    dough++;
    tomato++;
    gruyere++;
    ham++;
    mushroom++;
    steak++;
    eggplant++;
    goatCheese++;
    chiefLove++;
}

bool Kitchen::Stock::hasEnoughIngredient(Pizza pizza)
{
    return (dough >= _pizzaIngredients[pizza][Dough] && tomato >= _pizzaIngredients[pizza][Tomato] && gruyere >= _pizzaIngredients[pizza][Gruyere] && ham >= _pizzaIngredients[pizza][Ham] && mushroom >= _pizzaIngredients[pizza][Mushroom] && steak >= _pizzaIngredients[pizza][Steak] && eggplant >= _pizzaIngredients[pizza][Eggplant] && goatCheese >= _pizzaIngredients[pizza][Goatcheese] && chiefLove >= _pizzaIngredients[pizza][ChiefLove]);
}

void Kitchen::Stock::takeIngredient(Pizza pizza)
{
    dough -= _pizzaIngredients[pizza][Dough];
    tomato -= _pizzaIngredients[pizza][Tomato];
    gruyere -= _pizzaIngredients[pizza][Gruyere];
    ham -= _pizzaIngredients[pizza][Ham];
    mushroom -= _pizzaIngredients[pizza][Mushroom];
    steak -= _pizzaIngredients[pizza][Steak];
    eggplant -= _pizzaIngredients[pizza][Eggplant];
    goatCheese -= _pizzaIngredients[pizza][Goatcheese];
    chiefLove -= _pizzaIngredients[pizza][ChiefLove];
}

bool Kitchen::commandAreAvailable()
{
    return (_waitingCommands.size() + _inProgressCommands.size() < _nbCooks * 2);
}

void Kitchen::createCook()
{
    //_cooks->push_back(std::thread(&Kitchen::cook, this));
}

void Kitchen::handleCommands()
{
    std::string command = _kitchenQueue.pop();
    if (command == "status")
        this->status();
    else {
        try {
            std::regex commandRegex("");
            std::smatch match;
            if (std::regex_match(command, match, commandRegex)) {
                _waitingCommands.push_back(command);
            } else
                throw std::runtime_error("Invalid message queue command");
        } catch (std::exception &e) {
            throw std::runtime_error("Invalid message queue command");
        }
    }
}

void Kitchen::manageCooks()
{
}

void Kitchen::status()
{
    std::cout << "Kitchen of id: " << _id << ": " << std::endl;
    std::cout << "Stock: " << std::endl;
    std::cout << "\tDough: " << _stock.dough << std::endl;
    std::cout << "\tTomato: " << _stock.tomato << std::endl;
    std::cout << "\tGruyere: " << _stock.gruyere << std::endl;
    std::cout << "\tHam: " << _stock.ham << std::endl;
    std::cout << "\tMushroom: " << _stock.mushroom << std::endl;
    std::cout << "\tSteak: " << _stock.steak << std::endl;
    std::cout << "\tEggplant: " << _stock.eggplant << std::endl;
    std::cout << "\tGoat Cheese: " << _stock.goatCheese << std::endl;
    std::cout << "\tChief Love: " << _stock.chiefLove << std::endl;
    std::cout << "Number of commands: " << _waitingCommands.size() + _inProgressCommands.size() << std::endl;
    std::cout << "Number of cooks: " << _nbCooks << std::endl;
    for (size_t i = 0; i < _cooks.size(); i++) {
        // std::cout << "Cook " << i << " is ";
        // if (_cooks[i].getStatus() == Cook::WAITING)
        //     std::cout << "waiting" << std::endl;
        // else if (_cooks[i].getStatus() == Cook::COOKING)
        //     std::cout << "cooking" << std::endl;
    }
    _receptionQueue.push("OK" + std::to_string(_id));
}
