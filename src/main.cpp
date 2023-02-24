#include "fmt/core.h"

#include "Lexer.hpp"

int main()
{
    Lunasm::Lexer l = Lunasm::Lexer("ldi r1, [r2 + $05]");

    l.Tokenizer();

    return EXIT_SUCCESS;
}
