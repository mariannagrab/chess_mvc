#include "chessgame.h"

#include <algorithm>

char ChessGame::getWhosTurn()
{
    return whosTurn;
}

void ChessGame::changeTurn()
{
    whosTurn = (whosTurn == white ->getColor()) ? black ->getColor() : white ->getColor();
}

void ChessGame::setWhosTurn(const char &value)
{
    whosTurn = value;
}

void ChessGame::saveLastMove(char _figure, int _whatPiece_row, int _whatPiece_column, int _putWhere_row, int _putWhere_column)
{
    LastMove.figure = _figure;
    LastMove.moveFrom_row = _whatPiece_row;
    LastMove.moveFrom_column = _whatPiece_column;
    LastMove.moveTo_row = _putWhere_row;
    LastMove.moveTo_column = _putWhere_column;
    if(!doublePawnMove(_whatPiece_row,_whatPiece_column,_putWhere_row,_putWhere_column)){
         LastMove.is_enPassant= false;
    }else{
        LastMove.is_enPassant= true;
    };

}

char ChessGame::checkCheck()
{
    setChecktoFalse();
    char pieceColor;
    // rows
    for(int i = 0; i<=7; i++){
        //columns
        for(int j=0;j<=7;j++){
            // jeżeli
            pieceColor = checkPieceColor(checkPieceAtPosition(i,j));
            if(pieceColor == BLACK_COLOR){
                if(isMoveValid(i,j,white->getKingsPosition().row,white->getKingsPosition().column)){
                    black ->setHasCheck(true);
                    return WHITE_KING;
                };
            }else if(pieceColor == WHITE_COLOR){
                if(isMoveValid(i,j,black->getKingsPosition().row,black->getKingsPosition().column)){
                    white -> setHasCheck(true);
                    return BLACK_KING;
                };
            }
        }
    }
    return EMPTY;
}
// funkcja zwraca true jeżeli będzie szach gdy król będzie stał w danej lokalizacji
// szach będzie dla oppKingsColor
bool ChessGame::checkCheck(char piece, int whatPiece_row, int whatPiece_column)
{
    char currentpiece = checkPieceAtPosition(whatPiece_row,whatPiece_column);
    addPiece(piece,whatPiece_row,whatPiece_column);
    char pieceColor;
    char oppKingsColor = (piece == WHITE_KING) ? BLACK_COLOR : WHITE_COLOR;
    // rows
    for(int i = 0; i<=7; i++){
        //columns
        for(int j=0;j<=7;j++){
            // jeżeli kolor znalezionego na planszy pionka odpowiada przeciwnemu niż kolor króla
            // i ruch jest możliwy dla tego pionka na miejsce króla to zwróć true
            pieceColor = checkPieceColor(checkPieceAtPosition(i,j));
            if(oppKingsColor == pieceColor){
                if(isMoveValid(i,j,whatPiece_row,whatPiece_column)){
                    addPiece(currentpiece,whatPiece_row,whatPiece_column);
                    return true;
                };
        }
    }
    }
    //removePiece(whatPiece_row,whatPiece_column);
    addPiece(currentpiece,whatPiece_row,whatPiece_column);

    return false;
}

bool ChessGame::checkMate(char piece)
{
    if((white->getHasCheck() == false) && (black->getHasCheck() == false)){
        return false;
    }else{
        char kingColor = checkPieceColor(piece);
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
}}

bool ChessGame::doublePawnMove(int whatPiece_row, int whatPiece_column, int putWhere_row, int putWhere_column)
{
    char color = checkPieceColor(checkPieceAtPosition(whatPiece_row,whatPiece_column));
    if(whatPiece_column != putWhere_column){
        return false;
    };
    if(color == WHITE_COLOR){
        if((whatPiece_row != 6) || (putWhere_row != 4)){
            return false;
        }else if((EMPTY !=checkPieceAtPosition(putWhere_row,putWhere_column)) || (EMPTY !=checkPieceAtPosition(putWhere_row+1,putWhere_column))){
            return false;
        }else{
            return true;
        };
    }else{
        if((whatPiece_row != 1) || (putWhere_row != 3)){
            return false;
        }else if((EMPTY !=checkPieceAtPosition(putWhere_row,putWhere_column)) || (EMPTY !=checkPieceAtPosition(putWhere_row-1,putWhere_column))){
            return false;
        }else{
            return true;
        };
    };
    return false;
}



//bool ChessGame::isEPMove(char pieceColor, int whatPiece_row, int putWhere_row)
//{
//    if (((pieceColor == BLACK_COLOR) && (whatPiece_row == 4)  && (putWhere_row == 5))
//            || ((pieceColor == WHITE_COLOR) && (whatPiece_row == 3)  && (putWhere_row == 2))){
//        if(toupper(checkLastMove().figure) == 'P' && (abs(checkLastMove().moveFrom_row - checkLastMove().moveTo_row) == 2)){
//            return true;
//        };
//    }return false;
//}

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
    char wherePieceColor = checkPieceColor(checkPieceAtPosition(putWhere_row,putWhere_column));
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


char ChessGame::checkPieceAtPosition(int row, int column)
{
    return board[row][column];
}

char ChessGame::checkPieceColor(char piece)
{
    if (isupper(piece)){
        return white ->getColor();
    }else if(islower(piece)){
        return black -> getColor();
    }
    return EMPTY;
}

void ChessGame::setChecktoFalse()
{
    white ->setHasCheck(false);
    black ->setHasCheck(false);
}
// funkcja zwraca false gdy ruch nie jest możliwy
bool ChessGame::isMoveValid(int whatPiece_row,int whatPiece_column, int putWhere_row, int putWhere_column)
{
    // sprawdzenie czy na wybranym polu jest pionek
    char piece = checkPieceAtPosition(whatPiece_row,whatPiece_column);
    char wherePiece = checkPieceAtPosition(putWhere_row,putWhere_column);

    char pieceColor = checkPieceColor(piece);
    if (piece==EMPTY){
        return false;
    }
    // sprawdzenie czy poruszany pionek należy do gracza który ma ruch
    // czyli Turn is white poruszany pionek powinien być biały
    if (pieceColor!= getWhosTurn()){
        return false;
    }
    // sprawdzenie czy na wybranym polu docelowym nie ma pionka o tym samym kolorze
    if(checkPieceColor(wherePiece)==pieceColor){
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
            if(doublePawnMove(whatPiece_row,whatPiece_column,putWhere_row,putWhere_column)){
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
            // sprawdzenie czy na drodze nie ma innych pionków
            int minrow = min(putWhere_row, whatPiece_row);
            //  int maxrow = max(putWhere_row, whatPiece_row);
            int mincol = min(putWhere_column, whatPiece_column);
            int maxcol = max(putWhere_column, whatPiece_column);
            for(int i = mincol+1;i<maxcol;i ++){
                minrow++;
                if(EMPTY !=checkPieceAtPosition(minrow,i)){
                    return false;
                };
            }
            return true;
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
            //int minrow = min(putWhere_row, whatPiece_row);
            //int mincol = min(putWhere_column, whatPiece_column);
            //int maxcol = max(putWhere_column, whatPiece_column);
            // sprawdzenie czy na drodze nie ma innych pionków
            if((whatPiece_column<putWhere_column) && (whatPiece_row<putWhere_row)){
                for(int i = whatPiece_row+1;i<putWhere_row;i++){
                    whatPiece_column++;
                    if(EMPTY !=checkPieceAtPosition(i,whatPiece_column)){
                        return false;
                    };
                }
                return true;
            }else if((whatPiece_column>putWhere_column) && (whatPiece_row<putWhere_row)){
                 for(int i = whatPiece_row+1;i<putWhere_row;i++){
                    whatPiece_column--;
                    if(EMPTY !=checkPieceAtPosition(i,whatPiece_column)){
                        return false;
                    };
                }
                return true;
            }else if((whatPiece_column<putWhere_column) && (whatPiece_row>putWhere_row)){
                for(int i = whatPiece_row-1;i>putWhere_row;i--){
                    whatPiece_column++;
                    if(EMPTY !=checkPieceAtPosition(i,whatPiece_column)){
                        return false;
                    };
                }
                return true;
            }else if((whatPiece_column>putWhere_column) && (whatPiece_row>putWhere_row)){
                for(int i = whatPiece_row-1;i>putWhere_row;i--){
                    whatPiece_column--;
                    if(EMPTY !=checkPieceAtPosition(i,whatPiece_column)){
                        return false;
                    };
                }
                return true;
            }

        };
    }
        break;
        // czy to król (king)
    case 'K':
    {
        if(isKingsMoveValid(pieceColor,putWhere_row,putWhere_column)){
            return true;
        }
        else if(isCastleMove(pieceColor,whatPiece_row, whatPiece_column,putWhere_row,putWhere_column)){
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
bool ChessGame::isCastleMove(char pieceColor, int whatPiece_row, int whatPiece_column, int putWhere_row, int putWhere_column)
{
    if((pieceColor == BLACK_COLOR) && (whatPiece_row == 0) && (whatPiece_column == 4) && (putWhere_row == 0) && (white ->getHasCheck())){
        // roszada biała w lewo
        if (putWhere_column == 2){
            if((checkPieceAtPosition(0,1) == EMPTY) && (checkPieceAtPosition(0,2) == EMPTY) &&
                    (checkPieceAtPosition(0,3) == EMPTY) && (white ->getCastleParam().king_l == true)){
                return true;
            };
            // roszada biała w prawo
        }else if(putWhere_column == 6){
            if((checkPieceAtPosition(0,5) == EMPTY) && (checkPieceAtPosition(0,6) == EMPTY) && (white ->getCastleParam().king_r == true)){
                return true;
            };
        }
    }else if((pieceColor == WHITE_COLOR) && (whatPiece_row == 7) && (whatPiece_column == 4) && (putWhere_row == 7) && (white ->getHasCheck())){
        // roszada czarna w lewo
        if (putWhere_column == 2){
            if((checkPieceAtPosition(7,1) == EMPTY) && (checkPieceAtPosition(7,2) == EMPTY) &&
                    (checkPieceAtPosition(7,3) == EMPTY) && (black ->getCastleParam().king_l == true)){
                return true;
            };
            // roszada czarna w prawo
        }else if(putWhere_column == 6){
            if((checkPieceAtPosition(7,5) == EMPTY) && (checkPieceAtPosition(7,6) == EMPTY) && (black ->getCastleParam().king_r == true)){
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

void ChessGame::resetMove(ChessGame::Move move)
{
    move.figure = EMPTY;
    move.is_enPassant = false;
    move.moveFrom_column = -1;
    move.moveFrom_row = -1;
    move.moveTo_column = -1;
    move.moveTo_row = -1;
}

vector<int>* ChessGame::returnAvailableFields(int whatPiece_row, int whatPiece_column)
{
    std::vector< int > *availableFields = new std::vector<int>;
    //rows
    for(int i = 0; i<=7; i++){
        //columns
        for(int j=0;j<=7;j++){
            if(isMoveValid(whatPiece_row, whatPiece_column,i,j)){
                availableFields->push_back(i);
                availableFields->push_back(j);
            }
        }
    }
    return availableFields;
}


ChessGame::Move ChessGame::checkLastMove()
{
    return LastMove;
}

void ChessGame::movePiece(int whatPiece_row, int whatPiece_column, int putWhere_row, int putWhere_column)
{

    char piece = checkPieceAtPosition(whatPiece_row,whatPiece_column);
    char upperPiece = toupper(piece);
    char wherePiece = checkPieceAtPosition(putWhere_row,putWhere_column);
    char upperWherePiece = toupper(wherePiece);
    char pieceColor = checkPieceColor(piece);

    // sprawdzenie czy na docelowym polu nie ma króla
    // usunięcie pionka z pola
    if(!(upperWherePiece == 'K')){
        board[whatPiece_row][whatPiece_column] = EMPTY;
    };

    // jeżeli wieża będzie zbita to usuwamy możliwość roszady
    if(upperWherePiece == 'R'){
        saveCastlePossib(putWhere_row,putWhere_column);
    }
    // bicie w przelocie
//    if(LastMove.is_enPassant && isEPMove(pieceColor,whatPiece_row,putWhere_row)){
//        // jeżeli tak to usuwamy pionek co ostatnio zmienił pozycje
//        board[LastMove.moveTo_row][LastMove.moveTo_column] = EMPTY;
//        // dodajemy go do usuniętych pionków
//        addToCaptured(checkLastMove().figure);
//    };
    // roszada - przestawienie wieży
    if(isCastleMove(pieceColor,whatPiece_row, whatPiece_column,putWhere_row,putWhere_column)){
        if((putWhere_row == 0) &&  (putWhere_column == 2)){
           board[0][0] = EMPTY;
           board[0][3] = 'r';
        }else if((putWhere_row == 0) &&  (putWhere_column == 6)){
            board[0][7] = EMPTY;
            board[0][5] = 'r';
        }else if((putWhere_row == 7) &&  (putWhere_column == 2)){
            board[7][0] = EMPTY;
            board[7][3] = 'R';
        }else if((putWhere_row == 7) &&  (putWhere_column == 6)){
            board[7][7] = EMPTY;
            board[7][5] = 'R';
        };
    };
    // zapisanie last move musi odbyć się po sprawdzeniu zmiennej is_enPassant
    saveLastMove(piece,whatPiece_row,whatPiece_column,putWhere_row,putWhere_column);
    // jeżeli poruszyła się wieża - zapisujemy by zapobiec roszadzie
    switch (upperPiece){
    case 'R':{
        saveCastlePossib(whatPiece_row,whatPiece_column);
    }
    case 'K': {
        saveNewKingsPosition(piece, putWhere_row, putWhere_column);
    }
    }

    // jeżeli był jakiś pionek na miejscu docelowym to trzeba dodać go do listy zbitych pionków
    if(wherePiece != EMPTY){
        addToCaptured(wherePiece);
    };

    // przestawienie pionka
    board[putWhere_row][putWhere_column] = piece;

    // sprawdzenie czy nia ma szacha
    char checkPiece = checkCheck();
    if(checkPiece!=EMPTY){
        if(checkMate(checkPiece)){
            cout<<"szach mat";
        }
    }
    // zmiana gracza
    changeTurn();
}

void ChessGame::addToCaptured(char piece)
{
    char pieceColor = checkPieceColor(piece);

    if(pieceColor == white->getColor()){
        white -> addToCaptured(piece);
    }else if(pieceColor == black->getColor()){
        black -> addToCaptured(piece);
    };
}



ChessGame::ChessGame()
{
    white = new Player(WHITE_COLOR);
    black = new Player(BLACK_COLOR);

    whosTurn = white ->getColor();
    resetMove(LastMove);
    resetMove(ThisMove);

    black ->setKingPosition(0,4);
    white ->setKingPosition(7,4);

}

void ChessGame::initializeBoard()
{
    /* using memcpy to copy structure: */
     memcpy ( board, first_board, sizeof(char)* 8*8);
}
