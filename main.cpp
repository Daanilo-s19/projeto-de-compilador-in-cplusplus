#include <iostream>
#include <fstream>
#include "lexico.h"
#include "sintatico.h"
//#include "sintatico.cpp"

using namespace std;

// DRIVER FUNCTION
int main()
{

    ifstream arq("teste.txt"); // LEITURA DO ARQUIVO
    if (!arq.is_open())
    {
        cout << "DEU RUIM\n";
        return EXIT_FAILURE;
    }
    try
    {
        std::cout << "\n\n*ANALISE LEXICA*\n\n";
        auto tokens = getTokens(arq); // RETORNO DOS TOKENS E SEUS RESPECTIVOS ENUM

        std::cout << "\n\n*ANALISE SINTATICA*\n\n";
        syntatic(tokens);
        std::cout << "*\n\nFIM DA ANALISE SINTATICA*\n\n";
    }
    catch (exception &e)
    {
        cout << e.what() << '\n';
        return 1;
    }
    cin.get();
    return 0;
}
//g++ *.cpp -g
// ./a.exe