#pragma once
enum Token
{
    // terminais
    ABRE_PARENTESE = -17,
    FECHA_PARENTESE,
    INTEIRO,
    QUEBRADO,
    LOGICO,
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
    $,

    // Não terminal
    PROGRAMA,
    BLOCO,
    CMD,
    EXPRESSAO,
    EXP_LOGICA,

};