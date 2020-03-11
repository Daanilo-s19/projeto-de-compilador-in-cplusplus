// #include <stdio.h>
// #include <iostream>
// #include <string.h>
// #include <stdlib.h>
// #include <ctype.h>
// #include <string>
// #include <iostream>
#include <map>
// #include <stack>
// using std::string;
#include "sintatico.h"
#include "lexico.h"
#include <iostream>
#include <stack>

using namespace std;

void syntatic(vector<pair<Token, string>> &tokens)
{

    map<Token, map<Token, unsigned>> table{
        // REGRAS DA PARSER TABLE QUE SEGUE NO DOCUMENTO
        {Token::PROGRAMA,
         {{Token::ID, 1}, {Token::TIPO, 1}, {Token::SE, 1}, {Token::ENQUANTO, 1}, {Token::PNTVIRGULA, 1}}},
        {Token::BLOCO,
         {{Token::ID, 2}, {Token::TIPO, 2}, {Token::SE, 2}, {Token::ENQUANTO, 2}, {Token::PNTVIRGULA, 2}}},
        {Token::CMD,
         {{Token::ID, 3}, {Token::TIPO, 3}, {Token::SE, 4}, {Token::ENQUANTO, 5}, {Token::PNTVIRGULA, 3}}},
        {Token::SE,
         {{Token::SE, 4}}},
        {Token::ENQUANTO,
         {{Token::ENQUANTO, 5}}},
        {Token::ENTAO,
         {{Token::ENTAO, 6}}},
        {Token::EXPRESSAO,
         {{Token::TIPO, 7}, {Token::VALOR, 8}, {Token::NEGACAO, 9}, {Token::ABRE_PARENTESE, 10}}},
        {Token::ATRIB,
         {{Token::TIPO, 11}, {Token::ID, 12}}},

    };

    stack<Token>
        pilha{{Token::$, Token::PROGRAMA}}; // ADICIONA O $ NO INICIO DA PILHA
    size_t index = 0;
    while (pilha.size()) // ENQUANTO TIVER PILHA FAÇA REALIZE A VERIFICÃO DA PARSER TABLE
    {
        auto &token = tokens[index].first;
        auto topo = pilha.top();
        // cout << "parser:" << topo << '\n';
        // cin.get();
        if (token == topo) // HOUVE MATCH ENTRE O TOPO DA PILHA E O TOKEN LIDO
        {
            //bateu
            cout << "parser: topo bateu com o token lido do lexico" << token << "==" << topo << '\n';
            ++index;
            pilha.pop();
        }
        else
        {
            auto regra = table[topo][token];

            switch (regra)
            {
            case 1: //PROGRAMA ->CMD PROGRAMA
                pilha.push(Token::PROGRAMA);
                pilha.push(Token::CMD);
                break;
            case 2: //BLOCO -> PROGRAMA
                pilha.push(Token::PROGRAMA);
                break;
            case 3: //CMD ->  ATRIB ';'
                pilha.push(Token::PNTVIRGULA);
                pilha.push(Token::ATRIB);
                break;
            case 4: //SE ->‘se‘ EXPRESSAO ‘faça’ BLOCO SENAO  ‘acabou’
                pilha.push(Token::ACABOU);
                pilha.push(Token::ENTAO);
                pilha.push(Token::BLOCO);
                pilha.push(Token::FACA);
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::SE);
                break;
            case 5: //ENQUANTO -> ‘enquanto’  EXPRESSAO ‘faça’ BLOCO  ‘acabou’
                pilha.push(Token::ACABOU);
                pilha.push(Token::BLOCO);
                pilha.push(Token::FACA);
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::ENQUANTO);
                break;
            case 6: //ENTAO ->  ATRIB ';'
                pilha.push(Token::BLOCO);
                pilha.push(Token::ENTAO);
                break;
            case 7: //EXPRESSAO ->ID EXPL
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::ID);
                break;
            case 8: //EXPRESSAO ->VALOR EXPL
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::VALOR);
                break;
            case 9: //EXPRESSAO ->NEGACAO
                pilha.push(Token::NEGACAO);
                break;
            case 10: // EXPRESSAO ->(EXPRESSAO) EXPL
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::FECHA_PARENTESE);
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::ABRE_PARENTESE);
                break;
            case 11: // ATRIB -> TIPO ID
                pilha.push(Token::ID);
                pilha.push(Token::TIPO);
                break;
            case 12: // ATRIB -> TIPO ID
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::ATRIB);
                pilha.push(Token::ID);
                break;
            default:

                break;
            }
        }
    }
}