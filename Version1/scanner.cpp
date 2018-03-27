#include "scanner.h"


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
		//else if (c == '.')
		//{
		//	get();
		//	return token::TOK_DOT;
		//}
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
		//else if (c == 't')
		//{
		//	get();
		//	c = get();
		//	if (c == 'a')
		//	{
		//		c = get();
		//		if (c == 'b')
		//			return token::TOK_TAB;
		//	}
		//}
		else
		{
			std::cout << "scanning error";
			break;
		}
	}
	return token::TOK_EOF;
}

scanner::scanner(string filename)
{
	in.open(filename);
}

scanner::~scanner()
{
	in.close();
}

char scanner::peek()
{
	return in.peek();
}

char scanner::get()
{
	return in.get();
}

void scanner::unget()
{
	in.unget();
}

token token::TOK_LPAREN = token(TT_LPAREN, "(");
token token::TOK_RPAREN = token(TT_RPAREN, ")");
token token::TOK_TAB = token(TT_TAB, "tab");
//token token::TOK_DOT = token(TT_DOT, ".");
token token::TOK_NL = token(TT_NL, "\n");
token token::TOK_LBRAC = token(TT_LBRAC, "[");
token token::TOK_RBRAC = token(TT_RBRAC, "]");

token token::TOK_NOTOK = token(TT_NOTOK, "<NOTOK>");
token token::TOK_EOF = token(TT_EOF, "<EOF>");