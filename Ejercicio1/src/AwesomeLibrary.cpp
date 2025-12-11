#include "AwesomeLibrary.h"

void miliSleep (int miliseconds) 
{
	Sleep(miliseconds);
}

int getKey (bool wait) 
{
	int key;

	if (wait || _kbhit())
	{
		key = _getch();
		
		if (key == 0 || key == 224)
			key = _getch() + 256;
	}
	else
	{
		key = 0;
	}
	
	return key;
}

int getScreenWidth () 
{
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	return (!GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo)) ? 80 : screenBufferInfo.srWindow.Right + 1;
}

int getScreenHeight () 
{
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	return (!GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo)) ? 80 : screenBufferInfo.srWindow.Bottom + 1;
}

void setBackgroundColor (Color color) 
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wAttrib = 0;
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	
	GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo);
	wAttrib = screenBufferInfo.wAttributes;
	
	wAttrib &= ~(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);

	int c = (int)color;
	
	if (c & 1)		
		wAttrib |= BACKGROUND_BLUE;
	if (c & 2)		
		wAttrib |= BACKGROUND_GREEN;
	if (c & 4)
		wAttrib |= BACKGROUND_RED;
	if (c & 8)		
		wAttrib |= BACKGROUND_INTENSITY;
	
	SetConsoleTextAttribute(outputHandle, wAttrib);
}

void setForegroundColor (Color color) 
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wAttrib = 0;
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;

	GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo);
	wAttrib = screenBufferInfo.wAttributes;

	wAttrib &= ~(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

	int c = (int)color;

	if (c & 1)
		wAttrib |= FOREGROUND_BLUE;
	if (c & 2)
		wAttrib |= FOREGROUND_GREEN;
	if (c & 4)
		wAttrib |= FOREGROUND_RED;
	if (c & 8)
		wAttrib |= FOREGROUND_INTENSITY;

	SetConsoleTextAttribute(outputHandle, wAttrib);
}

void clearScreen () 
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0, 0 };
	DWORD dw;
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	DWORD dwSize;
	
	cout.flush();
	GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo);
	
	dwSize = screenBufferInfo.dwSize.X * screenBufferInfo.dwSize.Y;
	
	FillConsoleOutputCharacter(outputHandle, ' ', dwSize, coord, &dw);
	FillConsoleOutputAttribute(outputHandle, screenBufferInfo.wAttributes, dwSize, coord, &dw);
	SetConsoleCursorPosition(outputHandle, coord);
}

void goToCoordinates (float x, float y)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);
}

void hideCursor () 
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = false;

	SetConsoleCursorInfo(hCon, &cci);
}

void showCursor () 
{
	CONSOLE_CURSOR_INFO cursorInfo;
	
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = TRUE;
	
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void setTitle (const char* title) 
{
	SetConsoleTitleA(title);
}

void drawFrame (int x1, int y1, int x2, int y2) 
{
	goToCoordinates(x1, y1);
	cout << (char)LEFT_UP;
	goToCoordinates(x2, y1);
	cout << (char)RIGHT_UP;
	goToCoordinates(x2, y2);
	cout << (char)RIGHT_DW;
	goToCoordinates(x1, y2);
	cout << (char)LEFT_DW;
	
	for (int i = x1 + 1; i < x2; i++) 
	{
		goToCoordinates(i, y1);
		cout << (char)LINE_HOR;
		goToCoordinates(i, y2);
		cout << (char)LINE_HOR;
	}
	
	for (int i = y1 + 1; i < y2; i++) 
	{
		goToCoordinates(x2, i);
		cout << (char)LINE_VER;
		goToCoordinates(x1, i);
		cout << (char)LINE_VER;
	}
}