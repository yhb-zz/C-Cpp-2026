#include <stdio.h>
#include <windows.h>
#include <conio.h>

void print_map(int map[8][8]) {
    // 墙壁字符 "■" 箱子字符 "▢" 玩家字符 "@" 空地字符 " " 目标字符 "★"

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (map[i][j]){
                case 0:
                    printf("   ");
                    break;
                case 1:
                    printf(" ■ ");
                    break;
                case 2:
                    printf(" @ ");
                    break;
                case 3:
                    printf(" ▢ ");
                    break;
                case 4:
                    printf(" ★ ");
                    break;
            }
        }
        printf("\n");
    }
}

int move(char direction, int map[8][8]) {
    int x = 0, y = 0;  // 玩家位置
    for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
            if (map[x][y] == 2) {
                break;
            }
        }
        if (map[x][y] == 2) {
            break;
        }
    }

    switch (direction) {
        case 'w':
            switch (map[x-1][y]) {
                case 1:
                case 4:
                    return 0;
                case 0:
                    map[x-1][y] = 2;
                    map[x][y] = 0;
                    return 0;
                case 3:
                    switch (map[x-2][y]) {
                        case 1:
                        case 3:
                            return 0;
                        case 0:
                        case 4:
                            map[x-2][y] = 3;
                            map[x-1][y] = 2;
                            map[x][y] = 0;
                            return 0;
                        default:
                            perror("switch0");
                    }
                default:
                    perror("switch1");
            }
        case 's':
            switch (map[x+1][y]) {
                case 1:
                case 4:
                    return 0;
                case 0:
                    map[x+1][y] = 2;
                    map[x][y] = 0;
                    return 0;
                case 3:
                    switch (map[x+2][y]) {
                        case 1:
                        case 3:
                            return 0;
                        case 0:
                        case 4:
                            map[x+2][y] = 3;
                            map[x+1][y] = 2;
                            map[x][y] = 0;
                            return 0;
                        default:
                            perror("switch2");
                    }
                default:
                    perror("switch3");
            }
        case 'a':
            switch (map[x][y-1]) {
                case 1:
                case 4:
                    return 0;
                case 0:
                    map[x][y-1] = 2;
                    map[x][y] = 0;
                    return 0;
                case 3:
                    switch (map[x][y-2]) {
                        case 1:
                        case 3:
                            return 0;
                        case 0:
                        case 4:
                            map[x][y-2] = 3;
                            map[x][y-1] = 2;
                            map[x][y] = 0;
                            return 0;
                        default:
                            perror("switch4");
                    }
                default:
                    perror("switch5");
            }
        case 'd':
            switch (map[x][y+1]) {
                case 1:
                case 4:
                    return 0;
                case 0:
                    map[x][y+1] = 2;
                    map[x][y] = 0;
                    return 0;
                case 3:
                    switch (map[x][y+2]) {
                        case 1:
                        case 3:
                            return 0;
                        case 0:
                        case 4:
                            map[x][y+2] = 3;
                            map[x][y+1] = 2;
                            map[x][y] = 0;
                            return 0;
                        default:
                            perror("switch6");
                    }
                default:
                    perror("switch7");
            }
        default:
            perror("switch8");
    }
    return 0;
}

int check_game_over(int map[8][8]) {
    // 返回 0 代表游戏未结束, 返回 1 代表游戏结束

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (map[i][j] == 4) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    char ch;

    // 0 空地  1 墙壁  2 玩家  3 箱子  4 目标(箱子的最终位置)
    int map[8][8] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 1, 0, 0, 0, 4, 1},
        {1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 3, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 3, 0, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 4, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
    };

    while(! check_game_over(map)) {
        system("cls");
        print_map(map);
        ch = _getch();
        move(ch, map);
    }

    system("cls");
    print_map(map);
    printf("Game over, you win!");
    return 0;
}