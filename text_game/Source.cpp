#include <stdio.h>
#include <conio.h>
#include <windows.h>
void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
    gotoxy(x, y);
    printf(" <-0-> ");
}
void draw_space(int x, int y)
{
    gotoxy(x, y);
    printf("       ");
}
int main()
{
    char ch = ' ';
    int x = 38, y = 20;
    draw_ship(38, 20);
    do
    {
        if (_kbhit())
        {
            ch = _getch();
            if (ch == 'a' && x > 0)
            {
                draw_ship(--x, y);
            }
            if (ch == 'd' && x < 75)
            {
                draw_ship(++x, y);
            }
            if (ch == 'w' && y > 0)
            {
                draw_space(x, y);
                draw_ship(x, --y);

            }
            if (ch == 's' && y < 22)
            {
                draw_space(x, y);
                draw_ship(x, ++y);
            }
            fflush(stdin);
        }
        Sleep(100);
    } while (ch != 'x');
    printf("\nExit");
    return 0;
}