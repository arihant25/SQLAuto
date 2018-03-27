#pragma once
#include <string>
#include <iostream>
#include <fstream>
using std::string;

enum tok_type
{
	TT_NOTOK, TT_LPAREN, TT_RPAREN, TT_TAB, TT_TABLE, TT_DOT, TT_NL, TT_EOF, TT_COL, TT_LBRAC, TT_RBRAC
};

struct token
{
	tok_type type;
	string lexeme;
	token(tok_type t, string l) : type(t), lexeme(l) {}

	static token TOK_LPAREN;
	static token TOK_RPAREN;
	static token TOK_TAB;
	static token TOK_LBRAC;
	static token TOK_RBRAC;
//	static token TOK_DOT;
	static token TOK_NL;


	static token TOK_NOTOK;
	static token TOK_EOF;
};


class scanner
{
public:
	token scan();

	scanner(string filename);
	~scanner();

private:
	std::ifstream in;

	char peek();
	char get();
	void unget();
};