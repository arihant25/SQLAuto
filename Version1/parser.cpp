#include "parser.h"

void parser::parse()
{
	program();
}

void parser::program()
{
	stmt();
	match(TT_EOF);
}

void parser::stmt()
{
	token table1 = get();
	match(TT_TABLE);
	match(TT_NL);
	match(TT_TAB);
	match(TT_LPAREN);
	token table2 = get();
	match(TT_TABLE);
	match(TT_LBRAC);

	token colJoin = get();
	match(TT_COL);
	match(TT_RBRAC);
	match(TT_RPAREN);
	out << "SELECT " << "*" << std::endl << "FROM " << table1.lexeme << ", " << table2.lexeme
			<< std::endl << "WHERE "  << table1.lexeme << "." << colJoin.lexeme << " = " << table2.lexeme 
			<< "." << colJoin.lexeme << std::endl;
//	match(TT_RPAREN);
//	match(TT_DOT);
	
}

parser::parser(string inFilename, string outFilename) : scnr(inFilename), currTok(token::TOK_NOTOK)
{
	out.open(outFilename);
}
parser::~parser() 
{
	out.close();
}

token parser::get()
{
	if (currTok.type == TT_NOTOK)
		currTok = scnr.scan();
	return currTok;
}

void parser::match(tok_type type)
{
	token t = get();
	if (t.type != type)
	{
		std::cout << "Parsing ERROR" << std::endl;
	}
	currTok = token::TOK_NOTOK;
}