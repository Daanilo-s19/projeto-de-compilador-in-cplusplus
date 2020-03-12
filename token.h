#pragma once
enum Token
{
    // terminais
    ABRE_PARENTESE = -17,
    FECHA_PARENTESE,
    TIPO,
    VALOR,
    ID,
    ATRIB,
    OPA,
    OPB,
    PNTVIRGULA,
    SE,
    ENTAO,
    ENQUANTO,
    ACABOU,
    FACA,
    NEGACAO,
    $,

    // Não terminal
    PROGRAMA,
    PROGRAMAX,
    BLOCO,
    CMD,
    EXPRESSAO,
    EXPL,
    EXPLX,
    EXPAX,
    EXP_LOGICA,
    ERRO,

};
