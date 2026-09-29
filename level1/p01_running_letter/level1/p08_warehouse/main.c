#include <stdio.h>
#include <stdlib.h>

struct Item {
    int index;
    char name[20];
    int number;
};

int main() {

    // 打开文件
    FILE *fp = fopen("warehouse.dat", "a+");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    // 获取文件元素个数
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    int items_number = (int)(size / sizeof(struct Item));
    rewind(fp);

    struct Item *warehouse = malloc(size);
    fread(warehouse, sizeof(struct Item), items_number, fp);

    fclose(fp);

    int option;
    while (1) {
        printf("欢迎来到仓库智慧管理系统，输入数字即可执行操作。\n1.显示库存列表\n2.入库\n3.出库\n4.保存并退出程序\n请输入：");
        scanf("%d", &option);
        if (option == 1) {
            if (! items_number) {
                printf("空空如也~\n");
            } else {
                for (int i = 0; i < items_number; i++) {
                    printf("序号：%d 名字：%s 数量：%d\n", warehouse[i].index, warehouse[i].name, warehouse[i].number);
                }
            }
        } else if (option == 2) {

            int input;
            printf("仓库中是否已经记录入库物品？\n1.是\n2.否\n请输入:");
            scanf("%d", &input);
            if (input == 1) {
                
            int index_;
            int in_number;
            printf("请输入入库物品序号：");
            scanf("%d", &index_);
            printf("请输入入库物品数量：");
            scanf("%d", &in_number);
            warehouse[index_ - 1].number += in_number;
            printf("%d 个 %s 已存入仓库。\n", in_number, warehouse[index_ - 1].name);

            } else if (input == 2) {

                // 获取入库信息
                char name[20];
                int number;
                printf("请输入物品名字：");
                scanf("%s", name);
                printf("请输入物品数量：");
                scanf("%d", &number);

                // 动态内存分配
                struct Item *p = realloc(warehouse, sizeof(struct Item) * (++items_number));
                size += sizeof(struct Item);
                if (p == NULL) {
                    perror("realloc");
                    return 1;
                }
                warehouse = p;
                p = NULL;

                // 添加新物品到仓库
                warehouse[items_number - 1].index = items_number;
                for (int i = 0; i < 20; i++) {
                    warehouse[items_number - 1].name[i] = name[i];
                }
                warehouse[items_number - 1].number = number;
            }

        } else if (option == 3) {
            int index;
            int out_number;
            printf("请输入取出的物品序号：");
            scanf("%d", &index);
            printf("请输入取出的物品数量：");
            scanf("%d", &out_number);
            if (out_number > warehouse[index - 1].number) {
                printf("%s总数为%d，无法取出。\n", warehouse[index - 1].name, warehouse[index - 1].number);
            } else if (out_number == warehouse[index - 1].number) {
                printf("%s总数为%d，全部取出。\n", warehouse[index - 1].name, warehouse[index - 1].number);
                warehouse[index - 1].number = 0;
            } else {
                warehouse[index - 1].number -= out_number;
                printf("已取出，%s剩余数量：%d\n", warehouse[index - 1].name, warehouse[index - 1].number);
            }
        } else if (option == 4) {
            FILE *fp_ = fopen("warehouse.dat", "w");
            fwrite(warehouse, sizeof(struct Item), items_number, fp_);
            fclose(fp_);
            break;
        } else {
            printf("请输入数字1~4!\n");
        }
    }

    return 0;
}