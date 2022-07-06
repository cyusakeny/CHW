#include<iostream>
using namespace std;
// Details of disease
 class Disease{
    private:
        string name;
        int total;
        int location_id ;    
    public:
        void setName(string name){
            this->name = name;
        }
        string getName(){
            return name;
        }
        void setTotal(int total){
            this->total = total;
        }
        int getTotal(){
            return total;
        }
        void setLocation_id(int location_id){
            this->location_id = location_id;
        }
        int getLocation_id(){
            return location_id;
        }
 };