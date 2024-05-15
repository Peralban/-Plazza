/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include <iostream>
#include <vector>

// TYPE := [ a .. zA .. Z ]+
// SIZE := S | M | L | XL | XXL
// NUMBER := x [1..9][0..9]*

class Token {
public:
    enum Type {
        TYPE = 1,
        SIZE = 2,
        NUMBER = 4,
        SEMICOLON = 8,
        END = 16,
        INVALID = 0
    };

    Token() : _type(INVALID), _value("") {}
    Token(Type type, std::string value) : _type(type), _value(std::move(value)) {}
    Token(const Token &token) : _type(token._type), _value(token._value) {}
    Token &operator=(const Token &token)
    {
        if (this != &token) {
            _type = token._type;
            _value = token._value;
        }
        return *this;
    }

    Type _type;
    std::string _value;
};

class Parser {
public:
    Token current_token;

    explicit Parser(std::string input);

    void eat(Token::Type token_type);

    class InvalidToken : public std::runtime_error {
    public:
        explicit InvalidToken(const std::string &message) : std::runtime_error(message) {}
    };

    class Lexer {
    public:
        Lexer() = default;
        explicit Lexer(std::string input) : _input(std::move(input)), _pos(0) {}

        Token get_next_token();

    private:
        std::string _input;
        size_t _pos;

        [[ nodiscard ]] bool is_space() const { return _input[_pos] == ' ' || _input[_pos] == '\n' || _input[_pos] == '\t'; }
        [[ nodiscard ]] bool is_eof() const { return _pos >= _input.size(); }

        void skip_whitespace();

        Token parse_semicolon();
        Token parse_type();
        Token parse_size();
        Token parse_number();
        std::vector<Token (Lexer::*)()> _parsers = {&Lexer::parse_semicolon, &Lexer::parse_size, &Lexer::parse_number, &Lexer::parse_type};
    };

private:
    Lexer _lexer;
};
