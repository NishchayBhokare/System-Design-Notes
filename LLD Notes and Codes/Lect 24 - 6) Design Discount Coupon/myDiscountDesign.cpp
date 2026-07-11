#include<bits/stdc++.h>
using namespace std;

class User{
    public:
    string name;
    bool isPremiumMember;

    User(string name, bool isPremiumMember){
        this->name = name;
        this->isPremiumMember = isPremiumMember;
    }
    bool getPremiumStatus(){
        return this->isPremiumMember;
    }
    
};


class Product{

    public:
    string name;
    string cateogry;
    int price;

    Product(string name, string category, int price){
        this->name = name;
        this->cateogry = category;
        this->price = price;
    }

    int getProductPrice(){
        return this->price;
    }

    string getProductCategory(){
        return this->cateogry;
    }
};

class CartItem{
    public:
    Product *product;
    int quantity;

    CartItem(Product *product, int quantity){
        this->product = product;
        this->quantity = quantity;
    }

    int getPrice(){
        return (this->product->getProductPrice() * this->quantity);
    }

    Product * getProduct(){
        return this->product;
    }
};

class Cart{
    private:
        Cart(){
            this->totalPrice = 0;
            this->finalPrice = 0;
        };
    public:
    vector<CartItem*>cartItemsList;
    int totalPrice;
    int finalPrice;
    static Cart *instance;

    static Cart* getInstance(){
        
        if(!instance){
            instance = new Cart();
        }
        return instance;
    }


    int getTotalPrice(){
        
        if(this->totalPrice == 0){
            for(CartItem *cartItem: cartItemsList){
                this->totalPrice += cartItem->getPrice();
            }
        }
      
        return this->totalPrice;
    }

    void setFinalPrice(int price){
        this->finalPrice = price;
    }

    int getFinalPrice(){
        return this->finalPrice;
    }
    void addItemsToCart(Product *product, int quantity){
        this->cartItemsList.push_back(new CartItem(product,quantity));
    }

};

Cart *Cart::instance = nullptr; 




class DiscountStrategy{
    public:
    DiscountStrategy(){}

    virtual void applyDiscount(Cart *cart) = 0;
    virtual double getDiscount() = 0;
};

class Percentage:public DiscountStrategy{
    public:
    int totalDiscount, percentageDiscount;

    Percentage(int percentage){this->percentageDiscount = percentage;}

    void applyDiscount(Cart *cart)override{

        int totalPrice = cart->getTotalPrice();
        this->totalDiscount = double(percentageDiscount/100.0) * totalPrice;
    }

    double getDiscount()override{
        return this->totalDiscount;
    }
};



class Flat: public DiscountStrategy{
    public:
    int flatDiscount,totalDiscount;

    Flat(double discount){this->flatDiscount = discount;}

    void applyDiscount(Cart *cart)override{

        int totalPrice = cart->getTotalPrice();
        int discount = min(totalPrice,flatDiscount);
        this->totalDiscount = discount;
    }
    double getDiscount()override{
        return this->totalDiscount;
    }
};

class PercentageFlat: public DiscountStrategy{
    public:
    double upparCap, percentage, totalDiscount;

    PercentageFlat(int percentage, int upparCap){
        this->percentage = percentage;
        this->upparCap = upparCap; 
    }

    void applyDiscount(Cart *cart) override{

        
        double totalPrice = cart->getTotalPrice();
        
        double percentageDiscount = double(percentage/100.0) * totalPrice;
        
        double maxDiscount = min(totalPrice, percentageDiscount);
   
        this->totalDiscount = min(upparCap, maxDiscount);
    }
    double getDiscount() override{
        return this->totalDiscount;
    }

};

class CouponStrategy{
    public:
    bool isCouponCombinable;
    bool isCouponApplicable;
    int totalDiscount;

    CouponStrategy(){
        this->totalDiscount = 0;
    }

    virtual void applyCoupon(Cart *cart) = 0;
    
    virtual int getTotalDiscount()=0;
};

class SeasonalCoupon:public CouponStrategy{
    public:

    SeasonalCoupon(bool isCouponApplicable, bool isCouponCombinable){
        this->isCouponApplicable = isCouponApplicable;
        this->isCouponCombinable = isCouponCombinable;
    }

    void applyCoupon(Cart *cart) {
        if(this->isCouponApplicable){

            double flatDiscount = 100;
            DiscountStrategy *discountStrategy = new Flat(flatDiscount);
            discountStrategy->applyDiscount(cart);

            double discount = discountStrategy->getDiscount();
            this->totalDiscount += discount;
        }
        
    }
    
    int getTotalDiscount(){
        return this->totalDiscount;
    }
};


class BankingCoupon:public CouponStrategy{
  public:
    
    BankingCoupon(bool isCouponApplicable, bool isCouponCombinable){
        this->isCouponApplicable = isCouponApplicable;
        this->isCouponCombinable = isCouponCombinable;
    }

    void applyCoupon(Cart *cart){
        if(this->isCouponApplicable){

            double percentage = 30;
            DiscountStrategy *discountStrategy = new Percentage(30);
            discountStrategy->applyDiscount(cart);


            double discount = discountStrategy->getDiscount();
            this->totalDiscount += discount;
        }
        
    }
    
    int getTotalDiscount(){
        return this->totalDiscount;
    }
};

class PremiumCoupon:public CouponStrategy{
  public:
    
    PremiumCoupon(bool isCouponApplicable, bool isCouponCombinable){
        this->isCouponApplicable = isCouponApplicable;
        this->isCouponCombinable = isCouponCombinable;
    }

    void applyCoupon(Cart *cart){
        if(this->isCouponApplicable){

            double percentage = 10, upparCap=250;
            DiscountStrategy *discountStrategy = new PercentageFlat(percentage,upparCap);
 
            discountStrategy->applyDiscount(cart);

            double discount = discountStrategy->getDiscount();
            this->totalDiscount += discount;
        }
        
    }

    int getTotalDiscount(){
        return this->totalDiscount;
    }
};

enum CouponType{
    seasonalCoupon,
    bankingCoupon,
    premiumCoupon
};

class CouponManager{

    public:
    CouponStrategy *strategy;
    static CouponManager *instance;

    static CouponManager* getInstance(){
        if(!instance){
            instance = new CouponManager();
        }

        return instance;
    }

    void applyCoupon(CouponType type, Cart *cart){

        if(type == CouponType::seasonalCoupon){

            this->strategy = new SeasonalCoupon(true,true);
        }
        else if(type == CouponType::bankingCoupon){
            this->strategy = new BankingCoupon(true,false);
        }
        else if(type == CouponType::premiumCoupon){
            this->strategy = new PremiumCoupon(true,false);
        }
        else
        {
            this->strategy = nullptr;
        }

        if(this->strategy != nullptr){
            this->strategy->applyCoupon(cart);
        }
        else{
            cout<<"Invalid Coupon "<<endl;
        }
    }

    int getTotalDiscount(){
        return this->strategy->getTotalDiscount();
    }

};

CouponManager *CouponManager::instance = nullptr;

class CartManager{
    public:

    Cart *cart;
    static CartManager *instance;

    static CartManager* getInstance(){
        if(!instance){
            instance = new CartManager();
        }
        return instance;
    }

    CartManager(){
        this->cart = Cart::getInstance();
    }

    void addItemsToCart(Product *product, int quantity){
        this->cart->addItemsToCart(product,quantity);
    }    

    int totalPrice(){
        return this->cart->getTotalPrice();
    }
};

CartManager *CartManager::instance = nullptr;

class ApplicationManager{
    Cart *cart;
    CartManager *cartManager;
    CouponManager *couponManager;
    int finalPrice = 0;
    
    public:
    ApplicationManager(){
        this->cartManager = CartManager::getInstance();
        this->couponManager = CouponManager::getInstance();
        this->cart = Cart::getInstance();
    }


    void addItemsToCart(Product *product, int quantity){
        this->cartManager->addItemsToCart(product,quantity);
    }  

    int getTotalPrice(){
        return this->cart->getTotalPrice();
    }

    void applyCoupon(CouponType type){
        this->couponManager->applyCoupon(type,cart);
    }

    int getTotalDiscount(){
        return this->couponManager->getTotalDiscount();
    }

    int getFinalPrice(){
        this->finalPrice = this->getTotalPrice() - this->getTotalDiscount();

        cout<<endl<<"Discount "<< this->getTotalDiscount()<<endl;
        // cout<<"Total "<<this->getTotalPrice()<<endl;
        
        cart->setFinalPrice(finalPrice);

        return this->finalPrice;
    }
    
};

int main(){

    Product *p1 = new Product("Shirt", "Clothes", 250);
    Product *p2 = new Product("Trouser", "Clothes", 750);
    Product *p3 = new Product("Fan", "Electronics", 750);

    ApplicationManager *applicationManager = new ApplicationManager();
    applicationManager->addItemsToCart(p1,2);
    applicationManager->addItemsToCart(p2,1);
    applicationManager->addItemsToCart(p3,1);

    applicationManager->applyCoupon(CouponType::premiumCoupon);

    cout<<endl<<"The final price of your cart is "<<applicationManager->getFinalPrice()<<endl;
    
    return 0;
}