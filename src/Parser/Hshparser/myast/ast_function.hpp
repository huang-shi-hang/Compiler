#ifndef AST_FUNCTION_HPP
#define AST_FUNCTION_HPP

#include "ast.hpp"

#include <string>
#include <iostream>
#include <vector>


using namespace std;

class FuncDef : public Base {
    private:
        string Ident;
        string FuncType;
        const Base* FuncFParams;
        const Base* Block;
    public:
        FuncDef(const string& _FuncType, const string& _Ident, const Base* _Block, const Base* _FuncFParams = nullptr) : 
        FuncType(_FuncType),Ident(_Ident),FuncFParams(_FuncFParams),Block(_Block) {}
        
        virtual void print(int PAD) const{
            fpout<<"Function("<<Ident<<")\n"<<string(PAD, '\t');
            fpout<<"Type("<<FuncType<<")\n"<<string(PAD, '\t');
            if(FuncFParams != nullptr)
                FuncFParams->print(PAD+1);
                fpout<<"\n"<<string(PAD, '\t');
            Block->print(PAD+1);
            fpout<<"\n"<<string(PAD, '\t');
        }

        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }
};

class FuncFParams : public Base{
    private:
        mutable vector<const Base*> FuncFParam_List;
    public:
        FuncFParams(const Base* _FuncFParam){
            FuncFParam_List.push_back(_FuncFParam);
        }
        virtual void print(int PAD) const {
            fpout<<"FUNCFPARAMS\n"<<string(PAD, '\t');
            for(size_t i = 0; i < FuncFParam_List.size(); ++i){
                FuncFParam_List[i]->print(PAD+1);
                fpout<<"\n"<<string(PAD, '\t');
            }
        } 
        virtual void push(const Base* _FuncFParam) const {
                FuncFParam_List.push_back(_FuncFParam);//压进栈的是参数
        }
};

class FuncFParam :public Base{
    private:
        string BType;
        string Ident;
        const Base* ExpList;
        string BlacketString = "  ";
    public:
        FuncFParam(string& _BType, string _Ident, string _BlacketString ="  ", const Base* _ExpList = nullptr) : 
        BType(_BType),Ident(_Ident),BlacketString(_BlacketString), ExpList(_ExpList){}
        FuncFParam(string& _BType, string _Ident, const Base* _ExpList) : 
        BType(_BType),Ident(_Ident), ExpList(_ExpList){}
        virtual void print(int PAD) const {
            fpout<<"Ident("<<Ident<<BlacketString;
            if(ExpList != nullptr)
            {
                ExpList->print(PAD);
            }
            fpout<<")\n"<<string(PAD, '\t')<<"Type("<<BType<<")";
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }       
};

class ExpList: public Base{
    private:
        mutable vector<const Base*> Exp_List;
    public:
        ExpList(const Base* _Exp){
            Exp_List.push_back(_Exp);
        }
        virtual void print(int PAD) const{
            for(size_t i = 0; i < Exp_List.size();++i)
            {
                fpout<<"[";
                Exp_List[i]->print(PAD);
                fpout<<"]";
            }
        }
        virtual void push(const Base* _Exp) const{
            Exp_List.push_back(_Exp);
        }
};


// class Blcok : public Base{
//     private:
//         const Base* BlockItemList;
//     public:
//         Block() {}
//         Block(const Base* Stmnt){
//             Stmnt_List.push_back(Stmnt);
//         } 
//         virtual void print() const {
//             fpout<<"BLOCK\n\t\t\t";
//             for(size_t i = 0; i < Stmnt_List.size(); ++i){
//                 Stmnt_List[i]->print();
//                 fpout<<"\n\t\t\t";
//             }
//         }
//         virtual void push(const Base* _stmnt) const{
//             Stmnt_List.push_back(_stmnt);//压进栈的是语句。
//         }

// }
class BlockItemList : public Base{
    private:
        mutable vector<const Base*> BlockItem_List;
    public:
        BlockItemList(const Base* _BlockItem){
            BlockItem_List.push_back(_BlockItem);
        }
        virtual void print(int PAD) const {
            fpout<<"BLOCK"<<"\n"<<string(PAD, '\t');
            for( size_t i = 0; i < BlockItem_List.size(); ++i){
                BlockItem_List[i]->print(PAD+1);
                fpout<<"\n"<<string(PAD, '\t');
            }
        }
        virtual void push(const Base* _BlockItem) const{
            BlockItem_List.push_back(_BlockItem);
        }
};

// class BlockItem : public Base{
//     private:
//         const Base* Decl_Stmt;
//     public:
//         BlockItem(const Base* _Decl_Stmt) : Decl_Stmt(_Decl_Stmt){}
//         virtual void print() const{
//             fpout<<
//         }
// } 

#endif
