#pragma once
#include <string>
#include <iostream>
#include <ostream>
#include "scanner.h"
using std::string;

class parser
{
public:
	void parse();

	parser(string inFilename, string outFilename);
	~parser();

private:
	token currTok;
	scanner scnr;
	std::ofstream out;

	void program();
	void stmt();

	token get();

	void match(tok_type type);
};

int main(int argc, char* argv[])
{
	string inFile = "test.txt";
	string outFile = "test.sql";
	parser p(inFile, outFile);
	p.parse();
}