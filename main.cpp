#include <iostream>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <ctype.h>
#include <algorithm>



struct Elf{
    std::queue<std::string> people;
    int timeToRepairAToy;

    Elf(int _time )
    :timeToRepairAToy(_time){}
};

 void getValues(std::string input, std::string& name, int& numberOfElf)
    {
        std::istringstream exprs(input);
        std::ostringstream getName;
        std::ostringstream getNumber;
        char devider = ' ';
        char c;
        int flag = 0;
        while (exprs.get(c))
        {
            if( c!=devider && flag == 0)
                getName << c;
            else if(c == devider)
                flag =1;
            else
            {
                getNumber<<c;
            }


        }
        name.assign(getName.str());
        numberOfElf =  atoi(getNumber.str().c_str());
    }


    bool isNumber(std::string word){
        bool isNum = true;
        for(std::string::const_iterator i = word.begin(); i != word.end(); ++i)
        isNum= isNum && isdigit(*i);
        return isNum;
    }

    void printElf(Elf elf){
        if(elf.people.empty()) {
                std::cout<<"There are no reclamations"<<std::endl;
        return;
        }
        std::queue<std::string> copy = elf.people;
        while(!copy.empty()){
            std::cout<<copy.front()<<std::endl;
            copy.pop();
        }
    }


    void printPeople(std::vector<Elf> elfs){
        for(int i = 0; i<elfs.size(); i++){
            std::cout<<"Elf "<<i+1<<":"<<std::endl;
            printElf(elfs[i]);
        }
    }

    int numberOfPresentsRepairedBy(Elf elf, int  time){
        int size = elf.people.size();
        return std::min((time/elf.timeToRepairAToy), size);
    }

    int getNumberOfPresents(std::vector<Elf> elfs, int time){
        int presents = 0;
         for(int i = 0; i<elfs.size(); i++){
            presents+=numberOfPresentsRepairedBy(elfs[i],time);
         }
         return presents;
    }

    void emptyQueue(std::queue<std::string>& people){
        while(!people.empty()){
            people.pop();
        }
    }

    void removeRepairedPresents(Elf& elf, int time){
        if(numberOfPresentsRepairedBy(elf,time)== elf.people.size()){
            emptyQueue(elf.people);
            return;
        }

        for(int i = 1; i <= numberOfPresentsRepairedBy(elf, time); ++i){
            elf.people.pop();
        }
    }
    void printRemainingPresents(std::vector<Elf>& elfs, int time){
        std::cout<<"After "<<time<<" minutes:"<<std::endl;
        for(int i = 0; i<elfs.size(); i++){
            removeRepairedPresents(elfs[i],time);
         }
         printPeople(elfs);
    }

int main()
{
    std::vector<Elf> elfs;
    int n;
    std::cin>>n;
    for(int i =0; i< n; i++){
        Elf elf(i+1);
        elfs.push_back(elf);
    }
    std::cin.ignore();
    std::string input;
    std::getline(std::cin, input);

    while(!isNumber(input)){
        std::string  name;
        int numberOfElf;

        getValues(input, name, numberOfElf);
        elfs[numberOfElf-1].people.push(name);
        std::getline(std::cin, input);

    }
    int time = atoi(input.c_str());


    printPeople(elfs);
    std::cout<<std::endl<<std::endl;
    std::cout<<getNumberOfPresents(elfs,time)<<std::endl<<std::endl;
    printRemainingPresents(elfs,time);
    std::cout<<std::endl;



}
