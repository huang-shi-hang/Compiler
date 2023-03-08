#ifndef AST_STATEMENT_HPP
#define AST_STATEMENT_HPP

#include "ast.hpp"
#include <string>
#include <vector>


class AssignStmt :public Base{
    private:
        const Base* Lval = nullptr;
        const Base* Exp = nullptr;
    public:
        AssignStmt(){}
        AssignStmt(const Base* _Exp):Exp(_Exp){}
        AssignStmt(const Base* _Lval,const Base* _Exp) : 
        Lval(_Lval),Exp(_Exp){}
        virtual void print(int PAD) const{
            if(Lval != nullptr)
            {
                fpout<<"ASSIGNSTMT\n"<<string(PAD, '\t')<<"LVAL(";
                Lval->print(PAD);
                fpout<<")\n"<<string(PAD, '\t')<<"EXP(";
                Exp->print(PAD);
                fpout<<")";
            }
            else if(Exp != nullptr)
            {
                fpout<<"SINGLESTMT(";
                Exp->print(PAD);
                fpout<<")";
            }
            fpout<<"NULLSTMT";
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }
};
class IfStmt:public Base{
    private:
        const Base* Cond;
        const Base* Stmt;
    public:
        IfStmt(const Base* _Cond,const Base* _Stmt) : 
        Cond(_Cond),Stmt(_Stmt){}
        virtual void print(int PAD) const {
            fpout<<"IFSTMT\n"<<string(PAD, '\t')<<"COND(";
            Cond->print(PAD+1);
            fpout<<")\n"<<string(PAD, '\t')<<"STMT(";
            Stmt->print(PAD+1);
            fpout<<")";
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }    
};

class IfElseStmt: public Base{
    private:
        const Base* Cond;
        const Base* Stmt1;
        const Base* Stmt2;
    public:
       IfElseStmt(const Base* _Cond,const Base* _Stmt1,const Base* _Stmt2) : 
       Cond(_Cond), Stmt1(_Stmt1),Stmt2(_Stmt2){}
       virtual void print(int PAD) const{
           fpout<<"IFELSESTMT\n"<<string(PAD, '\t')<<"COND(";
           Cond->print(PAD+1);
           fpout<<")\n"<<string(PAD, '\t')<<"STMT1(";
           Stmt1->print(PAD+1);
           fpout<<")\n"<<string(PAD, '\t')<<"STMT2(";
           Stmt2->print(PAD+1);
           fpout<<")";
       }
       virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
       }
};

class WhileStmt: public Base{
    private:
        const Base* Cond;
        const Base* Stmt;
    public:
        WhileStmt(const Base* _Cond,const Base* _Stmt) : 
        Cond(_Cond),Stmt(_Stmt){}
        virtual void print(int PAD) const {
            fpout<<"WHILESTMT\n"<<string(PAD, '\t')<<"COND(";
            Cond->print(PAD+1);
            fpout<<")\n"<<string(PAD, '\t')<<"STMT(";
            Stmt->print(PAD+1);
            fpout<<")";
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }
};

class BreakStmt: public Base{
    public:
        BreakStmt(){}
        virtual void print(int PAD) const{
            fpout<<"BREAKSTMT";
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }
};



class ContinueStmt: public Base{
    public:
        ContinueStmt(){}
        virtual void print(int PAD) const{
            fpout<<"CONTINUESTMT";
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }
};

class ReturnStmt: public Base{
    private:
        const Base* Exp = nullptr;
    public:
        ReturnStmt(){}
        ReturnStmt(const Base* _Exp):Exp(_Exp){}
        virtual void print(int PAD) const{
            fpout<<"RETURNSTMT";
            if(Exp != nullptr){
                fpout<<"\n"<<string(PAD, '\t')<<"EXP(";
                Exp->print(PAD+1);
                fpout<<")";
            }
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        } 
};



#endif
