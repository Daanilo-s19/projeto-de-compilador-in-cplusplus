// #include <stdio.h>
// #include <iostream>
// #include <string.h>
// #include <stdlib.h>
// #include <ctype.h>
// #include <string>
// #include <iostream>
// #include <map>
// #include <stack>
// using std::string;
#include "sintatico.h"
#include "lexico.h"
#include <iostream>
#include <stack>

using namespace std;

void syntatic(vector<pair<Token, string>> &tokens)
{
    vector<vector<int>> table{
        {3, 3},
        {4, 4},
        {5, 5}};
    stack<Token> pilha{{Token::$, Token::PROGRAMA}};
    size_t index = 0;
    while (pilha.size())
    {
        auto &token = tokens[index].first;
        auto topo = pilha.top();
        if (token == topo)
        {
            //bateu
            cout << "parser: topo bateu com o token lido do lexico\n";
            ++index;
            pilha.pop();
        }
        else
        {
            auto regra = table[topo][token];
            if (regra)
            {
            }
            else
            {
                throw invalid_argument("ta fazendo merda...");
            }
        }
    }
}

//     map<Token, map<Token, int>> table;
//     stack<Token> symbolStack; // symbol stack
//     char *p;                  // input buffer

//     // initialize the symbols stack
//     symbolStack.push(Token::FIM_ARQ);  // terminal, $
//     symbolStack.push(Token::PROGRAMA); // non-terminal, S

//     // set up the parsing table
//     table[NTS_S][TS_L_PARENS] = 2;
//     table[NTS_S][TS_A] = 1;
//     table[NTS_F][TS_A] = 3;

//     while (symbolStack.size())
//     {
//         const auto topo = symbolStack.top();

//         switch (table[symbolStack.top()][lexer(*p)])
//         {
//         case 1: // 1. S → F
//             symbolStack.pop();
//             symbolStack.push(NTS_F); // F
//             break;

//         case 2: // 2. S → ( S + F )
//             symbolStack.pop();
//             symbolStack.push(TS_R_PARENS); // )
//             symbolStack.push(NTS_F);       // F
//             symbolStack.push(TS_PLUS);     // +
//             symbolStack.push(NTS_S);       // S
//             symbolStack.push(TS_L_PARENS); // (
//             break;

//         case 3: // 3. F → a
//             symbolStack.pop();
//             symbolStack.push(TS_A); // a
//             break;

//         default:
//             cout << "parsing table defaulted" << endl;
//             return 0;
//             break;
//         }
//     }
// }
