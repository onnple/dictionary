//
// Created by Once on 2019/8/12.
//

#ifndef DATALGORITHM_DICTIONARY_H
#define DATALGORITHM_DICTIONARY_H

// 散列表使用再散列法实现字典Dictionary

// 关键字
typedef int Keys;

// 数据实体
typedef struct values{
    char name[128];
    char author[128];
} Values;

typedef enum kinds{
    Avail, Emp, Dele
} Kinds;

// 数据记录
typedef struct dnode{
    Keys key;
    Values value;
    Kinds kind;
} DNode;

typedef enum{
    Linear, Square
} HashType;

// 字典Dictionary ADT对外接口
typedef struct dictionary{
    DNode *array;
    int length;
    int size;
    HashType type;
} Dictionary;


// 字典Dictionary函数声明
extern Dictionary *dict_init(int length);
extern int dict_is_empty(Dictionary *dict);
extern int dict_is_full(Dictionary *dict);
extern int dict_add(Dictionary *dict, Keys key, Values *value);
extern int dict_delete(Dictionary *dict, Keys key);
extern DNode *dict_get(Dictionary *dict, Keys key);
extern void dict_traverse(Dictionary *dict);
extern int dict_clear(Dictionary *dict);

#endif //DATALGORITHM_DICTIONARY_H
