#include "linuxterminalhandler.hpp"

void TerminalHandler::initNoBuffering(){
	termios newSettings;
	tcgetattr(0, &newSettings);

	newSettings.c_lflag &= ~ICANON;
	newSettings.c_lflag &= ~ECHO;

	setbuf(stdin, NULL);

	tcsetattr(0, TCSANOW, &newSettings);
}

void TerminalHandler::resetNoBuffering(){
	termios newSettings;
	tcgetattr(0, &newSettings);

	newSettings.c_lflag |= ICANON;
	newSettings.c_lflag |= ECHO;

	tcsetattr(0, TCSANOW, &newSettings);
}

void CursorToPosition(int x, int y){
	x += 1;
	y += 1;
	std::ostringstream oss;
	oss << "\033[" << x << ";" << y << "H";
	std::cout << oss.str();
}

void ChangeTrueColor(int r, int g, int b){
	std::ostringstream oss;
	oss << "\033[38;2;" << r << ";" << g << ";" << b << "m";
	std::cout << oss.str();
}

void ResetText(){
	std::cout << "\033[0m";
}

int _kbhit(){
	int bytesWaiting;
	ioctl(0, FIONREAD, &bytesWaiting);
	return bytesWaiting;
}

char _getch(){
	char c;
	c = getchar();
	return c;
}