#include <iostream>
#include <string>
#include "FileReader.h"
#include "Automatan.h"
#include "Comma.h"
#include "Colon.h"
#include "ColonDash.h"
#include "Period.h"
#include "Q_mark.h"
#include "Undefined.h"
#include <vector>

std::string generateToken(Automatan* a, FileReader input, int size)
{
	std::string output = "";
	output += "(" + a->getName() + ",\"" + input.getString(size) + "\"," + (char)(input.lineNumber()+48) + ")";
	return output;
}

int main( int argc, char *argv[])
{
	//Usage Requirements
	/*if (argc != 2)
	{
		std::cout << "usage: " << argv[0] << " <filename>\n";
	}
	else*/
	{
		//FileReader input(argv[1]);
		FileReader input;
		input.test(":-,,.?.\ns::-");
		std::vector<Automatan*> automata = {
			new Comma(),
			new Period(),
			new Q_mark(),
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
				std::cout << generateToken(undf, input, 1) << std::endl;;
				input.removeString(1);
			}
			else
			{
				std::cout << generateToken(automata[automataHigh], input, sl) << std::endl;
				input.removeString(sl);
			}
		}
	}

	system("pause");
	return 0;
}



