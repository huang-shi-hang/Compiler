%{
    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    #include "types.hpp"
    #include "hshlex.yy.hpp"
    extern int line;
    
    int _mov[4] = {movi, movf, movc, movb};
    int _add[2] = {addi, addf};
    int _sub[2] = {subi, subf};
    int _mul[2] = {muli, mulf};
    int _div[2] = {divi, divf};
    int _inv[2] = {invi, invf};

    val_type_ max[4][4] = {
    {INT, FLOAT, INT, INT},
    {FLOAT, FLOAT, FLOAT, FLOAT},
    {INT, FLOAT, CHAR, INT},
    {INT, FLOAT, INT, BOOL}
    };

    //四元组表
    quadtable *table = NULL;
    //符号表
    symbol_list *slist = NULL;
    //常量表
    constant_list *clist = NULL;
    //跳转
    goto_list *break_lists[MAXLEN];

    int tos = 0;

    int error = 0;

    void yyerror(char *msg)
    {
        error++;
        std::cout<<"\033[1mline "<<line<< ": "<<msg<<"\033[0m\n";
    }
%}

%token IF ELSE DO WHILE BREAK
%token BASIC ID CONST 

%left OR
%left AND
%left EQ NE
%left LT LE GT GE
%left '+' '-'
%left '*' '/'
%right INV NOT


%%
program : block

block   : '{' begin decls stmts end '}' 
            // {
            // if (slist == NULL)
            //     slist = new_symbol_list(NULL, SYMBOL_BEGIN);
            // else
            //     slist = new_symbol_list(slist, slist->end);

            // symbol_list *slist2 = slist;
            // if (error == 0)
            //     print_symbol_list(slist2);
            // slist = slist2->prev;
            // delete_symbol_list(slist2);
            // }

begin   :
        {
            //判断slist是否为空，如果空就新建，不空就要接着上一个生成
            if (slist == NULL)
                slist = new_symbol_list(NULL, SYMBOL_BEGIN);
            else
                slist = new_symbol_list(slist, slist->end);
        }

end     :
        {   //返回上一级的slist
            symbol_list *slist2 = slist;
            if (error == 0)
                print_symbol_list(slist2);
            slist = slist2->prev;
            delete_symbol_list(slist2);
        }

decls   : decls decl
        |

decl    : BASIC ID ';'
        {
            //看看本地的符号表有没有相关的内容，如果没有就加上
            if (find_local_symbol(slist, $2.name) == NULL)
                new_symbol(slist, $2.name, $1.val_type);
            else
            {
                char msg[MAXLEN];
                sprintf(msg, "duplicate declaration of symbol \"%s\"", $2.name);
                yyerror(msg);
            }
        }
stmts   : stmts stmt M
        {   backpatch(table, $2.n_list, $3.addr);  }
        |
M       : 
        {   //确定语句块的位置
            $$.addr = table->size + CODE_BEGIN; 
        }
N       :
        {
            //生成相邻下一个语句块的位置
            $$.n_list = new_goto_list(table->size + CODE_BEGIN);
            gen(table, slist, clist, jmp, -1, -1, -1);
        }

Q       :
        {   
            break_lists[tos++] = NULL;  
        }


//语句

stmt    : ID '=' expr ';'
        {
            //在符号表中找到ID
            $$.n_list = NULL;
            symbol *id = find_symbol(slist, $1.name);
            if (id == NULL)
            {
                char msg[MAXLEN];
                sprintf(msg, "undeclared symbol \"%s\"", $1.name);
                yyerror(msg);
                id = new_symbol(slist, $1.name, INT);
            }
            //语句的四元组组成
            int arg1 = $3.addr;
            int arg3 = id->addr;
            gen(table, slist, clist, _mov[id->val_type], arg1, -1, arg3);
        }
        | IF '(' bool ')' M stmt
        {
            //回填给bool语句的跳转位置
            backpatch(table, $3.t_list, $5.addr);
            //此语句的下一个语句
            $$.n_list = merge_goto_list($3.f_list, $6.n_list);
        }
        | IF '(' bool ')' M stmt N ELSE M stmt
        {
            //回填
            backpatch(table, $3.t_list, $5.addr);
            backpatch(table, $3.f_list, $9.addr);

            $$.n_list = merge_goto_list(merge_goto_list($6.n_list, $7.n_list), $10.n_list);
        }
        | WHILE Q M '(' bool ')' M stmt
        {
            //回填
            backpatch(table, $8.n_list, $3.addr);
            backpatch(table, $5.t_list, $7.addr);
            //保证嵌套是一层一层跳出来的
            $$.n_list = merge_goto_list($5.f_list, break_lists[--tos]);
            //生成一个跳转语句，跳到上一层
            gen(table, slist, clist, jmp, -1, -1, $3.addr);
        }
        | DO Q M stmt WHILE M '(' bool ')' ';'
        {
            backpatch(table, $8.t_list, $3.addr);
            backpatch(table, $4.n_list, $6.addr);
            $$.n_list = merge_goto_list($8.f_list, break_lists[--tos]);
        }
        | BREAK ';'
        {
            //打断循环
            $$.n_list = NULL;
            if (tos == 0)
                yyerror("\"break\" statement doesn't match any loop");
            else
            {
                break_lists[tos - 1] = merge_goto_list(break_lists[tos - 1], new_goto_list(table->size + CODE_BEGIN));
                gen(table, slist, clist, jmp, -1, -1, -1);
            }
        }
        | block
        {   $$.n_list = NULL;  }
        | error ';'

//条件语句
bool    : bool OR M bool
        {
            backpatch(table, $1.f_list, $3.addr);
            $$.t_list = merge_goto_list($1.t_list, $4.t_list);
            $$.f_list = $4.f_list;
        }
        | bool AND M bool
        {
            backpatch(table, $1.t_list, $3.addr);
            $$.t_list = $4.t_list;
            $$.f_list = merge_goto_list($1.f_list, $4.f_list);
        }
        | '!' bool %prec NOT
        {
            $$.t_list = $2.f_list;
            $$.f_list = $2.t_list;
        }
        | '(' bool ')'
        {
            $$.t_list = $2.t_list;
            $$.f_list = $2.f_list;
        }
        | expr EQ expr
        {
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, max[$1.val_type][$3.val_type]);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, max[$1.val_type][$3.val_type]);
            $$.t_list = new_goto_list(table->size + CODE_BEGIN);
            $$.f_list = new_goto_list(table->size + CODE_BEGIN + 1);
            gen(table, slist, clist, jeq, arg1, arg2, -1);
            gen(table, slist, clist ,jmp, -1, -1, -1);
        }
        | expr NE expr
        {
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, max[$1.val_type][$3.val_type]);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, max[$1.val_type][$3.val_type]);
            $$.t_list = new_goto_list(table->size + CODE_BEGIN);
            $$.f_list = new_goto_list(table->size + CODE_BEGIN + 1);
            gen(table, slist, clist, jne, arg1, arg2, -1);
            gen(table, slist, clist ,jmp, -1, -1, -1);
        }
        | expr LT expr
        {
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, max[$1.val_type][$3.val_type]);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, max[$1.val_type][$3.val_type]);
            $$.t_list = new_goto_list(table->size + CODE_BEGIN);
            $$.f_list = new_goto_list(table->size + CODE_BEGIN + 1);
            gen(table, slist, clist, jlt, arg1, arg2, -1);
            gen(table, slist, clist ,jmp, -1, -1, -1);
        }
        | expr LE expr
        {
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, max[$1.val_type][$3.val_type]);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, max[$1.val_type][$3.val_type]);
            $$.t_list = new_goto_list(table->size + CODE_BEGIN);
            $$.f_list = new_goto_list(table->size + CODE_BEGIN + 1);
            gen(table, slist, clist, jle, arg1, arg2, -1);
            gen(table, slist, clist ,jmp, -1, -1, -1);
        }
        | expr GT expr
        {
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, max[$1.val_type][$3.val_type]);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, max[$1.val_type][$3.val_type]);
            $$.t_list = new_goto_list(table->size + CODE_BEGIN);
            $$.f_list = new_goto_list(table->size + CODE_BEGIN + 1);
            gen(table, slist, clist, jgt, arg1, arg2, -1);
            gen(table, slist, clist ,jmp, -1, -1, -1);
        }
        | expr GE expr
        {
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, max[$1.val_type][$3.val_type]);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, max[$1.val_type][$3.val_type]);
            $$.t_list = new_goto_list(table->size + CODE_BEGIN);
            $$.f_list = new_goto_list(table->size + CODE_BEGIN + 1);
            gen(table, slist, clist, jge, arg1, arg2, -1);
            gen(table, slist, clist ,jmp, -1, -1, -1);
        }
        | expr
        {
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, BOOL);
            constant_val temp_const;
            temp_const.boolean = true;
            int arg2 = new_constant(clist, temp_const, BOOL)->addr;
            $$.t_list = new_goto_list(table->size + CODE_BEGIN);
            $$.f_list = new_goto_list(table->size + CODE_BEGIN + 1);
            gen(table, slist, clist, jeq, arg1, arg2, -1);
            gen(table, slist, clist ,jmp, -1, -1, -1);
        }

//表达式
expr    : expr OR expr
        {
            $$.val_type = BOOL;
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, $$.val_type);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, $$.val_type);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, or_, arg1, arg2, arg3);
            $$.addr = arg3;
        }
        | expr AND expr
        {
            $$.val_type = BOOL;
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, $$.val_type);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, $$.val_type);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, and_, arg1, arg2, arg3);
            $$.addr = arg3;
        }
        | expr EQ expr
        {
            $$.val_type = BOOL;
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, max[$1.val_type][$3.val_type]);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, max[$1.val_type][$3.val_type]);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, eq, arg1, arg2, arg3);
            $$.addr = arg3;
        }
        | expr NE expr
        {
            $$.val_type = BOOL;
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, max[$1.val_type][$3.val_type]);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, max[$1.val_type][$3.val_type]);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, ne, arg1, arg2, arg3);
            $$.addr = arg3;
        }
        | expr LT expr
        {
            $$.val_type = BOOL;
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, max[$1.val_type][$3.val_type]);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, max[$1.val_type][$3.val_type]);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, lt, arg1, arg2, arg3);
            $$.addr = arg3;
        }
        | expr LE expr
        {
            $$.val_type = BOOL;
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, max[$1.val_type][$3.val_type]);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, max[$1.val_type][$3.val_type]);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, le, arg1, arg2, arg3);
            $$.addr = arg3;
        }
        | expr GT expr
        {
            $$.val_type = BOOL;
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, max[$1.val_type][$3.val_type]);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, max[$1.val_type][$3.val_type]);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, gt, arg1, arg2, arg3);
            $$.addr = arg3;
        }
        | expr GE expr
        {
            $$.val_type = BOOL;
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, max[$1.val_type][$3.val_type]);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, max[$1.val_type][$3.val_type]);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, ge, arg1, arg2, arg3);
            $$.addr = arg3;
        }
        | expr '+' expr
        {
            $$.val_type = max[$1.val_type][$3.val_type];
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, $$.val_type);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, $$.val_type);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, _add[$$.val_type], arg1, arg2, arg3);
            $$.addr = arg3;
        }
        | expr '-' expr
        {
            $$.val_type = max[$1.val_type][$3.val_type];
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, $$.val_type);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, $$.val_type);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, _sub[$$.val_type], arg1, arg2, arg3);
            $$.addr = arg3;
        }
        | expr '*' expr
        {
            $$.val_type = max[$1.val_type][$3.val_type];
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, $$.val_type);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, $$.val_type);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, _mul[$$.val_type], arg1, arg2, arg3);
            $$.addr = arg3;
        }
        | expr '/' expr
        {
            $$.val_type = max[$1.val_type][$3.val_type];
            int arg1 = widen(table, slist, clist, $1.addr, $1.val_type, $$.val_type);
            int arg2 = widen(table, slist, clist, $3.addr, $3.val_type, $$.val_type);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, _div[$$.val_type], arg1, arg2, arg3);
            $$.addr = arg3;
        }
        | '!' expr %prec NOT
        {
            $$.val_type = BOOL;
            int arg1 = widen(table, slist, clist, $2.addr, $2.val_type, $$.val_type);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, not_, arg1, -1, arg3);
            $$.addr = arg3;
        }
        | '-' expr %prec INV
        {
            $$.val_type = max[$2.val_type][INT];
            int arg1 = widen(table, slist, clist, $2.addr, $2.val_type, $$.val_type);
            int arg3 = new_temp(slist, $$.val_type);
            gen(table, slist, clist, _inv[$$.val_type], arg1, -1, arg3);
            $$.addr = arg3;
        }
        | '(' expr ')'
        {
            $$.val_type = $2.val_type;
            $$.addr = $2.addr;
        }
        | ID
        {
            symbol *id = find_symbol(slist, $1.name);
            if (id == NULL)
            {
                char msg[MAXLEN];
                sprintf(msg, "undeclared symbol \"%s\"", $1.name);
                yyerror(msg);
                id = new_symbol(slist, $1.name, INT);
            }
            $$.val_type = id->val_type;
            $$.addr = id->addr;
        }
        | CONST
        {
            constant *c = new_constant(clist, $1.val, $1.val_type);
            $$.val_type = c->val_type;
            $$.addr = c->addr;
        }
%%
int main(int argc, char *argv[])
{
    if ((yyin = fopen(argv[1], "r")) == NULL) {
        perror("Can't open file \n");
        return -1;
    }
    table = new_quadtable();
    clist = new_constant_list(CONSTANT_BEGIN);
    yyparse();
    if (error == 0)
    {
        // print_constant_list(clist);
        print_quadtable(table);
    }
    else
        printf("%d error generated.\n", error);
    delete_constant_list(clist);
    delete_quadtable(table);
    return 0;
}
