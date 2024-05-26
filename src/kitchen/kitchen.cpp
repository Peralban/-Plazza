/*
** EPITECH PROJECT, 2024
** kitchen.cpp
** File description:
** DESCRIPTION
*/

#include "kitchen.hpp"
#include <unistd.h>
#include <regex>

Kitchen::Kitchen(size_t nbCooks, size_t time, double multiplier, size_t id):
    _nbCooks(nbCooks), _timeToRestock(time), _multiplier(multiplier), _id(id), _kitchenQueue((int)id), _receptionQueue(1)
{
    //for (size_t i = 0; i < nbCooks; i++) {
    //    std::shared_ptr<Cook> cook = std::make_shared<Cook>(std::ref(_cooksQueue[i]), multiplier);
    //    _cooks.push_back(cook);
    //}
    _stock = Stock();
    _lastRestock = std::chrono::system_clock::now();
    _startClock = std::chrono::system_clock::time_point();
    std::cout << "Kitchen " << id << ": created" << std::endl;
}

Kitchen::~Kitchen() {}

void Kitchen::run()
{
    while (1) {
        std::chrono::system_clock::time_point actualRestock = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(actualRestock - _lastRestock).count() >= (long int)_timeToRestock) {
            _stock.restock();
            _lastRestock = actualRestock;
        }
        if (!_kitchenQueue.empty()) {
            try {
                this->handleCommands();
            } catch (std::exception &e) {
                throw std::runtime_error("Error while handling commands");
            }
        }
        manageWaitingCommands();
    }
}

/* ----------------- Stock ----------------- */

Kitchen::Stock::Stock()
    : dough(5), tomato(5), gruyere(5), ham(5), mushroom(5), steak(5), eggplant(5), goatCheese(5), chiefLove(5) {}

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

bool Kitchen::Stock::hasEnoughIngredient(Plazza::PizzaType pizza)
{
    return (dough >= _pizzaIngredients[pizza][Dough] && tomato >= _pizzaIngredients[pizza][Tomato] && gruyere >= _pizzaIngredients[pizza][Gruyere] && ham >= _pizzaIngredients[pizza][Ham] && mushroom >= _pizzaIngredients[pizza][Mushroom] && steak >= _pizzaIngredients[pizza][Steak] && eggplant >= _pizzaIngredients[pizza][Eggplant] && goatCheese >= _pizzaIngredients[pizza][Goatcheese] && chiefLove >= _pizzaIngredients[pizza][ChiefLove]);
}

void Kitchen::Stock::takeIngredient(Plazza::PizzaType pizza)
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

Pizza Kitchen::Stock::getPizzaFromString(std::string &pizza)
{
    Pizza result;

    result.first = (Plazza::PizzaType)(std::stoi(pizza.substr(0, pizza.find(' '))));
    result.second = (Plazza::PizzaSize)(std::stoi(pizza.substr(pizza.find(' ') + 1, pizza.length() - pizza.find(' ') - 1)));

    return result;
}

/* -----------------/ Stock /----------------- */

bool Kitchen::commandAreAvailable()
{
    return (_waitingCommands.size() + getNbCooksWorking() < _nbCooks * 2);
}

void Kitchen::handleCommands()
{
    std::string command = _kitchenQueue.pop();
    if (command == "status")
        this->status();
    else {
        try {
            Pizza pizza = _stock.getPizzaFromString(command);
            if (_stock.hasEnoughIngredient(pizza.first)) {
                _stock.takeIngredient(pizza.first);
                _waitingCommands.push_back(command);
                std::cout << "Kitchen " << _id << ": Command " << command << " accepted" << std::endl;
                _receptionQueue.push("COK" + std::to_string(_id));
            } else {
                std::cout << "Kitchen " << _id << ": Command " << command << " denied" << std::endl;
                _receptionQueue.push("CKO" + std::to_string(_id));
            }
        } catch (std::exception &e) {
            throw std::runtime_error("Invalid pizza type");
        }
    }
}

void Kitchen::status()
{
    std::cout << "Kitchen " << _id << ": " << std::endl;
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
    std::cout << "Number of commands: " << _waitingCommands.size() + getNbCooksWorking() << std::endl;
    std::cout << "Number of cooks: " << _nbCooks << std::endl;
    for (size_t i = 0; i < _cooks.size(); i++) {
        std::cout << "Cook " << i << " is ";
        if (_cooks[i]->getStatus() == Cook::WAITING)
            std::cout << "waiting" << std::endl;
        else if (_cooks[i]->getStatus() == Cook::COOKING)
            std::cout << "cooking" << std::endl;
    }
    _receptionQueue.push("SOK" + std::to_string(_id));
}

void Kitchen::manageWaitingCommands()
{
    for (size_t i = 0; i < _cooks.size(); i++) {
        for (size_t j = 0; j < _waitingCommands.size(); j++) {
            if (_cooks[i]->getStatus() == Cook::WAITING) {
                _cooksQueue[i].push(_waitingCommands[j]);
                _waitingCommands.erase(_waitingCommands.begin() + j);
                break;
            }
        }
    }
}

size_t Kitchen::getNbCooksWorking()
{
    size_t nb = 0;
    for (size_t i = 0; i < _cooks.size(); i++) {
        if (_cooks[i]->getStatus() == Cook::COOKING)
            nb++;
    }
    return nb;
}

bool Kitchen::update()
{
    size_t workingCooks = getNbCooksWorking();

    if (!workingCooks) {
        if (_startClock == std::chrono::system_clock::time_point())
            _startClock = std::chrono::system_clock::now();
        else {
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - _startClock;
            if (elapsed_seconds.count() >= 5)
                return false;
        }
    } else
        _startClock = std::chrono::system_clock::time_point();
    return true;
}
