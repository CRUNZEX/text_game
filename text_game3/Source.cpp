#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define maxBullet 5
void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_ship(int x, int y)
{

    gotoxy(x, y);
    setcolor(2, 4);
    printf(" <-0-> ");
}
void draw_space(int x, int y)
{
    gotoxy(x, y);
    setcolor(0, 0);
    printf("       ");
}
void draw_bullet(int x, int y)
{
    gotoxy(x, y);
    setcolor(7, 0);
    printf("M3OW~");
}
void del_bullet(int x, int y)
{
    gotoxy(x, y);
    setcolor(0, 0);
    printf("     ");
}
void test(int x, int y)
{
    gotoxy(x, y);
    printf("Test");
}
int bulletPrint(int *bx, int *by, int *count)
{
    if (*by > 0)
    {
        del_bullet(*bx, *by);
        *by = *by - 1;
        draw_bullet(*bx, *by);
        return 1;
    }
    else if (*by == 0)
    {
        del_bullet(*bx, *by);
        *count = *count - 1;
        return 0;
    }
}
int main()
{
    setcursor(0);
    int bullet[maxBullet] = { 0 }, bx[maxBullet], by[maxBullet], count = 0, move = 0;
    char ch = ' ';
    int x = 38, y = 20;
    
    draw_ship(38, 20);
    do
    {
        if (_kbhit())
        {
            ch = _getch();
            if (ch == 'a' && x > 0)
                move = -1;
            if (ch == 'd' && x < 75)
                move = 1;
            if (ch == 's')
                move = 0;

            if (ch == ' ')
            {
                if (bullet[0] == 0 && count < maxBullet)
                {
                    bullet[0] = 1;
                    bx[0] = x + 1;
                    by[0] = y - 1;
                    count++;
                }
                else if (bullet[1] == 0 && count < maxBullet)
                {
                    bullet[1] = 1;
                    bx[1] = x + 1;
                    by[1] = y - 1;
                    count++;
                }
                else if (bullet[2] == 0 && count < maxBullet)
                {
                    bullet[2] = 1;
                    bx[2] = x + 1;
                    by[2] = y - 1;
                    count++;
                }
                else if (bullet[3] == 0 && count < maxBullet)
                {
                    bullet[3] = 1;
                    bx[3] = x + 1;
                    by[3] = y - 1;
                    count++;
                }
                else if (bullet[4] == 0 && count < maxBullet)
                {
                    bullet[4] = 1;
                    bx[4] = x + 1;
                    by[4] = y - 1;
                    count++;
                }
            }

            fflush(stdin);
        }

        for (int num = 0; num < maxBullet; num++)
        {
            if (bullet[num] == 1)
                bullet[num] = bulletPrint(&bx[num], &by[num], &count);
        }

        draw_space(x, y);
        x += move;
        draw_ship(x, y);
        if (x == 0 || x==75)
            move = 0;

        Sleep(100);
    } while (ch != 'x');
    setcolor(7, 0);
    printf("\n>> Exit");
    return 0;
}