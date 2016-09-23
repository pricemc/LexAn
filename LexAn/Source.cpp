#include <iostream>
#include <string>
#include "FileReader.h"
#include "Automatan.h"
#include "Comma.h"
#include "Period.h"
#include "Q_mark.h"
#include "Left_paren.h"
#include "Right_paren.h"
#include "Colon.h"
#include "ColonDash.h"
#include "Multiply.h"
#include "Add.h"
#include "Schemes.h"
#include "Facts.h"
#include "Rules.h"
#include "Queries.h"
#include "Id.h"
#include "String.h"
#include "Comment.h"
#include "Undefined_String.h"
#include "Undefined_Comment.h"
#include "Undefined.h"
#include <vector>
#include <sstream>

/*
generateToken
	prints out token
	pre: automatan exists, input is not empty, size != 0
	post: token printed to std::cout
*/
std::string generateToken(Automatan* a, FileReader input, int size)
{
	std::string output = "";
	input.reset();
	std::stringstream oss;

	oss << "("<< a->getName() << ",\"" << input.getString(size) << "\"," << input.lineNumber() + ")";

	return oss.str();
}

int main( int argc, char *argv[])
{
	int tokens = 0;
	//Usage Requirements
	FileReader input;
	std::string test = ":Facts*:-Fa+Queri\nesRules 'Hello'Schemes \n#|c\nomment|' hello";
	if (argc != 2)
	{
		//use test data
		std::cout << "usage: " << argv[0] << " <filename>\n";
		std::cout << "Using test data instead: " << test << std::endl;
		input.test(test);
	}
	else {
		input.read(argv[1]);
	}

	//Automata vector to run through in algorithm
	std::vector<Automatan*> automata = {
		new Comma(),
		new Period(),
		new Q_mark(),
		new Left_paren(),
		new Right_paren(),
		new Colon(),
		new ColonDash(),
		new Multiply(),
		new Add(),
		new Schemes(),
		new Facts(),
		new Rules(),
		new Queries(),
		new Id(),
		new String(),
		new Comment(),
		new Undefined_String(),
		new Undefined_Comment()
	};
	//Undefined Automata
	Undefined* undf = new Undefined();

	//Main Algorithm
	while (!input.isEmpty())
	{
		int sl = 0;
		int automataHigh = -1;
		for (int i = 0; i < automata.size(); i++)	//find correct automata
		{
			int automataRead = automata[i]->read(input);
			if ( automataRead > sl)
			{
				sl = automataRead;
				automataHigh = i;
			}
		}
		if (sl == 0)	//remove undefined and generate token
		{
			input.reset();
			char testt = input.getChar();
			if (!isspace(testt))
				std::cout << generateToken(undf, input, 1) << std::endl;;
			input.removeString(1);
		}
		else	//remove and generate token for longest automata
		{
			std::cout << generateToken(automata[automataHigh], input, sl) << std::endl;
			input.removeString(sl);
		}
		tokens++;
	}

	//generate EOF token
	std::cout << "(EOF,\"\"," << input.lineNumber() << ")" << std::endl;
	std::cout << "Total Tokens = " << ++tokens << std::endl;
	//mem clean
	delete undf;
	for (int i = 0; i < automata.size(); i++) delete automata[i];
	system("pause");
	return 0;
}



