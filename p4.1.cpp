#include<iostream>
using namespace std;
class Tracer{
    int id;
public:
    Tracer(int i):id(i)
    {cout<<"Constructing #"<<id<<endl; }
    ~Tracer()
    {cout<<"Destructing #"<<id<<endl;}
};
int main(){
    cout<<"Enter the block\n";
    {
        Tracer a(1),b(2); 
        cout<<"....working....\n";
    }
        cout<<"Left the block\n";   
        return 0;
    }
