#ifndef AST_PRIMITIVES_HPP
#define AST_PRIMITIVES_HPP
#include "ast.hpp"
#include <string>
#include <vector>


using namespace std;
// class Exp : public Base{
//     private:
//         const Base* AddExp;
//     public:
//         Exp(const Base* _AddExp): AddExp(_AddExp){}
//         virtual void print() const{
            
//         }

// }

// class Cond : public Base{
//     private:
//         const Base*
// }

class Lval: public Base{
    private:
        string Ident;
        const Base* ExpList;
    public:
        Lval(string& _Ident, const Base* _ExpList = nullptr) : 
        Ident(_Ident),ExpList(_ExpList){}

        virtual void print(int PAD) const{
            fpout<<Ident<<" ";
            if(ExpList != nullptr)
            {
                ExpList->print(PAD);
            }
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }    
};

class Number: public Base{
    private:
        int number;
    public:
        Number(int _number):number(_number){}
        virtual void print(int PAD) const{
            fpout<<number;
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }      
};

class UnaryExp1: public Base{
    private:
        string Ident;
        const Base* FuncRParams;
        // string UnaryOp;
        // const Base* UnaryExp;
    public:
        UnaryExp1(string& _Ident,const Base* _FuncRParams = nullptr) : 
        Ident(_Ident), FuncRParams(_FuncRParams){}

        virtual void print(int PAD) const{
            fpout<<Ident<<"(";
            if(FuncRParams == nullptr)
            FuncRParams->print(PAD);
            fpout<<")";
        }
        
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }
};

class UnaryExp2: public Base{
    private:
        string UnaryOp;
        const Base* UnaryExp;
        // string UnaryOp;
        // const Base* UnaryExp;
    public:
        UnaryExp2(string& _UnaryOp,const Base* _UnaryExp) : 
        UnaryOp(_UnaryOp), UnaryExp(_UnaryExp){}

        virtual void print(int PAD) const{
            fpout<<UnaryOp;
            UnaryExp->print(PAD);
        }
        
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }
};

class FuncRParams: public Base{
    private:
        mutable vector<const Base*> FuncRParam_List;
    public:
        FuncRParams(const Base* _Exp){
            FuncRParam_List.push_back(_Exp);
        }
        virtual void print(int PAD) const {
            for(size_t i = 0; i < FuncRParam_List.size(); ++i){
                FuncRParam_List[i]->print(PAD);
                fpout<<",";
            }
        }
        virtual void push(const Base* var) const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }
};

class opExp: public Base{
    public:
        virtual void pushop(string& _Op) const=0;
};

class MulExp: public opExp{
    private:
        mutable vector<const Base*> UnaryExp_List;
        mutable vector<string> Op_List;
    public:
        MulExp(const Base* _UnaryExp){
            UnaryExp_List.push_back(_UnaryExp);
            Op_List.push_back(" ");
        }
        virtual void print(int PAD) const{
            for(size_t i = 0; i < UnaryExp_List.size(); ++i){
                fpout<<Op_List[i];
                UnaryExp_List[i]->print(PAD);
            }
        }
        virtual void push(const Base* _UnaryExp) const
        {
            UnaryExp_List.push_back(_UnaryExp);
        }
        virtual void pushop(string& _Op) const
        {
            Op_List.push_back(_Op);
        } 
};

class AddExp: public opExp{
    private:
        mutable vector<const Base*> MulExp_List;
        mutable vector<string> Op_List;
    public:
        AddExp( const Base* _MulExp){
            MulExp_List.push_back(_MulExp);
            Op_List.push_back(" ");
        }
        virtual void print(int PAD) const{
            for(size_t i = 0; i < MulExp_List.size(); ++i){
                fpout<<Op_List[i];
                MulExp_List[i]->print(PAD);
            }
        }
        virtual void push( const Base* _MulExp)const
        {
            MulExp_List.push_back(_MulExp);
        }
        virtual void pushop(string& _Op) const
        {
            Op_List.push_back(_Op);
        } 
};



class RelExp: public opExp{
    private:
        mutable vector<const Base*> AddExp_List;
        mutable vector<string> Op_List;
    public:
        RelExp(const Base* _AddExp){
            AddExp_List.push_back(_AddExp);
            Op_List.push_back(" ");
        }
        virtual void print(int PAD) const{
            for(size_t i = 0; i < AddExp_List.size(); ++i){
                fpout<<Op_List[i];
                AddExp_List[i]->print(PAD);
            }
        }
        virtual void push( const Base* _AddExp) const
        {
            AddExp_List.push_back(_AddExp);
        }
        virtual void pushop(string& _Op) const
        {
            Op_List.push_back(_Op);
        } 
};

class EqExp: public opExp{
    private:
        mutable vector<const Base*> RelExp_List;
        mutable vector<string> Op_List;
    public:
        EqExp(const Base* _RelExp){
            RelExp_List.push_back(_RelExp);
            Op_List.push_back("");
        }
        virtual void print(int PAD) const{
            for(size_t i = 0; i < RelExp_List.size(); ++i){
                fpout<<Op_List[i];
                RelExp_List[i]->print(PAD);
            }
        }
        virtual void push( const Base* _RelExp) const
        {
            RelExp_List.push_back(_RelExp);
        }
        virtual void pushop(string& _Op) const
        {
            Op_List.push_back(_Op);
        } 
};

class LAndExp : public opExp{
    private:
        mutable vector<const Base*> EqExp_List;
        mutable vector<string> Op_List;
    public:
        LAndExp(const Base* _EqExp){
            EqExp_List.push_back(_EqExp);
            Op_List.push_back(" ");
        }
        virtual void print(int PAD) const{
            for(size_t i = 0; i < EqExp_List.size(); ++i){
                fpout<<Op_List[i];
                EqExp_List[i]->print(PAD);
            }
        }
        virtual void push( const Base* _EqExp) const
        {
            EqExp_List.push_back(_EqExp);
        } 
        virtual void pushop(string& _Op) const
        {
            Op_List.push_back(_Op);
        }
};

class LOrExp : public opExp{
    private:
        mutable vector<const Base*> LAndExp_List;
        mutable vector<string> Op_List;
    public:
        LOrExp(const Base* _LAndExp){
            LAndExp_List.push_back(_LAndExp);
            Op_List.push_back(" ");
        }
        virtual void print(int PAD) const{
            for(size_t i = 0; i < LAndExp_List.size(); ++i){
                fpout<<Op_List[i];
                LAndExp_List[i]->print(PAD);
            }
        }
        virtual void push( const Base* _LAndExp)const
        {
            LAndExp_List.push_back(_LAndExp);
        } 
        virtual void pushop(string& _Op) const
        {
            Op_List.push_back(_Op);
        }
};

#endif
