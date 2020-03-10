#include <stdio.h>
#include <iostream>
#include <cctype>
#include <string>
#include <list>
#include <fstream>
#include "lexico.h"

using namespace std;

Token r_words(const string &str)
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
    return Token::ID;
}

void resetaEstado(int &estado, string &substr)
{
    substr.clear();
    estado = 0;
}

vector<pair<Token, string>> getTokens(ifstream &file)
{
    int estado = 0;
    char c = '\0';
    string subString;
    vector<pair<Token, string>> groupTokens;

    while (!file.eof())
    {
        cout << '{' << estado << ", " << c << "}\n";
        switch (estado)
        {
        case 0:
            c = file.get();
            switch (c)
            {
            case '=':
                subString += c;
                estado = 1;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                subString += c;
                estado = 2;
                break;
            case ';':
                subString += c;
                estado = 3;
                break;
            case '(':
                subString += c;
                estado = 4;
                break;
            case ')':
                subString += c;
                estado = 5;
                break;
            case '&':
            case '|':
            case '!':
            case '<':
            case '>':
                subString += c;
                estado = 8;
                break;
            case EOF:
                cout << "acabou\n";
                groupTokens.push_back(make_pair(Token::$, ""));
                break;

            default:

                if (isalpha(c))
                {

                    // if (isspace(str[prox_char]) || str[prox_char] == ';')
                    // {
                    //     subString += c;
                    subString += c;
                    estado = 6;
                    // }
                }
                else if (isdigit(c))
                {
                    subString += c;
                    estado = 7;
                }
                else if (isspace(c))
                {
                    break;
                }
                else
                    throw invalid_argument("Oh deus");

                break;
            }
            break;
        case 1:
            std::cout << "OPERADOR ATRIBUICAO\n";
            groupTokens.push_back(make_pair(Token::ATRIB, subString));
            resetaEstado(estado, subString);
            //groupTokens += "ATRB ";

            break;
        case 2:
            std::cout << "OPERADOR ARITMETICO\n";
            // groupTokens += "OPA ";
            groupTokens.push_back(make_pair(Token::OPA, subString));
            resetaEstado(estado, subString);
            break;
        case 3:
            std::cout << "PONTO E VIRGULA\n";
            groupTokens.push_back(make_pair(Token::PNTVIRGULA, subString));
            resetaEstado(estado, subString);
            break;
        case 4:
            cout << "Abre paresentesess\n";
            groupTokens.push_back(make_pair(Token::ABRE_PARENTESE, "("));
            resetaEstado(estado, subString);
            break;
        case 5:
            cout << "Fecha parentese\n";
            // groupTokens += "FECHA_PARENTESE ";
            groupTokens.push_back(make_pair(Token::FECHA_PARENTESE, subString));
            resetaEstado(estado, subString);
            break;
        case 6:
        {
            c = file.get();
            if (!isalnum(c))
                estado = 9;
            else
                subString += c;
        }

        break;
        case 7:
            c = file.get();
            if (c == ',')
            {
                estado = 10;
                subString += c;
            }
            else if (!isdigit(c))
                estado = 11;

            break;
        case 8:
            std::cout << "OPERADOR LOGICO\n";
            // groupTokens += "OPB ";
            groupTokens.push_back(make_pair(Token::OPB, subString));
            resetaEstado(estado, subString);
            break;
        case 9:
        {
            auto token = r_words(subString);

            if (token != Token::ID)
                cout << subString << ": PALAVRA RESERVADA" << '\n';
            else
                cout << subString << ": ID" << '\n';

            //groupTokens += subString + " ";
            groupTokens.push_back(make_pair(token, subString));
            resetaEstado(estado, subString);
        }
        break;
        case 10:
            c = file.get();
            if (isdigit(c))
            {
                estado = 12;
                subString += c;
            }
            else
            {
                cout << "acabou\n";
                throw invalid_argument("Man, manda um valor correto ai.");
            }
            break;
        case 11:
            std::cout << subString << ": VALOR" << '\n';
            // groupTokens += "VALOR ";
            groupTokens.push_back(make_pair(Token::VALOR, subString));
            resetaEstado(estado, subString);
            break;
        case 12:
            c = file.get();
            if (!isdigit(c))
            {
                estado = 13;
            }
            else
            {
                subString += c;
            }
            break;
        case 13:
            std::cout << subString << ": VALOR" << '\n';
            resetaEstado(estado, subString);
            break;
        default:
            throw invalid_argument("Deu ruim demais");
        }
    }
    return groupTokens;
}
