#ifndef __LINUXTERMINALHANDLER_HPP__
#define __LINUXTERMINALHANDLER_HPP__

#include <stdio.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stropts.h>

#include <iostream>
#include <cstdlib>
#include <sstream>

// Settings necessary for kbhit() and getch() to work.
class TerminalHandler {
	TerminalHandler();
public:
	static void initNoBuffering();
	static void resetNoBuffering();
};

void CursorToPosition(int x, int y);
void ChangeTrueColor(int r, int g, int b);
void ResetText();

int kbhit();
char getch();

#endif