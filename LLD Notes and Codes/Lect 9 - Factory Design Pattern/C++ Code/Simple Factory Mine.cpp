#include<bits/stdc++.h>
using namespace std;

class Burger{

    public:
        virtual void prepare() = 0;
        virtual ~Burger(){};
};

class BasicBurger:public Burger{

    public:
    void prepare(){
        cout<<"preparing basic burger"<<endl;
    }
};

class StandardBurger:public Burger{

    public:
    void prepare(){
        cout<<"preparing Standard burger"<<endl;
    }
};

class PremiumBurger:public Burger{

    public:
    void prepare(){
        cout<<"preparing Premium burger"<<endl;
    }
};


class BurgerFactory{
    Burger *B;

    public:

    BurgerFactory(string BurgerType){

        if(BurgerType == "Basic")
            B = new BasicBurger;
        
        else if(BurgerType == "Standard")
            B = new StandardBurger;

        else if(BurgerType == "Premium")
            B = new PremiumBurger;

    }

    Burger* getBurger(){
        return this->B;
    }

};

int main(){

    BurgerFactory *BF = new BurgerFactory("Premium");

    Burger *b = BF->getBurger();
    b->prepare();
}