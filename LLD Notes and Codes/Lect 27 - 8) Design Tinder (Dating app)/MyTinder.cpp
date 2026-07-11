#include<bits/stdc++.h>
using namespace std;

// <<Modal Class>>
class Preferences{

    private:
    string WorkingProfessional;
    string EmotionalPerson;
    string PracticalPerson;
    string SpiritualPerson;

    public:
    Preferences(string WorkingProfessional, string EmotionalPerson, string PracticalPerson,
    string SpiritualPerson){

        this->WorkingProfessional = WorkingProfessional;
        this->EmotionalPerson = EmotionalPerson;
        this->PracticalPerson = PracticalPerson;
        this->SpiritualPerson = SpiritualPerson;
    }

    vector<pair<string,string>> getPreferences(){
        vector<pair<string,string>> profilePreferences;
        profilePreferences.push_back({"Would you prefer working professional?", WorkingProfessional});
        profilePreferences.push_back({"Would you prefer Emotional Person?", WorkingProfessional});
        profilePreferences.push_back({"Would you prefer Practical Person?", WorkingProfessional});
        profilePreferences.push_back({"Would you prefer Spiritual Person", WorkingProfessional});

        return profilePreferences;
    }
};

// <<Modal Class>>
class Profile{

    private:
    int id;
    string name;
    float location_x;
    float location_y;
    Preferences *preferences;

    public:

    Profile(int id, string name, float location_x, float location_y, Preferences *preferences){

        this->id = id;
        this->name = name;
        this->location_x = location_x;
        this->location_y = location_y;
        this->preferences = preferences;
    }

    string getName(){
        return this->name;
    }

    vector<pair<string,string>> getPreferences(){
        return this->preferences->getPreferences();
    }

    float getLocationX(){
        return this->location_x;
    }

    float getlocationY(){
        return this->location_y;
    }

    int getId(){
        return this->id;
    }

    void update(){
        cout<<"Congratulations "<<this->name<<" Match is found for you"<<endl;
    }
};


// <<Modal Class>>
class ChatRoom{

    private:
    Profile *firstProfile;
    Profile *secondProfile;

    public:
    ChatRoom(Profile *profile_1, Profile *profile_2){
        this->firstProfile = profile_1;
        this->secondProfile = profile_2;
    }

    pair<string,string>getProfiles(){
        return {firstProfile->getName(),secondProfile->getName()};
    }
};

class ChatRoomManager{
    private:
    vector<ChatRoom*> chatRoomList;
    static ChatRoomManager *instance;
    ChatRoomManager(){}

    public:
    static ChatRoomManager* getInstance(){

        if(!instance){
            instance = new ChatRoomManager();
        }
        return instance;
    }

    void createChatRoom(Profile *profile_1, Profile *profile_2){
        
        this->chatRoomList.push_back(new ChatRoom(profile_1, profile_2));
        cout<<endl<<"!Important! Chatroom for "<<profile_1->getName()<<" and "<<profile_2->getName()<<" is created"<<endl;
    }

    vector<ChatRoom*> getChatRoomList(){
        return this->chatRoomList;
    }
};

ChatRoomManager* ChatRoomManager::instance = nullptr;

//Comparision to get shortest distance.W
bool cmp(pair<int,Profile*> profile_1, pair<int,Profile*> profile_2){

    return profile_1.first < profile_2.first;
}

class ProfileManager{

    private:
    static ProfileManager *instance;
    vector<Profile*>profileList;
    vector< pair<float,Profile*> >nearestProfileList;
    ChatRoomManager *chatRoomManager;
    
    ProfileManager(){
        this->chatRoomManager = ChatRoomManager::getInstance();
    }
    
    public:
    static int index;
    static ProfileManager* getInstance(){

        if(!instance){
            instance = new ProfileManager();
        }
        return instance;
    }

    void setProfileList(vector<Profile*>profileList){
        this->profileList = profileList;
    }

    vector< pair<float,Profile*> >getAllNearestProfileList(Profile* client){
        //Here we have to show nearest profile as per distnace.

        for(Profile *profile: profileList){

            int client_id = client->getId();
            float client_x = client->getLocationX();
            float client_y = client->getlocationY();

            int profile_id = profile->getId();
            float profile_x = profile->getLocationX();
            float profile_y = profile->getlocationY();

            if(client_id == profile_id) continue;

            float distance = sqrt((profile_x - client_x) * (profile_y - client_y) + (profile_x - client_x) *
                (profile_y - client_y));

            nearestProfileList.push_back({distance, profile});
        }

        sort(nearestProfileList.begin(),nearestProfileList.end(),cmp);

        return nearestProfileList;
    }

    Profile* swipeLeft(Profile *client){

        if(index == 0){
            cout<<"Swap left on first profile is not possible, please swipe to right"<<endl<<endl;
            return nullptr;
        }

        index++;
        this->checkMatch(client, nearestProfileList[index].second);

        return nearestProfileList[index].second;
    }

    Profile* swipeRight(Profile *client){

        if(index == nearestProfileList.size()-1){
           index = -1;
        }

        index++;
        this->checkMatch(client, nearestProfileList[index].second);

        return nearestProfileList[index].second;
    }

    void checkMatch(Profile *client, Profile *profile){
        cout<<"Matching Profile name "<<client->getName()<<" with "<<profile->getName()<<endl;
        vector<pair<string,string>> clientPreferences = client->getPreferences();
        vector<pair<string,string>> profilePreferences = profile->getPreferences();

        int matchCount = 0;
        for(int i=0; i<clientPreferences.size(); i++){

            if(clientPreferences[i].second == profilePreferences[i].second){
                matchCount++;
            }
        }
        
        //IF matchcount is more than 50 percent of preference count. then consider it as match.
        if(matchCount > (clientPreferences.size()/2)){
            cout<<endl<<"The profile match is found for the client "<<client->getName()<<" with profile name "
            <<profile->getName()<<endl;

            //updating both clients for their matches.
            profile->update();
            client->update();

            //Creating chatroom
            this->chatRoomManager->createChatRoom(client,profile);
        }
        else{
            cout<<"Look for more, "<<profile->getName()<<" is not matching "<<endl<<endl;
        }


    }

    void printChatRoom(){
        vector<ChatRoom*>chatRoomList = this->chatRoomManager->getChatRoomList();

        for(ChatRoom * chatRoom:chatRoomList){
            cout<<"Chat room is created for user "<<chatRoom->getProfiles().first<<" and "<<chatRoom->getProfiles().second<<endl;
        }
    }
};

int ProfileManager::index = 0;

ProfileManager* ProfileManager::instance = nullptr;

class ApplicationManager{
    private:
    static ApplicationManager *instance;
    ProfileManager *profileManager;
    
    vector< pair<float,Profile*> >nearestProfileList;

    ApplicationManager(){
        this->profileManager = ProfileManager::getInstance();
    }

    public:
    static ApplicationManager* getInstance(){

        if(!instance){
            instance = new ApplicationManager();
        }
        return instance;
    }


    void setProfileList(vector<Profile*>profileList){
        this->profileManager->setProfileList(profileList);
    }

    void getAllNearestProfileList(Profile* client){
        //Here we have to show nearest profile as per distnace.
        this->nearestProfileList = profileManager->getAllNearestProfileList(client);
    }

    void swapLeft(Profile *client){
        profileManager->swipeLeft(client); 
    }

    void swapRight(Profile *client){
        profileManager->swipeRight(client);    
    }

    void printNearestProfileList(){

        cout<<setprecision(2);

        for(pair<float,Profile*> profile:nearestProfileList){
            cout<<"Profile name: "<<profile.second->getName()<<" with distance "<<profile.first<<" Km "<<endl;
        }cout<<endl<<endl;
    }
    
    void printChatRoom(){
        this->profileManager->printChatRoom();
    }
};

ApplicationManager* ApplicationManager::instance = nullptr;

int main(){

    //Creating Multiple Profiles
    vector<Profile*>profileList;

    Preferences *preferences1 = new Preferences("Yes","Yes","No","No");
    Profile *profile1 = new Profile(101, "Nishchay", 1.0, 2.0, preferences1);

    Preferences *preferences2 = new Preferences("No","Yes","No","No");
    Profile *profile2 = new Profile(102, "Rohan", 1.2, 2.5, preferences2);

    Preferences *preferences3 = new Preferences("No","Yes","No","No");
    Profile *profile3 = new Profile(103, "Kiran", 3.0, 4.0, preferences3);

    Preferences *preferences4 = new Preferences("Yes","Yes","No","Yes");
    Profile *profile4 = new Profile(104, "Viraj", 2.5, 2.8, preferences4);

    Preferences *preferences5 = new Preferences("No","Yes","Yes","No");
    Profile *profile5 = new Profile(105, "Jagtap", 1.0, 2.0, preferences5);

    Preferences *preferences6 = new Preferences("Yes","Yes","Yes","No");
    Profile *profile6 = new Profile(106, "Sandesh", 7.0, 7.8, preferences6);

    Preferences *preferences7 = new Preferences("No","Yes","No","Yes");
    Profile *profile7 = new Profile(107, "Preetam", 3.2, 5.0, preferences7);

    Preferences *preferences8 = new Preferences("Yes","No","No","No");
    Profile *profile8 = new Profile(108, "Astuk", 4.0, 6.0, preferences8);

    profileList.push_back(profile1);
    profileList.push_back(profile2);
    profileList.push_back(profile3);
    profileList.push_back(profile4);
    profileList.push_back(profile5);
    profileList.push_back(profile6);
    profileList.push_back(profile7);
    profileList.push_back(profile8);
    

    //Profile Manager
    ApplicationManager *applicationManager = ApplicationManager::getInstance();
    
    //Client Profile
    Preferences *clientPreferences = new Preferences("No","Yes","No","Yes");
    Profile *client = new Profile(109, "Vivek", 4.0, 6.0, clientPreferences);
    
    applicationManager->setProfileList(profileList);

    applicationManager->getAllNearestProfileList(client);
    applicationManager->printNearestProfileList();

    applicationManager->swapLeft(client);
    applicationManager->swapRight(client);
    applicationManager->swapRight(client);
    applicationManager->swapRight(client);
    applicationManager->swapRight(client);
    applicationManager->swapRight(client);

    applicationManager->printChatRoom();
}