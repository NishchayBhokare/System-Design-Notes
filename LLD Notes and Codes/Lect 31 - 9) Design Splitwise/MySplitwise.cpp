#include<bits/stdc++.h>
using namespace std;

class User{
    private:
    int id;
    string name;
    int borrowedMoney;
    int tokenMoney;
    unordered_map<int,User*>IndividualBorrowedMoney; //map<Amount,Second User>
    unordered_map<int,User*>IndividualTokenMoney;

    public:
    int getBorrowedMoney(){
        return this->borrowedMoney;
    }
    int getTokenMoney(){
        return this->tokenMoney;
    }
    int getBorrowedMoney(){
        return this->borrowedMoney;
    }

    void addBorrowedMoney(int amount){
        this->borrowedMoney += amount;
    }

    void substractBorrowedMoney(int amount){
        this->borrowedMoney -= amount;
    }

    void addTokenMoney(int amount){
        this->tokenMoney += amount;
    }

    void sustractTokenMoney(int amount){
        this->tokenMoney -=amount;
    }

    int getUserId(){
        return this->id;
    }


    unordered_map<int,User*> getIndividualBorrowedMoney(){
        return this->IndividualBorrowedMoney;
    }
    unordered_map<int,User*> getIndividualTokenMoney(){
        return this->IndividualTokenMoney;
    }
};


class UserGroup{
    private:
    vector<User*>userList;

    public:
    
    void addUser(User *user){
        userList.push_back(user);
    }

    void removeUser(User *user){
        //first check any borrowed money user is holding or not.
        //Also, checking if user has token money then also don't remove user
        if(user->getBorrowedMoney() == 0  && user->getTokenMoney() == 0){

            userList.erase(remove(userList.begin(), userList.end(), user), userList.end());
        }

    }
};

class ExpenseStrategy{

    public:
    virtual void addExpense(User *user, int expenseAmt, vector<User*>&userList) = 0;

    void settleExpense(User *user, int settleAmt, vector<User*>&userList){

        user->substractBorrowedMoney(settleAmt);

        int index = 0;
        while(settleAmt > 0 && index < userList.size()){
            if(userList[index]->getUserId() == user->getUserId()) continue;

            int tokenMoney = userList[index]->getTokenMoney();

            if(tokenMoney>0){
                
                int Amt = min(tokenMoney, settleAmt); //if settlement amount fulfilling token money..then take minmimum which token money else
                //taken settlement amount completely if token money is bigger.
                settleAmt -= Amt;
                userList[index]->sustractTokenMoney(Amt);
            }
            index++;
        }

    }
};

class ExpenseManager{
    public:
    void addExpense(User *user, int expenseAmt, vector<User*>&userList){

        int 
    }  

};