#pragma once

#include <string_view>

namespace Lunasm {

class L16Token
{
public:
    L16Token(std::size_t l, std::size_t o, std::string k, std::string_view t);
    std::string kind() const;

public:
    void print() const;

private:
    std::size_t m_line;
    std::size_t m_offset;
    std::string m_kind;
    std::string_view m_text;
};

}  // namespace Lunasm
