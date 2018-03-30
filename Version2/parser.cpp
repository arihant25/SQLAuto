#include "parser.h"
#include <iostream>

//This is the default constructor.
void parser::parse()
{
	program();
}

void parser::program()
{
	stmt();
	match(TT_EOF);
}

//This function consumes tokens invokes print().
void parser::stmt()
{
	tableinfo* t = table();
	data* cdata = join();
	data* root = new data(t, cdata);

	printSQL(root);
}

//This function returns tableinfo consisting of tablename and the column name.
tableinfo* parser::table()
{
	token table = peek();
	match(TT_TABLE);
	token pk = peek();
	string colname = "";
	if (pk.type == TT_LBRAC) {
		match(TT_LBRAC);
		token colJoin = peek();
		colname = colJoin.lexeme;
		match(TT_COL);
		match(TT_RBRAC);		
	}
	return new tableinfo(table.lexeme, colname);
}

//This function checks for nested joins returns data consisting of tableinfo and data(recurses).
data* parser::join() 
{
	match(TT_NL);
	match(TT_TAB);
	match(TT_LPAREN);
	tableinfo* t = table();
	token pk = peek();
	data* cdata = NULL;
	if (pk.type == TT_NL) {
		data* childdata = join();
		cdata = childdata;
	}
	match(TT_RPAREN);

	return new data(t, cdata);
}

int count = 1;
//This function prints to SQL.
void parser::printSQL(data* root)
{
	std::cout << "1";
	if (root->childData->childData == NULL)
	{
		out << "SELECT * \nFROM " << root->joinedTable->tablename << ", " << root->childData->joinedTable->tablename
			<< " \nWHERE " << root->joinedTable->tablename << "." << root->childData->joinedTable->colname << " = "
			<< root->childData->joinedTable->tablename << "." << root->childData->joinedTable->colname;
	}
	else
	{
		out << "SELECT * \nFROM " << root->joinedTable->tablename << ", (";
		printSQL(root->childData);
		out << ") as joinedTable_" << count << " \nWHERE " << root->joinedTable->tablename << "."
			<< root->childData->joinedTable->colname << " = " << "joinedTable_" << count << "."
			<< root->childData->joinedTable->colname;
		count++;
	}
}

//This is the constructor.
parser::parser(string inFilename, string outFilename) : scnr(inFilename), currTok(token::TOK_NOTOK)
{
	out.open(outFilename);
}

//This is the destructor.
parser::~parser() 
{
	out.close();
}

//This function matches the current token.
void parser::match(tok_type type)
{
	token t = peek();
	if (t.type != type)
	{
		std::cout << "Parsing ERROR" << std::endl;
	}
	currTok = token::TOK_NOTOK;
}

//This function peeks for the next token.
token parser::peek()
{
	if (currTok.type == TT_NOTOK)
		currTok = scnr.scan();
	return currTok;
}