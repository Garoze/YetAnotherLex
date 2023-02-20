#pragma once

#include <optional>
#include <string>

namespace Lunasm {

class Lexer
{
public:
    Lexer(const std::string&);
    void step(void);
    void skip(std::size_t);
    void skip(const std::string&);
    char current_char(void) const;
    void Tokenizer(void);
    void Immediate(void);
    void Identifier(void);
    void Register(void);
    char eat(void);
    std::size_t offset(std::size_t) const;
    std::optional<char> peek(std::size_t);
    bool is_empty(void) const;

private:
    std::size_t m_index;
    std::string m_source_code;
};

}  // namespace Lunasm
