//
// Created by Once on 2019/8/12.
//

#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dictionary *dict_init(int length){
    if(length <= 0){
        perror("length is too small");
        return NULL;
    }
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if(!dict){
        perror("alloc mem for dict error");
        return NULL;
    }
    dict->size = 0;
    dict->length = length;
    dict->type = Linear;
    dict->array = (DNode*)malloc(sizeof(DNode) * length);
    if(!dict->array){
        perror("alloc mem for array error");
        free(dict);
        return NULL;
    }
    for (int i = 0; i < length; ++i)
        dict->array[i].kind = Emp;
    return dict;
}

int dict_is_empty(Dictionary *dict){
    if(dict == NULL)
        return 1;
    return dict->size == 0;
}

int dict_is_full(Dictionary *dict){
    if(dict == NULL)
        return 0;
    return dict->size == dict->length;
}

static int hash(Dictionary *dict, Keys key){
    return key % dict->length;
}

// 再散列
static int rehashing(Dictionary *dict){
    int old_length = dict->length;
    DNode *old_array = dict->array;
    int length = 2 * old_length + 3;
    DNode *array = (DNode*)malloc(sizeof(DNode) * length);
    if(!array){
        perror("realloc mem for array error");
        return 0;
    }
    for (int j = 0; j < length; ++j)
        array[j].kind = Emp;
    dict->length = length;
    dict->array = array;
    dict->type = Square;
    dict->size = 0;
    for (int i = 0; i < old_length; ++i) {
        if(old_array[i].kind == Avail)
            dict_add(dict, old_array[i].key, &old_array[i].value);
    }
    free(old_array);
    printf("rehashing finished.\n");
    return 1;
}

int dict_add(Dictionary *dict, Keys key, Values *value){
    if(dict == NULL || value == NULL)
        return 0;
    if((float)dict->size / (float)dict->length >= 0.75 && !rehashing(dict)){
        perror("rehasing error.");
        return 0;
    }
    DNode *node = dict_get(dict, key);
    if(node->kind != Avail){
        node->kind = Avail;
        node->key = key;
        strcpy(node->value.name, value->name);
        strcpy(node->value.author, value->author);
        dict->size++;
    }
    else{
        strcpy(node->value.name, value->name);
        strcpy(node->value.author, value->author);
    }
    return 1;
}

// 散列收缩
static int shrink(Dictionary *dict){
    int old_length = dict->length;
    DNode *old_array = dict->array;
    int length = (old_length - 3) / 2;
    DNode *array = (DNode*)malloc(sizeof(DNode) * length);
    if(!array){
        perror("realloc mem for array error");
        return 0;
    }
    for (int j = 0; j < length; ++j)
        array[j].kind = Emp;
    dict->length = length;
    dict->array = array;
    dict->type = Linear;
    dict->size = 0;
    for (int i = 0; i < old_length; ++i) {
        if(old_array[i].kind == Avail)
            dict_add(dict, old_array[i].key, &old_array[i].value);
    }
    free(old_array);
    printf("shrinking finished.\n");
    return 1;
}

int dict_delete(Dictionary *dict, Keys key) {
    if (dict == NULL || dict->size == 0)
        return 0;
    DNode *node = dict_get(dict, key);
    if (node->kind == Avail) {
        node->kind = Dele;
        dict->size--;
    }
    if((float)dict->size / (float)dict->length <= 0.125 && !shrink(dict)){
        perror("shrink hash table error");
        return 0;
    }
    return 1;
}

// 1、线性探测法，任何再散列使用线性探测法，表初始化大小使用线性探测法
static DNode *hash_linear_probing(Dictionary *dict, Keys key){
    int index = hash(dict, key);
    DNode *node = &dict->array[index];
    int i = 0;
    while(node->kind != Emp && node->key != key){
        index += ++i;
        index %= dict->length;
        node = &dict->array[index];
    }
    return node;
}

// 2、平方探测法，散列收缩使用平方探测法
static DNode *hash_square_probing(Dictionary *dict, Keys key){
    int index = hash(dict, key);
    DNode *node = &dict->array[index];
    int i = 0;
    while(node->kind != Emp && node->key != key){
        ++i;
        index += i * i;
        index %= dict->length;
        node = &dict->array[index];
    }
    return node;
}

DNode *dict_get(Dictionary *dict, Keys key){
    if(dict == NULL)
        return NULL;
    if(dict->type == Linear)
        return hash_linear_probing(dict, key);
    else
        return hash_square_probing(dict, key);
}

void dict_traverse(Dictionary *dict){
    if(dict == NULL)
        return;
    for (int i = 0; i < dict->length; ++i) {
        if(dict->array[i].kind == Emp)
            printf("[Empty] ");
        else if(dict->array[i].kind == Dele)
            printf("[Deleted] ");
        else
            printf("(%s) ", dict->array[i].value.name);
    }
    printf("\n");
}

int dict_clear(Dictionary *dict){
    if(dict == NULL)
        return 0;
    free(dict->array);
    free(dict);
    return 1;
}
