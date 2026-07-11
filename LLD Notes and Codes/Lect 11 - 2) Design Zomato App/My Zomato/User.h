#ifndef USER_H
#define USER_H

#include<bits/stdc++.h>
#include "Cart.h"

using namespace std;

class User{
    public:
    int userId;
    string userName;
    string address;
    string mobNo;
    Cart *cart;


    User(int userId, string userName, string address, string mobNo){
        this->userId = userId;
        this->userName = userName;
        this->address = address;
        this->cart = new Cart();
    }

    int getUserId(){
        return this->userId;
    }

    string getUserName(){
        return this->userName;
    }

    string getUserAddress(){
        return this->address;
    }

    string getMobileNumber(){
        return this->mobNo;
    }

    Cart* getUserCart(){
        return this->cart;
    }
};


#endif