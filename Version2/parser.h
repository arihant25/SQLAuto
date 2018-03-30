/**
	This is the header for the parser class.
*/

#pragma once
#include <string>
#include <iostream>
#include <ostream>
#include "scanner.h"
using std::string;

//Stores table name and the column name with which the table is going to be joined with.
struct tableinfo
{
	string tablename;
	string colname;

	tableinfo(string name, string col) : tablename(name), colname(col) {}
	bool hasCol() { return colname.length() > 0; }
};


//Recursively stores the table info for the joined table and data for the child class.
struct data
{
	tableinfo* joinedTable;
	data* childData;

	data(tableinfo* table, data* cdata) : joinedTable(table), childData(cdata) {}
};

//This class parses tokens and transpiles it to the SQL language.
class parser
{
public:
	void parse();

	parser(string inFilename, string outFilename);
	~parser();

private:
	token currTok;
	scanner scnr;
	tableinfo* table();
	data* join();
	std::ofstream out;

	token peek();
	void match(tok_type type);

	void program();
	void stmt();
	void printSQL(data* root);
};

int main(int argc, char* argv[])
{
	string inFile = "test.asql";
	string outFile = "test.sql";
	parser p(inFile, outFile);
	p.parse();
}