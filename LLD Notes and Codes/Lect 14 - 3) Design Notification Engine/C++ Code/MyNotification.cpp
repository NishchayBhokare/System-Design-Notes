#include<bits/stdc++.h>
using namespace std;


class NotificationDetails{
    public:
        string type;
        string time;    
};

class NotificationLogger{
    private:
        static NotificationLogger *instance;
        vector<NotificationDetails*>notificationLoggedList;
        NotificationLogger(){}

    public:
    static NotificationLogger* getInstance(){
        mutex m;
        unique_lock<mutex> lock(m);
        if(!instance){
            instance = new NotificationLogger();
        }
        lock.unlock();
        return instance;
    }

    void setNotificationLog(string type){
        NotificationDetails * details = new NotificationDetails();

        time_t now = time(0);
        string time = ctime(&now);

        details->type = type;
        details->time = time;
        
        this->notificationLoggedList.push_back(details);
    }

    vector<NotificationDetails*> getNotificationLog(){
        return this->notificationLoggedList;
    }
};

NotificationLogger* NotificationLogger::instance = nullptr;

class Notification{
    public:
        Notification(){}

        virtual void pushNotification() = 0;
};


class SMS_Notification: public Notification{

    public:
        void pushNotification(){
            cout<<"Sending SMS Notification"<<endl;
        }
};

class Email_Notification: public Notification{
    public:
        void pushNotification(){
            cout<<"Sending Email Notification"<<endl;
        }
};

class NotificationFactory{
    string type;
    Notification *notification;
    static NotificationFactory* instance;

    NotificationFactory(){}
    public:

    static NotificationFactory* getInstance(){

        mutex m;
        unique_lock<mutex>lock(m);
        if(!instance){
            instance = new NotificationFactory();
        }
        lock.unlock();
        return instance;
    }
    
    void createNotification(string type){
        if(type == "SMS")
            this->notification = new SMS_Notification();

        else if(type == "Email")
            this->notification = new Email_Notification();

        else 
            this->notification = nullptr;

        //call push notification
        this->notification->pushNotification();
    }

};

NotificationFactory* NotificationFactory :: instance = nullptr;

class NotificationManager{
    private:
        NotificationManager(){
            logger = NotificationLogger::getInstance(); 
            notificationFactory = NotificationFactory::getInstance();
        }

        static NotificationManager *instance;
        Notification *notification;
        NotificationLogger *logger;
        NotificationFactory *notificationFactory;
        
    public:
        static NotificationManager* getInstance(){
          
            if(!instance){
                instance = new NotificationManager();
            }

            return instance;
        }

        
        void sendNotificationRequest(string type){
           this->notificationFactory->createNotification(type);
           this->logger->setNotificationLog(type);
        }

      

        void showNotificationLog(){
            vector<NotificationDetails*> notificationLogList =  this->logger->getNotificationLog();

            cout<<endl;
            for(auto *notification:notificationLogList){
                cout<<"Notification Type: "<<notification->type<<", ";
                cout<<"Notification Time: "<<notification->time;
            }
        }

};

NotificationManager* NotificationManager::instance = nullptr;

int main(){
 

    NotificationManager *manager = NotificationManager::getInstance();

    manager->sendNotificationRequest("Email");
    manager->sendNotificationRequest("SMS");
    manager->sendNotificationRequest("SMS");
    manager->sendNotificationRequest("Email");
    manager->sendNotificationRequest("SMS");


    manager->showNotificationLog();
    

    return 0;
}