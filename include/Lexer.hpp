#pragma once

#include <optional>
#include <string>
#include <vector>

#include "Token.hpp"

namespace Lunasm {

class Lexer
{
public:
    Lexer(const std::string&);

    std::vector<L16Token> Tokenizer(void);

private:
    L16Token next_token(void);

private:
    L16Token Immediate(void);
    L16Token Identifier(void);
    L16Token Register(void);

private:
    void step(void);
    void skip(std::size_t);
    void skip(const std::string&);
    char eat(void);

private:
    bool is_empty(void) const;
    std::optional<char> peek(std::size_t);
    std::size_t offset(std::size_t) const;

    char current_char(void) const;

private:
    std::size_t m_line;
    std::size_t m_index;
    std::string m_source_code;
};

}  // namespace Lunasm
