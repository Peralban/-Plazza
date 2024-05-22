/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
*/

#include "shellParser.hpp"
#include "messageQueue/messageQueueIPC.hpp"

int Shell::run(Plazza::Arguments &args)
{
    MessageQueueIPC<std::string> receiverQueue(1);
    std::vector<MessageQueueIPC<std::string>> kitchenQueues;

    std::string input;
    std::getline(std::cin, input);
    (void)args;

    while (!input.empty()) {
        Parser parser(input);
        while (parser.current_token.getType() != Token::END) {
            try {
                parser.eat(Token::TYPE);
                std::cerr << "TYPE: " << parser.current_token.getValue() << std::endl;
                parser.eat(Token::SIZE);
                std::cerr << "SIZE: " << parser.current_token.getValue() << std::endl;
                parser.eat(Token::NUMBER);
                std::cerr << "NUMBER: " << parser.current_token.getValue() << std::endl;
                parser.eat((Token::Type)(Token::SEMICOLON | Token::END));
                //do something with the tokens
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
