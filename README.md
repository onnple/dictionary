# 散列表实现字典Dictionary
再散列法实现散列表，散列表实现字典Dictionary，原文地址：http://www.srcmini.com/1507.html  

## 字典Dictionary函数说明
### 1、初始化字典Dictionary
extern Dictionary *dict_init(int length);

### 2、判断字典Dictionary是否已空
extern int dict_is_empty(Dictionary *dict);

### 3、判断字典Dictionary是否已满
extern int dict_is_full(Dictionary *dict);

### 4、添加记录到字典Dictionary
extern int dict_add(Dictionary *dict, Keys key, Values *value);

### 5、从字典Dictionary中删除记录
extern int dict_delete(Dictionary *dict, Keys key);

### 6、从字典Dictionary中搜索记录
extern DNode *dict_get(Dictionary *dict, Keys key);

### 7、遍历字典Dictionary
extern void dict_traverse(Dictionary *dict);

### 8、清空和删除字典Dictionary
extern int dict_clear(Dictionary *dict);

