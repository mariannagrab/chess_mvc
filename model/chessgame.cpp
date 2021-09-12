#include "chessgame.h"
#include <algorithm>

// konstruktor
ChessGame::ChessGame()
{
    white = new Player(WHITE_COLOR);
    black = new Player(BLACK_COLOR);
    whosTurn = WHITE_COLOR;
    resetMove(LastMove);
    resetMove(ThisMove);
    setWhosCheckMate(EMPTY);
    black ->setKingPosition(0,4);
    white ->setKingPosition(7,4);
}

// kopiuje początkową stałą planszę do tymczasowej
void ChessGame::initializeBoard()
{
    /* using memcpy to copy structure: */
     memcpy (board, first_board, sizeof(char)* 8*8);
}

char ChessGame::getWhosTurn()
{
    return whosTurn;
}

void ChessGame::changeTurn()
{
    whosTurn = (whosTurn == WHITE_COLOR) ? BLACK_COLOR : WHITE_COLOR;
}

char ChessGame::checkPieceAtPosition(int row, int column)
{
    return board[row][column];
}


bool ChessGame::isMoveValid(Move move)
{
    int whatPiece_row = move.moveFrom_row;
    int whatPiece_column = move.moveFrom_column;
    int putWhere_row = move.moveTo_row;
    int putWhere_column = move.moveTo_column;

    // sprawdzenie czy na wybranym polu jest pionek
    char piece = checkPieceAtPosition(whatPiece_row,whatPiece_column);
    char wherePiece = checkPieceAtPosition(putWhere_row,putWhere_column);

    char pieceColor = getPieceColor<char>(piece);
    if (piece==EMPTY){
        return false;
    }
    // sprawdzenie czy na wybranym polu docelowym nie ma pionka o tym samym kolorze
    if(getPieceColor<char>(wherePiece)==pieceColor){
        return false;
    }

    // czy to pionek (pawn)
    switch(toupper(piece)){
    case 'P':
        // kroki do przodu
    {
        if(whatPiece_column == putWhere_column){
            // pojedynczy ruch do przodu
            // sprawdzenie czy nie ma pionka pna polu
            if(EMPTY ==checkPieceAtPosition(putWhere_row,putWhere_column)){
                if((pieceColor == BLACK_COLOR) && (putWhere_row-whatPiece_row==1)){
                    return true;
                }else if((pieceColor == WHITE_COLOR) && (putWhere_row-whatPiece_row==-1)){
                    return true;
                }};

                // podwójny ruch do przodu
                // sprawdzenie czy pionek jest w drugim lub szóstym rzedzie
                // sprawdzenie czy nie ma pionków z przodu
            if(doublePawnMove(move)){
                return true;
            };

        }
        // bicie na skos
        else if((abs(putWhere_column-whatPiece_column)==1) &&
                (((pieceColor == BLACK_COLOR) && (putWhere_row - whatPiece_row == 1))
                 || ((pieceColor == WHITE_COLOR) && (putWhere_row - whatPiece_row == -1)))){
            // sprawdzenie czy pole nie jest puste
            if(EMPTY != checkPieceAtPosition(putWhere_row,putWhere_column)){
                return true;
                //@TODO
                // bicie w przelocie

            }};

    }
        break;
    // czy to wieża (rook)
    case 'R':
    {
        // ruchy do boków
        if((putWhere_row == whatPiece_row) && (putWhere_column != whatPiece_column)) {
            // nie mogę zastapic funkcja
            // np. gdy col1 = 4 col2 = 0 to sprawdzamy tylko czy pola 1,2,3 są puste
            // pola pomiędzy
            int mincol = min(putWhere_column, whatPiece_column);
            int maxcol = max(putWhere_column, whatPiece_column);
            for(int i = mincol+1;i<maxcol;i ++){
                if(EMPTY !=checkPieceAtPosition(putWhere_row,i)){
                    return false;
                };
            }
            return true;
        // ruchy do przodu i do tyłu
        }else if((putWhere_row != whatPiece_row) && (putWhere_column == whatPiece_column)){
            int minrow = min(putWhere_row, whatPiece_row);
            int maxrow = max(putWhere_row, whatPiece_row);
            for(int i = minrow+1;i<maxrow;i ++){
                if(EMPTY !=checkPieceAtPosition(i,putWhere_column)){
                    return false;
                };
            }
            return true;
        };
    }
        break;
    // czy to koń/skoczek (knight)
    case 'N':
    {
        // ruchy po literze L
        if ((abs(whatPiece_row - putWhere_row)==1) && (abs(putWhere_column - whatPiece_column))==2){
            return true;
        }else if ((abs(whatPiece_row - putWhere_row)==2) && (abs(putWhere_column - whatPiece_column))==1){
            return true;
        }
    }
        break;

    // czy to goniec (bishop)
    case 'B':
    {
        //ruchy na skos
        if (abs(putWhere_column - whatPiece_column) == abs(whatPiece_row - putWhere_row)){
            return checkDiagonalMove(move);
        }
    }
        break;

    // czy to królowa/hetman (queen)
    case 'Q':
    {
        // ruchy tak jak wieży + tak jak gońca
        // ruchy do boków
        if((putWhere_row == whatPiece_row) && (putWhere_column != whatPiece_column)) {
            int mincol = min(putWhere_column, whatPiece_column);
            int maxcol = max(putWhere_column, whatPiece_column);
            for(int i = mincol+1;i<maxcol;i ++){
                if(EMPTY !=checkPieceAtPosition(putWhere_row,i)){
                    return false;
                };
            }
            return true;
            // ruchy do przodu i do tyłu
        }else if((putWhere_row != whatPiece_row) && (putWhere_column == whatPiece_column)){
            int minrow = min(putWhere_row, whatPiece_row);
            int maxrow = max(putWhere_row, whatPiece_row);
            for(int i = minrow+1;i<maxrow;i ++){
                if(EMPTY !=checkPieceAtPosition(i,putWhere_column)){
                    return false;
                };
            }
            return true;
        // ruchy na skos
        }else if(abs(putWhere_column - whatPiece_column) == abs(whatPiece_row - putWhere_row)){
            return checkDiagonalMove(move);
        };
    }
        break;
        // czy to król (king)
    case 'K':
    {
        if(isKingsMoveValid(pieceColor,putWhere_row,putWhere_column)){
            return true;
        }
        else if(isCastleMove(pieceColor,putWhere_row,putWhere_column)){
            return true;
        }
        break;
    }
    default:
    {
            return false;
    }
    };
    return false;
};

bool ChessGame::checkDiagonalMove(Move move)
{
    if((move.moveFrom_column<move.moveTo_column) && (move.moveFrom_row<move.moveTo_row)){
        for(int i = move.moveFrom_row+1;i<move.moveTo_row;i++){
            move.moveFrom_column++;
            if(EMPTY !=checkPieceAtPosition(i,move.moveFrom_column)){
                return false;
            };
        }
        return true;
    }else if((move.moveFrom_column>move.moveTo_column) && (move.moveFrom_row<move.moveTo_row)){
         for(int i = move.moveFrom_row+1;i<move.moveTo_row;i++){
            move.moveFrom_column--;
            if(EMPTY !=checkPieceAtPosition(i,move.moveFrom_column)){
                return false;
            };
        }
        return true;
    }else if((move.moveFrom_column<move.moveTo_column) && (move.moveFrom_row>move.moveTo_row)){
        for(int i = move.moveFrom_row-1;i>move.moveTo_row;i--){
            move.moveFrom_column++;
            if(EMPTY !=checkPieceAtPosition(i,move.moveFrom_column)){
                return false;
            };
        }
        return true;
    }else if((move.moveFrom_column>move.moveTo_column) && (move.moveFrom_row>move.moveTo_row)){
        for(int i = move.moveFrom_row-1;i>move.moveTo_row;i--){
            move.moveFrom_column--;
            if(EMPTY !=checkPieceAtPosition(i,move.moveFrom_column)){
                return false;
            };
        }
        return true;
    }
    return false;
}

void ChessGame::movePiece()
{
    char upperPiece = toupper(ThisMove.figure);
    char wherePiece = checkPieceAtPosition(ThisMove.moveTo_row,ThisMove.moveTo_column);
    char upperWherePiece = toupper(wherePiece);
    char pieceColor = getPieceColor<char>(ThisMove.figure);

    // sprawdzenie czy na docelowym polu nie ma króla
    // usunięcie pionka z pola
    if(!(upperWherePiece == 'K')){
        removePiece(ThisMove.moveFrom_row,ThisMove.moveFrom_column);
        //board[ThisMove.moveFrom_row][ThisMove.moveFrom_column] = EMPTY;
        // przestawienie pionka na miejsce docelowe
        addPiece(ThisMove.figure,ThisMove.moveTo_row,ThisMove.moveTo_column);
        //board[ThisMove.moveTo_row][ThisMove.moveTo_column] = ThisMove.figure;
    }else{
        return;
    }
    // jeżeli był jakiś pionek na miejscu docelowym to trzeba dodać go do listy zbitych pionków
    if(wherePiece != EMPTY){
        addToCaptured(wherePiece);
    };
    // roszada - przestawienie wieży
    if(isCastleMove(pieceColor,ThisMove.moveTo_row,ThisMove.moveTo_column)){
       doCastleMove();
    };
    // zapisanie last move musi odbyć się po sprawdzeniu zmiennej is_enPassant
    saveLastMove(ThisMove.figure,ThisMove.moveFrom_row,ThisMove.moveFrom_column,ThisMove.moveTo_row,ThisMove.moveTo_column);
    // jeżeli poruszyła się lub została zbita wieża zapisujemy by zapobiec roszadzie
    if ((upperPiece == 'R') || (upperWherePiece == 'R')){
        saveCastlePossib(ThisMove.moveFrom_row, ThisMove.moveFrom_column);
    // jeżeli poruszył się król zapisujemy nowe współrzędne
    }else if(upperPiece == 'K'){
        saveNewKingsPosition(ThisMove.figure, ThisMove.moveTo_row, ThisMove.moveTo_column);
    }
    // sprawdzenie czy nia ma szacha
    char checkPiece = checkCheck();
    if(checkPiece!=EMPTY){
        if(checkMate(checkPiece)){
            setWhosCheckMate(checkPiece);
        }
    }
    // zmiana gracza
    changeTurn();
}

void ChessGame::doCastleMove()
{
    if((ThisMove.moveTo_row == 0) &&  (ThisMove.moveTo_column == 2)){
       board[0][0] = EMPTY;
       board[0][3] = 'r';
    }else if((ThisMove.moveTo_row == 0) &&  (ThisMove.moveTo_column == 6)){
        board[0][7] = EMPTY;
        board[0][5] = 'r';
    }else if((ThisMove.moveTo_row == 7) &&  (ThisMove.moveTo_column == 2)){
        board[7][0] = EMPTY;
        board[7][3] = 'R';
    }else if((ThisMove.moveTo_row == 7) &&  (ThisMove.moveTo_column == 6)){
        board[7][7] = EMPTY;
        board[7][5] = 'R';
    };
}
char ChessGame::checkCheck()
{

    char pieceColor;
    Move currentMove;

    // rows
    for(int i = 0; i<=7; i++){
        //columns
        for(int j=0;j<=7;j++){
            currentMove.moveFrom_row = i;
            currentMove.moveFrom_column = j;
            // jeżeli
            pieceColor = getPieceColor<int>(i,j);
            if(pieceColor == BLACK_COLOR){

                currentMove.moveTo_row = white->getKingsPosition().row;
                currentMove.moveTo_column = white->getKingsPosition().column;
                if(isMoveValid(currentMove)){
                    black ->setHasCheck(true);
                    return WHITE_KING;
                };
            }else if(pieceColor == WHITE_COLOR){

                currentMove.moveTo_row = black->getKingsPosition().row;
                currentMove.moveTo_column = black->getKingsPosition().column;
                if(isMoveValid(currentMove)){
                    white -> setHasCheck(true);
                    return BLACK_KING;
                };
            }
        }
    }
    setChecktoFalse();
    return EMPTY;
}
// funkcja zwraca true jeżeli będzie szach gdy król będzie stał w danej lokalizacji
// szach będzie dla oppKingsColor
bool ChessGame::checkCheck(char piece, int whatPiece_row, int whatPiece_column)
{
    Move currentMove;
    currentMove.moveTo_row = whatPiece_row;
    currentMove.moveTo_column = whatPiece_column;
    currentMove.figure = checkPieceAtPosition(whatPiece_row,whatPiece_column);
    addPiece(piece,whatPiece_row,whatPiece_column);
    char pieceColor;
    char oppKingsColor = (piece == WHITE_KING) ? BLACK_COLOR : WHITE_COLOR;
    // rows
    for(int i = 0; i<=7; i++){
        //columns
        for(int j=0;j<=7;j++){
            currentMove.moveFrom_row = i;
            currentMove.moveFrom_column = j;

            // jeżeli kolor znalezionego na planszy pionka odpowiada przeciwnemu niż kolor króla
            // i ruch jest możliwy dla tego pionka na miejsce króla to zwróć true
            pieceColor = getPieceColor<int>(i,j);
            if(oppKingsColor == pieceColor){
                if(isMoveValid(currentMove)){
                    addPiece(currentMove.figure,whatPiece_row,whatPiece_column);
                    return true;
                };
        }
    }
    }
    //removePiece(whatPiece_row,whatPiece_column);
    addPiece(currentMove.figure ,whatPiece_row,whatPiece_column);

    return false;
}


void ChessGame::setChecktoFalse()
{
    white ->setHasCheck(false);
    black ->setHasCheck(false);
}

bool ChessGame::checkMate(char piece)
{
    if((white->getHasCheck() == false) && (black->getHasCheck() == false)){
        return false;
    }else{
        char kingColor = getPieceColor<char>(piece);
        bool condit = (kingColor == WHITE_COLOR);
        int king_column= (condit) ? white->getKingsPosition().column : black->getKingsPosition().column;
        int king_row = (condit) ? white->getKingsPosition().row : black->getKingsPosition().row;

        // rows
        for(int i = -1; i<=1; i++){
            // columns
            for(int j = -1; j<=1; j++){
                if((king_column +j>=0) && (king_column +j<=7) && (king_row +i>=0) && (king_row +i<=7)){
                    // nie sprawdzamy jeżeli jest to pozycja teraźniejsza króla
                    if((i==0) && (j==0)){
                        continue;
                    };
                    // jeżeli król może się poruszyć na dane pole
                    // to sprawdź funkcją checkcheck czy na tym polu zbije go jakiś pionek
                    // jeżeli zbije to sprawdź kolejne opcje ruchu
                    // jeżeli nie zbije to zwróć false - król ma opcje ruchu
                    if(isKingsMoveValid(kingColor,king_row + i,king_column +j)){
                        //usuń na chwilę pionek z tablicy, by funkcja sprawdzająca check działała poprawnie
                        removePiece(king_row,king_column);
                        if(!checkCheck(piece,king_row + i,king_column +j)){
                            // dodaj pionek na poprzednie miejsce
                            addPiece(piece,king_row ,king_column);
                            return false;
                        }
                    }
                }
            };
        };
        // dodaj pionek na poprzednie miejsce
        addPiece(piece,king_row ,king_column);
        return true;
    }
}

vector<int>* ChessGame::returnAvailableFields(int whatPiece_row, int whatPiece_column)
{
    std::vector< int > *availableFields = new std::vector<int>;
    ThisMove.figure = checkPieceAtPosition(whatPiece_row,whatPiece_column);
    ThisMove.moveFrom_row = whatPiece_row;
     ThisMove.moveFrom_column = whatPiece_column;
    //rows
    for(int i = 0; i<=7; i++){
        //columns
        for(int j=0;j<=7;j++){
            ThisMove.moveTo_row = i;
            ThisMove.moveTo_column = j;
            if(isMoveValid(ThisMove)){

                availableFields->push_back(i);
                availableFields->push_back(j);
            }
        }
    }
    return availableFields;
}

void ChessGame::addToCaptured(char piece)
{
    char pieceColor = getPieceColor<char>(piece);

    if(pieceColor == WHITE_COLOR){
        black -> addToCaptured(piece);
    }else if(pieceColor == BLACK_COLOR){
        white -> addToCaptured(piece);
    };
}

void ChessGame::saveThisMove(char _figure, int _whatPiece_row, int _whatPiece_column, int _putWhere_row, int _putWhere_column)
{
    ThisMove.figure = _figure;
    ThisMove.moveFrom_row = _whatPiece_row;
    ThisMove.moveFrom_column = _whatPiece_column;
    ThisMove.moveTo_row = _putWhere_row;
    ThisMove.moveTo_column = _putWhere_column;
}

ChessGame::Move ChessGame::getLastMove()
{
    return LastMove;
}

void ChessGame::saveLastMove(char _figure, int _whatPiece_row, int _whatPiece_column, int _putWhere_row, int _putWhere_column)
{
    LastMove.figure = _figure;
    LastMove.moveFrom_row = _whatPiece_row;
    LastMove.moveFrom_column = _whatPiece_column;
    LastMove.moveTo_row = _putWhere_row;
    LastMove.moveTo_column = _putWhere_column;
}

bool ChessGame::doublePawnMove(Move move)
{
    //char color = checkPieceColor(checkPieceAtPosition(move.moveFrom_row,move.moveFrom_column));
    if(move.moveFrom_column != move.moveTo_column){
        return false;
    };
    if(getPieceColor<char>(move.figure) == WHITE_COLOR){
        if((move.moveFrom_row != 6) || (move.moveTo_row != 4)){
            return false;
        }else if((EMPTY !=checkPieceAtPosition(move.moveTo_row,move.moveTo_column)) || (EMPTY !=checkPieceAtPosition(move.moveTo_row+1,move.moveTo_column))){
            return false;
        }else{
            return true;
        };
    }else{
        if((move.moveFrom_row  != 1) || (move.moveTo_row != 3)){
            return false;
        }else if((EMPTY !=checkPieceAtPosition(move.moveTo_row,move.moveTo_column)) || (EMPTY !=checkPieceAtPosition(move.moveTo_row-1,move.moveTo_column))){
            return false;
        }else{
            return true;
        };
    };
    return false;
}

void ChessGame::saveNewKingsPosition(char piece, int row, int column)
{
    // jeżeli pionek to król to zapisujemy nową pozycję króla
    // oraz ustalamy, że roszada nie jest już możliwa
    if(piece == WHITE_KING){
        white ->setKingPosition(row,column);
        white ->setCastleLefttoFalse();
        white ->setCastleRighttoFalse();
    }else if(piece ==BLACK_KING){
        black -> setKingPosition(row,column);
        black -> setCastleLefttoFalse();
        black -> setCastleRighttoFalse();
    }
}

// funkcja zwracca true gdy ruch króla o kolorze color jest możliwy w miejsce o współrzędnych putWhere_row,putWhere_column
bool ChessGame::isKingsMoveValid(char color, int putWhere_row, int putWhere_column)
{
    int whatPiece_row = (color == BLACK_COLOR) ? black->getKingsPosition().row : white -> getKingsPosition().row;
    int whatPiece_column = (color == BLACK_COLOR) ? black -> getKingsPosition().column : white -> getKingsPosition().column;
    char wherePieceColor = getPieceColor<int>(putWhere_row,putWhere_column);
    // plus sprawdzenie czy nie ma pionka w tym samym kolorze
    // ruch o jedno pole w pionie lub poziomie
    if((((abs(whatPiece_column-putWhere_column)==1)&& (whatPiece_row==putWhere_row)) ||
            ((abs(whatPiece_row-putWhere_row)==1) && (whatPiece_column==putWhere_column))) && (wherePieceColor!= color)){
        return true;
    // ruch o jedno pole diagonalnie
    }else if(((abs(whatPiece_row-putWhere_row)==1) && (abs(whatPiece_column-putWhere_column)==1)) && (wherePieceColor!= color)){
        return true;
    };
    return false;
}

void ChessGame::saveCastlePossib(int whatPiece_row, int whatPiece_column)
{
    // jeżeli nie u gracza białego i u gracza czarnego parametry są false
    // nie sprawdzamy dalej
    if((black ->isCastleFalse()) && (white->isCastleFalse())){
        return;
    };

    if((whatPiece_row == 0) && (whatPiece_column == 0)){
        black ->setCastleLefttoFalse();
        return;
    };
    if((whatPiece_row == 0) && (whatPiece_column == 7)){
        black ->setCastleRighttoFalse();
        return;
    };
    if((whatPiece_row == 7) && (whatPiece_column == 0)){
        white ->setCastleLefttoFalse();
        return;
    };
    if((whatPiece_row == 7) && (whatPiece_column == 7)){
        white ->setCastleRighttoFalse();
        return;
    };
}

bool ChessGame::isCastleMove(char pieceColor, int putWhere_row, int putWhere_column)
{
    //roszada dla czarnego króla:
    if((pieceColor == BLACK_COLOR) && (putWhere_row == 0) && !(white ->getHasCheck())){
        // roszada czarna w lewo
        if ((putWhere_column == 2)&& (black ->getCastleParam().king_l)){
            if((checkPieceAtPosition(0,1) == EMPTY) && (checkPieceAtPosition(0,2) == EMPTY) &&
                    (checkPieceAtPosition(0,3) == EMPTY) ){
                return true;
            };
            // roszada czarna w prawo
        }else if((putWhere_column == 6)&& (black ->getCastleParam().king_r)){
            if((checkPieceAtPosition(0,5) == EMPTY) && (checkPieceAtPosition(0,6) == EMPTY) ){
                return true;
            };
        }
    //roszada dla białego króla:
    }else if((pieceColor == WHITE_COLOR) && (putWhere_row == 7) && !(black ->getHasCheck())){
        // roszada biała w lewo
        if ((putWhere_column == 2)&& (white ->getCastleParam().king_l)){
            if((checkPieceAtPosition(7,1) == EMPTY) && (checkPieceAtPosition(7,2) == EMPTY) &&
                    (checkPieceAtPosition(7,3) == EMPTY)){
                return true;
            };
            // roszada biała w prawo
        }else if((putWhere_column == 6) && (white ->getCastleParam().king_r)){
            if((checkPieceAtPosition(7,5) == EMPTY) && (checkPieceAtPosition(7,6) == EMPTY)){
                return true;
            };
        }
    }
    return false;
}

void ChessGame::removePiece(int row, int column)
{
    board[row][column] = EMPTY;
}

void ChessGame::addPiece(char piece, int row, int column)
{
    board[row][column] = piece;

}

void ChessGame::resetMove(Move move)
{
    move.figure = EMPTY;
    move.moveFrom_column = -1;
    move.moveFrom_row = -1;
    move.moveTo_column = -1;
    move.moveTo_row = -1;
}

char ChessGame::getWhosCheckMate() const
{
    return whosCheckMate;
}

void ChessGame::setWhosCheckMate(char value)
{
    whosCheckMate = value;
}

Player *ChessGame::getWhite() const
{
    return white;
}

Player *ChessGame::getBlack() const
{
    return black;
}





