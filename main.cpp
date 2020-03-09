#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <list>
#include "lexico.cpp"
#include "sintatico.cpp"

using namespace std;

// DRIVER FUNCTION
int main()
{

    FILE *arq;
    char Linha[100];
    char *str;
    list<pair<Token, string>> tokens;
    int i;

    arq = fopen("teste.txt", "rt");
    if (arq == NULL) // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
        return 0;
    }
    i = 1;
    while (!feof(arq))
    {
        str = fgets(Linha, 100, arq);

        tokens = token(str);

        i++;
    }
    fclose(arq);

    for (const auto &p : tokens)
    {
        std::cout << p.first << ", " << p.second << std::endl;
        // or std::cout << std::get<0>(p) << ", " << std::get<1>(p) << std::endl;
    }
    // syntatic(tokens);

    getchar();
    return (0);
}