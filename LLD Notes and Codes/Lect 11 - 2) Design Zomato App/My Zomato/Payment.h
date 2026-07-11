#ifndef PAYMENT_H
#define PAYMENT_H

#include<bits/stdc++.h>
#include "Restaurant.h"
#include "itemDetails.h"


class Payment{
    public:
    static int paymentId;

    bool doPayment(string restaurantName, vector<ItemDetails>&itemList, int totalPrice){


        cout<<"Payment Successfull with Payment Id "<< ++this->paymentId <<" , Please find below details"<<endl<<endl;;
        cout<<"Restaurant Name: "<<restaurantName<<endl<<endl;

        for(auto item:itemList){
            cout<<"Dish: "<<item.dish<<endl;
            cout<<"Quantity: "<<item.quanatity<<endl;
            cout<<"Price: "<<item.price<<endl<<endl;
        }

        return true;
    }
    
};

int Payment::paymentId = 0;


#endif