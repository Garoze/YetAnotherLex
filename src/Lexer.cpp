#include <cctype>
#include <vector>
#include <iostream>
#include <string_view>

#include "fmt/core.h"

#include "Lexer.hpp"
#include "Token.hpp"

namespace Lunasm {

Lexer::Lexer(const std::string& code)
{
    m_line = 1;
    m_index = 0;
    m_source_code = code;
}

void Lexer::step(void)
{
    m_index++;
}

void Lexer::skip(std::size_t n = 1)
{
    m_index += n;
}

void Lexer::skip(const std::string& msg)
{
    m_index++;
}

char Lexer::eat()
{
    return m_source_code.at(m_index++);
}

bool Lexer::is_empty(void) const
{
    return m_index >= m_source_code.length();
}

std::optional<char> Lexer::peek(std::size_t pos = 1)
{
    auto index = m_index + pos;

    if (index < m_source_code.length())
        return m_source_code.at(index);

    return {};
}

std::size_t Lexer::offset(std::size_t n = 0) const
{
    return m_index - n;
}

char Lexer::current_char(void) const
{
    return m_source_code.at(m_index);
}

L16Token Lexer::Immediate(void)
{
    if (!std::isxdigit(peek().value()))
    {
        fmt::print("Exception missing immediate after $");
        exit(1);
    }

    skip("Skipping the '$' character");

    std::size_t start = offset();

    while (!is_empty() && std::isxdigit(current_char()))
        step();

    std::string_view text(m_source_code.c_str() + start, offset(start));

    return L16Token(m_line, m_index, "Immediate", text);
}

L16Token Lexer::Register(void)
{
    skip("Skipping the 'r' character");

    switch (char n = eat())
    {
        case '0' ... '8': {
            std::string_view reg(m_source_code.c_str() + m_index - 2, 2);
            return L16Token(m_line, m_index, "Register", reg);
        }
        break;

        default:
            fmt::print("Invalid register\n");
            exit(1);
            break;
    }
}

L16Token Lexer::Identifier(void)
{
    std::size_t start = m_index;

    while (!is_empty() && std::isalnum(current_char()))
        step();

    std::size_t end = m_index - start;
    std::string_view text(m_source_code.c_str() + start, end);

    return L16Token(m_line, m_index, "Identifier", text);
}

L16Token Lexer::next_token()
{
    while (m_index < m_source_code.length())
    {
        switch (current_char())
        {
            case '[':
                step();
                return L16Token(m_line, m_index, "OpenBracket", "[");
                break;
            case ']':
                step();
                return L16Token(m_line, m_index, "CloseBracket", "[");
                break;
            case '+':
                step();
                return L16Token(m_line, m_index, "AddOperation", "+");
                break;
            case '-':
                step();
                return L16Token(m_line, m_index, "SubOperation", "-");
                break;
            case ',':
                step();
                return L16Token(m_line, m_index, "Comma", ",");
                break;
            case ' ':
            case '\t': skip(); break;
            case '\n':
                m_line++;
                skip();
                break;
            case '$': return Immediate(); break;
            case 'r': return Register(); break;
            default: return Identifier(); break;
        }
    }

    fmt::print("Line: {} Offset: {} Char: {}\n", m_line, m_index, current_char());
    exit(1);
}

std::vector<L16Token> Lexer::Tokenizer(void)
{
    std::vector<L16Token> tokens;

    while (m_index < m_source_code.length())
    {
        auto t = next_token();
        tokens.push_back(t);
    }

    tokens.push_back(L16Token(m_line, m_index, "EOF", "EOF"));

    return tokens;
}

}  // namespace Lunasm
