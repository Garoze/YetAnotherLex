#include "fmt/core.h"

#include "Lexer.hpp"

int main()
{
    Lunasm::Lexer l = Lunasm::Lexer("ldi, r1 $05\nldi r2, $10");

    l.Tokenizer();

    return EXIT_SUCCESS;
}
