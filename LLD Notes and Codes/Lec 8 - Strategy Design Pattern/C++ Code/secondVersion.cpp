//By creating another class for projectile.

#include<bits/stdc++.h>
#include<iostream>
#include<conio.h>
using namespace std;

//Talkable Interface.
class Talkable{
    public:
    virtual void Talk() = 0;
    virtual ~Talkable() {};
};

class NormalTalk:public Talkable{
    public:
        NormalTalk(){};

        void Talk() override{
            cout<<"Normal Walk"<<endl;
        }
};

class NoTalk:public Talkable{
    public:
        void Talk() override{
            cout<<"Not talk"<<endl;
        }
};

//Walkable Interface
class Walkable{
    public:
        virtual void Walk()=0;
        virtual ~Walkable(){};
};

class NormalWalk:public Walkable{
    public:
        void Walk() override{
            cout<<"Normal Walk"<<endl;
        }
};

class NoWalk:public Walkable{
    public:
        void Walk() override{
            cout<<"No Walk"<<endl;
        }
};


//Flyable Interface
class Flayble{
    public:
        virtual void Fly()=0;
        virtual ~Flayble(){};
};

class NormalFly:public Flayble{
    public:
        void Fly() override{
            cout<<"Normal Fly"<<endl;
        }
};

class NoFly:public Flayble{
    public:
        void Fly() override{
            cout<<"No Fly"<<endl;
        }
};

//Projectile Inteface
class Projectile{
    public:
        virtual void Projection() = 0;
        virtual ~Projectile(){};
};

class NormalProjectile:public Projectile{
    public:
        void Projection() override{
            cout<<"Normal Projection"<<endl;
        }
};

class NoProjectile:public Projectile{
    public:
        void Projection() override{
            cout<<"No Projection"<<endl;
        }
};

class Robot{
    
    protected:

    Talkable *T;
    Walkable *W;
    Flayble *F;
    Projectile *P;

    public:

    Robot(Talkable *t, Walkable *w, Flayble *f, Projectile *p){
        this->T = t;
        this->W = w;
        this->F = f;
        this->P = p;
    }

    void Talk(){
        T->Talk();
    }

    void Walk(){
        W->Walk();
    }

    void Fly(){
        F->Fly();
    }

    void Projectile(){
        P->Projection();
    }

};



int main(){
  Robot *robot1 = new Robot(new NormalTalk(), new NoWalk(), new NoFly(),new NormalProjectile());
    robot1->Talk();
    robot1->Walk();
    robot1->Fly();
    robot1->Projectile();
    

    return 0;

}