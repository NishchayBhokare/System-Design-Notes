#include<bits/stdc++.h>
#include "itemDetails.h"
#include "User.h"
#include "Restaurant.h"
#include "Payment.h"
#include "Cart.h"
using namespace std;


class ApplicatinManager{

    private:

    ApplicatinManager(){
        Restaurant *r1 = new Restaurant(1, "Bombay Restaurant", "Karad", { {"Vadapav",20}, {"Misal",50}, {"PavBhaji",60} });
        Restaurant *r2 = new Restaurant(2, "Sadashiv Restaurant", "Satara",{{"Chicken",100}, {"Mutton",250}, {"Fish",120} });
        Restaurant *r3 = new Restaurant(3, "Amrai Restaurant", "Pune",{{"Paneer", 150}, {"Dal Tadka", 140}, {"Dal Fry", 170}});
        

        restaurantList.push_back(r1);
        restaurantList.push_back(r2);
        restaurantList.push_back(r3);
    }

    public:
    vector<Restaurant*>restaurantList;
    static ApplicatinManager *instance;

    static ApplicatinManager * getInstance(){
        if(!instance){
            instance = new ApplicatinManager();
        }
         
        return instance;
    }
    
    vector<Restaurant*> getRestaurant(string dish){
        vector<Restaurant*> filteredRestaurantList;

        for(auto restaurant: restaurantList){
            for(auto restaurantDishPair:restaurant->menuItems){

                if(dish == restaurantDishPair.first){
                    filteredRestaurantList.push_back(restaurant);
                }
            }
        }
        return filteredRestaurantList;
    }

    int getDishPrice(Restaurant *restaurant, string dish, int quantity){

        for(auto item:restaurant->menuItems){
            if(item.first == dish)
                return (item.second*quantity);
        }
        return -1;
    }


    void addItem(Cart *cart, Restaurant *restaurant, string dish, int quantity){
        cart->addItemToCart(restaurant,dish,quantity);
    }

    void checkoutCart(Cart *cart){
        cart->checkout();
    }

    void paymentMethod(int restaurantId, Cart *cart){
        cart->paymentDetails(restaurantId);
    }
    
};


ApplicatinManager* ApplicatinManager:: instance = nullptr;


int main(){

    User *user = new User(1, "Nishchay", "Kolhapur", "8999841319"); 

    string dish = "Fish";
    int quantity = 2;
    
    ApplicatinManager *manager = ApplicatinManager::getInstance();
    

    vector<Restaurant*>restaurantList = manager->getRestaurant(dish); //in return we will get list of restaurant

    manager->addItem(user->cart, restaurantList[0], dish, 1);
    manager->addItem(user->cart, restaurantList[0], "Mutton", 2);

    manager->checkoutCart(user->cart);
    manager->paymentMethod(restaurantList[0]->restaurantId,user->cart);

    return 0;
};
