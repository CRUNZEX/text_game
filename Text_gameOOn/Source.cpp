#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

// style
void setcursor(bool visible) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

// control
char cursor(int x, int y) {
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[2]; COORD c = { x,y }; DWORD num_read;
    if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
        return '\0';
    else
        return buf[0];
}
void gotoxy(int x, int y)
{
    COORD c = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y) {
    gotoxy(x, y);
    setcolor(2, 4);
    printf(" <-0-> ");
}
void draw_bullet(int x, int y) {
    gotoxy(x, y);
    setcolor(10, 0);
    printf("^");
}
void erase_bullet(int x, int y) {
    gotoxy(x, y);
    setcolor(7, 0);
    printf(" ");
}
void erase_ship(int x, int y) {
    gotoxy(x, y);
    setcolor(7, 0);
    printf("       ");
}
int main()
{
    char ch = '.';
    int x = 38, y = 20, bx[5] = { 0 }, by[5] = { 0 };
    int path = 0, sleep = 100;
    int j = -1, max = 0;
    int bull[5] = { 0 };
    int sx, sy, scount = 0;
    int score = 0;
    setcursor(0);
    srand(time(NULL));
    draw_ship(x, y);

    do {
        gotoxy(80, 0);
        setcolor(7, 0);
        printf("score : %d", score);
        sx = rand() % 71;
        sy = rand() % 6;
        if (sx <= 70 && sx >= 10 && sy >= 2 && sy <= 5 && scount < 20 && cursor(sx, sy) != '*')
        {
            gotoxy(sx, sy);
            setcolor(7, 0);
            printf("*");
            scount++;
        }
        if (_kbhit())
        {
            ch = _getch();
            if (ch == ' ' && max < 5)
            {
                ++j;
                bull[j % 5] = 1;
                bx[j % 5] = x + 3;
                by[j % 5] = y - 1;
                ++max;
            }
        }

        if (ch == 'a') { path = 1; }
        if (ch == 'd') { path = 2; }
        if (ch == 's') { path = 0; }

        int i = 0;
        while (i < 5) {
            if (bull[i] == 1 && by[i] > 0)
            {
                erase_bullet(bx[i], by[i]);
                --max;
                if (by[i] == 2)
                {
                    bull[i] = 0;
                }
                else
                {
                    if (cursor(bx[i], by[i] - 1) == '*')
                    {
                        Sleep(sleep);
                        by[i] = 0;
                        erase_bullet(bx[i], by[i] + 1);
                        //      --max;
                        Beep(700, 100);
                        score++;
                        scount--;
                    }
                    else
                    {
                        draw_bullet(bx[i], --by[i]);
                    }
                }
            }
            ++i;
        }

        if (x > 0 && x < 75)
        {
            if (path == 1)
            {
                erase_ship(x, y);
                draw_ship(--x, y);
                Sleep(sleep);
            }
            else if (path == 2)
            {
                erase_ship(x, y);
                draw_ship(++x, y);
                Sleep(sleep);
            }
        }
        if (ch == 'a' && x == 75)
        {
            erase_ship(x, y);
            draw_ship(--x, y);
            Sleep(sleep);
        }
        if (ch == 'd' && x == 0)
        {
            erase_ship(x, y);
            draw_ship(++x, y);
            Sleep(sleep);
        }
        fflush(stdin);
        Sleep(sleep);

    } while (ch != 'x');
    setcolor(7, 0);

    return 0;
}