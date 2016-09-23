#include "Comment.h"


Comment::Comment()
{
}


Comment::~Comment()
{
}


int Comment::read(FileReader& file)
{
	file.reset();
	if (hash(file))
	{
		int number = whichComment(file);
		if (number == 0) return 0;
		return number + 1;
	}
	return 0;
}

std::string Comment::getName()
{
	return "COMMENT";
}
bool Comment::hash(FileReader& file)
{
	if (file.getChar() == '#') return true;
	return false;
}
int Comment::whichComment(FileReader& file)
{
	if (file.getChar() == '|'){
		int number = block(file);
		if (number == 0) return 0;
		return number + 1;
	}
	return line(file) + 1;
}

int Comment::line(FileReader& file)
{
	char c = file.getChar();
	if (c != '\n' && c != EOF)
	{
		int number = line(file);
		if (number == 0) return 0;
		return number + 1;
	}
	return 1;
}

int Comment::block(FileReader& file)
{
	char c = file.getChar();
	if (c != EOF && c != '|')
	{
		int number = block(file);
		if (number == 0) return 0;
		return number + 1;
	}
	else if (c == '|' && hash(file))
	{
		return 2;
	}
	return 0;
}