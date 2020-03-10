#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "token.h"

Token r_words(const std::string &str);
void resetaEstado(int &estado, std::string &substr);
std::vector<std::pair<Token, std::string>> getTokens(std::ifstream &file);