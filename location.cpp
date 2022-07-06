#include<iostream>
using namespace std;
// Details of A location
class Location{
    private:
        int id;
        string name;
    public:
    void setName(string name){
        this->name = name;
    }
    string getName(){
        return name;
    }
    void setId(int id){
        this->id = id;
    }
    int getId(){
        return id;
    }
};
