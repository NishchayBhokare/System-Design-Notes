#include<bits/stdc++.h>
using namespace std;


class Observer{

    public:
    virtual void update(string message) = 0;
};

class User: public Observer{

    private:
    int id;
    string name;

    public:
    User(int id, string name){
        this->id = id;
        this->name = name;
    }
    string getName(){
        return this->name;
    }

    void update(string message){
        cout<<message<<endl;
    }
};


class Board{

    public:
    int row;
    int col;
    vector<vector<char> >matrix;

    public:
    Board(int row, int col){

        this->row=row;
        this->col=col;
        matrix.resize(this->row, vector<char>(this->col));

        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                matrix[i][j]='A';
            }
        }
    }

    vector<vector<char> >& getMatrix(){
        return this->matrix;
    }
};

class BoardMatcher{
    protected:
    int row, col;
    char character;
    vector<vector<char>>matrix;
    public:
    BoardMatcher(int row, int col, vector<vector<char>>&matrix, char character){
        this->row = row;
        this->col = col;
        this->matrix = matrix;
        this->character = character;
    }
    virtual bool matcher() = 0;
};

class HorizontalMatcher: public BoardMatcher{
    public:
    HorizontalMatcher(int row, int col, vector<vector<char>>&matrix, char character):BoardMatcher(row,col,matrix,character){}

    bool matcher(){         
        for(int col=0; col<matrix[0].size(); col++){

            if(matrix[this->row][col] != character){
                return false;
            }
        }

        cout<<"Horizontal Match"<<endl;
        return true;
    } 
};

class VerticalMatcher: public BoardMatcher{
    public:
    VerticalMatcher(int row, int col, vector<vector<char>>&matrix, char character):BoardMatcher(row,col,matrix,character){}

    bool matcher(){         
        for(int row=0; row<matrix.size(); row++){

            if(matrix[row][this->col] != character){
                return false;
            }
        }

        cout<<"Vertical Match"<<endl;
        return true;
    } 
};

class DiagonalMatcher: public BoardMatcher{
    public:
    DiagonalMatcher(int row, int col, vector<vector<char>>&matrix, char character):BoardMatcher(row,col,matrix,character){}

    bool matcher(){     
        //Top left to bottom right matcher    
        bool isMatch = true;
        for(int row=0,col=0; row<matrix.size(); row++,col++){

            if(matrix[row][col] != character){
                isMatch = false;
                break;
            }
        }

        if(isMatch) {
            cout<<"Diagonal Match"<<endl;
            return true;
        }


        //Top right to bottom left matcher
        isMatch = true;
        for(int row=0,col=matrix[0].size()-1; row<matrix.size(); row++,col--){

            if(matrix[row][col] != character){
                isMatch = false;
                break;
            }
        }

        if(isMatch) {
            cout<<"Diagonal Match"<<endl;
            return true;
        }
        return false;
    } 
};

class Observable{
    protected:
    vector<User*>userList;

    public:
    virtual void addUser(User *user) = 0;
    virtual void notifyOne(int userIndex, string message) = 0;
    virtual void notifyAll(string message)=0;
    virtual vector<User*>& getList() =0;
};

class boardObservable:public Observable{
    public:
    void addUser(User *user){
        if(userList.size() < 2)
            userList.push_back(user);
        else   
            cout<<"Couldn't add more than two user"<<endl;
    }

    void notifyOne(int userIndex, string message){
        cout<<userList[userIndex]->getName()<<" --> ";
        this->userList[userIndex]->update(message);
    }

    void notifyAll(string message){
        for(User *user:userList){
            user->update(message);
        }
    }

    vector<User*>& getList(){
        return this->userList;
    }
};


class BoardChecker{
    public:
    bool isMatrixAllPosFilled(vector<vector<char>>&matrix){
        for(int i=0; i<matrix.size(); i++){
            for(int j=0; j<matrix[0].size(); j++){

                if(matrix[i][j] == 'A'){
                    return false;
                }
            }
        }

        return true;
    }

    void checkMatch(int row, int col, int userIndex, char character,vector<vector<char>>&matrix, Observable *observable){
        BoardMatcher *matcher1 = new HorizontalMatcher(row,col,matrix,character);
        BoardMatcher *matcher2 = new VerticalMatcher(row,col,matrix,character);
        BoardMatcher *matcher3 = new DiagonalMatcher(row,col,matrix,character);

        vector<User*>userList = observable->getList();

        if(matcher1->matcher() || matcher2->matcher() || matcher3->matcher()){
            observable->notifyOne(userIndex,"You have won!");

            string message = "Winner is "+userList[userIndex]->getName()+". Congratulations dear.";
            observable->notifyAll(message);
        }

        for(int i=0; i<matrix.size(); i++){
            for(int j=0; j<matrix[0].size(); j++){
                cout<<matrix[i][j]<<" ";
            }cout<<endl;
        }
        cout<<endl;
    }
};

class BoardManager{

    private:
    Board *board;
    Observable *observable;
    BoardChecker *boardChecker;
    vector<vector<char>>matrix;

    public:
    BoardManager(){
        this->observable = new boardObservable();
        this->boardChecker = new BoardChecker();
    }
    //Manager work.
    void createBoard(int row, int col){
        this->board = new Board(row, col);

        this->matrix = this->board->getMatrix();
    }
   
    void addCross(int row, int col, int userIndex){

        if(matrix[row][col] == 'A'){
            matrix[row][col] = 'X';
            
            this->notifyOne(userIndex,"Cross added successfully");
        }
        else{
            this->notifyOne(userIndex,"Position is already filled, please try other positions");
            return;
        }

        cout<<"Checking for match..."<<endl;
        this->checkMatch(row,col,userIndex,'X');

        if(this->isMatrixAllPosFilled()){
            this->notifyAll("Match is draw");
        }
    }
    
    void addCircle(int row, int col, int userIndex){

        if(matrix[row][col] == 'A'){
            matrix[row][col] = 'O';

            this->notifyOne(userIndex,"Circle added successfully");
        }
        else{
             this->notifyOne(userIndex,"Position is already filled, please try other positions");
            return;
        }

        cout<<"Checking for match..."<<endl;
        this->checkMatch(row,col,userIndex,'O');

        if(this->isMatrixAllPosFilled()){
            this->notifyAll("Match is draw");
        }
    }


    //Delegated tasks.
    void addUser(User *user){
       this->observable->addUser(user);
    }
    
    void notifyAll(string message){
        this->observable->notifyAll(message); 
    }

    void notifyOne(int userIndex, string message){
       this->observable->notifyOne(userIndex,message);
    }

    
    bool isMatrixAllPosFilled(){
        return this->boardChecker->isMatrixAllPosFilled(this->matrix);
    }

    void checkMatch(int row, int col, int userIndex, char character){
        this->boardChecker->checkMatch(row,col,userIndex,character,this->matrix,observable);
    }

};


int main(){

    User *rohan = new User(1,"Rohan");
    User *nishchay = new User(2,"Nishchay");


    //Adding user
    BoardManager *manager = new BoardManager();
    manager->addUser(rohan);
    manager->addUser(nishchay);


    //Creating board.
    manager->createBoard(3,3);


    //now add actions X and O
    manager->addCircle(0,0,0); //row=0,col=0,userIndex=0 i.e Nishchay.

    manager->addCross(2,0,1); //row=2,col=0,userIndex=0 i.e Rohan.

    manager->addCircle(1,1,0); 

    manager->addCross(2,1,1); 

    manager->addCircle(2,2,0); 

}