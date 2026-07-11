#include<bits/stdc++.h>
using namespace std;

//Modal Class
class Product{
    private:

    string name;
    string category;
    int quantity;

    public:
    Product(string name, string category, int quantity){
        this->name = name;
        this->category = category;
        this->quantity = quantity;
    }

    int getQuantity(){
        return this->quantity;
    }

    string getName(){
        return this->name;
    }

    string getCategory(){
        return this->category;
    }

    void setQuantity(int quantity){
        this->quantity =quantity;
    }
};


class InventoryStore{
    protected:
    string name;
    vector<Product*>productList;
    
    InventoryStore(string name){
        this->name = name;
    }

    public:
   

    Product* getProduct(string name, string category, int quantity){

        for(Product* product: this->productList){

            string productCategory = product->getCategory();
            string productName = product->getName();
            int productQuantity = product->getQuantity();

            if(productCategory == category && productName == name 
                && productQuantity >= quantity){
                
                //Before returning decrease the quantity of current product.
                if((productQuantity - quantity) > 0){

                    int remainingQuantity = productQuantity - quantity;
                    product->setQuantity(remainingQuantity);
                }

                if((productQuantity - quantity) == 0){
                    this->productList.erase(remove(this->productList.begin(), this->productList.end(),
                product), this->productList.end());

                }

                return product;
            }
        }

        //if not found return product is not available.
        return nullptr;
    }

    vector<Product*> getProductList(){
        return this->productList;
    }
    
    void addProduct(string name, string category, int quantity){

        this->productList.push_back(new Product(name,category,quantity));
    }

    string getInventoryName(){
        return this->name;
    }

    int getInventoryListSize(){
        return this->productList.size();
    }
};

class DB_Inventory:public InventoryStore{
    public:
    DB_Inventory(string name):InventoryStore(name){}
};

class Dateverse_Inventory:public InventoryStore{
    Dateverse_Inventory(string name):InventoryStore(name){}
};

class Replenish{
    public:

    Replenish(){}
    virtual void replenishStatus(Darkstore *darsktore) = 0;
};

class ThresholdStrategy:public Replenish{
    private:
    int Threshold;

    public:
    ThresholdStrategy(int Threshold){
        this->Threshold = Threshold;
    }

    void replenishStatus(Darkstore *darkstore){

        bool isEnoughInventory = true;

        for(InventoryStore* store:darkstore->getInventory()){

            vector<Product*> productList = store->getProductList();
            
            if(productList.size() < this->Threshold){
                isEnoughInventory = false;

                cout<<"Required Immediate Action! The Darkstore "<<darkstore->getDarkStoreName()
                <<" has low inventory at "<<store->getInventoryName()<<endl;
            }
        }

        if(isEnoughInventory){
            cout<<"Darkstore "<<darkstore->getDarkStoreName()<<
            " has enough inventory in all Inventory stores"<<endl;
        }
    }
};

class WeeklyStrategy:public Replenish{
    private:
    string day;

    public:
    WeeklyStrategy(string day){
        this->day = day;
    }

    void replenishStatus(Darkstore *darkstore){

        cout<<"Darkstore "<<darkstore->getDarkStoreName()<<" will get get fill on every "<<this->day<<endl;
    }   
};

class Darkstore{
    private:
    string name;

    Replenish *replenish;
    InventoryStore* inventoryStore;

    public:
    Darkstore(string DarkstoreName, string type, int Threshold=0, string day=""){
        this->name = DarkstoreName;

        if(type == "Threshold"){
            replenish = new ThresholdStrategy(Threshold);
        }
        else if(type == "Weekly"){
            replenish = new WeeklyStrategy(day);
        }
    }

    string getDarkStoreName(){
        return this->name;
    }

    InventoryStore*> getInventory(){
        return this->inventoryStore;
    }

    void addInventoryProduct(string name, string category, int quantity){     
        InventoryStore *smallestInventory;
        int length = INT_MAX;

        for(InventoryStore* store:inventoryStore){

            if(store->getInventoryListSize() < length){
                smallestInventory = store;
                length = store->getInventoryListSize();
            }
        
        }

        smallestInventory->addProduct(name,category,quantity);
    }

    Product* getInventoryProduct(string name, string category, int quantity){

        Product *product = nullptr;
        for(InventoryStore* store:inventoryStore){
            product = store->getProduct(name, category, quantity);

            if(product != nullptr) {
                cout<<"Product is present at Inventory "<<store->getInventoryName()<<endl;
                return product;
            }
        }

        return nullptr;
    }
};


class DarkStoreFactory{
    public:
    Darkstore* createDarkstore(string darkstoreName, string replinishStrategyType, int Threshold, string day){
        return new Darkstore(darkstoreName,replinishStrategyType, Threshold, day);
    }
};

class ApplicationManager{
    private:
    unordered_map<string, Darkstore* > darkStoreList;
    
    DarkStoreFactory *darkstoreFactory;

    public:
    ApplicationManager(){
        this->darkstoreFactory = new DarkStoreFactory();
    }


    void createDarkStore(string darkstoreName, string replinishStrategyType, int Threshold=0, string day=""){
        Darkstore* newDarkstore = 
        this->darkstoreFactory->createDarkstore(darkstoreName,replinishStrategyType, Threshold, day);
        
        this->darkStoreList.insert({darkstoreName,newDarkstore});
    }

    void addProduct(string name, string category, int quantity, string darkstoreName){
        darkStoreList[darkstoreName]->addInventoryProduct(name,category,quantity);
    }

    Product* getProduct(string name, string category, int quantity, string darkstoreName){
        return darkStoreList[darkstoreName]->getInventoryProduct(name,category,quantity);
    }

    // void getDarkstoreReplenishStatus(string darkstoreName){
    //     darkStoreList[darkstoreName]
    // }
};

int main(){
    ApplicationManager *applicationManager = new ApplicationManager();

    int threshold = 2;
    string DarkstoreName = "Pune_DarkStore";
    applicationManager->createDarkStore(DarkstoreName, "Threshold", threshold);

    applicationManager->addProduct("Fan","Electronics",3, DarkstoreName);
    applicationManager->addProduct("TV","Electronics",2, DarkstoreName);
    applicationManager->addProduct("Shirt","Fashion",1, DarkstoreName);

    applicationManager->addProduct("coolar","Electronics",3, DarkstoreName);
    applicationManager->addProduct("Brush","Home",2, DarkstoreName);
    applicationManager->addProduct("Dettol","Home",1, DarkstoreName);

    Product * product = applicationManager->getProduct("Fan","Electronics", 2, DarkstoreName);

    cout<<"Received product with product name "<<product->getName()<<" and with product category "
    <<product->getCategory()<<" and with product quantity "<<product->getQuantity();


}