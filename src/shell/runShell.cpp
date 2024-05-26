/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
*/

#include "shellParser.hpp"
#include "Reception/Reception.hpp"

static Plazza::command_t parseOrder(std::string order)
{
    Plazza::command_t command;

    for (auto &pizzatype : Plazza::pizzaTypesMap)
        if (order.substr(0, pizzatype.first.size()) == pizzatype.first) {
            command.type = pizzatype.second;
            order = &order[pizzatype.first.size()];
        }
    if (order[0] == ' ')
        order = &order[1];
    else
        throw std::runtime_error("Invalid pizza type");
    for (auto &pizzasize : Plazza::pizzaSizesMap)
        if (order.substr(0, pizzasize.first.size()) == pizzasize.first) {
            command.size = pizzasize.second;
            order = &order[pizzasize.first.size()];
        }
    if (order[0] == ' ')
        order = &order[1];
    else
        throw std::runtime_error("Invalid pizza size");
    if (order[0] == 'x' && std::isdigit(order[1]))
        order = &order[1];
    else
        throw std::runtime_error("Invalid pizza number");
    command.number = std::stoi(order);
    return command;
}

int Shell::run(Plazza::Reception &reception)
{
    std::string input;
    std::getline(std::cin, input);

    while (!input.empty()) {
        Parser parser(input);
        while (parser.current_token.getType() != Token::END) {
            try {
                std::string order;
                parser.eat((Token::Type)(Token::TYPE | Token::STATUS));
                if (parser.current_token.getType() == Token::STATUS) {
                    parser.eat((Token::Type)(Token::SEMICOLON | Token::END));
                    reception.getStatus();
                    continue;
                }
                order += parser.current_token.getValue() + " ";
                parser.eat(Token::SIZE);
                order += parser.current_token.getValue() + " ";
                parser.eat(Token::NUMBER);
                order += parser.current_token.getValue();
                parser.eat((Token::Type)(Token::SEMICOLON | Token::END));
                reception.addOrder(parseOrder(order));
            }
            catch (std::runtime_error &e) {
                std::cerr << e.what() << std::endl;
                break;
            }
        }
        std::getline(std::cin, input);
    }
    return 0;
}
