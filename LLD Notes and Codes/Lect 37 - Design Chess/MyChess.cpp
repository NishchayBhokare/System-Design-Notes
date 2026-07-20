#include<bits/stdc++.h>
using namespace std;

class User{

    private:
    int id;
    string name;
    int rating;

    public:
    User(int id, string name, int rating){
        this->id = id;
        this->name = name;
        this->rating = rating;
    }
    int getId(){
        return this->id;
    } 

    string getName(){
        return this->name;
    }
    int getRating(){
        return this->rating;
    }
};

class Observer{
    public:
    virtual void update(string &msg) = 0;
};

class ChessboardConsoleObserver:public Observer{
    
    public:
    void update(string &msg){
        cout<<msg<<endl;
    }
};

enum class PieceType{
    _____,
    Pawn,
    Rook,
    Bishop, 
    Knight,
    Queen,
    King
};

enum class PieceColor{
    Null,
    White,
    Black
};

class Cell{
    public:
    PieceType pieceType;
    PieceColor pieceColor;

    Cell(){
        this->pieceColor = PieceColor::Null;
        this->pieceType = PieceType::_____;
    }

    bool isCellEmpty(){

        if(this->pieceType == PieceType::_____)
            return true;
        
        return false;
    }

    PieceType getPiece(){
        return pieceType;
    }

    PieceColor getColor(){
        return pieceColor;
    }
};

class BoardRules;

class PieceEnumToString{
    public:
    static string pieceTypeToString(PieceType pieceType) {
        switch (pieceType) {
            case PieceType::_____:
                return "____";
                
            case PieceType::Pawn:
                return "Paw";

            case PieceType::Rook:
                return "Roo";

            case PieceType::Bishop:
                return "Bis";

            case PieceType::Knight:
                return "Kni";

            case PieceType::Queen:
                return "Que";

            case PieceType::King:
                return "Kin";

            default:
                return "hey";
        }
    }

    static string pieceColorToString(PieceColor pieceColor){
        switch (pieceColor) {
            case PieceColor::White:
                return "W";
                
            case PieceColor::Black:
                return "B";
            
            default:
                return "";
        }
    }
};

class ChessBoard{

    private:
    vector<vector<Cell> >boardMatrix;
    
    public:

    ChessBoard() {
        this->boardMatrix = vector<vector<Cell>>(8,vector<Cell>(8));
    }


    void movePiece(string startPos, string endPos){

        
        //String to index mapping.
        int row = 7 - (startPos[1] - '1');
        int col = startPos[0] - 'a';

        int newR = 7 - (endPos[1] - '1');
        int newC = endPos[0] - 'a';
         

        PieceType ptype = this->boardMatrix[row][col].pieceType; //storing current piece.
        PieceColor pcolor = this->boardMatrix[row][col].pieceColor;

        this->boardMatrix[row][col].pieceType = PieceType::_____; //current Position marking as empty.
        this->boardMatrix[row][col].pieceColor = PieceColor::Null;
      
        this->boardMatrix[newR][newC].pieceType = ptype; //moved current piece to new position.
        this->boardMatrix[newR][newC].pieceColor = pcolor;
    }

    void createBoard(){

        //now set black positions of all pieces.
        this->boardMatrix[0][0].pieceType = PieceType::Rook;
        this->boardMatrix[0][1].pieceType = PieceType::Knight;
        this->boardMatrix[0][2].pieceType = PieceType::Bishop;
        this->boardMatrix[0][3].pieceType = PieceType::Queen;
        this->boardMatrix[0][4].pieceType = PieceType::King;
        this->boardMatrix[0][5].pieceType = PieceType::Bishop;
        this->boardMatrix[0][6].pieceType = PieceType::Knight;
        this->boardMatrix[0][7].pieceType = PieceType::Rook;

        //mark all  pieces in first row to black.
        for(int j=0; j<boardMatrix[0].size(); j++){
            this->boardMatrix[0][j].pieceColor = PieceColor::Black;
        }

        //Assigning black pawns.
        for(int j=0; j<boardMatrix[0].size(); j++){
            this->boardMatrix[1][j].pieceType = PieceType::Pawn;
            this->boardMatrix[1][j].pieceColor = PieceColor::Black;
        }

        //same for black pawns.
        for(int j=0; j<boardMatrix[0].size(); j++){
            this->boardMatrix[6][j].pieceType = PieceType::Pawn;
            this->boardMatrix[6][j].pieceColor = PieceColor::White;
        }

        //marking all pieces in last row to white.
        for(int j=0; j<boardMatrix[0].size(); j++){
            this->boardMatrix[7][j].pieceColor = PieceColor::White;
        }

        //now set all white positions.
        this->boardMatrix[7][0].pieceType = PieceType::Rook;
        this->boardMatrix[7][1].pieceType = PieceType::Knight;
        this->boardMatrix[7][2].pieceType = PieceType::Bishop;
        this->boardMatrix[7][3].pieceType = PieceType::Queen;
        this->boardMatrix[7][4].pieceType = PieceType::King;
        this->boardMatrix[7][5].pieceType = PieceType::Bishop;
        this->boardMatrix[7][6].pieceType = PieceType::Knight;
        this->boardMatrix[7][7].pieceType = PieceType::Rook;

    }

    vector<vector<Cell> >& getBoardMatrix(){
        return this->boardMatrix;
    }
};


class BoardRules{
    public:
        int currRow, currCol, newRow, newCol;

        bool isValidMoveOfPiece(vector<vector<Cell>>&boardMatrix){

            PieceType currPieceType = boardMatrix[this->currRow][this->currCol].pieceType;
            PieceColor currPieceColor = boardMatrix[this->currRow][this->currCol].pieceColor;

            if(currPieceType == PieceType::Pawn && currPieceColor == PieceColor::White){
                
                //if piece trying to move one place in straight direction and we have empty cell so its valid move
                if((this->currCol == this->newCol) && (this->currRow - this->newRow == 1) && boardMatrix[this->newRow][this->newCol].isCellEmpty() == true){
                    cout<<"Piece pawn is moved"<<endl;
                    return true;
                }
                
                //moving to left of its diagonal and there is one piece to capture
                else if((this->currRow - this->newRow == 1) && (this->currCol - this->newCol == 1) && boardMatrix[this->newRow][this->newCol].isCellEmpty() == false){
                    cout<<"left pice captured by Pawn"<<endl;
                    return true;
                }

                //right side.
                else if((this->currRow - this->newRow == 1) && (this->newCol - this->currCol == 1) && boardMatrix[this->newRow][this->newCol].isCellEmpty() == false){
                    cout<<"right pice captured by Pawn"<<endl;
                    return true;
                }
                
                cout<<"Pawn move is wrong"<<endl;
                //apart from all these valid move, if user move piece then its invalid.
                return false;
            }

            else if(currPieceType == PieceType::Pawn && currPieceColor == PieceColor::Black){

                //if piece trying to move one place in straight direction and we have empty cell so its valid move
                if((this->currCol == this->newCol) && (this->newRow - this->currRow == 1) && boardMatrix[this->newRow][this->newCol].isCellEmpty() == true)
                    return true;
                
                //moving to left of its diagonal and there is one piece to capture
                else if((this->newRow - this->currRow == 1) && (this->newCol - this->currCol == 1) && boardMatrix[this->newRow][this->newCol].isCellEmpty() == false){
                    cout<<"Pice captured by Pawn"<<endl;
                    return true;
                }

                else if((this->newRow - this->currRow == 1) && (this->currCol - this->newCol == 1) && boardMatrix[this->newRow][this->newCol].isCellEmpty() == false){
                    cout<<"Pice captured by Pawn"<<endl;
                    return true;
                }
                
                //apart from all these valid move, if user move piece then its invalid.
                return false;
            }

            else if(currPieceType == PieceType::Knight){

                //8 valid conditions are there
                if(
                    ((this->newRow == this->currRow-2) && (this->newCol == this->currCol-1)) || //1) newR=row-2, newC=C-1.
                    ((this->newRow == this->currRow-2) && (this->newCol == this->currCol+1)) || //2) newR=row-2, newC=C+1.
                    ((this->newRow == this->currRow+2) && (this->newCol == this->currCol-1)) || //3) newR=row+2, newC=C-1.
                    ((this->newRow == this->currRow+2) && (this->newCol == this->currCol+1)) || //4) newR=row+2, newC=C+1.
                    ((this->newRow == this->currRow-1) && (this->newCol == this->currCol-2)) || //5) newR=row-1, newC=C-2.
                    ((this->newRow == this->currRow+1) && (this->newCol == this->currCol-2)) || //6) newR=row+1, newC=C-2.
                    ((this->newRow == this->currRow-1) && (this->newCol == this->currCol+2)) || //7) newR=row-1, newC=C+2.
                    ((this->newRow == this->currRow+1) && (this->newCol == this->currCol+2))    //8) newR=row+1, newC=C+2.
                ){

                    //If destination has piece. then we're capturing it
                    if(boardMatrix[newRow][newCol].isCellEmpty() == false){
                        cout<<"Piece is captured by Knight."<<endl;
                    }   
      
                    return true;
                }

                return false;
            }

            else if(currPieceType == PieceType::Bishop){

                //Total 4 ways to move.
                //1) top left Diagonal. row > newR and col > newC. r--,c--
                if((this->currRow > this->newRow) && (this->currCol > this->newCol)){
                    int i=currRow-1, j=currCol-1;
                    for(; i!=newRow; i--,j--){
                        
                        //if in the path any piece is there..then we cant direct move to destination.
                        if(boardMatrix[i][j].isCellEmpty() == false){
                            cout<<"some pieces are found in between."<<endl;
                            return false;
                        }
                    }
                    
                }

                //2) bottom left Diagonal. row < newR and col > newC. r++,c--
                if((this->currRow < this->newRow) && (this->currCol > this->newCol)){
                int i=currRow+1, j=currCol-1;
                    for(; i!=newRow; i++,j--){
                        
                        if(boardMatrix[i][j].isCellEmpty() == false)
                            return false;
                    }
                }


                //3) top right Diagonal. row > newR nad col < newC. r--, c++
                if((this->currRow > this->newRow) && (this->currCol < this->newCol)){
                int i=currRow-1, j=currCol+1;
                    for(; i!=newRow; i--,j++){
                        
                        if(boardMatrix[i][j].isCellEmpty() == false)
                            return false;
                    }
                }


                //4) bottom right Diagonal. row < newR nad col < newC. r++, c++
                if((this->currRow < this->newRow) && (this->currCol < this->newCol)){
                int i=currRow+1, j=currCol+1;

                    for(; i!=newRow; i++,j++){
                        
                        if(boardMatrix[i][j].isCellEmpty() == false)
                            return false;
                    }
                }


                //if path is clear but destination has piece. then we're capturing it
                    if(boardMatrix[newRow][newCol].isCellEmpty() == false){
                        cout<<"Piece is captured by bishoop."<<endl;
                    }   
                    
                return true;
            }
        
            else if(currPieceType == PieceType::Rook){
                //Total 4 ways to move.
                //1) vertical up. 
                if((this->currRow > this->newRow) && (this->currCol == this->newCol)){

                    for(int i=currRow; i!=newRow; i--){
                        
                        if(boardMatrix[i][currCol].isCellEmpty() == false)
                            return false;
                    }
                }

                //2) vertical down. 
                if((this->currRow < this->newRow) && (this->currCol == this->newCol)){

                    for(int i=currRow; i!=newRow; i++){
                        
                        if(boardMatrix[i][currCol].isCellEmpty() == false)
                            return false;
                    }
                }


                //3) horizontal left
                if((this->currRow > this->newRow) && (this->newRow == this->newRow)){

                    for(int j=currRow; j!=newCol; j--){
                        
                        if(boardMatrix[currRow][j].isCellEmpty() == false)
                            return false;
                    }
                }


                //4) horizontal right
                if((this->currRow > this->newRow) && (this->newRow == this->newRow)){

                    for(int j=currRow; j!=newCol; j++){
                        
                        if(boardMatrix[currRow][j].isCellEmpty() == false)
                            return false;
                    }
                }
                
                //if path is clear but destination has piece. then we're capturing it
                    if(boardMatrix[newRow][newCol].isCellEmpty() == false){
                        cout<<"Piece is captured by bishoop."<<endl;
                    }   
                    
                return true;

            }
        
            else if(currPieceType == PieceType::Queen){
                    //Total 8 ways to move.

                //1) top left Diagonal. row > newR and col > newC. r--,c--
                if((this->currRow > this->newRow) && (this->currCol > this->newCol)){
                    int i=currRow-1, j=currCol-1;
                   
                    for(; i!=newRow; i--,j--){
                        
                        //if in the path any piece is there..then we cant direct move to destination.
                        if(boardMatrix[i][j].isCellEmpty() == false)
                            return false;
                    }
                    
                }

                //2) bottom left Diagonal. row < newR and col > newC. r++,c--
                if((this->currRow < this->newRow) && (this->currCol > this->newCol)){
                    int i=currRow+1, j=currCol-1;
                   
                    for(; i!=newRow; i++,j--){
                        
                        if(boardMatrix[i][j].isCellEmpty() == false)
                            return false;
                    }
                }


                //3) top right Diagonal. row > newR nad col < newC. r--, c++
                if((this->currRow > this->newRow) && (this->currCol < this->newCol)){
                    int i=currRow-1, j=currCol+1;
                    for(; i!=newRow; i--,j++){
                        
                        if(boardMatrix[i][j].isCellEmpty() == false)
                            return false;
                    }
                }


                //4) bottom right Diagonal. row < newR nad col < newC. r++, c++
                if((this->currRow < this->newRow) && (this->currCol < this->newCol)){
                    int i=currRow+1, j=currCol+1;

                    for(; i!=newRow; i++,j++){
                        
                        if(boardMatrix[i][j].isCellEmpty() == false)
                            return false;
                    }
                }

                //forward and backward.

                  //1) vertical up. 
                if((this->currRow > this->newRow) && (this->currCol == this->newCol)){
                    int i=currRow-1;
                   
                    for(; i!=newRow; i--){
                        
                        if(boardMatrix[i][currCol].isCellEmpty() == false)
                            return false;
                    }
                }

                //2) vertical down. 
                if((this->currRow < this->newRow) && (this->currCol == this->newCol)){

                    for(int i=currRow+1; i!=newRow; i++){
                        
                        if(boardMatrix[i][currCol].isCellEmpty() == false)
                            return false;
                    }
                }


                //3) horizontal left
                if((this->currRow > this->newRow) && (this->currRow == this->newRow)){

                    for(int j=currRow; j!=newCol; j--){
                        
                        if(boardMatrix[currRow][j].isCellEmpty() == false)
                            return false;
                    }
                }


                //4) horizontal right
                if((this->currRow > this->newRow) && (this->currRow == this->newRow)){

                    for(int j=currRow+1; j!=newCol; j++){
                        
                        if(boardMatrix[currRow][j].isCellEmpty() == false)
                            return false;
                    }
                }

                  //if path is clear but destination has piece. then we're capturing it
                    if(boardMatrix[newRow][newCol].isCellEmpty() == false){
                        cout<<"Piece is captured by bishoop."<<endl;
                    }   
                    
                return true;
            }
        
            else if(currPieceType == PieceType::King){
                
                //8 Moves possible similar to queen, but only one step at a time.
                //Simple writing one condition.
                if((abs(this->newRow - this->currRow) <= 1) || (abs(this->newCol - this->currCol) <= 1))
                    return true;
            }
            return false;
        }

        bool validateMove(string startPos, string endPos, vector<vector<Cell>>&boardMatrix){
            
            //String to index mapping.
            this->currRow = 7 - (startPos[1] - '1');
            this->currCol = startPos[0] - 'a';

            this->newRow = 7 - (endPos[1] - '1');
            this->newCol = endPos[0] - 'a';

            // cout<<PieceEnumToString::pieceTypeToString(boardMatrix[currRow][currCol].pieceType)<<endl;

            //1)Invalid Move: If move is out of the board.
            if(this->newRow > 7 || this->newRow < 0 || newCol > 7 || newCol < 0){

                cout<<"Move is out of board";
                return false;
            }

            //2)Invalid Move: If trying to capture same color piece.
            if(boardMatrix[this->currRow][this->currCol].pieceColor == boardMatrix[this->newRow][this->newCol].pieceColor){
                
                cout<<"Can't capture same color piece"<<endl;
                return false;
            }

            //3)Invalid Move: If Incorrect move of piece.
            if(this->isValidMoveOfPiece(boardMatrix)){ 
                cout<<"Piece Moved"<<endl;
                return true;
            }


            

            //4)Invalid Move: If King is in check and moving another piece.

            //5)Invalid Move: If Moving the piece is getting its king is in check. 


            
            
            
            

            return false;
        }
};

class ChessGame{
    public:
    ChessBoard *chessBoard;
    BoardRules *boardRules;
    vector<vector<Cell> >& boardMatrix;

    ChessGame():chessBoard(new ChessBoard()), boardMatrix(chessBoard->getBoardMatrix()){

        this->boardRules = new BoardRules();
        this->chessBoard->createBoard();
    }

    void print(){
        for(int i=0; i<boardMatrix.size(); i++){
            for(int j=0; j<boardMatrix[0].size(); j++){
                cout<<PieceEnumToString::pieceTypeToString(boardMatrix[i][j].pieceType)
                    <<PieceEnumToString::pieceColorToString(boardMatrix[i][j].pieceColor)<<"  ";
                    
            }cout<<endl;
        }cout<<endl<<endl;
    }

    void MovePice(string startPos, string endPos){

        if(this->boardRules->validateMove(startPos, endPos, boardMatrix)){
            cout<<"Moving Piece"<<endl;
            chessBoard->movePiece(startPos, endPos);
        }
    }
};

class ScoreMatchAlgo{
    public:
    ScoreMatchAlgo(){}

    User* getMatchingUser(User *newUser, vector<User*>&userlist){

        for(User* user:userlist){

            if(user->getId() != newUser->getId() && abs(user->getRating() - newUser->getRating()) < 500){
                return user;
            }
        }

        //If we not found any other user near to newuser rating then return first user in list
        //but make sure, both user should not be same.
        if(userlist.front()->getId() != newUser->getId()){
            return userlist.front();
        }
        
        //if both user are the same then return second user and if second user is not there then retur
        //null as only single user is there in list.
        return userlist[1]? userlist[1]: nullptr; 
    }
};

class UserFactory{
    private:
    static int id;
    static UserFactory* instance;
    User *user;

    
    public:
    UserFactory(){}
    static User* createUser(string name){
        int rating = 800;
        User *user = new User(id++, name, rating);

        return user;
    }
};

int UserFactory::id = 1;

int main(){
    ChessGame *game = new ChessGame();

    UserFactory *factory = new UserFactory();
    User *nishchay = factory->createUser("Nishchay");
    User *yash = factory->createUser("Yash");

    queue<User*>userQueue;
    userQueue.push(nishchay);
    userQueue.push(yash);

    int tempCnt=50;
        game->print();

    while(true){
        User *front = userQueue.front();
        userQueue.pop();

        cout<<"Enter your move "<<front->getName()<<endl;
        string startPos, endPos;
        cin>>startPos>>endPos;

        game->MovePice(startPos, endPos);
        game->print();

        userQueue.push(front);
    }

    return 0;
}











