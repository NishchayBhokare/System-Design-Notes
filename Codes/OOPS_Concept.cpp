#include<bits/stdc++.h>
using namespace std;

class car{
    public:

    void working(){
        cout<<"yes working"<<endl;
    }

    virtual void accelarte()=0;
    virtual void applyBreak()=0;

    virtual ~car(){};
};



class sportsCar: public car{
    public:
        int speed;

        sportsCar(int speed){
            this->speed = 0;
        }

        void accelarte(){
            this->speed += 20;
            cout<<"Increase speed "<<this->speed<<endl;
        }

        void applyBreak(){
            cout<<"Break applied"<<endl;
        }

        void notapply(){

        }
};

int main(){
    sportsCar *sp = new sportsCar(20);
    car* c = new sportsCar(20);
  

    sp->accelarte();
    sp->applyBreak();
    sp->working();
    
    cout<<endl;

    c->applyBreak();
    c->accelarte();
    c->working();
    
}