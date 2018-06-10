#ifndef __WINDOWS_TERMINAL_HANDLER__
#define __WINDOWS_TERMINAL_HANDLER__

#ifdef _WIN32
#include <Windows.h>

void CursorToPosition(int x, int y);
void Change16Color(int att);
void ResetText();
#endif

#endif