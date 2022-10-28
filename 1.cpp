#include "myLib.h"
using namespace std;
int main()
{
    pthread_t thread2;
    int pos1,pos2;
    int dificultad = 0;
    string fichero;
    char prompt;
    match partida(5,5,5);
    match partida2(10,10,10);
    match partida3(15,15,15); 
    Titulos("Welcome.txt");
    cout<<"Please select difficult\n1. Easy.\n2. Medium.\n3. Hard."<<endl;
    cin>>dificultad;
    switch(dificultad)
    {
        case 1:
            asignalos(partida);
            break;
        case 2:
            asignalos(partida2);
            break;
        case 3:
            asignalos(partida3);          
            break;
        default:
            cout<<"Please select a number from 1 to 3";
            break;
    }
    srand(time(NULL));
    clear();
    SetShipsRival();
    cout<<"Enter the name of the file with the coordinates: ";
    cin>>fichero;
    SetShips(fichero);
    pthread_create(&thread2,NULL,&tempo,NULL);
    cout<<"Wait a moment please.";
    system("cls");
    while(1)
    {
        cout<<"Your turn..."<<endl;
        cout << "Please enter the coordinate of the attack(separated by a space): "; 
        cin >> pos1 >> pos2;
        while(pos1>rows-1 || pos2>rows-1)
        {
            cout<<"Please enter a coordenate between 0 - "<<rows-1<<endl;
            cin >> pos1 >> pos2;
        }
        if(Attack(pos1,pos2))
        {
            cout<<endl<<"You have sunk an enemy ship!!"<<endl;
        }
        else
        {
            cout<<endl<<"No ship at that position"<<endl;
        }
        show();
        cout<<"Number of enemy ships left: "<<NumberOfShipsRival()<<endl<<"Number of allies: "<<NumberOfShips()<<endl<<endl;
        cout<<"Enemy turn..."<<endl;
        AttackRival();
        show();
        cout<<"Number of enemy ships left: "<<NumberOfShipsRival()<<endl<<"Number of allies: "<<NumberOfShips()<<endl<<"Do you want to continue?(y/n)"<<endl<<endl;
        cin>> prompt;
        if(prompt == 'n')
        {
            break;
        }
        else if(victoria >= maxShips || victoriaRival >= maxShips)
        {
            break;
        }
    }
    showGame();
    Titulos("Gameover.txt");       
    winner(NumberOfShips(),NumberOfShipsRival());
    cout<<endl<<"Choose an option: "<<endl<<"1. Show moves and quit"<<endl<<"2. Quit game"<<endl;
    int opcion;
    cin>>opcion;
    int th;
    switch(opcion)
    {   
        case 1:
            cout<<"Your moves: "<<endl;
            mostrarMapitas();
            mostrarHits();
            cout<<"Enemy moves: "<<endl;
            mostrarMapitasRival();
            mostrarHitsRival();
            ciclo = false;
            pthread_join(thread2,(void**)&th);
            cout<<"Thanks for play";
            exit(0);
            break;
        case 2:
            ciclo = false;
            pthread_join(thread2,(void**)&th);
            cout<<"Thanks for play";
            exit(0);
            break;
    }
}