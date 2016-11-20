#include <string>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>

#include "renderer.h"

void PrintColoredText(int color, const char* text) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
	printf("%s", text);
	SetConsoleTextAttribute(h, 7);
}

inline int ParseColor(char code)
{
	int color = 7;
	switch (code)
	{
	case 'R':
		color = 12;
		break;
	case 'Y':
		color = 14;
		break;
	case 'C':
		color = 11;
		break;
	case 'G':
		color = 10;
		break;
	}

	return color;
}

void PrintBoard(const std::string& board)
{
	std::string code = "";
	bool openBracket = false, shouldParse = false;

	unsigned int index = 45;

	for (char c : board)
	{
		switch (c)
		{
		case '[':
			code += c;
			openBracket = true;
			break;
		case ']':
			code += c;
			openBracket = false;
			shouldParse = true;
			break;
		default:
			if (openBracket)
			{
				code += c;
			}
			else
			{
				printf("%c", c);
			}
			break;
		}

		if (shouldParse)
		{
			if (code[1] == 'N')
			{
				unsigned int id = atoi(code.substr(2, 2).c_str());

				char buf[3];
				if (code[5] == 'C')
				{
					sprintf_s(buf, "[]", id);
				}
				else
				{
					sprintf_s(buf, "%02d", id);
				}

				int color = ParseColor(code[4]);
				PrintColoredText(color, buf);
			}
			else
			{
				unsigned int src = atoi(code.substr(1, 2).c_str());
				unsigned int dst = atoi(code.substr(3, 2).c_str());


				char buf[14];

				switch (code[code.length() - 2])
				{
				case '-':
					sprintf_s(buf, "%s", "-------------");
					break;
				case '\\':
					sprintf_s(buf, "%s", "\\");
					break;
				case '/':
					sprintf_s(buf, "%s", "/");
					break;
				}

				int color = ParseColor(code[5]);
				PrintColoredText(color, buf);
			}

			code = "";
			shouldParse = false;
		}
	}
}