#include<stdio.h>
#include<windows.h>
#include<conio.h>
void setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void gotoxy(int x, int y)
{
    COORD c = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
void erase_ship(int x, int y)
{
    gotoxy(x, y); printf("       ");
}
void draw_ship(int x, int y)
{
    gotoxy(x, y); printf(" <-0-> ");
}
void erase_bullet(int x, int y)
{
    gotoxy(x, y); printf(" ");
}
void bullet(int x, int y)
{
    gotoxy(x, y);
    printf("-");
}
int main()
{
    setcursor(0);
    char ch = '.';
    int bu = 0, direction = 0, bx, by;
    int x = 38, y = 20;
    draw_ship(x, y);
    do {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'a' && x > 0) { direction = -1; }
            if (ch == 'd' && x < 75) { direction = 1; }
            if (ch == 's') { direction = 0; }
            if (ch == ' ') { bu = 1; bx = x + 3; by = y - 1; }
        }
        if (direction != 0)
        {
            erase_ship(x, y);
            x += direction;
            draw_ship(x, y);
            Sleep(100);
            if (x == 0 || x == 75)
            {
                direction = 0;
            }
        }
        if (bu == 1)
        {
            erase_bullet(bx, by);
            bullet(bx, --by);
            if (by <= 0)
            {
                bu = 0;
                erase_bullet(bx, by);
            }
        }

    } while (ch != 'x');

    return 0;
}