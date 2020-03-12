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
std::fstream fss;

void salvarOutput(string output) // escrita no arquivo
{
    fss.open("OUTPUT_SINTATICO.txt", std::fstream::out | std::fstream::app);
    fss << output << std::endl;
    fss.close();
}
void syntatic(vector<pair<Token, string>> &tokens)
{

    map<Token, map<Token, unsigned>>
        table{
            // REGRAS DA PARSER TABLE QUE SEGUE NO DOCUMENTO
            {Token::PROGRAMA,
             {{Token::ID, 1}, {Token::TIPO, 1}, {Token::SE, 1}, {Token::ENQUANTO, 1}}},
            {Token::PROGRAMAX,
             {{Token::ID, 1}, {Token::TIPO, 1}, {Token::SE, 1}, {Token::ENQUANTO, 1}, {Token::$, 99}, {Token::ENTAO, 99}, {Token::ACABOU, 99}}},
            {Token::BLOCO,
             {{Token::ID, 2}, {Token::TIPO, 2}, {Token::SE, 2}, {Token::ENQUANTO, 2}}},
            {Token::CMD,
             {{Token::ID, 3}, {Token::TIPO, 3}, {Token::SE, 4}, {Token::ENQUANTO, 5}}},
            {Token::SE,
             {{Token::SE, 6}}},
            {Token::ENQUANTO,
             {{Token::ENQUANTO, 7}}},
            {Token::ENTAO,
             {{Token::ENTAO, 8}, {Token::ACABOU, 99}}},
            {Token::EXPRESSAO,
             {{Token::ID, 9}, {Token::VALOR, 10}, {Token::NEGACAO, 11}, {Token::ABRE_PARENTESE, 12}}},
            {Token::EXPL,
             {{Token::OPA, 13}, {Token::FACA, 99}, {Token::FECHA_PARENTESE, 99}}},
            {Token::EXPLX,
             {{Token::OPB, 14}, {Token::FACA, 99}, {Token::OPA, 99}, {Token::FECHA_PARENTESE, 99}}},
            {Token::EXPAX,
             {{Token::OPA, 15}, {Token::OPB, 99}}},
            {Token::ATRIB,
             {{Token::ID, 16}, {Token::TIPO, 17}}},

        };

    stack<Token>
        pilha{{Token::$, Token::PROGRAMA}}; // ADICIONA O $ NO INICIO DA PILHA
    size_t index = 0;
    while (pilha.size()) // ENQUANTO TIVER PILHA FAÇA REALIZE A VERIFICÃO DA PARSER TABLE
    {
        auto &token = tokens[index].first;
        auto topo = pilha.top();

        cout << "parser: TOKEN LIDO[" << token << "] TOPO:[" << topo << "]\n";
        cin.get();
        if (token == topo) // HOUVE MATCH ENTRE O TOPO DA PILHA E O TOKEN LIDO
        {
            //bateu
            cout << "parser: topo bateu com o token lido do lexico" << token << "==" << topo << '\n';
            // salvarOutput(" PARSER: TOKEN = TOPO\n");
            pilha.pop();
            ++index;
        }
        else
        {
            auto regra = table[topo][token];
            pilha.pop();
            switch (regra)
            {

            case 1: //<programa> -> cmd programax
                pilha.push(Token::PROGRAMAX);
                pilha.push(Token::CMD);
                salvarOutput("<programa> -> cmd programax");
                break;
            case 2: //<bloco> -> programa
                pilha.push(Token::PROGRAMA);
                pilha.push(Token::CMD);
                salvarOutput("<bloco> -> programa");
                break;
            case 3: //<cmd>->  atrib ‘;’
                pilha.push(Token::PNTVIRGULA);
                pilha.push(Token::ATRIB);
                salvarOutput("<cmd>->  atrib ‘;’");
                break;
            case 4: //<cmd>->  se
                pilha.push(Token::SE);
                salvarOutput("<cmd>->  se");
                break;
            case 5: //<cmd>->  enquanto
                pilha.push(Token::ENQUANTO);
                salvarOutput("<cmd>->  enquanto");
                break;
            case 6: //<se> -> ‘se‘ expressao ‘faça’ bloco senao  ‘acabou’
                pilha.push(Token::ACABOU);
                pilha.push(Token::ENTAO);
                pilha.push(Token::BLOCO);
                pilha.push(Token::FACA);
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::SE);
                salvarOutput("<se> -> ‘se‘ expressao ‘faça’ bloco senao  ‘acabou’");
                break;
            case 7: //<enquanto> -> ‘enquanto’  expressao ‘faça’ bloco  ‘acabou’
                pilha.push(Token::ACABOU);
                pilha.push(Token::BLOCO);
                pilha.push(Token::FACA);
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::ENQUANTO);
                salvarOutput("<enquanto> -> ‘enquanto’  expressao ‘faça’ bloco  ‘acabou’");
                break;
            case 8: //<senao> -> ‘senao’ bloco
                pilha.push(Token::BLOCO);
                pilha.push(Token::ENTAO);
                salvarOutput("<senao> -> ‘senao’ bloco");
                break;
            case 9: //<expressao> -> id expl
                pilha.push(Token::EXPL);
                pilha.push(Token::ID);
                salvarOutput("<expressao> -> id expl");
                break;
            case 10: //<expressao> -> valor expl
                pilha.push(Token::EXPL);
                pilha.push(Token::VALOR);
                salvarOutput("<expressao> -> valor expl");
                break;
            case 11: //<expressao> -> negacao  expressao expl
                pilha.push(Token::EXPL);
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::NEGACAO);
                salvarOutput("<expressao> -> negacao  expressao expl");
                break;
            case 12: //<expressao> -> (expressao)  expl
                pilha.push(Token::EXPL);
                pilha.push(Token::FECHA_PARENTESE);
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::FECHA_PARENTESE);
                salvarOutput("<expressao> -> (expressao)  expl ");
                break;
            case 13: //<expl>-> expax explx
                pilha.push(Token::EXPLX);
                pilha.push(Token::EXPAX);
                salvarOutput("<expl>-> expax explx");
                break;
            case 14: //<explx> -> opb expressao explx
                pilha.push(Token::EXPLX);
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::OPB);
                salvarOutput("<explx> -> opb expressao explx ");
                break;
            case 15: //<expa¹> -> opa expressao expa’
                pilha.push(Token::EXPAX);
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::OPA);
                salvarOutput("<expa¹> -> opa expressao expax ");
                break;
            case 16: //<atrib> -> tipo id
                pilha.push(Token::ID);
                pilha.push(Token::TIPO);
                salvarOutput("<atrib> -> tipo id");
                break;
            case 17: //<atrib> -> id “=” expressao
                pilha.push(Token::EXPRESSAO);
                pilha.push(Token::ATRIB);
                pilha.push(Token::ID);
                salvarOutput("<atrib> -> id “=” expressao");
                break;
            case 99:
                cout << "FOLLOW ->e\n";
                break;

            default:
                cout << "Parser: Producao nao registrada\n";
                pilha.pop();
                break;
            }
            // switch (regra)            {
            // case 1: //PROGRAMA ->CMD PROGRAMA
            //     pilha.push(Token::PROGRAMA);
            //     pilha.push(Token::CMD);
            //     salvarOutput("PROGRAMA ->CMD PROGRAMA");
            //     break;
            // case 2: //BLOCO -> PROGRAMA
            //     pilha.push(Token::PROGRAMA);
            //     salvarOutput("BLOCO -> PROGRAMA");
            //     break;
            // case 3: //CMD ->  ATRIB ';'
            //     pilha.push(Token::PNTVIRGULA);
            //     pilha.push(Token::ATRIB);
            //     salvarOutput("CMD ->  ATRIB ';'");
            //     break;
            // case 4: //SE ->‘se‘ EXPRESSAO ‘faça’ BLOCO SENAO  ‘acabou’
            //     pilha.push(Token::ACABOU);
            //     pilha.push(Token::ENTAO);
            //     pilha.push(Token::BLOCO);
            //     pilha.push(Token::FACA);
            //     pilha.push(Token::EXPRESSAO);
            //     pilha.push(Token::SE);
            //     salvarOutput("SE ->‘se‘ EXPRESSAO ‘faça’ BLOCO SENAO  ‘acabou’");
            //     break;
            // case 5: //ENQUANTO -> ‘enquanto’  EXPRESSAO ‘faça’ BLOCO  ‘acabou’
            //     pilha.push(Token::ACABOU);
            //     pilha.push(Token::BLOCO);
            //     pilha.push(Token::FACA);
            //     pilha.push(Token::EXPRESSAO);
            //     pilha.push(Token::ENQUANTO);
            //     salvarOutput("ENQUANTO -> ‘enquanto’  EXPRESSAO ‘faça’ BLOCO  ‘acabou’");
            //     break;
            // case 6: //ENTAO ->  ATRIB ';'
            //     pilha.push(Token::BLOCO);
            //     pilha.push(Token::ENTAO);
            //     salvarOutput("ENTAO ->  ATRIB ';'");
            //     break;
            // case 7: //EXPRESSAO ->ID EXPL
            //     pilha.push(Token::EXPRESSAO);
            //     pilha.push(Token::ID);
            //     salvarOutput("EXPRESSAO ->ID EXPL");
            //     break;
            // case 8: //EXPRESSAO ->VALOR EXPL
            //     pilha.push(Token::EXPRESSAO);
            //     pilha.push(Token::VALOR);
            //     salvarOutput("EXPRESSAO ->VALOR EXPL");
            //     break;
            // case 9: //EXPRESSAO ->NEGACAO
            //     pilha.push(Token::NEGACAO);
            //     salvarOutput("EXPRESSAO ->NEGACAO");
            //     break;
            // case 10: // EXPRESSAO ->(EXPRESSAO) EXPL
            //     pilha.push(Token::EXPRESSAO);
            //     pilha.push(Token::FECHA_PARENTESE);
            //     pilha.push(Token::EXPRESSAO);
            //     pilha.push(Token::ABRE_PARENTESE);
            //     salvarOutput("EXPRESSAO ->(EXPRESSAO) EXPL");
            //     break;
            // case 11: // ATRIB -> TIPO ID
            //     pilha.push(Token::ID);
            //     pilha.push(Token::TIPO);
            //     salvarOutput("ATRIB -> TIPO ID");
            //     break;
            // case 12: // ATRIB ->  ID = expressao
            //     pilha.push(Token::EXPRESSAO);
            //     pilha.push(Token::ATRIB);
            //     pilha.push(Token::ID);
            //     salvarOutput("ATRIB ->  ID = expressao");
            //     break;
            // default:
            //     cout << "Parser: Producao nao registrada\n";
            //     pilha.pop();

            //     break;
            // }
        }
    }
}