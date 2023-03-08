#ifndef AST_TOP_HPP
#define AST_TOP_HPP

#include "ast.hpp"

#include <vector>
#include <iostream>

#include <fstream>

// extern std::ofstream fpout;

using namespace std;

class ast_Top {
    private:
        vector<const Base*> vec;
        int PAD = 0;
    public:
        void print(){
            PAD++;
            fpout<<"COMPUNIT\n"<<string(PAD, '\t');
            for(size_t i = 0; i < vec.size(); ++i){
                vec[i]->print(PAD+1);
                // fpout<<"\n"<<string(PAD, '\t');
                fpout<<"\n"<<string(PAD, '\t');
            }
        }
        void push(const Base *_var){
            vec.push_back(_var);//压进栈的可以是func也可以是decl
        }
};

// class CompUnit : public Base{
//     private:
//         const Base* Decl_FuncDef;
//     public:
//         CompUnit(const Base* _Decl_FuncDef) : Decl_FuncDef(_Decl_FuncDef) {}
//         virtual void print() const {
//             Decl_FuncDef->print();
//         }
//         virtual void push(const Base* var) const {
//             cerr<<"Error: This class doesn't have this function"<<endl;
//             (void)var;
//         }
// };

#endif
