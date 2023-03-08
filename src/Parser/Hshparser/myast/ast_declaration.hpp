#ifndef AST_DECLARATION_HPP
#define AST_DECLARATION_HPP

#include "ast.hpp"

#include <vector>
#include <string>


using namespace std;

// class Decl : public Base{
//     private:
//         mutable vector<const Base*>Dec_List;
//     public:
//         Decl(const Base* _ConstDecl_VarDecl){
//             Dec_List.push_back(_ConstDecl_VarDecl);
//         }
//         virtual void print() const {
//             fpout<<"DECLARATION\n\t\t";
//             for(size_t i = 0; i < Dec_List.size(); ++i){
//                 Dec_List[i]->print();
//                 fpout<<"\n\t\t";
//             }
//         }
//         virtual void push(const Base* _dec) const{
//             dec_list.push_back(_dec);//把decl存储起来
//         }
// };

class ConstDecl : public Base{
    private:
        string BType;
        const Base* ConstDefList;
    public:
        ConstDecl(const string& _BType, const Base* _ConstDefList):
        BType(_BType),ConstDefList(_ConstDefList) {}
        virtual void print(int PAD) const{
            fpout<<"CONSTDECL\n"<<string(PAD, '\t')<<"Type("<<BType<<")\n"<<string(PAD, '\t');
            ConstDefList->print(PAD);
        }

        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }    
};

class ConstDefList : public Base{
    private:
        mutable vector<const Base*> ConstDef_List;
    public:
        ConstDefList(const Base* _ConstDef){
            ConstDef_List.push_back(_ConstDef);
        }
        virtual void print(int PAD) const{
            for(size_t i = 0; i < ConstDef_List.size(); ++i){
                ConstDef_List[i]->print(PAD+1);
                fpout<<"\n"<<string(PAD, '\t');
            }
        }
        virtual void push(const Base* _ConstDef) const{
            ConstDef_List.push_back(_ConstDef);
        }
};

class ConstDef : public Base{
    private:
        string Ident;
        const Base* S_BracketList;
        const Base* ConstInitVal;
    public:
        ConstDef(string& _Ident, const Base* _ConstInitVal, const Base* _S_BracketList=nullptr):
        Ident(_Ident),ConstInitVal(_ConstInitVal),S_BracketList(_S_BracketList){}
        virtual void print(int PAD) const{
            if(S_BracketList != nullptr)
            {
                fpout<<"Ident("<<Ident;
                S_BracketList->print(PAD);
                fpout<<")\n"<<string(PAD, '\t')<<"Value(";
                ConstInitVal->print(PAD);
                fpout<<")";
            }
            else
            {
                fpout<<"Ident("<<Ident<<")\n"<<string(PAD, '\t')<<"Value(";
                ConstInitVal->print(PAD);
                fpout<<")";
            }
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }
};

class S_BracketList : public Base{
    private:
        mutable vector<const Base*> ConstExpList;

    public:
        S_BracketList(const Base* _ConstExp){
            ConstExpList.push_back(_ConstExp);
        }
        virtual void print(int PAD) const{
            for(size_t i = 0; i < ConstExpList.size(); ++i)
            {
                fpout<<"[";
                ConstExpList[i]->print(PAD);
                fpout<<"]";
            }
        }
        virtual void push(const Base* _ConstExp) const{
            ConstExpList.push_back(_ConstExp);
        }
};

class ConstInitVal :public Base{
    private: 
        string BrackString;
        const Base* Const_ExpInitValList;
    public:
        ConstInitVal(const Base* _Const_ExpInitValList = nullptr,string _BrackString = "  "):
        Const_ExpInitValList(_Const_ExpInitValList) {}
        virtual void print(int PAD) const {
            if(Const_ExpInitValList == nullptr)
                fpout<<"{ }";
            else
            {
                fpout<<BrackString[0];
                Const_ExpInitValList->print(PAD);
                fpout<<BrackString[1];
            }
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }
};

class ConstInitValList : public Base{
    private:
        mutable vector<const Base*> ConstInitVal_List;
    public:
        ConstInitValList(const Base* _ConstInitVal){
            ConstInitVal_List.push_back(_ConstInitVal);
        }
        virtual void print(int PAD) const {
            for(size_t i = 0; i < ConstInitVal_List.size(); ++i)
            {
                ConstInitVal_List[i]->print(PAD);
                fpout<<",";
            }
        }
        virtual void push(const Base* _ConstInitVal) const{
            ConstInitVal_List.push_back(_ConstInitVal);
        } 
};


class VarDecl : public Base{
    private:
        string BType;
        const Base* VarDefList;
    public:
        VarDecl(string& _BType, const Base* _VarDefList) : 
        BType(_BType),VarDefList(_VarDefList){}
        virtual void print(int PAD) const {
            fpout<<"VARDECL\n"<<string(PAD, '\t')<<"Type("<<BType<<")\n"<<string(PAD, '\t');
            VarDefList->print(PAD);
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }
};

class VarDefList : public Base{
    private:
        mutable vector<const Base*> VarDef_List;
    public:
        VarDefList(const Base* _VarDef)
        {
            VarDef_List.push_back(_VarDef);
        }
        virtual void print(int PAD) const {
            for(size_t i = 0; i < VarDef_List.size(); ++i)
            {
                VarDef_List[i]->print(PAD+1);
                fpout<<"\n"<<string(PAD, '\t');
            }
        }
        virtual void push(const Base*  _VarDef) const {
            VarDef_List.push_back(_VarDef);
        }
};

class VarDef : public Base{
    private:
        string Ident;
        const Base* InitVal;
        const Base* S_BracketList;
    public:
        VarDef(string& _Ident,const Base* _InitVal = nullptr, const Base* _S_BracketList = nullptr) : 
        Ident(_Ident),InitVal(_InitVal),S_BracketList( _S_BracketList){}

        virtual void print(int PAD) const {
            fpout<<"Ident("<<Ident;
            if(S_BracketList != nullptr)
            {
                S_BracketList->print(PAD);
            }
            fpout<<")";
            if(InitVal != nullptr)
            {
                fpout<<"\t Value(";
                InitVal->print(PAD);
                fpout<<")";
            }
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }     
};

class InitVal : public Base{
    private:
        string BrackString;
        const Base* Exp_InitValList;
    public:
        InitVal(const Base* _Exp_InitValList = nullptr, string _BrackString = "  "):
        Exp_InitValList(_Exp_InitValList),BrackString(_BrackString){}
        virtual void print(int PAD) const {
            fpout<<BrackString[0];
            if(Exp_InitValList != nullptr)
                Exp_InitValList->print(PAD);
            fpout<<BrackString[1];
        }
        virtual void push(const Base* var)const{
            cerr<<"Error: This class doesn't have this function"<<endl;
            (void)var;
        }
};

class InitValList : public Base{
    private:
        mutable vector<const Base*> InitVal_List;
    public:
        InitValList(const Base* _InitVal){
            InitVal_List.push_back(_InitVal);
        }
        virtual void print(int PAD) const {
            for(size_t i = 0; i < InitVal_List.size(); ++i)
            {
                InitVal_List[i]->print(PAD);
                fpout<<",";
            }
        }
        virtual void push(const Base* _InitVal) const{
            InitVal_List.push_back(_InitVal);
        }
};

#endif
