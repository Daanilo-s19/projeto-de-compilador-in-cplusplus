#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <list>
#include "token.h"

using std::string;

using namespace std;

Token r_words(string str)
{
    if (str == "SE")
    {
        return Token::SE;
    }
    else if (str == "ENTAO")
    {
        return Token::ENTAO;
    }
    else if (str == "FACA")
    {
        return Token::FACA;
    }
    else if (str == "ENQUANTO")
    {
        return Token::ENQUANTO;
    }
    else if (str == "ACABOU")
    {
        return Token::ACABOU;
    }
    else if (str == "VALOR")
    {
        return Token::VALOR;
    }
    else if (str == "INTEIRO")
    {
        return Token::INTEIRO;
    }
    else if (str == "QUEBRADO")
    {
        return Token::QUEBRADO;
    }
    else if (str == "LOGICO")
    {
        return Token::LOGICO;
    }
    else
        return Token::erro;
}

list<pair<Token, string>> token(char *str)
{
    int estado = 0;
    char c;
    string subString;
    list<pair<Token, string>> groupTokens;

    for (int i = 0; i < strlen(str); i++)
    {
        int prox_char = i + 1;
        c = str[i];

        switch (estado)
        {
        case 0:
            switch (c)
            {
            case '=':
                estado = 1;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                estado = 2;
                break;
            case ';':
                estado = 3;
                break;
            case '(':
                estado = 4;
                break;
            case ')':
                estado = 5;
                break;
            case '&':
            case '|':
            case '!':
            case '<':
            case '>':
                estado = 8;
                break;
            case '\0':
                printf("acabou");
                break;

            default:

                if (isalpha(c))
                {

                    if (isspace(str[prox_char]) || str[prox_char] == ';')
                    {
                        subString += c;
                        estado = 6;
                    }

                    else
                        subString += c;
                }
                else if (isdigit(c))
                {
                    if (isspace(str[prox_char]) || str[prox_char] == ';')
                    {
                        subString += c;
                        estado = 7;
                    }

                    else
                        subString += c;
                }
                else if (c == '.')
                {
                    if (subString.find('.') != -1)
                    {
                        printf("numero inválido");
                        estado = -1;
                    }
                    subString += c;
                }
                else if (isspace(c))
                {

                    // if (c == '\n')
                    // {
                    //     mColCount = 0;
                    //     ++mLinhaCount;
                    // }
                    // lexema.pop_back();
                    break;
                }

                else
                    printf("Deu merda\n");

                break;
            }
            break;
        case 1:
            std::cout << str[i - 1] << ": OPERADOR ATRIBUICAO" << '\n';
            estado = 0;
            groupTokens.push_back(make_pair(Token::ATRIB, string("=")));
            //groupTokens += "ATRB ";

            break;
        case 2:
            std::cout << str[i - 1] << ": OPERADOR ARITMETICO" << '\n';
            subString += str[i - 1];
            // groupTokens += "OPA ";
            groupTokens.push_back(make_pair(Token::OPA, subString));
            estado = 0;
            subString = "";
            break;
        case 3:
            std::cout << str[i - 1] << ":  PONTO E VIRGULA" << '\n';
            estado = 0;
            //groupTokens += ";";
            groupTokens.push_back(make_pair(Token::PNTVIRGULA, ";"));
            break;
        case 4:
            printf("Abre paresentesess\n");
            estado = 0;
            //groupTokens += "ABRE_PARENTESE ";
            groupTokens.push_back(make_pair(Token::ABRE_PARENTESE, "("));
            break;
        case 5:
            printf("Fecha parentese\n");
            estado = 0;
            // groupTokens += "FECHA_PARENTESE ";
            groupTokens.push_back(make_pair(Token::FECHA_PARENTESE, ")"));
            break;
        case 6:
        {
            auto token = r_words(subString);

            if (token != Token::erro)
                cout << subString << ": PALAVRA RESERVADA" << '\n';
            else
                cout << subString << ": ID" << '\n';

            //groupTokens += subString + " ";
            groupTokens.push_back(make_pair(token, subString));
        }
            // else if (isalpha(subString[0]))
            // {
            //     std::cout
            //         << subString << ": ID" << '\n';
            //     groupTokens += "ID ";
            // }
            // else
            // {
            //     std::cout << subString << ": IDENTIFICADOR INVÁLIDO" << '\n';
            //     estado = -1;
            // }
            subString = "";
            estado = 0;
            break;
        case 7:
            std::cout << subString << ": VALOR" << '\n';
            // groupTokens += "VALOR ";
            groupTokens.push_back(make_pair(Token::VALOR, subString));
            subString = "";
            estado = 0;
            break;
        case 8:
            std::cout << str[i - 1] << ": OPERADOR LOGICO" << '\n';
            subString += str[i - 1];
            // groupTokens += "OPB ";
            groupTokens.push_back(make_pair(Token::OPB, subString));
            estado = 0;
            subString = "";

        default:
            break;
        }
    }

    return groupTokens;
}
