#include "FileReader.h"
#include <fstream>
#include <iostream>


void FileReader::read(std::string fileName)
{
	std::ifstream myfile(fileName);
	std::string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			file += line + "\n";
		}
		myfile.close();
	}
	else std::cout << "Unable to open file\n";
}

FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

bool FileReader::isEmpty()
{
	if (file.length() == 0) return true;
	return false;
}
void FileReader::reset()
{
	p = 0;
}

char FileReader::getChar()
{
	char a = file.at(p);
	p++;
	return a;
}

std::string FileReader::getString(int size)
{
	return file.substr(0, size);
}

void FileReader::removeString(int size)
{
	reset();
	for (int i = 0; i < size; i++)
		if (getChar() == '\n')
			line++;
	file.erase(0, size);
}

int FileReader::lineNumber()
{
	return line;
}

void FileReader::test(std::string testFile)
{
	file = testFile;
}
