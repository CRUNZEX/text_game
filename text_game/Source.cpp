#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define maxBullet 5
#define maxStar 20

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
char cursor(int x, int y)
{
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[2];
    COORD c = { x,y };
    DWORD num_read;
    if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
        return '\0';
    else
        return buf[0];
}

//Score
void scorePrint(int score)
{
    gotoxy(65, 0);
    setcolor(7, 0);
    printf("Score : %d", score);
}

//Ship
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

//Star
void starPrint()
{
    int x, y, color = (rand() % 9) + 1;
    do
    {
        x = (rand() % 60) + 10;
        y = (rand() % 3) + 2;
    } while (cursor(x, y) == '*');
    gotoxy(x, y);
    setcolor(color, 0);
    printf("*");
}

//Bullet
void draw_bullet(int x, int y)
{
    gotoxy(x, y);
    setcolor(7, 0);
    printf("|");
}
void del_bullet(int x, int y)
{
    gotoxy(x, y);
    setcolor(0, 0);
    printf(" ");
}
int bulletPrint(int* bx, int* by, int* count, int* score)
{
    if (*by > 0)
    {
        del_bullet(*bx, *by);
        *by = *by - 1;
        if (cursor(*bx, *by) == '*') // Check Star
        {
            del_bullet(*bx, *by);
            starPrint();
            Beep(535, 200);         // Sound
            *score = *score + 1;
            *count %= maxBullet;
            return 0;
        }
        draw_bullet(*bx, *by);
        return 1;
    }
    else if (*by == 0)
    {
        del_bullet(*bx, *by);
        *count %= maxBullet;
        return 0;
    }
}

    //Main
int main()
{
    setcursor(0);
    int bullet[maxBullet] = { 0 }, bx[maxBullet], by[maxBullet], count = 0, move = 0;
    char ch = ' ';
    int x = 38, y = 20, score = 0;

    srand(time(NULL));
    for (int num = 0; num < maxStar; num++)
        starPrint();

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

            if (ch == ' ' && bullet[count] == 0 && count < maxBullet)
            {
                bullet[count] = 1;
                bx[count] = x + 1;
                by[count] = y - 1;
                count++;
            }

            fflush(stdin);
        }

        for (int num = 0; num < maxBullet; num++)
        {
            if (bullet[num] == 1)
                bullet[num] = bulletPrint(&bx[num], &by[num], &count, &score);
        }

        scorePrint(score);
        
        draw_space(x, y);
        x += move;
        draw_ship(x, y);
        if (x == 0 || x == 75)
            move = 0;

        Sleep(100);
    } while (ch != 'x');
    setcolor(7, 0);
    printf("\n>> Exit");
    return 0;
}