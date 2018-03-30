/**
	@author Arihant Jain & Christopher Higgs

	This class reads a .asql file and converts strings of chars to tokens.
*/

#include "scanner.h"

//This function scans and returns tokens.
token scanner::scan()
{
	char c = peek();
	while (c != EOF)
	{
		if (c == '(')
		{
			get();
			return token::TOK_LPAREN;
		}
		else if (c == ')')
		{
			get();
			return token::TOK_RPAREN;
		}
		else if (c == '\n')
		{
			get();
			return token::TOK_NL;
		}
		else if (isupper(c))
		{
			
			string tableId = "";
			tableId += c;
			get();
			c = get();
			while (isupper(c))
			{
				tableId += c;
				c = get();
			}
			unget();

			return token(TT_TABLE, tableId);
		}
		else if (c == '[')
		{
			get();
			return token::TOK_LBRAC;
		}
		else if (c == ']')
		{
			get();
			return token::TOK_RBRAC;
		}
		else if (islower(c))
		{

			string tableId = "";
			tableId += c;
			get();
			c = get();
			while (islower(c))
			{
				tableId += c;
				c = get();
			}
			unget();
			if (tableId == "tab")
				return token::TOK_TAB;
			else
				return token(TT_COL, tableId);
		}
		else
		{
			std::cout << "scanning error";
			break;
		}
	}
	return token::TOK_EOF;
}

//This is the constructor.
scanner::scanner(string filename)
{
	in.open(filename);
}

//This is the destructor.
scanner::~scanner()
{
	in.close();
}

//This function peeks for the next char.
char scanner::peek()
{
	return in.peek();
}

//This function gets the next char and moves the read position.
char scanner::get()
{
	return in.get();
}

//This function changes the read position back one char.
void scanner::unget()
{
	in.unget();
}

token token::TOK_LPAREN = token(TT_LPAREN, "(");
token token::TOK_RPAREN = token(TT_RPAREN, ")");
token token::TOK_TAB = token(TT_TAB, "tab");
token token::TOK_NL = token(TT_NL, "\n");
token token::TOK_LBRAC = token(TT_LBRAC, "[");
token token::TOK_RBRAC = token(TT_RBRAC, "]");
token token::TOK_NOTOK = token(TT_NOTOK, "<NOTOK>");
token token::TOK_EOF = token(TT_EOF, "<EOF>");