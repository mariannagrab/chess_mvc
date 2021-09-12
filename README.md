# chess_mvc
Class List
Here are the classes, structs, unions and interfaces with brief descriptions:
*  *  Model:
*   CPlayer	Klasa Player Reprezentuje gracza w tym kolor jego pionków, ustawienie króla, zbite pionki przechowuje informację o szachu
*  CChessGame	Klasa ChessGame kieruje logiką gry tworzy instancje graczy, przechowuje tablicę [2D] z ustawieniem pionków zamodelowanych jako znaki char, sprawdza poprawność ruchów pionków na tablicy zmienia kolej gracza, wykonuje ruch zmieniając pozycję pionka w tablicy, sprawdza czy jest szach lub szach mat
*  *  View:
*   CBoard	Klasa Board, dziedzicząca po QWidget tworzy 64 obiekty BoardPiece w GUI wyświetla je jako planszę [8][8] odpowiada za walidację klikniecia na kwadrat orz ich podświetlanie oraz odznaczanie odbiera sygnał z przycisku przechowuje informacje o zaznaczonych polach
*   CBoardPiece	Klasa BoardPiece, dziedzicząca po QLabel tworzy kwadrat w GUI
*  CMainWindow	Klasa MainWindow dziedzicząca po QMainWindow odpowiada za stworzenie, wyświetlanie wszystkich elementów GUI, ich rozłożenie oraz update przy zmianie parametrów gry
*  *  Controller:
*   Kontroler gry przesyła informację z modelu do GUI odpowiada za rozpoczęcie gry oraz jej przebieg
![image](https://user-images.githubusercontent.com/80004072/132985959-d00aa501-b6e9-4de5-9898-7b92dbeef2b6.png)
![image](https://user-images.githubusercontent.com/80004072/132985971-452b0657-9295-497f-959f-528015a11460.png)
![image](https://user-images.githubusercontent.com/80004072/132986009-65518359-40ac-4233-99f7-49f48f496fda.png)
![szachmat2](https://user-images.githubusercontent.com/80004072/132985870-c5b02d39-125f-4289-adc8-60a0d30fdf79.PNG)

