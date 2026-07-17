#include<bits/stdc++.h>
using namespace std;

class Player{

    private:

    int playerId;
    string playerName;
    int position;

    public:

    Player(int id, string name){
        this->playerId = id;
        this->playerName = name;
        this->position = 0;
    }
    void updatePosition(int pos){
        this->position = pos;
    }

    int getPosition(){
        return this->position;
    }

    string getName(){
        return this->playerName;
    }
};

class Dice{
    private:
    int diceNumber;

    public:
    int rotateDice(){

        random_device rd;
        mt19937 gen(rd());  

        uniform_int_distribution<> randomDice(1,6);

        this->diceNumber = randomDice(gen);
        
        return this->diceNumber;
    }

};


class Observer{
    public:
    virtual void update(string message) = 0;
};

class ConsoleObserver:public Observer{

    public:
    void update(string message){
        cout<<message<<endl;
    }
};


class BoardSetup{
    public:
    int startPosition,endPosition;
    unordered_map<int,int>ladderPosMap;
    unordered_map<int,int>snakePosMap;

    BoardSetup(){
        this->startPosition = 0;
        this->endPosition = 100;
    }

    int getEndPosition(){
        return this->endPosition;
    }

    virtual void setLadderPosition(int startPos, int endPos) = 0;
    virtual void setSnakePosition(int startPos, int endPos) = 0;

    unordered_map<int,int> getLadderPosMap(){
        return this->ladderPosMap;
    }

    unordered_map<int,int> getSnakePosMap(){
        return this->snakePosMap;
    }

    friend class BoardRules;
};

class StandardSetup:public BoardSetup{

    public:
    StandardSetup(){
        this->setLadderPosition(5,58);
        this->setLadderPosition(14,49);
        this->setLadderPosition(42,60);
        this->setLadderPosition(53,72);
        this->setLadderPosition(64,83);
        this->setLadderPosition(75,94);


        this->setSnakePosition(38,20);
        this->setSnakePosition(45,7);
        this->setSnakePosition(51,10);
        this->setSnakePosition(65,54);
        this->setSnakePosition(91,73);
        this->setSnakePosition(97,61);


        for(auto ladder:ladderPosMap){
            cout<<"ladder starting point "<<ladder.first<<" and ladder ending point "<<ladder.second<<endl;
        }

        for(auto snake:snakePosMap){
            cout<<"snake starting point "<<snake.first<<" and snake ending point "<<snake.second<<endl;
        }
        cout<<endl<<endl;
    }

    void setLadderPosition(int startPos, int endPos){
        this->ladderPosMap[startPos] = endPos;
    }

    void setSnakePosition(int startPos, int endPos){
        this->snakePosMap[startPos] = endPos;
    }
};

class RandomSetup:public BoardSetup{
    public:
    RandomSetup(){
        this->generateRandomValues();
    }

    void generateRandomValues(){
        
        random_device rd;
        mt19937 gen(rd());  

        while(this->ladderPosMap.size() != 6){

            uniform_int_distribution<> startDest(2,90);
            int startPos = startDest(gen);

            uniform_int_distribution<> endDest(startPos+1,98);
            int endPos = endDest(gen);
                

            if(this->ladderPosMap.find(startPos) == this->ladderPosMap.end())
            //if generated position is unique then insert this new position in map.
                this->ladderPosMap.insert({startPos,endPos});

        }

        while(this->snakePosMap.size() != 6){

            uniform_int_distribution<> startDest(2,99);
            int startPos = startDest(gen);

            uniform_int_distribution<> endDest(1,startPos-1);
            int endPos = endDest(gen);

            if(this->snakePosMap.find(startPos) == this->snakePosMap.end() && this->ladderPosMap.find(startPos) == this->ladderPosMap.end() )
            //if generated position is unique then insert this new position in map.
                this->snakePosMap.insert({startPos,endPos});
        }
    }

    void setLadderPosition(int startPos, int endPos){
        this->ladderPosMap[startPos] = endPos;
    }

    void setSnakePosition(int startPos, int endPos){
        this->snakePosMap[startPos] = endPos;
    }
};


class BoardRules{

    protected:
    BoardSetup *board;

    public:
    BoardRules(BoardSetup *board){
        this->board = board;
    }

    virtual bool isSnakeCapture(Player *player, int position)=0;

    virtual bool isLadderAvailable(Player *player, int position)= 0;

    virtual bool checkWinCondition(Player *player, int position)=0;

};

class StandardRules:public BoardRules{
    public:
    StandardRules(BoardSetup *board):BoardRules(board){}

     bool isSnakeCapture(Player *player, int position){

        if(this->board->snakePosMap.find(position) != this->board->snakePosMap.end()){ //if condition is true that means piece captured by snake
            int snakeEndPos = this->board->snakePosMap[position]; //store second value which is ending position of snake.

            player->updatePosition(snakeEndPos);
            return true; 
        }
        return false;
    }

    bool isLadderAvailable(Player *player, int position){

        if(this->board->ladderPosMap.find(position) != this->board->ladderPosMap.end()){ //now check on postion is there any ladder.
            //if yes, then we have ladder from this position.

            int ladderEndPos = this->board->ladderPosMap[position]; //getting ladder ending position.

            player->updatePosition(ladderEndPos); //so update player value with ending of ladder position.
            return true; 
        }
       
        return false; //if ladder is not present then return false.
    }

    bool checkWinCondition(Player *player, int position){
        if(position == this->board->getEndPosition()){
            
            player->updatePosition(position);
            return true;
        }

        return false;
    }
};

enum BoardType{
    StandardSetupType,
    RandomSetupType
};

enum BoardRule{
    StandardRuleType
};
class SnakeLadderGame{

    private:
    Dice *dice;
    BoardRules *boardRules;
    BoardSetup *board;
    Observer *observer;
    Player *currentPlayer;
    queue<Player*>playerList;

    public:
    SnakeLadderGame(){
        this->dice = new Dice();
        this->observer = new ConsoleObserver();
    }

    void createBoard(BoardType type){
        
        if(type == BoardType::RandomSetupType){
            this->board = new RandomSetup();

        }
        else {
            this->board = new StandardSetup();
        }

        //creation of board rules. normally we could create multiple hirarchy of different type of rules.
    }

    void createBoardRules(BoardRule type){

        if(type == BoardRule::StandardRuleType){
            this->boardRules = new StandardRules(this->board);
        }
    }

    void addPlayer(Player *player){

        if(this->playerList.size() < 2)
            this->playerList.push(player);
        
        else  
            cout<<"Couldn't add more player as lobby is full "<<endl;
        

    }

    int rotateDice(){
       return this->dice->rotateDice();
    }

    bool checkWinCondition(int position){
        return this->boardRules->checkWinCondition(this->currentPlayer, position);
    }

    bool isLadderAvailable(int position){
        return this->boardRules->isLadderAvailable(this->currentPlayer, position);
    }

    bool isSnakeCapture(int position){
        return this->boardRules->isSnakeCapture(this->currentPlayer, position);
    }

    void notifyAll(string message){
        this->observer->update(message);
    }

    string getWinMessage(int oldPosition){
        return "Player: "+currentPlayer->getName()+" moved from position "+ to_string(oldPosition)+" to position "+ to_string(currentPlayer->getPosition())+" win. Congratulations...!";
    }

    string getLadderMessage(int currPosition, int oldPosition){
       return "Player: "+currentPlayer->getName()+" moved from position "+ to_string(oldPosition) + " to position "+ to_string(currPosition)+ 
                    " and climbed the ladder to position "+ to_string(currentPlayer->getPosition());
    }

    string getSnakeMessage(int currPosition, int oldPosition){
       return "Player: "+ currentPlayer->getName() + " moved from position "+ to_string(oldPosition)+" to position "+ to_string(currPosition)+
                    ", landed on a snake, and slid down to position "+ to_string(currentPlayer->getPosition());
    }

    string nextMoveMessage(int currPosition){
        return "Player: "+currentPlayer->getName()+" is move to  "+ to_string(currPosition) + " from "+ to_string(currentPlayer->getPosition());
    }

    void play(){

        if(this->playerList.size() >= 2){
            bool gameover = false;

            while(!gameover){ 

                int diceNumber;
                
                this->currentPlayer = this->playerList.front();
                
                diceNumber = this->rotateDice();

                if(diceNumber != 6){
                    this->playerList.pop();

                    this->playerList.push(this->currentPlayer);
                }
                else
                    cout<<"Congratulations! you got 6, so you will get one more chance"<<endl;

                
                int oldPosition = currentPlayer->getPosition();
                int currPosition = oldPosition + diceNumber;

                if(currPosition > 100){
                    cout<<"Player: "+ currentPlayer->getName()+ " Try again, look for smaller value "<<endl;
                    continue;
                }

                string msg;

                if(this->checkWinCondition(currPosition)){
                    msg = this->getWinMessage(oldPosition);
                    gameover = true;
                }
               
                
                else if(this->isLadderAvailable(currPosition))
                    msg = this->getLadderMessage(currPosition, oldPosition);
                
                else if(this->isSnakeCapture(currPosition)){
                    msg = this->getSnakeMessage(currPosition, oldPosition);

                    //if piece captured by snake, then on snake ending position, There could be chance of ladder. so checking that scneario.
                    if(this->isLadderAvailable(currPosition))
                       msg = this->getLadderMessage(currPosition, oldPosition);
                }
                    
                
                else{
                     //when player just move.
                    msg = this->nextMoveMessage(currPosition);
                    currentPlayer->updatePosition(currPosition);
                }  

                this->notifyAll(msg);              
            }
        }
        else{
            this->notifyAll("Add player, At least 2 player should be pariticpate.");
        }
    }
};

int main(){

    SnakeLadderGame * game = new SnakeLadderGame();
    game->createBoard(BoardType::RandomSetupType);
    game->createBoardRules(BoardRule::StandardRuleType);

    Player *nishchay = new Player(1,"Nishchay");
    Player *rohan = new Player(2,"Rohan");

    game->addPlayer(nishchay);
    game->addPlayer(rohan);

    game->play();
}