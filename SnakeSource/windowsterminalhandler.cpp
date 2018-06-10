#ifdef _WIN32
#include "windowsterminalhandler.hpp"
void CursorToPosition(int x, int y) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD c;
	c.X = x;
	c.Y = y;

	SetConsoleCursorPosition(h, c);
}

void Change16Color(int att) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(h, att);
}

void ResetText() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(h, 7);
}
#endif