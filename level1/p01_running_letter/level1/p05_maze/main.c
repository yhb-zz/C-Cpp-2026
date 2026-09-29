#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int random(int min,int max){
    return rand() % ( max - min + 1 ) + min;
}

int sleep(int seconds){
    clock_t start = clock();
    while (clock() - start <= CLOCKS_PER_SEC * seconds);
    return 0;
}

int explore(int length, int width, int x, int y, int maze[length][width][4]){
    int unknown; // 相邻区域(上下左右)未被探索的数量
    int direction[4];  // 对应上右下左（顺时针）,0 代表无法探索， 1代表可以探索
    int i, j, k;

    while (1){
        // 初始化
        unknown = 0;
        for (i = 0; i < 4; i++){
            direction[i] = 0;
        }

        if(maze[x][y][0] >= 0){
            if(maze[x][y-1][0] && maze[x][y-1][1] && maze[x][y-1][2] && maze[x][y-1][3]){
                unknown += 1;
                direction[0] = 1;
            }
        }
        if(maze[x][y][1] >= 0){
            if(maze[x+1][y][0] && maze[x+1][y][1] && maze[x+1][y][2] && maze[x+1][y][3]){
                unknown += 1;
                direction[1] = 1;
            }
        }
        if(maze[x][y][2] >= 0){
            if(maze[x][y+1][0] && maze[x][y+1][1] && maze[x][y+1][2] && maze[x][y+1][3]){
                unknown += 1;
                direction[2] = 1;
            }
        }
        if(maze[x][y][3] >= 0){
            if(maze[x-1][y][0] && maze[x-1][y][1] && maze[x-1][y][2] && maze[x-1][y][3]){
                unknown += 1;
                direction[3] = 1;
            }
        }
        if (unknown == 0){
            return -1;  // 回溯
        }
        else if (unknown == 1){
            for(i = 0; i < 4; i++){
                if(direction[i]){
                    if(i == 0){
                        maze[x][y][0] = 0;
                        maze[x][y-1][2] = 0;
                        explore(length, width, x, y-1, maze);
                    }
                    else if (i == 1){
                        maze[x][y][1] = 0;
                        maze[x+1][y][3] = 0;
                        explore(length, width, x+1, y, maze);
                    }
                    else if (i == 2){
                        maze[x][y][2] = 0;
                        maze[x][y+1][0] = 0;
                        explore(length, width, x, y+1, maze);
                    }
                    else{
                        maze[x][y][3] = 0;
                        maze[x-1][y][1] = 0;
                        explore(length, width, x-1, y, maze);
                    }
                }
            }
        }
        else{
            j = random(1, unknown);
            for (i = 0; i < 4; i++){
                if(direction[i]){
                    j -= 1;
                    if (j == 0){
                        if(i == 0){
                        maze[x][y][0] = 0;
                        maze[x][y-1][2] = 0;
                        explore(length, width, x, y-1, maze);
                        }
                        else if (i == 1){
                            maze[x][y][1] = 0;
                            maze[x+1][y][3] = 0;
                            explore(length, width, x+1, y, maze);
                        }
                        else if (i == 2){
                            maze[x][y][2] = 0;
                            maze[x][y+1][0] = 0;
                            explore(length, width, x, y+1, maze);
                        }
                        else{
                            maze[x][y][3] = 0;
                            maze[x-1][y][1] = 0;
                            explore(length, width, x-1, y, maze);
                        }
                    }
                }
            }
        }
    }
}

int print_maze(int length, int width, int maze_display[length * 2 + 1][width * 2 + 1]){
    // 墙壁字符串" ▢ " 玩家字符串" @ " 空地字符串 "   " 出口字符串 " ★ "
    // 墙壁 1 玩家 2 空地 0 出口 3
    int i, j;

    // 打印
    for(i = 0; i < length * 2 + 1; i++){
        for(j = 0; j < width * 2 + 1; j++){
            if(maze_display[i][j]){
                if (maze_display[i][j] == 1){
                    printf(" ▢ ");
                }
                else if (maze_display[i][j] == 2){
                    printf(" @ ");
                }
                else{
                    printf(" ★ ");
                }
            }
            else{
                printf("   ");
            }
//            printf("%d ", maze_display[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int maze_init(int length, int width, int maze[length][width][4], int maze_display[length * 2 + 1][width * 2 + 1]){
    int i, j;

    // 初始化maze_display全部元素为 0
    for(i = 0; i < length * 2 + 1; i++){
        for(j = 0; j < width * 2 + 1; j++){
            maze_display[i][j] = 0;
        }
    }

    // 确定墙的位置
    for(i = 0; i < length * 2 + 1; i += 2){
        for(j = 0; j < width * 2 + 1; j += 2){
            maze_display[i][j] = 1;
        }
    }
    i = length * 2;
    for(j = 0; j < width * 2 + 1; j++){
        maze_display[i][j] = 1;
    }
    j = length * 2;
    for(i = 0; i < width * 2 + 1; i++){
        maze_display[i][j] = 1;
    }
    for(i = 0; i < length * 2 + 1; i += 2){
        for(j = 1; j < width * 2 + 1; j += 2){
            if(maze[i/2][(j-1)/2][3]){
                maze_display[i][j] = 1;
            }
        }
    }
    for(i = 1; i < length * 2 + 1; i += 2){
        for(j = 0; j < width * 2 + 1; j += 2){
            if(maze[(i-1)/2][j/2][0]){
                maze_display[i][j] = 1;
            }
        }
    }

    // 设置玩家起始位置和终点
    maze_display[1][0] = 2;
    maze_display[length * 2 - 1][width * 2] = 3;
}

int maze_move(int length, int width, char ch, int maze_display[length * 2 + 1][width * 2 + 1]){
    int x, y;

    for(x = 0; x < length * 2 + 1; x++){
        for(y = 0; y < width * 2 + 1; y++){
            if(maze_display[x][y] == 2){
                break;
            }
        }
        if(maze_display[x][y] == 2){
                break;
            }
    }

    if(ch == 'a' || ch == 'A'){
        if(!maze_display[x][y-1]){
            maze_display[x][y-1] = 2;
            maze_display[x][y] = 0;
        }
        else if(maze_display[x][y+1] == 3){return 1;}
    }
    else if(ch == 'w' || ch == 'W'){
        if(!maze_display[x-1][y]){
            maze_display[x-1][y] = 2;
            maze_display[x][y] = 0;
        }
        else if(maze_display[x][y+1] == 3){return 1;}
    }
    else if(ch == 's' || ch == 'S'){
        if(!maze_display[x+1][y]){
            maze_display[x+1][y] = 2;
            maze_display[x][y] = 0;
        }
        else if(maze_display[x][y+1] == 3){return 1;}
    }
    else if(ch == 'd' || ch == 'D'){
        if(!maze_display[x][y+1]){
            maze_display[x][y+1] = 2;
            maze_display[x][y] = 0;
        }
        else if(maze_display[x][y+1] == 3){return 1;}
    }
    return 0;
}

int main() {
    SetConsoleOutputCP(65001);  // 设置控制台输出为 UTF-8
    int seed = (unsigned)time(NULL);  // 记录种子，用于调试
    srand(seed);  // 设置随机种子
    int i, j, k;
    char ch;  // 储存键盘输入
    int result = 0;  // 判断游戏是否胜利

    // 获取用户输入：迷宫尺寸
    int size;
    printf("请输入迷宫尺寸：");
    scanf("%d", &size);

    const int length = size;
    const int width = size;

    // 初始化迷宫列表, 尺寸10*10每个格子的四个数分别对应上右下左（顺时针）
    // 每个格子的四个数分别对应上右下左（顺时针），-1 为边界，0 表示通路，1 表示有墙
    int maze[length][width][4];
    for(i = 0; i < length; i++){
        for(j = 0; j < width; j++){
            for(k = 0; k < 4; k++){
                maze[i][j][k] = 1;
                if(i == 0 && k == 3){maze[i][j][k] = -1;}
                else if(i == length - 1 && k == 1){maze[i][j][k] = -1;}
                if(j == 0 && k == 0){maze[i][j][k] = -1;}
                else if(j == width - 1 && k == 2){maze[i][j][k] = -1;}
            }
        }
    }

    // 迷宫生成
    explore(length, width, 0, 0, maze);

    // 用于在控制台上打印迷宫
    int maze_display[length * 2 + 1][width * 2 + 1];  // 墙壁 1 玩家 2 空地 0 出口 3

    // 初始化
    maze_init(length, width, maze, maze_display);

    //运行
    while (1){
        system("cls");
        print_maze(length, width, maze_display);
        ch = _getch();
        result = maze_move(length, width, ch, maze_display);
        if (result){break;}
    }

    // 结束页面
    system("cls");
    printf("胜利!!!");
    sleep(2);
    
    return 0;
}