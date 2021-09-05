#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include "controller.h"

//using namespace std;
//---------------------------------------------------------------------------------------
// Global variable
//---------------------------------------------------------------------------------------




// funkcja zwraca fałsz jeżeli input jest niewłaściwy pole nie istnieje lub nie ma pionka
//bool validateInputToMove(string input){
//    if(input.length() != 2)
//        return true;
//    char firstchar = toupper(input[0]);
//    char secondchar = input[1];

//    if(firstchar < 'A' || firstchar > 'H' )
//        return true;
//    if(secondchar < '1' || secondchar > '8' )
//        return true;

//    return false;
//}
//void movePiece(void)
//{
//    string inputpiece = "";
//    string inputwhere = "";


//    do{
//        cout << "Choose piece to move: ";
//        cin >> inputpiece;
//    }while(validateInputToMove(inputpiece));

//    do{
//        cout << "Choose where to move: ";
//        cin >> inputwhere;
//    }while(validateInputToMove(inputwhere));

//    // Convert column from ['A'-'H'] to [0x00-0x07]
//    int inputpiece1 = toupper(inputpiece[0]) - 'A';
//    // Convert row from ['1'-'8'] to [0x00-0x07]
//    int inputpiece2  = inputpiece[1]  - '1';
//    int  inputwhere1 = toupper(inputwhere[0]) - 'A';
//    int inputwhere2  = inputwhere[1]  - '1';

//    if(game -> isMoveValid(inputpiece2,inputpiece1,inputwhere2,inputwhere1)){
//        game -> movePiece(inputpiece2,inputpiece1,inputwhere2,inputwhere1);
//    }


//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    start();

    return a.exec();
}
//    bool isGameOn = true;
//    while (isGameOn){
//        string inputStr = "";

//        printMenu();
//        // Get input from user
//        cout << "Type here: ";
//        //cin: It is an object of istream class and tells the function about the stream from where to read the input from.
//        //input: It is a string object, the input is stored in this object after being read from the stream.
//        getline(cin, inputStr);

//        switch(tolower(inputStr[0]))
//        {
//        case 'n':

//           newGame();
//           printTurn(*game);
//           printBoard(*game);
//           break;

//        case 'm':
//            printTurn(*game);
//            movePiece();
//            printBoard(*game);
//            break;

//        case 'q':
//            isGameOn = false;
//            quitGame();
//            break;

//        default:
//                    cout<<"coś innego";
//            break;

//        }

//    }
//    cout << "Koniec gry" << endl;
//    return 0;

