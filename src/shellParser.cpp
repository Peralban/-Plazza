/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
*/

#include "shellParser.hpp"

Parser::Parser(std::string input)
{
    _lexer = Lexer(std::move(input));
    current_token = Token();
}

Token Parser::Lexer::get_next_token()
{
    if (!is_eof()) {
        if (is_space()) {
            skip_whitespace();
        }
        Token token;
        for (auto parser : _parsers) {
            token = (this->*parser)();
            if (token._type != Token::INVALID)
                return token;
        }
        return {Token::INVALID, ""};
    }
    return {Token::END, ""};
}

void Parser::Lexer::skip_whitespace()
{
    while (!is_eof() && is_space())
        _pos++;
}

Token Parser::Lexer::parse_type()
{
    std::string type;
    while (!is_eof() && isalpha(_input[_pos])) {
        type += _input[_pos];
        _pos++;
    }
    return {Token::TYPE, type};
}

std::string sizes[] = {"S", "M", "L", "XL", "XXL"};

Token Parser::Lexer::parse_size()
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

Token Parser::Lexer::parse_number()
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

Token Parser::Lexer::parse_semicolon()
{
    if (_input[_pos] == ';') {
        _pos++;
        return {Token::SEMICOLON, ";"};
    }
    return {Token::INVALID, ""};
}

void Parser::eat(Token::Type token_type)
{
    current_token = _lexer.get_next_token();
    if ((current_token._type & token_type) != 0)
        return;
    else
        throw InvalidToken("Invalid token");
}

int shell()
{
    std::string input;
    std::getline(std::cin, input);

    while (!input.empty()) {
        Parser parser(input);
        while (parser.current_token._type != Token::END) {
            try {
                parser.eat(Token::TYPE);
                std::cout << "TYPE: " << parser.current_token._value << std::endl;
                parser.eat(Token::SIZE);
                std::cout << "SIZE: " << parser.current_token._value << std::endl;
                parser.eat(Token::NUMBER);
                std::cout << "NUMBER: " << parser.current_token._value << std::endl;
                parser.eat((Token::Type)(Token::SEMICOLON | Token::END));
            }
            catch (Parser::InvalidToken &e) {
                std::cerr << e.what() << std::endl;
                return 84;
            }
        }
        std::getline(std::cin, input);
    }
    return 0;
}
