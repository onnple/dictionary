#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"


static void dict(void){
    Dictionary *dict = dict_init(23);
    for (int i = 0; i < 100; ++i) {
        Values v;
        char temp[32];
        itoa(i * i * i, temp, 10);
        strcpy(v.name, temp);
        strcpy(v.author, "Descartes");
        dict_add(dict, i * i * i, &v);
    }
    dict_traverse(dict); // 遍历Dictionary

    for (int k = 0; k < 100; ++k) {
        DNode *node = dict_get(dict, k * k * k); // 搜索Dictionary中的元素
        if(node->kind == Avail)
            printf("|%s| ", node->value.name);
    }
    printf("\n");

    for (int j = 0; j < 100; ++j) {
        dict_delete(dict, j * j * j); // 删除Dictionary中的元素
    }

    dict_clear(dict); // 清空Dictionary和清除Dictionary
}

int main() {
    dict();
    return 0;
}

