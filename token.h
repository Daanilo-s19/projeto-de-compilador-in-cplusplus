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
    SE_T,
    ENTAO_T,
    ENQUANTO_T,
    ACABOU,
    FACA,
    NEGACAO,
    $,

    // produção
    PROGRAMA,
    PROGRAMAX,
    BLOCO,
    CMD,
    EXPRESSAO,
    EXPL,
    EXPLX,
    EXPAX,
    EXP_LOGICA,
    SE,
    ENTAO,
    ENQUANTO,
    ERRO,

};
