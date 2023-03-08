#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "types.hpp"
using namespace std;
int temp_count = 1;

int type_width[4] = {4, 8, 1, 1};
string type_name[4] = {"int", "float", "char", "bool"};

string op_name[42] = {
    "addi", "subi", "muli", "divi", "invi",
    "addf", "subf", "mulf", "divf", "invf",
    "movi", "movf", "movc", "movb",
    "itof", "itoc", "itob",
    "ftoi", "ftoc", "ftob",
    "ctoi", "ctof", "ctob",
    "btoi", "btof", "btoc",
    "and", "or", "not", "eq", "ne", "gt", "ge", "lt", "le",
    "jmp", "jeq", "jne", "jgt", "jge", "jlt", "jle"};


int conv[4][4] = {
    {-1, itof, itoc, itob},
    {ftoi, -1, ftoc, ftob},
    {ctoi, ctof, -1, ctob},
    {btoi, btof, btoc, -1}};

//生成新的符号，将新的数据进行输入
symbol *new_symbol(symbol_list *list, char *name, val_type_ val_type)
{
    symbol *id = (symbol*)malloc(sizeof(symbol));
    strcpy(id->name, name);
    id->val_type = val_type;
    id->width = type_width[val_type];
    id->addr = list->end;
    list->end += id->width;
    id->next = list->head;
    list->head = id;
    return id;
}

//生成一个临时变量
int new_temp(symbol_list *list, val_type_ val_type)
{
    symbol *id =(symbol *)malloc(sizeof(symbol));
    sprintf(id->name, "_t%d", temp_count++);
    id->val_type = val_type;
    id->width = type_width[val_type];
    id->addr = list->end;
    list->end += id->width;
    id->next = list->head;
    list->head = id;
    return id->addr;
}

//寻找符号，由于符号表设计的时候是多级的，在本小段找不到就会上一层找
symbol *find_symbol(symbol_list *list, char *name)
{
    symbol *id;
    symbol_list *list2 = list;
    while (list2 != NULL)
    {
        id = find_local_symbol(list2, name);
        if (id != NULL)
            return id;
        list2 = list2->prev;
    }
    return NULL;
}

//使用地址来寻找符号
symbol *find_symbol_by_addr(symbol_list *list, int addr)
{
    symbol *id;
    symbol_list *list2 = list;
    while (list2 != NULL)
    {
        symbol *id2 = list2->head;
        while (id2 != NULL)
        {
            if (id2->addr == addr)
                return id2;
            id2 = id2->next;
        }
        list2 = list2->prev;
    }
    return NULL;
}

//寻找此表里的符号
symbol *find_local_symbol(symbol_list *list, char *name)
{
    symbol *id = list->head;
    while (id != NULL)
    {
        if (strcmp(id->name, name) == 0)
            return id;
        id = id->next;
    }
    return NULL;
}

//创建新的符号表
symbol_list *new_symbol_list(symbol_list *prev, int addr)
{
    symbol_list *list = (symbol_list *)malloc(sizeof(symbol_list));
    list->head = NULL;
    list->prev = prev;
    list->begin = addr;
    list->end = addr;
    return list;
}

//打印符号表
void print_symbol_list(symbol_list *list)
{
    symbol *id = list->head;
    printf("\n--------- symbol list ---------\n");
    printf("name\ttype\taddr\twidth\n");
    printf("-------------------------------\n");
    while (id != NULL)
    {
        printf("%s\t%s\t%d\t%d\n", id->name, type_name[id->val_type].c_str(), id->addr, id->width);
        id = id->next;
    }
    printf("-------------------------------\n\n");
}

//删除符号表
void delete_symbol_list(symbol_list *list)
{
    if (list == NULL)
        return;
    symbol *id = list->head, *id2;
    while (id != NULL)
    {
        id2 = id->next;
        free(id);
        id = id2;
    }
    free(list);
}


//生成新的常量
constant *new_constant(constant_list *list, constant_val val, val_type_ val_type)
{
    constant *c = find_constant(list, val, val_type);
    if (c == NULL)
    {
        c = (constant *)malloc(sizeof(constant));
        c->val = val;
        c->val_type = val_type;
        c->width = type_width[val_type];
        c->addr = list->end;
        list->end += c->width;
        c->next = list->head;
        list->head = c;
    }
    return c;
}

//寻找常量
constant *find_constant(constant_list *list, constant_val val, val_type_ val_type)
{
    constant *c = list->head;
    while (c != NULL)
    {
        if (c->val_type == val_type && memcmp(&c->val, &val, c->width) == 0)
            return c;
        c = c->next;
    }
    return NULL;
}

constant *find_constant_by_addr(constant_list *list, int addr)
{
    constant *c = list->head;
    while (c != NULL)
    {
        if (c->addr == addr)
            return c;
        c = c->next;
    }
    return NULL;
}

constant_list *new_constant_list(int addr)
{
    constant_list *list = (constant_list *)malloc(sizeof(constant_list));
    list->head = NULL;
    list->begin = addr;
    list->end = addr;
    return list;
}

void print_constant_list(constant_list *list)
{
    constant *c = list->head;
    printf("\n-------- constant list --------\n");
    printf("val\ttype\taddr\twidth\n");
    printf("-------------------------------\n");
    while (c != NULL)
    {
        switch (c->val_type)
        {
        case INT:
            printf("%d\t", c->val.num);
            break;
        case FLOAT:
            printf("%.9g\t", c->val.real);
            break;
        case CHAR:
            printf("'%c'\t", c->val.ch);
            break;
        case BOOL:
            printf("%s\t", c->val.boolean ? "true" : "false");
            break;
        }
        printf("%s\t%d\t%d\n", type_name[c->val_type].c_str(), c->addr, c->width);
        c = c->next;
    }
    printf("-------------------------------\n\n");
}

void delete_constant_list(constant_list *list)
{
    if (list == NULL)
        return;
    constant *c = list->head, *c2;
    while (c != NULL)
    {
        c2 = c->next;
        free(c);
        c = c2;
    }
    free(list);
}

goto_list *new_goto_list(int addr)
{
    goto_list *list = (goto_list *)malloc(sizeof(goto_list));
    list->addr = addr;
    list->next = NULL;
    return list;
}

goto_list *merge_goto_list(goto_list *list1, goto_list *list2)
{
    goto_list *list = list1;
    if (list1 == NULL && list2 == NULL)
        return NULL;
    if (list1 == NULL)
        return list2;
    if (list2 == NULL)
        return list1;
    while (list1->next != NULL)
        list1 = list1->next;
    list1->next = list2;
    return list;
}

void delete_goto_list(goto_list *list)
{
    goto_list *list2;
    while (list != NULL)
    {
        list2 = list->next;
        free(list);
        list = list2;
    }
}

//根据地址值找到相应的符合和值
void arg_name(char *code, symbol_list *slist, constant_list *clist, int addr)
{
    if (addr == -1)
    {
        sprintf(code, "");
        return;
    }
    if (addr >= CONSTANT_BEGIN)
    {
        constant *c = find_constant_by_addr(clist, addr);
        switch (c->val_type)
        {
        case INT:
            sprintf(code, "%d", c->val.num);
            break;
        case FLOAT:
            sprintf(code, "%.9g", c->val.real);
            break;
        case CHAR:
            sprintf(code, "'%c'", c->val.ch);
            break;
        case BOOL:
            sprintf(code, "%s", c->val.boolean ? "true" : "false");
            break;
        }
    }
    else if (addr >= SYMBOL_BEGIN)
    {
        symbol *id = find_symbol_by_addr(slist, addr);
        sprintf(code, "%s", id->name);
    }
    else
        sprintf(code, "%d", addr);
}

//生成代码
void gen(quadtable *table, symbol_list *slist, constant_list *clist, int op, int arg1, int arg2, int arg3)
{
    if (table->size == table->bufsize)
    {
        table->bufsize += MAXLEN;
        table->buf = (quadruple *)realloc(table->buf, table->bufsize);
    }
    quadruple *t = table->buf + table->size;

    t->op = op;
    t->arg1 = arg1;
    t->arg2 = arg2;
    t->arg2 = arg2;
    t->arg3 = arg3;

    int addr = table->size + CODE_BEGIN;
    char code1[MAXLEN];
    char code2[MAXLEN];
    char code3[MAXLEN];
    arg_name(code1, slist, clist, t->arg1);
    arg_name(code2, slist, clist, t->arg2);
    arg_name(code3, slist, clist, t->arg3);

    switch (t->op)
    {
    case movi:
    case movf:
    case movc:
    case movb:
        sprintf(t->code, "%d:\t%s = %s\n", addr, code3, code1);
        break;
    case addi:
    case addf:
        sprintf(t->code, "%d:\t%s = %s + %s\n", addr, code3, code1, code2);
        break;
    case subi:
    case subf:
        sprintf(t->code, "%d:\t%s = %s - %s\n", addr, code3, code1, code2);
        break;
    case muli:
    case mulf:
        sprintf(t->code, "%d:\t%s = %s * %s\n", addr, code3, code1, code2);
        break;
    case divi:
    case divf:
        sprintf(t->code, "%d:\t%s = %s / %s\n", addr, code3, code1, code2);
        break;
    case and_:
        sprintf(t->code, "%d:\t%s = %s && %s\n", addr, code3, code1, code2);
        break;
    case or_:
        sprintf(t->code, "%d:\t%s = %s || %s\n", addr, code3, code1, code2);
        break;
    case eq:
        sprintf(t->code, "%d:\t%s = %s == %s\n", addr, code3, code1, code2);
        break;
    case ne:
        sprintf(t->code, "%d:\t%s = %s != %s\n", addr, code3, code1, code2);
        break;
    case gt:
        sprintf(t->code, "%d:\t%s = %s > %s\n", addr, code3, code1, code2);
        break;
    case ge:
        sprintf(t->code, "%d:\t%s = %s >= %s\n", addr, code3, code1, code2);
        break;
    case lt:
        sprintf(t->code, "%d:\t%s = %s < %s\n", addr, code3, code1, code2);
        break;
    case le:
        sprintf(t->code, "%d:\t%s = %s <= %s\n", addr, code3, code1, code2);
        break;
    case invi:
    case invf:
        sprintf(t->code, "%d:\t%s = -%s\n", addr, code3, code1);
        break;
    case not_:
        sprintf(t->code, "%d:\t%s = !%s\n", addr, code3, code1);
        break;
    case ftoi:
    case ctoi:
    case btoi:
        sprintf(t->code, "%d:\t%s = (int)%s\n", addr, code3, code1);
        break;
    case itof:
    case ctof:
    case btof:
        sprintf(t->code, "%d:\t%s = (float)%s\n", addr, code3, code1);
        break;
    case itoc:
    case ftoc:
    case btoc:
        sprintf(t->code, "%d:\t%s = (char)%s\n", addr, code3, code1);
        break;
    case itob:
    case ftob:
    case ctob:
        sprintf(t->code, "%d:\t%s = (bool)%s\n", addr, code3, code1);
        break;
    case jmp:
        sprintf(t->code, "%d:\tgoto %s\n", addr, code3);
        break;
    case jeq:
        sprintf(t->code, "%d:\tif %s == %s goto %s\n", addr, code1, code2, code3);
        break;
    case jne:
        sprintf(t->code, "%d:\tif %s != %s goto %s\n", addr, code1, code2, code3);
        break;
    case jgt:
        sprintf(t->code, "%d:\tif %s > %s goto %s\n", addr, code1, code2, code3);
        break;
    case jge:
        sprintf(t->code, "%d:\tif %s >= %s goto %s\n", addr, code1, code2, code3);
        break;
    case jlt:
        sprintf(t->code, "%d:\tif %s < %s goto %s\n", addr, code1, code2, code3);
        break;
    case jle:
        sprintf(t->code, "%d:\tif %s <= %s goto %s\n", addr, code1, code2, code3);
        break;
    }
    table->size++;
}

int widen(quadtable *table, symbol_list *slist, constant_list *clist, int addr, val_type_ type1, val_type_ type2)
{
    int op = conv[type1][type2];
    if (op != -1)
    {
        int arg3 = new_temp(slist, type2);
        gen(table, slist, clist, op, addr, -1, arg3);
        return arg3;
    }
    return addr;
}

void backpatch(quadtable *table, goto_list *list, int addr)
{
    while (list != NULL)
    {
        quadruple *t = table->buf + list->addr - CODE_BEGIN;
        t->arg3 = addr;
        sprintf(t->code + strlen(t->code) - 1, "%d\n", addr);
        list = list->next;
    }
}

quadtable *new_quadtable()
{
    quadtable *table =(quadtable *)malloc(sizeof(quadtable));
    table->buf = (quadruple *)malloc(sizeof(quadruple) * MAXLEN);
    table->size = 0;
    table->bufsize = MAXLEN;
    return table;
}

void print_quadtable(quadtable *table)
{
    printf("\n-------------- quadtable --------------\n");
    printf("addr\top\targ1\targ2\tresult\n");
    printf("---------------------------------------\n");
    for (int i = 0; i < table->size; i++)
        printf("%d\t%s\t%d\t%d\t%d\n", i + CODE_BEGIN, op_name[table->buf[i].op].c_str(), table->buf[i].arg1, table->buf[i].arg2, table->buf[i].arg3);
    printf("---------------------------------------\n\n");
    for (int i = 0; i < table->size; i++)
        printf("%s", table->buf[i].code);
}

void delete_quadtable(quadtable *table)
{
    free(table->buf);
    free(table);
}
