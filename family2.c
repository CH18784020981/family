#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NUM 50

typedef struct person {
    char name[NUM];
    char date[NUM];
    char sex[NUM];
    int generation;
    struct person *header;
    struct person *left;
    struct person *right;
} people;
people *result = NULL;
people *node[NUM][NUM] = {NULL};

/**
 * 用于排序的显示
 */
void Display2(people *display) {
    if (display != NULL) {
        for (int i = 0; i < 100; i++) {
            if (node[display->generation - 1][i] == NULL) {
                node[display->generation - 1][i] = display;
                break;
            }
        }
        Display2(display->right);
        Display2(display->left);
    }
}

/**
 *  用于更改的查询
 */
void SearchName2(char *names, people *header) {
    if (header != NULL) {
        if (strcmp(header->name, names) == 0) {
            result = header;
        }
        SearchName2(names, header->right);
        SearchName2(names, header->left);
    }
}

/**
 * 查询
 */
void SearchName(char *names, people *header) {

    if (header != NULL) {
        if (strcmp(header->name, names) == 0) {
            printf("姓名：%s  性别：%s  出生日期：%s\n", header->name, header->sex, header->date);
            if (header->left == NULL) {
                printf("没有孩子\n");
            } else {
                header = header->left;
                printf("孩子：%s，", header->name);
                while (header->right != NULL) {
                    header = header->right;
                    printf("%s，", header->name);
                }
                printf("\n");
            }

            return;
        }

        SearchName(names, header->right);
        SearchName(names, header->left);
    }
}

/**
 * 排序
 */
void sort(people *sort) {
    Display2(sort);
    int j = 0;
    for (int p = 0; p < 100; p++) {
        if (node[p][0] == NULL) {
            break;
        }
        printf("第%d代\n", p + 1);
        for (int i = 1; i < 100; i++) {
            if (node[p][i] == NULL) {
                break;
            }
            people *tem = node[p][i];
            j = i - 1;
            while (j >= 0 && strcmp(tem->date, node[p][j]->date) < 0) {
                node[p][j + 1] = node[p][j];
                j--;
            }
            node[p][j + 1] = tem;
        }
        for (int o = 0; o < 100; o++) {
            if (node[p][o] == NULL) {
                break;
            }
            SearchName(node[p][o]->name, node[p][o]);
            node[p][o] = NULL;
        }
    }
}

/**
 * 显示
 */
void display(people *display) {
    Display2(display);
    for (int i = 0; i < 100; i++) {
        if (node[i][0] == NULL) {
            break;
        }
        printf("第%d代\n", i + 1);
        for (int j = 0; j < 100; j++) {
            if (node[i][j] == NULL) break;
            SearchName(node[i][j]->name, node[i][j]);
            node[i][j] = NULL;
        }

    }
}

/**
 * 添加
 */
void AddName(char *names, people *t) {
    SearchName2(names, t);
    people *header = (people *) malloc(sizeof(people));
    printf("请输⼊入成员姓名\n");
    scanf("%s", header->name);
    while (getchar() != '\n');
    printf("请输⼊入成员性别\n");
    scanf("%s", header->sex);
    while (getchar() != '\n');
    printf("请输⼊入成员出⽣生⽇日期");
    scanf("%s", header->date);
    header->right = NULL;
    header->left = NULL;
    header->generation = result->generation + 1;
    header->header = result;
    if (result->left == NULL) {
        result->left = header;
    } else {
        result = result->left;
        while (result->right != NULL) {
            result = result->right;
        }
        result->right = header;
    }
}

/**
 * 删除
 */
void DeleteInformation(char *names, people *header) {
    SearchName2(names, header);
    if (result == NULL || strcmp(result->name, names) != 0) {
        printf("查无此人,请重新操作\n");
        return;
    }
    if (result->header->left == result) {
        result->header->left = result->right;
    } else {
        people *pl = result->header->left;
        while (pl->right != result) {
            pl = pl->right;
        }
        pl->right = result->right;

    }

}

/**
 * 修改
 */
void ModifyInformation(char *names, people *header) {

    SearchName2(names, header);

    if (result == NULL) {
        printf("查⽆无此⼈，请重新操作");
        return;
    }

    printf("请输⼊成员姓名\n");
    while (getchar() != '\n');
    scanf("%s", result->name);
    while (getchar() != '\n');
    printf("请输⼊成员性别\n");
    scanf("%s", result->sex);
    printf("请输⼊成员出⽣日期\n");
    scanf("%s", result->date);
    printf("修改成功\n");
}


int main() {
    people *family = (people *) malloc(sizeof(people));
    strcpy(family->name, "陈一");
    strcpy(family->date, "1970-1-1");
    strcpy(family->sex, "男");
    family->generation = 1;
    family->right = NULL;
    family->left = NULL;
    family->header = NULL;
    people *descendant = (people *) malloc(sizeof(people));
    strcpy(descendant->name, "陈海");
    strcpy(descendant->date, "1990-1-1");
    strcpy(descendant->sex, "男");
    descendant->left = NULL;
    descendant->right = NULL;
    descendant->generation = 2;
    family->left = descendant;
    descendant->header = family;
    people *SecondGeneration = (people *) malloc(sizeof(people));
    strcpy(SecondGeneration->name, "陈浩");
    strcpy(SecondGeneration->date, "1990-1-2");
    strcpy(SecondGeneration->sex, "男");
    SecondGeneration->right = NULL;
    SecondGeneration->left = NULL;
    descendant->right = SecondGeneration;
    SecondGeneration->generation = 2;
    SecondGeneration->header = family;
    int end = 0;
    char names[NUM] = {"陈浩"};
    int input;
    while (2) {
        printf("欢迎来到家谱管理理系统!\n"
               "1. 显示家谱图\n"
               "2. 根据姓名查询，输出成员信息 \n"
               "3. 给某个成员添加孩子\n4. 修改某个成员信息\n"
               "5. 删除某成员(连同其后代) \n"
               "6. 按出⽣日期增顺显示家族成员 \n"
               "7. 退出系统\n");
        scanf("%d", &input);
        if (input == 1) {
            display(family);
        } else if (input == 2) {
            printf("请输⼊要查询成员姓名\n");
            scanf("%s", names);
            SearchName(names, family);
        } else if (input == 3) {
            printf("输入你需要添加孩子的成员\n");
            scanf("%s", names);
            AddName(names, family);
        } else if (input == 4) {
            printf("请输⼊要修改成员姓名\n");
            scanf("%s", names);
            ModifyInformation(names, family);
        } else if (input == 5) {
            printf("请输⼊要删除成员姓名\n");
            scanf("%s", names);
            DeleteInformation(names, family);
        } else if (input == 6) { sort(family); }
        else if (input == 7) {
            end = 2;
        }
        if (end == 2) {
            break;
        }

    }

}

