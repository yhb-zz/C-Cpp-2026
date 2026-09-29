#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// 返回终端宽度（列数），失败返回 80
int get_console_width() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(h, &info)) {
        return info.srWindow.Right - info.srWindow.Left + 1;
    }
    return 80;  // 拿不到就用默认值
}

int main() {
    int width = get_console_width();

    while (1){
        int i;
        for(i = 0; i+1 <= width; i++) {
            int j;
            system("cls");
            for(j = 1; j <= i; j++) {
                printf(" ");
            }
            printf("A");
        }

        for(i = width-1; i >= 0; i--) {
        int j;
        system("cls");
        for(j = 1; j <= i; j++) {
            printf(" ");
        }
        printf("A");
        }
    }

    return 0;
}