#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<bits/stdc++.h>
using namespace std;

class Restaurant{
    public:
    int restaurantId;
    string restaurantName;
    string location;
    vector< pair<string,int> >menuItems;
    

    Restaurant(int restaurantId, string restaurantName, string location, vector< pair<string,int> >menuItems){
        this->restaurantId = restaurantId;
        this->restaurantName = restaurantName;
        this->location = location;
        this->menuItems = menuItems;
    }
};

#endif