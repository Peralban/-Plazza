/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include <vector>
#include "Reception/Reception.hpp"

// TYPE := [ a .. zA .. Z ]+
// SIZE := S | M | L | XL | XXL
// NUMBER := x [1..9][0..9]*

namespace Shell {

    /**
     * @brief Array of valid sizes.
     * The sizes are represented as strings.
     */
    static const std::string sizes[] = {"S", "M", "L", "XL", "XXL"};

    /**
     * @class Token
     * @brief This class represents a token.
     * It contains the type of the token and its value.
     * The type is a bitfield.
     * The value is a string.
     * The type can be TYPE, SIZE, NUMBER, SEMICOLON, END or INVALID.
     * The value is the string that the token represents.
     */
    class Token {
    public:
        /**
         * @enum Type
         * @brief Enumerates the possible types of tokens.
         *
         * This enumeration is used to represent the type of a token. The possible types are:
         * TYPE, SIZE, NUMBER, SEMICOLON, END, INVALID.
         */
        enum Type {
            TYPE = 1,      /**< Represents a type token. */
            SIZE = 2,      /**< Represents a size token. */
            NUMBER = 4,    /**< Represents a number token. */
            SEMICOLON = 8, /**< Represents a semicolon token. */
            END = 16,      /**< Represents an end token. */
            INVALID = 0    /**< Represents an invalid token. */
        };

        /**
         * @brief Default constructor for the Token class.
         *
         * This constructor initializes a Token object with INVALID type and an empty value.
         */
        Token() : _type(INVALID), _value() {}

        /**
         * @brief Constructor for the Token class.
         * @param type The type of the token.
         * @param value The value of the token.
         *
         * This constructor initializes a Token object with the given type and value.
         */
        Token(Type type, std::string value) : _type(type), _value(std::move(value)) {}

        /**
         * @brief Copy constructor for the Token class.
         * @param token The token to be copied.
         *
         * This constructor creates a new Token object that is a copy of the given token.
         */
        Token(const Token &token) = default;

        /**
         * @brief Copy assignment operator for the Token class.
         * @param token The token to be copied.
         * @return A reference to the token object.
         *
         * This operator assigns the values of the given token to the token object.
         */
        Token &operator=(const Token &token) = default;

        /**
         * @brief Getter for the type of the token.
         * @return The type of the token.
         *
         * This function returns the type of the token.
         */
        [[ nodiscard ]] Type getType() const { return _type; }

        /**
         * @brief Getter for the value of the token.
         * @return The value of the token.
         *
         * This function returns the value of the token.
         */
        [[ nodiscard ]] std::string getValue() const { return _value; }

    private:
        Type _type;
        std::string _value;
    };

    /**
     * @class Parser
     * @brief This class is responsible for parsing the input string into tokens.
     *
     * The Parser class uses a Lexer object to tokenize the input string. It then processes these tokens
     * according to the rules of the grammar. The current token being processed is stored in the
     * current_token member variable.
     *
     * The Parser class also defines an exception class, InvalidToken, which is thrown when an unexpected
     * token is encountered during the parsing process.
     */
    class Parser {
    public:
        /**
         * @brief Current token being processed by the parser.
         */
        Token current_token;

        /**
         * @brief Constructor for the Parser class.
         * @param input The string to be parsed.
         */
        explicit Parser(std::string input) : current_token(Token()), _input(std::move(input)), _pos(0) {}

        /**
         * @brief Consumes the current token if its type matches the given token type.
         * @param token_type The expected type of the current token.
         * @throws InvalidToken If the current token's type does not match the given token type.
         */
        void eat(Token::Type token_type);

        /**
         * @class InvalidToken
         * @brief Exception class for invalid tokens.
         * Inherits from std::runtime_error.
         */
        class InvalidToken : public std::runtime_error {
        public:
            /**
             * @brief Constructor for the InvalidToken class.
             * @param message The error message.
             */
            explicit InvalidToken(const std::string &message) : std::runtime_error(message) {}
        };

    private:
        std::string _input;
        size_t _pos;

        Token getNextToken();

        [[ nodiscard ]] bool is_space() const { return _input[_pos] == ' ' || _input[_pos] == '\n' || _input[_pos] == '\t'; }
        [[ nodiscard ]] bool is_eof() const { return _pos >= _input.size(); }

        void skip_whitespace();

        Token parseSemicolon();
        Token parseType();
        Token parseSize();
        Token parseNumber();
        std::vector<Token (Parser::*)()> _parsers = {&Parser::parseSemicolon, &Parser::parseSize, &Parser::parseNumber, &Parser::parseType};
    };

    /**
     * @brief This function is the entry point for the Shell namespace.
     * It is responsible for initiating the parsing process.
     * @return an integer indicating the success or failure of the operation.
     * A return value of 0 typically indicates success, while any other value indicates failure.
     */
    int run(Plazza::Reception &reception);
}
