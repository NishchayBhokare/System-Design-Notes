#ifndef CART_H
#define CART_H

#include<bits/stdc++.h>
#include "itemDetails.h"
#include "Payment.h"
#include "Restaurant.h"

using namespace std;

class Cart{
    public:
    static int cartId;
    vector<ItemDetails> itemList;
    int totalPrice;
    Payment *payment;

    Cart(){
        this->cartId++;
        this->totalPrice = 0;
        payment = new Payment();
    }

    void addItemToCart(Restaurant *restaurant, string dish, int quantity){

        int price = 0;
        for(auto item:restaurant->menuItems){

            if(item.first == dish){
                price = item.second;
            }
        }

        itemList.push_back({restaurant->restaurantId, restaurant->restaurantName, dish,quantity, price*quantity});
    }

    void checkout(){
        for(auto item:itemList){
           totalPrice += item.price; 
        }
    }

    void paymentDetails(int restaurantId){
        string restaurantName = "";

        for(auto item:itemList){
            if(item.restaurantId == restaurantId){
                restaurantName = item.restaurantName;
            }
        }

        bool status = payment->doPayment(restaurantName, itemList,totalPrice);

        this->totalPrice = 0;
        this->itemList.clear();
    }
};

int Cart::cartId = 0;


#endif