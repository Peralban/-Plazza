/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
*/

#include "shellParser.hpp"
#include "messageQueue/messageQueueIPC.hpp"

int Shell::run(Plazza::Reception &reception)
{

    std::string input;
    std::getline(std::cin, input);

    while (!input.empty()) {
        Parser parser(input);
        while (parser.current_token.getType() != Token::END) {
            try {
                std::string order;
                parser.eat(Token::TYPE);
                order += parser.current_token.getValue() + "=";
                parser.eat(Token::SIZE);
                order += parser.current_token.getValue() + "=";
                parser.eat(Token::NUMBER);
                order += parser.current_token.getValue();
                parser.eat((Token::Type)(Token::SEMICOLON | Token::END));
                reception.addOrder(order);
            }
            catch (Shell::Parser::InvalidToken &e) {
                std::cerr << e.what() << std::endl;
                return 84;
            }
        }
        std::getline(std::cin, input);
    }
    return 0;
}
