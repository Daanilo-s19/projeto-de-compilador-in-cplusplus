#include <stdio.h>
#include <iostream>
#include <cctype>
#include <string>
#include <list>
#include <fstream>
#include "lexico.h"

using namespace std;
std::fstream fs;

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
        return Token::TIPO;
    }
    else if (str == "QUEBRADO")
    {
        return Token::TIPO;
    }
    else if (str == "LOGICO")
    {
        return Token::TIPO;
    }
    return Token::ID;
}

void resetaEstado(int &estado, string &substr)
{
    substr.clear();
    estado = 0;
}
void salvarOutput(string substr, string output) // escrita no arquivo
{
    fs.open("OUTPUT_LEXICO.txt", std::fstream::out | std::fstream::app);
    fs << " [" << substr << "]" << output << std::endl;
    fs.close();
}

vector<pair<Token, string>> getTokens(ifstream &file)
{
    int estado = 0;
    char c = '\0';
    string subString;
    vector<pair<Token, string>> groupTokens;

    while (!file.eof())
    {
        // cout << '{' << estado << ", " << c << "}\n";
        switch (estado)
        {
        case 0:
            c = file.get();
            switch (c)
            {
            case '=':
                subString += c;
                estado = 1; // ATRIBUIÇÃO
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                subString += c;
                estado = 2; //OPERACAO ARITMETICA
                break;
            case ';':
                subString += c;
                estado = 3; // PONTO E VIRGULA
                break;
            case '(':
                subString += c;
                estado = 4; // ABRE PARENTESE
                break;
            case ')':
                subString += c;
                estado = 5; //FECHA PARENTESE
                break;
            case '&':
            case '|':
            case '<':
            case '>':
                subString += c;
                estado = 8; // OPERECAO LOGICA
                break;
            case '!':
                std::cout << "NEGAÇÃO\n";
                groupTokens.push_back(make_pair(Token::NEGACAO, subString));
                salvarOutput(string("!"), string("NEGACAO"));
                resetaEstado(estado, subString);
                break;
            case EOF:
                cout << "acabou\n"; // FIM DE ARQ
                groupTokens.push_back(make_pair(Token::$, ""));
                break;

            default:

                if (isalpha(c)) // SE FOR CARACTERE
                {
                    subString += c;
                    estado = 6; // ESTADO DE VERIFICAÇÃO DO PROXIMO CHAR PRA DEFINIÇÃO DO LEXEMA
                }
                else if (isdigit(c)) //SE FOR DIGITO
                {
                    subString += c;
                    estado = 7; // ESTADO DE VERIFICAÇÃO DO PROXIMO CHAR DO LEXEMA
                }
                else if (isspace(c)) // SE FOR ESPAÇO BREAK E PROXIMO CHAR
                {
                    break;
                }
                else
                    throw invalid_argument("INVALID");

                break;
            }
            break;
        case 1:
            std::cout << "OPERADOR ATRIBUICAO\n";
            groupTokens.push_back(make_pair(Token::ATRIB, subString));
            salvarOutput(subString, string("OPERADOR ATRIBUICAO"));
            resetaEstado(estado, subString);

            break;
        case 2:
            std::cout << "OPERADOR ARITMETICO\n";
            groupTokens.push_back(make_pair(Token::OPA, subString));
            salvarOutput(subString, string("OPERADOR ARITMETICO"));
            resetaEstado(estado, subString);
            break;
        case 3:
            std::cout << subString << "PONTO E VIRGULA\n";
            groupTokens.push_back(make_pair(Token::PNTVIRGULA, subString));
            salvarOutput(subString, string("PONTO E VIRGULA"));
            resetaEstado(estado, subString);
            break;
        case 4:
            cout << subString << "ABRE PARENTESE\n";
            groupTokens.push_back(make_pair(Token::ABRE_PARENTESE, subString));
            salvarOutput(subString, string("ABRE PARENTESE"));
            resetaEstado(estado, subString);
            break;
        case 5:
            cout << subString << "FECHA PARENTESE\n";
            groupTokens.push_back(make_pair(Token::FECHA_PARENTESE, subString));
            salvarOutput(subString, string("FECHA PARENTESE"));
            resetaEstado(estado, subString);
            break;
        case 6:
        {
            c = file.get();  // VERIFICA O PROXIMO CARACTERE DO ARQUIVO
            if (!isalnum(c)) // SE  NAO FOR UM DIGITO OU NUMERO SIGNIFICA QUE ACABOU A LEITURA DO LEXEMA
                estado = 9;  // ESTADO DE VALIDACAO
            else
                subString += c; // CONTINUA A LEITURA DO LEXEMA
        }

        break;
        case 7:
            c = file.get(); // VERIFICA O PROXIMO CARACTERE DO ARQUIVO
            if (c == ',')   // SE FOR ','
            {
                estado = 10; // MANDA PARA O ESTADO 10  QUE ADICIONA NUMEROS
                subString += c;
            }
            else if (!isdigit(c))
                estado = 11; // ESTADO QUE DETERMINA QUE É VALOR

            break;
        case 8:
            std::cout << subString << "OPERADOR LOGICO\n";
            groupTokens.push_back(make_pair(Token::OPB, subString));
            salvarOutput(subString, string("OPERADOR LOGICO"));
            resetaEstado(estado, subString);
            break;
        case 9:
        {
            auto token = r_words(subString);

            if (token != Token::ID)
            {
                cout << subString << ": PALAVRA RESERVADA" << '\n';
                salvarOutput(subString, string("PALAVRA RESERVADA"));
            }
            else
            {
                cout << subString << ": ID" << '\n';
                salvarOutput(subString, string(": ID"));
            }
            groupTokens.push_back(make_pair(token, subString));

            resetaEstado(estado, subString);
        }
        break;
        case 10: // DEPOIS DA VIRGULA ESTADO 10  QUE ADICIONA NUMEROS
            c = file.get();
            if (isdigit(c))
            {
                estado = 12; // VALIDA QUE É UM VALOR
                subString += c;
            }
            else
            {
                cout << "acabou\n";
                throw invalid_argument("Man, manda um valor correto ai.");
            }
            break;
        case 11: // FINAL DA LEITURA DE VALOR
            std::cout << subString << ": VALOR" << '\n';
            groupTokens.push_back(make_pair(Token::VALOR, subString));
            salvarOutput(subString, string(": VALOR"));
            resetaEstado(estado, subString);
            break;
        case 12:
            c = file.get();
            if (!isdigit(c))
            {
                estado = 13; //VALIDA QUE É VALOR
            }
            else
            {
                subString += c;
            }
            break;
        case 13:
            std::cout << subString << ": VALOR" << '\n';
            salvarOutput(subString, string(": VALOR"));
            resetaEstado(estado, subString);
            break;
        default:
            throw invalid_argument("Deu ruim demais");
        }
    }
    return groupTokens;
}
