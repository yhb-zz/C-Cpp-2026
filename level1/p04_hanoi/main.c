#include <stdio.h>

int move_plate(int num,char start,char end){
    //num表示start柱子上需要搬运到end柱子上的圆盘的数量
    char third; //第三个柱子
    if(start != 'A' && end != 'A'){third = 'A';}
    else if(start != 'B' && end != 'B'){third = 'B';}
    else{third = 'C';}

    if(num == 1){
        printf("%c->%c\n", start, end);
        return 0;
    }
    else{
        move_plate(num - 1, start, third);
        printf("%c->%c\n", start, end);
        move_plate(num - 1, third, end);
        return 0;
    }
}

int main() {
    int num;

    printf("Please input the layers of the hanoi:");
    scanf("%d", &num);
    move_plate(num, 'A', 'B');
    return 0;
}
