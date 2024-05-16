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

namespace Shell {

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

        Token() : _type(INVALID), _value() {}
        Token(Type type, std::string value) : _type(type), _value(std::move(value)) {}
        Token(const Token &token) = default;
        Token &operator=(const Token &token) = default;

        [[ nodiscard]] Type getType() const { return _type; }
        [[ nodiscard]] std::string getValue() const { return _value; }

    private:
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
            Lexer() : _input(), _pos(0) {}
            explicit Lexer(std::string input) : _input(std::move(input)), _pos(0) {}

            Token getNextToken();

        private:
            std::string _input;
            size_t _pos{};

            [[ nodiscard ]] bool is_space() const { return _input[_pos] == ' ' || _input[_pos] == '\n' || _input[_pos] == '\t'; }
            [[ nodiscard ]] bool is_eof() const { return _pos >= _input.size(); }

            void skip_whitespace();

            Token parseSemicolon();
            Token parseType();
            Token parseSize();
            Token parseNumber();
            std::vector<Token (Lexer::*)()> _parsers = {&Lexer::parseSemicolon, &Lexer::parseSize, &Lexer::parseNumber, &Lexer::parseType};
        };

    private:
        Lexer _lexer;
    };

    int run();
}
