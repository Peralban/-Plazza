/*
** EPITECH PROJECT, 2024
** kitchen.hpp
** File description:
** DESCRIPTION
*/

#pragma once

#include <iostream>
#include <list>
#include <thread>
#include <map>
#include <functional>

class Kitchen {
    public:
        Kitchen();
        ~Kitchen();

        bool commandAreAvailable();

        void createCook();

    private:
        class Stock {
        public:
            Stock();
            ~Stock();

            enum Ingredients {
                Dough,
                Tomato,
                Gruyere,
                Ham,
                Mushroom,
                Steak,
                Eggplant,
                Goatcheese
                ChiefLove
            };

            enum Pizza {
                Regina,
                Margarita,
                Americana,
                Fantasia
            };

            void restock();

            bool hasEnoughIngredient(Pizza pizza);

            void takeIngredient(Pizza pizza);

        private:
            size_t _dough;
            size_t _tomato;
            size_t _gruyere;
            size_t _ham;
            size_t _mushroom;
            size_t _steak;
            size_t _eggplant;
            size_t _goatcheese;
            size_t _chiefLove;

            std::map<Kitchen::Stock::Pizza, std::map<Ingredients, size_t>> _pizzaIngredients = {
                {Regina, {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}, {Ham, 1}, {Mushroom, 1}}},
                {Margarita, {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}}},
                {Americana, {{Dough, 1}, {Tomato, 1}, {Gruyere, 1}, {Steak, 1}}},
                {Fantasia, {{Dough, 1}, {Tomato, 1}, {Eggplant, 1}, {Goatcheese, 1}, {ChiefLove, 1}}}
            };
        };
        size_t _nbCooks;
        size_t _commandNumber;
        std::list<std::thread> _cooks;
        size_t _timeToRestock;
        Stock _stock;
};