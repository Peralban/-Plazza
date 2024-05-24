/*
** EPITECH PROJECT, 2024
** kitchen.cpp
** File description:
** DESCRIPTION
*/

#include "kitchen.hpp"
#include "cook.hpp"

Kitchen::Kitchen(size_t nbCooks, size_t timeToRestock, size_t multi, std::shared_ptr<MessageQueueIPC<std::string>> kitchenQueue, std::shared_ptr<MessageQueueIPC<std::string>> receptionQueue)
    : _nbCooks(nbCooks), _commandNumber(0), _timeToRestock(timeToRestock), _multi(multi), _clockIsRunning(false), _kitchenQueue(kitchenQueue), _receptionQueue(receptionQueue)
{
    _stock = Stock();
    _messageQueue = std::make_shared<MessageQueueThread<std::string>>();
    for (size_t i = 0; i < nbCooks; i++)
        _cooks.push_back(std::make_shared<Cook>(_messageQueue));
}

Kitchen::~Kitchen() {}

bool Kitchen::commandAreAvailable()
{
    return _commandNumber != _nbCooks * 2;
}

bool Kitchen::update()
{
    size_t waiting_cook = 0;
    for (auto &cook : _cooks) {
        if (cook->getStatus() == Cook::WAITING)
            waiting_cook++;
    }
    if (waiting_cook == _nbCooks) {
        _clockIsRunning = true;
        if (_startClock == std::chrono::system_clock::time_point()) {
            _startClock = std::chrono::system_clock::now();
        } else {
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - _startClock;
            if (elapsed_seconds.count() >= 5)
                return false;
        }
    } else {
        _startClock = std::chrono::system_clock::time_point();
    }
    return true;
}

/* ----------------- Stock ----------------- */

Kitchen::Stock::Stock()
    : _dough(5), _tomato(5), _gruyere(5), _ham(5), _mushroom(5), _steak(5), _eggplant(5), _goatCheese(5) {}

Kitchen::Stock::~Stock() {}

void Kitchen::Stock::restock()
{
    _dough++;
    _tomato++;
    _gruyere++;
    _ham++;
    _mushroom++;
    _steak++;
    _eggplant++;
    _goatCheese++;
    _chiefLove++;
}

bool Kitchen::Stock::hasEnoughIngredient(Plazza::PizzaType pizza)
{
    return (_dough >= _pizzaIngredients[pizza][Dough] && _tomato >= _pizzaIngredients[pizza][Tomato] && _gruyere >= _pizzaIngredients[pizza][Gruyere] && _ham >= _pizzaIngredients[pizza][Ham] && _mushroom >= _pizzaIngredients[pizza][Mushroom] && _steak >= _pizzaIngredients[pizza][Steak] && _eggplant >= _pizzaIngredients[pizza][Eggplant] && _goatCheese >= _pizzaIngredients[pizza][Goatcheese] && _chiefLove >= _pizzaIngredients[pizza][ChiefLove]);
}

void Kitchen::Stock::takeIngredient(Plazza::PizzaType pizza)
{
    _dough -= _pizzaIngredients[pizza][Dough];
    _tomato -= _pizzaIngredients[pizza][Tomato];
    _gruyere -= _pizzaIngredients[pizza][Gruyere];
    _ham -= _pizzaIngredients[pizza][Ham];
    _mushroom -= _pizzaIngredients[pizza][Mushroom];
    _steak -= _pizzaIngredients[pizza][Steak];
    _eggplant -= _pizzaIngredients[pizza][Eggplant];
    _goatCheese -= _pizzaIngredients[pizza][Goatcheese];
    _chiefLove -= _pizzaIngredients[pizza][ChiefLove];
}
