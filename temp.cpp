

      //first create 1 pawn white  and then use its copy, which is prototyp pattern
        // Pawn *pawnWhite1 = new Pawn(PieceType::PawnW);

        // //now create rest pawns.
        // Pawn *pawnWhite2 = dynamic_cast<Pawn*>(pawnWhite1->clone());
        // Pawn *pawnWhite3 = dynamic_cast<Pawn*>(pawnWhite1->clone());
        // Pawn *pawnWhite4 = dynamic_cast<Pawn*>(pawnWhite1->clone());
        // Pawn *pawnWhite5 = dynamic_cast<Pawn*>(pawnWhite1->clone());
        // Pawn *pawnWhite6 = dynamic_cast<Pawn*>(pawnWhite1->clone());
        // Pawn *pawnWhite7 = dynamic_cast<Pawn*>(pawnWhite1->clone());
        // Pawn *pawnWhite8 = dynamic_cast<Pawn*>(pawnWhite1->clone());

        // //Similarly create for black
        // Pawn *pawnBlack1 = new Pawn(PieceType::PawnB);

        // //rest black pawns
        // Pawn *pawnBlack2 = dynamic_cast<Pawn*>(pawnBlack1->clone());
        // Pawn *pawnBlack3 = dynamic_cast<Pawn*>(pawnBlack1->clone());
        // Pawn *pawnBlack4 = dynamic_cast<Pawn*>(pawnBlack1->clone());
        // Pawn *pawnBlack5 = dynamic_cast<Pawn*>(pawnBlack1->clone());
        // Pawn *pawnBlack6 = dynamic_cast<Pawn*>(pawnBlack1->clone());
        // Pawn *pawnBlack7 = dynamic_cast<Pawn*>(pawnBlack1->clone());
        // Pawn *pawnBlack8 = dynamic_cast<Pawn*>(pawnBlack1->clone());
        
        // //now create 4 instances, 2 White rook and 2 Black rook.
        // Rook *rookWhite1 = new Rook(PieceType::RookW);
        // Rook *rookWhite2 = new Rook(PieceType::RookW);

        // Rook *rookBlack1 = new Rook(PieceType::RookB);
        // Rook *rookBlack2 = new Rook(PieceType::RookB);

        // //Bishop
        // Bishop *bishopWhite1 = new Bishop(PieceType::BishW);
        // Bishop *bishopWhite2 = new Bishop(PieceType::BishW);

        // Bishop *bishopBlack1 = new Bishop(PieceType::BishB);
        // Bishop *bishopBlack2 = new Bishop(PieceType::BishB);
        
        // //Knight
        // Knight *knightWhite1 = new Knight(PieceType::KnitW);
        // Knight *knightWhite2 = new Knight(PieceType::KnitW);

        // Knight *knightBlack1 = new Knight(PieceType::KnitB);
        // Knight *knightBlack2 = new Knight(PieceType::KnitB);

        // //Queen
        // Queen *queenWhite = new Queen(PieceType::QueeW);
        // Queen *queenBlack = new Queen(PieceType::QueeB);

        // //King
        // King *kingWhite = new King(PieceType::KingW);
        // King *kingBlack = new King(PieceType::KingB);




//
// class ChessPiece{
//     public:
//     int rowPos;
//     int colPos;
//     PieceType pieceType;

//     ChessPiece(){}

//     ChessPiece(PieceType pieceType){
//         this->pieceType = pieceType;
//         this->rowPos = 0;
//         this->colPos = 0;
//     }

//     ChessPiece(ChessPiece *piece){
//         this->pieceType = piece->pieceType;
//         this->rowPos = piece->rowPos;
//         this->colPos = piece->colPos;
//     }

//     virtual ChessPiece* clone() = 0;
//     virtual void knowMe() = 0;

//     void updatePosition(int row, int col){
//         this->rowPos = row;
//         this->colPos = col;
//     }
// };

// class Pawn:public ChessPiece{

//     public:
//     Pawn(PieceType pieceType):ChessPiece(pieceType){}

//     Pawn(Pawn *piece):ChessPiece(piece){}

//     ChessPiece* clone(){
//         return new Pawn(this);
//     }

//     void knowMe(){
//         cout<<"I am Pawn, I can move one step ahead at a time and I capture piece only diagonally with one step."<<endl;
//     }
// };

// class Rook:public ChessPiece{

//     public:
//     Rook(PieceType pieceType):ChessPiece(pieceType){}

//     Rook(Rook *piece):ChessPiece(piece){}

//     ChessPiece *clone(){
//         return new Rook(this);
//     }

//     void knowMe(){
//         cout<<"I am Rook, I can move any number of steps in Horizontal and veritical"<<endl;
//     }
// };      

// class Bishop:public ChessPiece{

//     public:
//     Bishop(PieceType pieceType ):ChessPiece(pieceType){}

    
//     Bishop(Bishop *piece):ChessPiece(piece){}

//     ChessPiece *clone(){
//         return new Bishop(this);
//     }

//     void knowMe(){
//         cout<<"I am Bishop, I can move any number of steps in diagonal."<<endl;
//     }
// };      


// class Knight:public ChessPiece{

//     public:
//     Knight(PieceType pieceType):ChessPiece(pieceType){}
    
//     Knight(Knight *piece):ChessPiece(piece){}

//     ChessPiece *clone(){
//         return new Knight(this);
//     }

//     void knowMe(){
//         cout<<"I am Knight, I can move any number of steps in diagonal."<<endl;
//     }
// };      


// class King:public ChessPiece{

//     public:
//     King(PieceType pieceType):ChessPiece(pieceType){}
    
//     King(King *piece):ChessPiece(piece){}

//     ChessPiece *clone(){
//         return new King(this);
//     }

//     void knowMe(){
//         cout<<"I am King, I can move only one place in all four direction, if there is not check"<<endl;
//     }
// };


// class Queen:public ChessPiece{

//     public:
//     Queen(PieceType pieceType):ChessPiece(pieceType){}
    
//     Queen(Queen *piece):ChessPiece(piece){}

//     ChessPiece *clone(){
//         return new Queen(this);
//     }

//     void knowMe(){
//         cout<<"I am Queen, I can move any number of steps in all four directions along with diagonal directions"<<endl;
//     }
// };