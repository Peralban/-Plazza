/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
*/

#include "shellParser.hpp"

Shell::Parser::Parser(std::string input)
{
    _lexer = Lexer(std::move(input));
    current_token = Token();
}

Shell::Token Shell::Parser::Lexer::getNextToken()
{
    if (!is_eof()) {
        if (is_space()) {
            skip_whitespace();
        }
        Token token;
        for (auto parser : _parsers) {
            token = (this->*parser)();
            if (token.getType() != Token::INVALID)
                return token;
        }
        return {Token::INVALID, ""};
    }
    return {Token::END, ""};
}

void Shell::Parser::Lexer::skip_whitespace()
{
    while (!is_eof() && is_space())
        _pos++;
}

Shell::Token Shell::Parser::Lexer::parseType()
{
    std::string type;
    while (!is_eof() && isalpha(_input[_pos])) {
        type += _input[_pos];
        _pos++;
    }
    return {Token::TYPE, type};
}

Shell::Token Shell::Parser::Lexer::parseSize()
{
    std::string size;

    for (const auto &s : sizes) {
        if (_input.substr(_pos, s.size()) == s && std::isblank(_input[_pos + s.size()])) {
            size = s;
            _pos += s.size();
            return {Token::SIZE, size};
        }
    }
    return {Token::INVALID, ""};
}

Shell::Token Shell::Parser::Lexer::parseNumber()
{
    std::string number;
    if (_input[_pos] == 'x') {
        number += _input[_pos];
        _pos++;
        while (!is_eof() && isdigit(_input[_pos])) {
            number += _input[_pos];
            _pos++;
        }
        return {Token::NUMBER, number};
    }
    return {Token::INVALID, ""};
}

Shell::Token Shell::Parser::Lexer::parseSemicolon()
{
    if (_input[_pos] == ';') {
        _pos++;
        return {Token::SEMICOLON, ";"};
    }
    return {Token::INVALID, ""};
}

void Shell::Parser::eat(Token::Type token_type)
{
    current_token = _lexer.getNextToken();
    if ((current_token.getType() & token_type) != 0)
        return;
    else
        throw InvalidToken("Invalid token");
}

int Shell::run()
{
    std::string input;
    std::getline(std::cin, input);

    while (!input.empty()) {
        Parser parser(input);
        while (parser.current_token.getType() != Token::END) {
            try {
                parser.eat(Token::TYPE);
                std::cout << "TYPE: " << parser.current_token.getValue() << std::endl;
                parser.eat(Token::SIZE);
                std::cout << "SIZE: " << parser.current_token.getValue() << std::endl;
                parser.eat(Token::NUMBER);
                std::cout << "NUMBER: " << parser.current_token.getValue() << std::endl;
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
