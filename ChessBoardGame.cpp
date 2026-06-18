#include <iostream>
#include <string>
#include<fstream>
#include <cmath>
using namespace std;

class ChessPiece {
private:
    string name;
    char color;
    char symbol;

public:
    ChessPiece() : name("Pawn"), color('W'), symbol('p') {}
    ChessPiece(string name, char color, char symbol) : name(name), color(color), symbol(symbol) {}
    template<typename t>
    t getName() { return name; }
    char getColor() { return color; }
    char getSymbol() { return symbol; }
    
    void setName(string name) { this->name = name; }
    void setColor(char color) { this->color = color; }
    void setSymbol(char symbol) { this->symbol = symbol; }
};

class ChessBoard {
private:
    ChessPiece* board[8][8];
    int sourceRow;
    int sourceCol;
    int destRow;
    int destCol;
    ChessPiece* piece;
    int rowChange;
    int colChange;

public:
    ChessBoard() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j] = nullptr;
            }
        }
        board[7][0] = new ChessPiece("Rook", 'B', 'R');
        board[7][1] = new ChessPiece("Knight", 'B', 'N');
        board[7][2] = new ChessPiece("Bishop", 'B', 'B');
        board[7][3] = new ChessPiece("Queen", 'B', 'Q');
        board[7][4] = new ChessPiece("King", 'B', 'K');
        board[7][5] = new ChessPiece("Bishop", 'B', 'B');
        board[7][6] = new ChessPiece("Knight", 'B', 'N');
        board[7][7] = new ChessPiece("Rook", 'B', 'R');
        
        for (int col = 0; col < 8; col++) {
            board[6][col] = new ChessPiece("Pawn", 'B', 'P');
        }
        for (int col = 0; col < 8; col++) {
            board[1][col] = new ChessPiece("Pawn", 'W', 'p');
        }
        board[0][0] = new ChessPiece("Rook", 'W', 'r');
        board[0][1] = new ChessPiece("Knight", 'W', 'n');
        board[0][2] = new ChessPiece("Bishop", 'W', 'b');
        board[0][3] = new ChessPiece("Queen", 'W', 'q');
        board[0][4] = new ChessPiece("King", 'W', 'k');
        board[0][5] = new ChessPiece("Bishop", 'W', 'b');
        board[0][6] = new ChessPiece("Knight", 'W', 'n');
        board[0][7] = new ChessPiece("Rook", 'W', 'r');
    }

    ~ChessBoard() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                delete board[i][j];
            }
        }
    }

    void display()
	{
        cout << "  a b c d e f g h" << endl;
        for (int i = 7; i >= 0; --i) {
            cout << 8-i<< " ";
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == nullptr) {
                    cout << ". ";
                } else {
                    cout << board[i][j]->getSymbol() << " ";
                }
            }
            cout << 8-i << endl;
        }
        cout << "  a b c d e f g h" << endl;
    }

    bool movePiece(string source, string destination) {
        sourceRow = 8 - (source[1] - '0');
        sourceCol = source[0] - 'a';
        destRow = 8 - (destination[1] - '0');
        destCol = destination[0] - 'a';
        
        if (sourceRow < 0 || sourceRow >= 8 || sourceCol < 0 || sourceCol >= 8 || 
            destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8) {
            cout << "Invalid source or destination position" << endl;
            return false;
        }
        
        piece = board[sourceRow][sourceCol];
        
        if (piece == nullptr) {
            cout << "No piece at source position" << endl;
            return false;
        }

        if (!isValidMove(source,destination,sourceRow, sourceCol, destRow, destCol, piece->getSymbol(), piece->getColor())) {
            cout << "Invalid move for the piece" << endl;
            return false;
        }
        //board[destRow][destCol] = nullptr;
        board[destRow][destCol] = piece;
        board[sourceRow][sourceCol] = nullptr;
        cout << "Piece moved successfully from " << source << " to " << destination << "." << endl;
        return true;
    }

    bool isValidMove(string source,string destination,int sourceRow, int sourceCol, int destRow, int destCol, char pieceSymbol, char pieceColor) {
        // Implement logic for valid moves for each piece type
        rowChange = abs(destRow - sourceRow);
        colChange = abs(destCol - sourceCol);
        
        // Check if the destination is within the board
        if (destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8) {
            return false;
        }

        // Check if the destination is not occupied by the same color piece
        if (board[destRow][destCol] != nullptr && board[destRow][destCol]->getColor() == board[sourceRow][sourceCol]->getColor()) {
            return false;
        }

        // Pawn movement
        if (pieceSymbol == 'P') { // White pawn initial move
            if (sourceRow == 6) {  
                if (destRow == sourceRow - 1 && destCol == sourceCol && (board[destRow][destCol] == nullptr)) {
                    return true;
                } else if (destRow == sourceRow - 2 && destCol == sourceCol && 
                        board[destRow][destCol] == nullptr && board[sourceRow - 1][destCol] == nullptr) {
                    return true;
                } else if (destRow == sourceRow - 1 && (destCol == sourceCol + 1 || destCol == sourceCol - 1) &&  
                        board[destRow][destCol] != NULL && (board[destRow][destCol]->getColor() != board[sourceRow][sourceCol]->getColor())) {
                    delete board[destRow][destCol];
                    board[destRow][destCol] = NULL;
                    return true;
                }
            } else {  // Pawn movement after the initial move
                if (destRow == sourceRow - 1 && destCol == sourceCol && board[destRow][destCol] == nullptr) {
                    return true;
                } else if (destRow == sourceRow - 1 && (destCol == sourceCol + 1 || destCol == sourceCol - 1) &&  
                        board[destRow][destCol] != nullptr && (board[destRow][destCol]->getColor() != board[sourceRow][sourceCol]->getColor())) {
                    delete board[destRow][destCol];
                    board[destRow][destCol] = nullptr;
                    return true;
                }
            }
        } else if(pieceSymbol == 'p') { // Black pawn initial move
            if (sourceRow == 1) {  
                if (destRow == sourceRow + 1 && destCol == sourceCol && board[destRow][destCol] == nullptr) {
                    return true;
                } else if (destRow == sourceRow + 2 && destCol == sourceCol && 
                        board[destRow][destCol] == nullptr && board[sourceRow + 1][destCol] == nullptr) {
                    return true;
                }
            } else {  // Pawn movement after the initial move
                if (destRow == sourceRow + 1 && destCol == sourceCol && board[destRow][destCol] == nullptr) {
                    return true;
                } else if (destRow == sourceRow + 1 && (destCol == sourceCol + 1 || destCol == sourceCol - 1) &&  
                        board[destRow][destCol] != nullptr && (board[destRow][destCol]->getColor() != board[sourceRow][sourceCol]->getColor())) {
                    delete board[destRow][destCol];
                    board[destRow][destCol] = nullptr;
                    return true;
                }
            }
        }


        // Other pieces' movement logic can be implemented similarly
        // Queen's Movement
        if (pieceSymbol == 'Q') { // Black Queens Initial Straight Movement
                if (destRow <= sourceRow - 1 && destCol == sourceCol) {
                    for (int i = sourceRow - 1; i >= destRow; i--) {
                        if (board[i][destCol] != nullptr) {
                            if(board[i][destCol]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow <= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false; // If any piece is found in the path, return false
                        }
                    }
                    return true;
                }
                // Black Queens Left Right Movement
                else if (destCol <= 7 && destRow == sourceRow) {
                    for(int i = sourceCol + 1; i <= destCol; i++){
                        if(board[destRow][i] != nullptr) {
                            if(board[destRow][i]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destCol <= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                                else
                                    return false;
                            }
                        }
                    }
                }

                // Black Queens Diagonal Movements
                else if(destCol < sourceCol && destRow > sourceRow){
                    for(int i = sourceRow - 1, j = sourceCol - 1; i >= destRow; i--, j--){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow <= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
                else if(destCol > sourceCol && destRow < sourceRow) {
                    for(int i = sourceRow + 1, j = sourceCol + 1; i <= destRow; i++, j++){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow >= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
                else if(destCol > sourceCol && destRow > sourceRow) {
                    for(int i = sourceRow + 1, j = sourceCol + 1; i <= destRow; i++, j++){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow >= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
                else if(destCol < sourceCol && destRow < sourceRow) {
                    for(int i = sourceRow - 1, j = sourceCol - 1; i >= destRow; i--, j--){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow <= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
            } else if(pieceSymbol == 'q') { // White Queens Initial Straight Movement
                if (destRow >= sourceRow + 1 && destCol == sourceCol) {
                    for (int i = sourceRow + 1; i <= destRow; i++) {
                        if (board[i][destCol] != nullptr) {
                            if(board[i][destCol]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow <= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        }
                    }
                    return true;
                }
                // White Queens Left Right Movement
                else if (destCol <= 7 && destRow == sourceRow) {
                    for(int i = sourceCol + 1; i <= destCol; i++){
                        if(board[destRow][i] != nullptr) {
                            if(board[destRow][i]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                    if(destCol >= i){
                                        delete board[destRow][destCol];
                                        board[destRow][destCol] = nullptr;
                                        return true;
                                    }
                                    else
                                        return false;
                        }
                        }
                        return true;
                    }
                }

                // White Queens Diagonal Movements
                else if(destCol < sourceCol && destRow > sourceRow){
                    for(int i = sourceRow - 1, j = sourceCol - 1; i >= destRow; i--, j--){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow >= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
                else if(destCol > sourceCol && destRow < sourceRow) {
                    for(int i = sourceRow + 1, j = sourceCol + 1; i <= destRow; i++, j++){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow >= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
                else if(destCol > sourceCol && destRow > sourceRow) {
                    for(int i = sourceRow + 1, j = sourceCol + 1; i <= destRow; i++, j++){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow >= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;    
                        } 
                    }
                    return true;
                }
                else if(destCol < sourceCol && destRow < sourceRow) {
                    for(int i = sourceRow - 1, j = sourceCol - 1; i >= destRow; i--, j--){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow <= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
            }
         
        
            

        //Bhisop's Movement
        // Black Bhisop's Movement
    
            if(pieceSymbol == 'B'){
                if(destCol < sourceCol && destRow > sourceRow){
                    for(int i = sourceRow - 1, j = sourceCol - 1; i >= destRow; i--, j--){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow <= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
                else if(destCol > sourceCol && destRow < sourceRow) {
                    for(int i = sourceRow + 1, j = sourceCol + 1; i <= destRow; i++, j++){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow >= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
                else if(destCol > sourceCol && destRow > sourceRow) {
                    for(int i = sourceRow + 1, j = sourceCol + 1; i <= destRow; i++, j++){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow >= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
                else if(destCol < sourceCol && destRow < sourceRow) {
                    for(int i = sourceRow - 1, j = sourceCol - 1; i >= destRow; i--, j--){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow <= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
            } // White Bishops Movement
            else if(pieceSymbol == 'b'){
                if(destCol < sourceCol && destRow > sourceRow){
                    for(int i = sourceRow - 1, j = sourceCol - 1; i >= destRow; i--, j--){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow <= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
                else if(destCol > sourceCol && destRow < sourceRow) {
                    for(int i = sourceRow + 1, j = sourceCol + 1; i <= destRow; i++, j++){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow >= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
                else if(destCol > sourceCol && destRow > sourceRow) {
                    for(int i = sourceRow + 1, j = sourceCol + 1; i <= destRow; i++, j++){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow >= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;    
                        } 
                    }
                    return true;
                }
                else if(destCol < sourceCol && destRow < sourceRow) {
                    for(int i = sourceRow - 1, j = sourceCol - 1; i >= destRow; i--, j--){
                        if(board[i][j] != nullptr) {
                            if(board[i][j]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow <= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        } 
                    }
                    return true;
                }
            }
        


        if(pieceSymbol == 'N' || pieceSymbol == 'n'){
            if ((colChange == 2 && rowChange == 1) || 
                    (colChange == 1 && rowChange == 2) ){
                        if(board[destRow][destCol] == nullptr){
                            return true;
                        }
                        else if(board[destRow][destCol] != nullptr && board[destRow][destCol]->getColor() != board[sourceRow][sourceCol]->getColor()){
                            delete board[destRow][destCol];
                            board[destRow][destCol] = nullptr;
                            return true;
                        }
                        else
                            return false;
                }
                else
                    return false;
        }

        if(pieceSymbol == 'R' || pieceSymbol == 'r'){
            if(pieceSymbol == 'R'){
                if (destRow <= sourceRow - 1 && destCol == sourceCol) {
                    for (int i = sourceRow - 1; i >= destRow; i--) {
                        if (board[i][destCol] != nullptr) {
                            if(board[i][destCol]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow <= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        }
                    }
                    return true;
                }
                
                else if (destCol <= 7 && destRow == sourceRow) {
                    for(int i = sourceCol + 1; i <= destCol; i++){
                        if (board[destRow][i] != nullptr) {
                            if(board[destRow][i]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destCol <= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        }
                    }
                }
                return true;
            }
            else if (pieceSymbol == 'r') {
                if (destRow >= sourceRow + 1 && destCol == sourceCol) {
                    for (int i = sourceRow + 1; i <= destRow; i++) {
                        if (board[i][destCol] != nullptr) {
                            if(board[i][destCol]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destRow >= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        }
                    }
                    return true;
                }
                
                else if (destCol <= 7 && destRow == sourceRow) {
                    for(int i = sourceCol + 1; i <= destCol; i++){
                        if (board[destRow][i] != nullptr) {
                            if(board[destRow][i]->getColor() != board[sourceRow][sourceCol]->getColor()){
                                if(destCol >= i){
                                    delete board[destRow][destCol];
                                    board[destRow][destCol] = nullptr;
                                    return true;
                                }
                            }
                            else
                                return false;
                        }
                    }
                }
                return true;
            }
        }

        if(pieceSymbol == 'K' || pieceSymbol == 'k'){
            if(rowChange == 1 || colChange == 1 && board[destRow][destCol] == nullptr){
                return true;
            } 
            else if (rowChange == 1 || colChange == 1 && board[destRow][destCol] != nullptr && (board[destRow][destCol]->getColor() != board[sourceRow][sourceCol]->getColor())) {
                delete board[destRow][destCol];
                board[destRow][destCol] = nullptr;
                return true;
            }
            else
                return false;
        }

        return false; // Invalid move
    }
//    friend class Player;
};


class Player : public ChessBoard {
private:
    string name;
    string gameid;
    string flexstatement;
    int level;
    int experience;
    int playerpoints;

public:
	Player() {}
    Player(string name, string gameid, string flexstatement) 
        : name(name), gameid(gameid), flexstatement(flexstatement), level(0), experience(0), playerpoints(0) {}

    string getName() { return name; }
    int getlevel() { return level; }
    int getexp() { return experience; }
    string getstat() { return flexstatement; }
    
    void setname(string a) { name =a;}
    void setid(string b) { gameid=b;}
    void setstatement(string c) { flexstatement = c;}

    friend ostream& operator<<(ostream& os, const Player &player) {
        os << "Player's Information" << endl;
        os << "Name is: "<<player.name <<endl;
		os << "id is is: "<<player.gameid <<endl; 
        os << "level is: " << player.level << endl;
        os << "experience is: " << player.experience << endl;
        os << "flex statement is: " << player.flexstatement << endl;
        os << "player points are: " << player.playerpoints << endl;
        return os;
    }

   void signup(Player p3) {
    string name, id, statement;
    try {
        if (p3.name.empty()) {
            cout << "Enter name: ";
            cin >> name;
            if (name.empty()) {
                throw runtime_error("Name cannot be empty.");
            }

            cout << "Enter gameid: ";
            cin >> id;
            if (id.empty()) {
                throw runtime_error("Game ID cannot be empty.");
            }

            cout << "Enter statement: ";
            cin >> statement;
            if (statement.empty()) {
                throw runtime_error("Statement cannot be empty.");
            }

            p3.setname(name);
            p3.setid(id);
            p3.setstatement(statement);
        }
    } catch (const exception& e) {
        cerr << "Exception occurred: " << e.what() << endl;
    }
}

    void learnabtboard(ChessBoard b) {
        b.display();
    }

    void PlayGame() {
        char playAgain = 'n';
        ChessBoard board;
        do {
            board.display();
            string source, destination;
            cout << "Enter source position (e.g., a2): ";
            cin >> source;
            cout << "Enter destination position (e.g., a4): ";
            cin >> destination;

            if (board.movePiece(source, destination)) {
                board.display();
            }

            cout << "Do you want to move a piece again? (y/n): ";
            cin >> playAgain;
        } while (playAgain == 'y');
    }

    void chatbox(Player &p1, Player &p2) {
        
		string nameone,nametwo;
		cout << "Player 1, enter your name: ";
        cin >> nameone;
        cout << "Player 2, enter your name: ";
        cin >> nametwo;

        cout << "Welcome, " << nameone << " and " << nametwo << "!" << endl;
        cout << "Start chatting. Type 'exit' to end the conversation." << endl;

        string message;
        if(nameone==p1.name && nametwo==p2.name)
        {
        	        while (true) {
            cout << p1.name << ": ";
            getline(cin, message);
            if (message == "exit") {
                cout << p1.name << " has left the chat. Goodbye!";
                break;
            }
            cout << p2.name << ": ";
            getline(cin, message);
            if (message == "exit") {
                cout << p2.name << " has left the chat. Goodbye!";
                break;
            }
        }
		}
    }
    
     void writeToFile(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << name << endl;
            outFile << gameid << endl;
            outFile << flexstatement << endl;
            outFile << level << endl;
            outFile << experience << endl;
            outFile << playerpoints << endl;
            outFile.close();
            cout << "Player data has been written to file." << endl;
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    void readFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            getline(inFile, name);
            getline(inFile, gameid);
            getline(inFile, flexstatement);
            inFile >> level;
            inFile >> experience;
            inFile >> playerpoints;
            inFile.close();
            cout << "Player data has been read from file." << endl;
        } else {
            cout << "Unable to open file for reading." << endl;
        }
    }
};

int main() {
    cout << "-----------------------" << endl;
    cout << "=======================" << endl;
    cout << "THE CHESS GAME IS HERE" << endl;
    cout << "=======================" << endl;
    cout << "-----------------------" << endl;
    cout << "Welcome to the game..." << endl;
    cout << "To sign up, press 0" << endl;
    cout << "To learn about the board, press 1" << endl;
    cout << "To play the game, press 2" << endl;
    cout << "To chat with another player, press 3" <<endl;
    cout << "to save the information, press 4" <<endl;
    
	
    Player p1("harry","0029","I am lazy");
	Player p2("Chunkz","0018","Best football player is here to play chess");
    int choice;
    cin >> choice;
	ChessBoard b;
	Player p3;
	        Player player2;
    switch (choice) {
        case 0: 
            p3.signup(p3);
            break;
        
        case 1:
        	
            p1.learnabtboard(b);
            break;

        case 2: 
            p1.PlayGame();
            break;

        case 3:
            p1.chatbox(p1, p2);
            break;
		        
        case 4:
	        p1.writeToFile("player_data.txt");
	        player2.readFromFile("player_data.txt");
	        cout<<player2<<endl;
	        break;
        
        default:
            cout << "Invalid choice" << endl;
            break;
    }
//cout<<p1<<endl;
//ChessPiece pawn;
//cout << "Pawn Name: " << pawn.getName<string>() <<endl;
    return 0;
}
