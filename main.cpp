#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

struct Man{
    public: std::string s_Name;
    public: char c_Gender;
    public: Man* op_Next;
    public: Man(std::string s_Name, char c_Gender){
        this->s_Name = s_Name;
        this->c_Gender =c_Gender;
        op_Next = nullptr;
    }
};

struct Hash{
    public: int i_Size;
    public: Man** o2p_ManSet;
    //COM: Functional
    public: std::hash<std::string> str_Hash;

    public: Hash(int i_Size){
        this->i_Size = i_Size;
        o2p_ManSet = new Man*[i_Size];
        std::fill(o2p_ManSet, o2p_ManSet+ i_Size, nullptr);
    }
    public: ~Hash(){
        for(int i_Ct=0; i_Ct< i_Size; i_Ct++){
            if(o2p_ManSet[i_Ct] == nullptr){
                continue;
            }

            for(Man* op_Tmp =o2p_ManSet[i_Ct];
                op_Tmp != nullptr;){
                Man* op_Tmp2 = op_Tmp->op_Next;
                delete op_Tmp;
                op_Tmp = op_Tmp2;
            }
        }
        delete [] o2p_ManSet;
    }

    public: void fn_InsItem(Man* op_Man){
        int i_Ind = str_Hash(op_Man->s_Name) % i_Size;
        Man* op_TmpMan = o2p_ManSet[i_Ind];
        op_Man->op_Next = op_TmpMan;
        o2p_ManSet[i_Ind] = op_Man;
    }

    public: void fn_GetRes(){
        for(int i_Ct=0; i_Ct< i_Size; i_Ct++){
            std::cout<< i_Ct << "-\t";
            for(Man* op_Tmp =o2p_ManSet[i_Ct];
                op_Tmp != nullptr;
                op_Tmp= op_Tmp->op_Next){
                std::cout<< op_Tmp->s_Name << ":"
                    << op_Tmp->c_Gender << " ";
            }
            std::cout<< "\n";
        }
    }
};

int main(){
    Hash o_HMap(5);
    o_HMap.fn_InsItem(new Man("Joe", 'M'));
    o_HMap.fn_InsItem(new Man("Sue", 'F'));
    o_HMap.fn_InsItem(new Man("Dan", 'M'));
    o_HMap.fn_InsItem(new Man("Nell", 'F'));
    o_HMap.fn_InsItem(new Man("Ally", 'F'));
    o_HMap.fn_InsItem(new Man("Bob", 'M'));

    return 0;
}
