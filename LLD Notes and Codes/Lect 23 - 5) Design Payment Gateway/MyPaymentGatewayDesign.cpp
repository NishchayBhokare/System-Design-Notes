#include<bits/stdc++.h>
using namespace std;

class BankUserAccount{
    private:
        string accountHolderName;
        int accountId;
        int balance;
    
    public:
        BankUserAccount(int accountId, string accountHolderName, int balance){
            this->accountId = accountId;
            this->accountHolderName = accountHolderName;
            this->balance = balance;
        }
        int getAccountId(){
            return this->accountId;
        }

        string getAccountHolderName(){
            return this->accountHolderName;
        }
        int getBalance(){
            return this->balance;
        }
        void depositBalance(int amount){
            this->balance += amount;
        }
        void withdrawAmount(int amount){
            balance -= amount;

        }
};


class BankUserFactory{
    private:
    vector<BankUserAccount*>userAccounts;
    static int accountId;
    static BankUserFactory *instance;

    BankUserFactory(){}

    public:
    static BankUserFactory* getInstance(){
        
        if(!instance){
            instance = new BankUserFactory();
        }
        return instance;
    }

    int addUser(string accountHolderName, int balance){

        this->accountId+=1;
        BankUserAccount *newAccount = new BankUserAccount(accountId,accountHolderName,balance);
        this->userAccounts.push_back(newAccount);
        
        return this->accountId;
    }

    int getUserId(){
        return this->accountId;
    }

    vector<BankUserAccount*>& getUserFactory(){
        return this->userAccounts;
    }
};

int BankUserFactory::accountId = 0;
BankUserFactory* BankUserFactory::instance = nullptr;



class PaymentGateway{
    protected:
        BankUserFactory *userFactory;
        BankUserAccount *senderAccount;
        BankUserAccount *receiverAccount;
        int senderId, receiverId, amount;
        
        
    public:

        PaymentGateway(int senderId, int receiverId, int amount){
            this->senderId = senderId;
            this->receiverId = receiverId;
            this->amount = amount;

            this->userFactory = BankUserFactory::getInstance();
        }

        virtual bool validate() = 0;
        virtual bool initiate() = 0;
        virtual bool confirm() = 0;

        bool paymentTemplate(){
            bool validateStatus, initiateStatus, confirmStatus;

            validateStatus = validate();
            if(validateStatus) initiateStatus = initiate();
            if(initiateStatus) confirmStatus = confirm();

            return (validateStatus && initiateStatus && confirmStatus);
        }
};

class PaytmGateway:public PaymentGateway{

    public:
    PaytmGateway(int senderId, int receiverId, int amount):PaymentGateway
    ( senderId, receiverId, amount){
        this->senderAccount = nullptr;
        this->receiverAccount = nullptr;
    }

    bool validate(){

        //validating receiver account exist or not.
        vector<BankUserAccount*> userAccounts = userFactory->getUserFactory();
        
        for(BankUserAccount* userAccount:userAccounts){
            if(userAccount->getAccountId() == this->receiverId){
                receiverAccount = userAccount;
                break;
            }
        }
        

        if(receiverAccount == nullptr) {
            cout<<"Reciever Account doesn't exist, Transaction Failed "<<endl;
            return false;
        }
        
        //if true, then check sender account balance.

        for(BankUserAccount* userAccount:userAccounts){
            if(userAccount->getAccountId() == this->senderId){
                senderAccount = userAccount;
                break;
            }
        }

        if(senderAccount->getBalance() < amount){
            cout<<"Sender Account doesn't have enough balance, Transaction Failed "<<endl;
            return false;
        }

        return true;
    }

    bool initiate(){
        cout<<"Initiating payment"<<endl;
        return true;
    }

    bool confirm(){

        //Upadate sender account and reciver account balance.
        senderAccount->withdrawAmount(this->amount);
        receiverAccount->depositBalance(this->amount);

        cout<<"Paytm Gateway Transaction Completed "<<endl;
        return true;
    }
};

class RazorpayGateway:public PaymentGateway{


    public:
    RazorpayGateway(int senderId, int receiverId, int amount):PaymentGateway
    ( senderId, receiverId, amount){
        this->senderAccount = nullptr;
        this->receiverAccount = nullptr;
    }

    bool validate(){

        //validating receiver accountexist or not.
        vector<BankUserAccount*> userAccounts = userFactory->getUserFactory();
        
        for(BankUserAccount* userAccount:userAccounts){
            if(userAccount->getAccountId() == this->receiverId){
                receiverAccount = userAccount;
                break;
            }
        }

        if(receiverAccount == nullptr){
            cout<<"Reciever Account doesn't exist, Transaction Failed "<<endl;
            return false;
        }
        
        //if true, then check sender account balance.

        for(BankUserAccount* userAccount:userAccounts){
            if(userAccount->getAccountId() == this->senderId){
                senderAccount = userAccount;
                break;
            }
        }

        if(senderAccount->getBalance() < amount){
            cout<<"Sender Account doesn't have enough balance, Transaction Failed "<<endl;
            return false;
        }

        
        return true;

    }

    bool initiate(){
        cout<<"Initiating payment";
        return true;

    }

    bool confirm(){

        //Upadate sender account and reciver account balance.
        senderAccount->withdrawAmount(this->amount);
        receiverAccount->depositBalance(this->amount);

        cout<<"RazorpayGateway Gateway Transaction Completed "<<endl;
        return true;
    }
};



enum class PaymentMethod{
    PaytmGateway,
    RazorpayGateway
};


class PaymentGatewayFactory{
    private:
    PaymentGateway *paymentGateway;
    
    public:
    PaymentGateway* createPaymentMethod(int senderId, int reciverId, int amount, PaymentMethod paymentType){
        
        if(PaymentMethod::PaytmGateway == paymentType){

            return new PaytmGateway(senderId, reciverId, amount);
        }
        else if(PaymentMethod::RazorpayGateway == paymentType){
            return new RazorpayGateway(senderId, reciverId, amount);
        }
        else
            return nullptr;

    }
};

// class PaymentServiceProvider{

//     private:
//     PaymentGateway *paymentGateway;

//     public:

//     bool pay(int senderId, int reciverId, int amount, PaymentMethod paymentType){
    
//         return this->paymentGateway->paymentTemplate();
//     }

// };

class PaymentController{
    private:
        PaymentGateway *paymentGateway;
        PaymentGatewayFactory *paymentGatewayFactory;

    public:
    PaymentController(){
        this->paymentGatewayFactory = new PaymentGatewayFactory();
    }


    bool pay(int senderId, int receiverId, int amount, PaymentMethod paymentType){
        this->paymentGateway = paymentGatewayFactory->
                createPaymentMethod(senderId,receiverId,amount,paymentType);

        
        return this->paymentGateway->paymentTemplate();
    }
};


int main(){
    BankUserFactory *bankUserFactory = BankUserFactory::getInstance();
    int nishchayId = bankUserFactory->addUser("Nishchay", 5000);
    int kiranId = bankUserFactory->addUser("Kiran", 3000);
    int RamId = bankUserFactory->addUser("Ram ", 2000);
    int Viraj = bankUserFactory->addUser("Viraj ",1000);

    vector<BankUserAccount*> userAccounts = bankUserFactory->getUserFactory();
 

    PaymentController *paymentController = new PaymentController();
    bool paymentStatus = paymentController->pay(nishchayId,2,7000, PaymentMethod::PaytmGateway);

    if(paymentStatus)
        cout<<"Transaction is successful"<<endl;
    
    else   
        cout<<"Transaction is Failed"<<endl;

    return 0;
}


