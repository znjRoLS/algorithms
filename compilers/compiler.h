//
// Created by rols on 4/23/17.
//

#ifndef HELMET_PARSERS_H
#define HELMET_PARSERS_H

#include <vector>

using namespace std;

class Parser {

};

Parser lr0(vector<string> terminals, vector<string> nonTerminals, vector<string> rules, string startSymbol);
Parser slr1(vector<string> terminals, vector<string> nonTerminals, vector<string> rules, string startSymbol);
Parser lr1(vector<string> terminals, vector<string> nonTerminals, vector<string> rules, string startSymbol);
Parser lalr1(vector<string> terminals, vector<string> nonTerminals, vector<string> rules, string startSymbol);
Parser lr0(string parserConf);
Parser slr1(string parserConf);
Parser lr1(string parserConf);
Parser lalr1(string parserConf);

class Lexer {

};

Lexer constructLexer(string lexerConf);

#endif //HELMET_PARSERS_H
