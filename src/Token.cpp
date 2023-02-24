#include "fmt/core.h"

#include "Token.hpp"

namespace Lunasm {

L16Token::L16Token(std::size_t line, std::size_t offset, std::string kind, std::string_view text)
{
    m_line = line;
    m_offset = offset;
    m_kind = kind;
    m_text = text;
}

void L16Token::print() const
{
    fmt::print("Token( T: {:8} Kind: {:18} Line: {:2}, Offset: {:d} )\n", m_text, m_kind, m_line, m_offset);
}

}  // namespace Lunasm
