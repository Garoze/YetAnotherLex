#pragma once

#include <string>
#include <string_view>

namespace Lunasm {

class L16Token
{
public:
    L16Token(std::size_t line, std::size_t offset, std::string kind, std::string_view text);

public:
    void print() const;

private:
    std::size_t m_line;
    std::size_t m_offset;
    std::string m_kind;
    std::string_view m_text;
};

}  // namespace Lunasm
