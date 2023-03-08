/*******************************************************
*            Compiler :hshconpiler for C               *
*           Shihang Huang, 304256263@qq.com            *
*               Buildtime :2022.5.1                    *
*                                                      *
*                   SysY Compiler                      *
*                                                      *
*           hshparser : praser  by bison               *
*******************************************************/

/*******************************************************
*               Chenge Log                             *
*       1.                                             *             
*******************************************************/
%code requires {
    #include "ast.hpp"
    extern ast_Top *ast_root;//AST's root
    using namespace std;
    /*声明flex的函数以便调用*/
    int yylex(void);
    void yyerror(const char *);
}

%{
    #include "hshlex.yy.hpp"
    #include "hshparser.tab.hpp"
%}


%union{
    const Base *stmnt;
    const opExp *stmnt1;
    int number;
    string *str;
}

%token Y_INT Ident Y_CONST Y_VOID 
%token Y_Semicolon Y_Comma Y_L_RBracket Y_R_RBracket Y_L_CBracket Y_R_CBracket Y_L_SBracket Y_R_SBracket Y_Or Y_And Y_Equality Y_U_Equality Y_Relation Y_Mult Y_Div Y_Rem Y_Inc_Dec Y_Add_Sub Y_Equal Y_OPPOSIT
%token INT_CONST
%token Y_IF Y_ELSE Y_RETURN Y_WHILE Y_BREAK Y_CONTINUE

%type<stmnt>CompUnit CompUnitList
%type<stmnt>Decl ConstDecl ConstDefList ConstDef S_BracketList ConstInitVal ConstInitValList VarDecl VarDefList VarDef
%type<stmnt>InitVal InitValList FuncDef FuncFParams FuncFParam ExpList Block BlockItemList BlockItem
%type<stmnt>Stmt Exp Cond Lval PrimaryExp UnaryExp FuncRParams ConstExp Number
%type<str>BType UnaryOp Y_INT Ident Y_VOID Y_Add_Sub Y_OPPOSIT Y_Mult Y_Div Y_Rem Y_Relation Y_Equality Y_U_Equality Y_And Y_Or
%type<number>INT_CONST
%type<stmnt1>MulExp AddExp RelExp EqExp LAndExp LOrExp

%%
//任何的关键字我都用Y_...表示
//标点符号直接用引号表示，现在还没有改过来
//程序
Program         : CompUnitList {;}
                ;

//编译单元列表
CompUnitList    : CompUnit {ast_root->push($1);}
                | CompUnitList CompUnit {ast_root->push($2);}
                ;

//编译单元
CompUnit        : Decl {$$ =$1;}
                | FuncDef {$$ = $1;}
                ;
//声明
Decl            : ConstDecl {$$ = $1;}
                | VarDecl {$$ = $1;}
                ;

//常量声明
ConstDecl       : Y_CONST BType ConstDefList Y_Semicolon {$$ = new ConstDecl(*$2,$3);}
                ;

//常量定义表——辅助
ConstDefList    : ConstDef {$$ = new ConstDefList($1);}
                | ConstDefList Y_Comma ConstDef {$$->push($3);}
                ;

//基本类型
BType           : Y_INT {$$ = new string(*$1);}
                ;

//常量定义
ConstDef        : Ident Y_Equal ConstInitVal {$$ = new ConstDef(*$1,$3);}
                | Ident S_BracketList Y_Equal ConstInitVal {$$ = new ConstDef(*$1,$4,$2);}
                ;
        
//方括号列定义-辅助
S_BracketList   : Y_L_SBracket ConstExp Y_R_SBracket {$$ = new S_BracketList($2);}
                | S_BracketList Y_L_SBracket ConstExp Y_R_SBracket {$$->push($3);}
                ;

//常量初值
ConstInitVal    : ConstExp {$$ = new ConstInitVal($1);}
                | Y_L_CBracket ConstInitValList Y_R_CBracket {$$ = new ConstInitVal($2,"{}");}
                | Y_L_CBracket Y_R_CBracket {$$ = new ConstInitVal();}
                ;

//常量初值列表-辅助
ConstInitValList : ConstInitVal {$$ = new ConstInitValList($1);}
                | ConstInitValList Y_Comma ConstInitVal {$$->push($3);}
                ;

//变量声明
VarDecl         : BType VarDefList Y_Semicolon {$$ = new VarDecl(*$1,$2);}
                ;

//变量定义列表-辅助
VarDefList      : VarDef {$$ = new VarDefList($1);}
                | VarDefList Y_Comma VarDef {$$->push($3);}
                ;

//变量定义
VarDef          : Ident {$$ = new VarDef(*$1);}
                | Ident Y_Equal InitVal {$$ = new VarDef(*$1,$3);}
                | Ident S_BracketList {$$ = new VarDef(*$1, nullptr, $2);}
                | Ident S_BracketList Y_Equal InitVal {$$ = new VarDef(*$1, $4, $2);}
                ;

//变量初值
InitVal         : Exp {$$ = new InitVal($1);}
                | Y_L_CBracket InitValList Y_R_CBracket {$$ = new InitVal($2);}
                | Y_L_CBracket Y_R_CBracket {$$ = new InitVal();}
                ;

//变量初值列表——辅助
InitValList     : InitVal {$$ = new InitValList($1);}
                | InitValList Y_Comma InitVal {$$->push($3);}
                ;
            
//函数定义
FuncDef         : Y_VOID Ident Y_L_RBracket FuncFParams Y_R_RBracket Block {$$ = new FuncDef(*$1,*$2,$6,$4);}
                | Y_VOID Ident Y_L_RBracket Y_R_RBracket Block {$$ = new FuncDef(*$1,*$2,$5);}
                | Y_INT Ident Y_L_RBracket FuncFParams Y_R_RBracket Block {$$ = new FuncDef(*$1,*$2,$6,$4);}
                | Y_INT Ident Y_L_RBracket Y_R_RBracket Block {$$ = new FuncDef(*$1,*$2,$5);}
                ;

//函数类型定义
// FuncType        : Y_VOID {$$ = new string(*$1);}
//                 | Y_INT {$$ = new string(*$1);}
//                 ;

//函数形参表
FuncFParams     : FuncFParam {$$ = new FuncFParams($1);}
                | FuncFParams Y_Comma FuncFParam {$$->push($3);}
                ;

//函数形参
FuncFParam      : BType Ident {$$ = new FuncFParam(*$1, *$2);}
                | BType Ident Y_L_SBracket Y_R_SBracket {$$ = new FuncFParam(*$1, *$2, "[]");}
                | BType Ident ExpList {$$ = new FuncFParam(*$1, *$2, $3);}
                ;

//表达式表-辅助
ExpList         : Y_L_SBracket Exp  Y_R_SBracket {$$ = new ExpList($2);}
                | ExpList Y_L_SBracket Exp  Y_R_SBracket {$$->push($3);}
                ;

//语句块
Block           : Y_L_CBracket BlockItemList Y_R_CBracket {$$ = $2;}
                ;

//语句块项列表
BlockItemList   : BlockItem {$$ = new BlockItemList($1);}
                | BlockItemList BlockItem {$$->push($2);}
                ;

//语句块项
BlockItem       : Decl {$$ = $1;}
                | Stmt {$$ = $1;}
                ;

//语句
Stmt            : Lval Y_Equal Exp Y_Semicolon {$$ = new AssignStmt($1, $3);}
                | Y_Semicolon{$$ = new AssignStmt();}  //忽略
                | Exp Y_Semicolon {$$ = new AssignStmt($1);}
                | Block {$$ = $1;}
                | Y_IF Y_L_RBracket Cond Y_R_RBracket Stmt {$$ = new IfStmt($3,$5);}
                | Y_IF Y_L_RBracket Cond Y_R_RBracket Stmt Y_ELSE Stmt {$$ = new IfElseStmt($3, $5, $7);}
                | Y_WHILE Y_L_RBracket Cond Y_R_RBracket Stmt {$$ = new WhileStmt($3,$5);}
                | Y_BREAK Y_Semicolon {$$ = new BreakStmt();}
                | Y_CONTINUE Y_Semicolon {$$ = new ContinueStmt();}
                | Y_RETURN Y_Semicolon {$$ = new ReturnStmt();}
                | Y_RETURN Exp Y_Semicolon { $$ = new ReturnStmt($2);}
                ; 

//表达式
Exp             : AddExp {$$ = $1;}
                ;

//条件表达式
Cond            : LOrExp {$$ = $1;}
                ;

//左值表达式 
Lval            : Ident ExpList {$$ =new Lval(*$1, $2);}
                | Ident {$$ =new Lval(*$1);}
                ;

//基本表达式
PrimaryExp      : Y_L_RBracket Exp Y_R_RBracket {$$ = $2;}
                | Lval {$$ = $1;}
                | Number {$$ = $1;}
                ;

//数值
Number          : INT_CONST {$$ = new Number($1);}
                ;

//一元表达式
UnaryExp        : PrimaryExp {$$ = $1;}
                | Ident Y_L_RBracket Y_R_RBracket {$$ = new UnaryExp1(*$1);}
                | Ident Y_L_RBracket FuncRParams Y_R_RBracket {$$ = new UnaryExp1(*$1,$3);}
                | UnaryOp UnaryExp {$$ = new UnaryExp2(*$1,$2);}
                ;

//单目运算符
UnaryOp         : Y_Add_Sub {$$ = $1;}
                // | '-' {$$ = *$1;}
                | Y_OPPOSIT {$$ = $1;}
                ;

//函数实参表
FuncRParams     : Exp {$$ = new FuncRParams($1);}
                | FuncRParams Y_Comma Exp {$$->push($3);}
                ;

//乘除模表达式   
MulExp          : UnaryExp {$$ = new MulExp($1);}
                | MulExp Y_Mult UnaryExp { $$->pushop(*$2); $$->push($3);}
                | MulExp Y_Div UnaryExp {$$->pushop(*$2); $$->push($3);}
                | MulExp Y_Rem UnaryExp {$$->pushop(*$2); $$->push($3);}
                ;

//加减表达式
AddExp          : MulExp {$$ = new AddExp($1);}
                | AddExp Y_Add_Sub MulExp {$$->pushop(*$2); $$->push($3);}
                // | AddExp '-' MulExp {$$->push($2,$3);}
                ;

//关系表达式
RelExp          : AddExp {$$ = new RelExp($1);}
                | RelExp Y_Relation AddExp {$$->pushop(*$2); $$-> push($3);}
                // | RelExp '>' AddExp {$$->push($2,$3);}
                // | RelExp '<=' AddExp {$$->push($2,$3);}
                // | RelExp '>=' AddExp {$$->push($2,$3);}
                ;

//相等性表达式
EqExp           : RelExp {$$ = new EqExp($1);}
                | EqExp Y_Equality RelExp {$$->pushop(*$2); $$->push($3);}
                | EqExp Y_U_Equality RelExp {$$->pushop(*$2); $$->push($3);}
                ;

//逻辑与表达式
LAndExp         : EqExp {$$ = new LAndExp($1);}
                | LAndExp Y_And EqExp {$$->pushop(*$2); $$->push($3);}
                ;

//逻辑或表达式
LOrExp          : LAndExp {$$ = new LOrExp($1);}
                | LOrExp Y_Or LAndExp {$$->pushop(*$2); $$->push($3);}
                ;

//常量表达式
ConstExp        : AddExp {$$ = $1;}
                ;
%%

ast_Top *ast_root;

ast_Top *parseAST(){
    ast_root = new ast_Top;
    yyparse();
    return ast_root;
}
