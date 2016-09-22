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
#include "Undefined.h"
#include <vector>

std::string generateToken(Automatan* a, FileReader input, int size)
{
	std::string output = "";
	input.reset();
	output += "(" + a->getName() + ",\"" + input.getString(size) + "\"," + (char)(input.lineNumber()+48) + ")";
	return output;
}

int main( int argc, char *argv[])
{
	//Usage Requirements
	FileReader input;
	std::string test = ":-, (),.?.\ns::-";
	if (argc != 2)
	{
		std::cout << "usage: " << argv[0] << " <filename>\n";
		std::cout << "Using test data instead: " << test << std::endl;
		input.test(test);
	}
	else {
		input.read(argv[1]);
	}
	std::vector<Automatan*> automata = {
		new Comma(),
		new Period(),
		new Q_mark(),
		new Left_paren(),
		new Right_paren(),
		new Colon(),
		new ColonDash()
	};
	Undefined* undf = new Undefined();
	while (!input.isEmpty())
	{
		int sl = 0;
		int automataHigh = -1;
		for (int i = 0; i < automata.size(); i++)
		{
			int automataRead = automata[i]->read(input);
			if ( automataRead > sl)
			{
				sl = automataRead;
				automataHigh = i;
			}
		}
		if (sl == 0)
		{
			input.reset();
			char testt = input.getChar();
			if (!isspace(testt))
				std::cout << generateToken(undf, input, 1) << std::endl;;
			input.removeString(1);
		}
		else
		{
			std::cout << generateToken(automata[automataHigh], input, sl) << std::endl;
			input.removeString(sl);
		}
	}
	delete undf;
	for (int i = 0; i < automata.size(); i++) delete automata[i];
	system("pause");
	return 0;
}



