#include<bits/stdc++.h>
using namespace std;

class LeaveHandler{
    protected:
        LeaveHandler *nextHandler;
    
    public:
        virtual void approveLeave(int requestedLeaveCount) = 0;

        virtual void setNextHandler(LeaveHandler *nextLeaveHandler){
            this->nextHandler = nextLeaveHandler;
        };

        LeaveHandler(){
            this->nextHandler = nullptr;
        }
};

class TeamLeaderHandler: public LeaveHandler{
    private:
        int approvableLeaveCount;

    public:
        TeamLeaderHandler(int approvableleaveCount){
            this->approvableLeaveCount = 2;
        }

        void approveLeave(int requestedLeaveCount){
            if(approvableLeaveCount >= requestedLeaveCount){
                cout<<"Your request is approved at TeamLeader level"<<endl;
                return;
            }

            if(this->nextHandler != nullptr){
                this->nextHandler->approveLeave(requestedLeaveCount);
            }
            else{
                 cout<<"Sorry for inconvenience, We couldn't approve your request as your requested leave count is exceeds the maximum limitation system can approve.";
            }
        }


};

class ManagerHandler: public LeaveHandler{
    private:
        int approvableLeaveCount;

    public:
        ManagerHandler(int approvableleaveCount){
            this->approvableLeaveCount = 10;
        }

        void approveLeave(int requestedLeaveCount){
            if(approvableLeaveCount >= requestedLeaveCount){
                cout<<"Your request is approved at Manager level"<<endl;
                return;
            }

            if(this->nextHandler != nullptr){
                this->nextHandler->approveLeave(requestedLeaveCount);
            }
            else{
                 cout<<"Sorry for inconvenience, We couldn't approve your request as your requested leave count is exceeds the maximum limitation system can approve.";
            }
        }

};

class DirectorHandler: public LeaveHandler{
    private:
        int approvableLeaveCount;

    public:
        DirectorHandler(int approvableleaveCount){
            this->approvableLeaveCount = 30;
        }

        void approveLeave(int requestedLeaveCount){
            if(approvableLeaveCount >= requestedLeaveCount){
                cout<<"Your request is approved at director level"<<endl;
                return;
            }

            if(this->nextHandler != nullptr){
                this->nextHandler->approveLeave(requestedLeaveCount);
            }
            else{
                 cout<<"Sorry for inconvenience, We couldn't approve your request as your requested leave count is exceeds the maximum limitation system can approve.";
            }
        }

};


int main(){

    LeaveHandler *teamLeaderHandler = new TeamLeaderHandler(2);
    LeaveHandler *managerHandler = new ManagerHandler(10);
    LeaveHandler *directorHandler = new DirectorHandler(30);
    
    teamLeaderHandler->setNextHandler(managerHandler);
    managerHandler->setNextHandler(directorHandler);

    int requestedLeaveCount = 3;
    teamLeaderHandler->approveLeave(requestedLeaveCount);

    return 0;
}