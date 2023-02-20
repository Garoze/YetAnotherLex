#include <cctype>
#include <string_view>

#include "fmt/core.h"

#include "Lexer.hpp"

namespace Lunasm {

Lexer::Lexer(const std::string& code)
{
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

void Lexer::Immediate(void)
{
    if (!std::isxdigit(peek().value()))
    {
        fmt::print("Exception missing immediate after $");
    }

    skip("Skipping the '$' character");

    std::size_t start = offset();

    while (!is_empty() && std::isxdigit(current_char()))
        step();

    std::string_view text(m_source_code.c_str() + start, offset(start));
    fmt::print("Immediate {}\n", text);
}

void Lexer::Register(void)
{
    skip("Skipping the 'r' character");

    switch (char n = eat())
    {
        case '0' ... '8': fmt::print("Register r{}\n", n); break;
        default: fmt::print("Invalid register\n"); break;
    }
}

void Lexer::Identifier(void)
{
    std::size_t start = m_index;

    while (!is_empty() && std::isalnum(current_char()))
        step();

    std::size_t end = m_index - start;
    std::string_view text(m_source_code.c_str() + start, end);
    fmt::print("Identifier {}\n", text);
}

void Lexer::Tokenizer(void)
{
    while (m_index < m_source_code.length())
    {
        switch (current_char())
        {
            case '[':
                fmt::print("Open bracket {}\n", current_char());
                step();
                break;
            case ']':
                fmt::print("Close bracket {}\n", current_char());
                step();
                break;
            case '(':
                fmt::print("Open paren {}\n", current_char());
                step();
                break;
            case ')':
                fmt::print("Close paren {}\n", current_char());
                step();
                break;
            case '+':
                fmt::print("Plus {}\n", current_char());
                step();
                break;
            case '-':
                fmt::print("Minus {}\n", current_char());
                step();
                break;
            case '*':
                fmt::print("Mult {}\n", current_char());
                step();
                break;
            case '/':
                fmt::print("Div {}\n", current_char());
                step();
                break;
            case ':':
                fmt::print("Colon {}\n", current_char());
                step();
                break;
            case ',':
                fmt::print("Comma {}\n", current_char());
                step();
                break;
            case '$': Immediate(); break;
            case 'r': Register(); break;
            case ' ':
            case '\t': skip(); break;
            case '\n': /* m_line++ */ skip(); break;
            default: Identifier(); break;
        }
    }
}

}  // namespace Lunasm
