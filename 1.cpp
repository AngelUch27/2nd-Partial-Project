#include "myLib.h"
#include <iostream>
#include <ctime>

using namespace std;
int main()
{
    //Comentario pruebaaaaaaaaaaaaaaa
    pthread_t thread1;
    int pos1,pos2;
    int dificultad = 0;
    string fichero;
    
    
    char prompt;
    match partida(5,5,5);
    match partida2(10,10,10);
    match partida3(50,50,50); 
    cout<<"Welcome to Battleship"<<endl;
    cout<<"Please select difficult\n1. Easy.\n2. Medium.\n3.Hard."<<endl;
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
    while(1)
    {
        cout<<"Your turn..."<<endl;
        cout << "Please enter the coordinate of the attack(separated by a space): "; 
        cin >> pos1 >> pos2;
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
        pthread_create( &thread1, NULL, &functionC, NULL);//Hilos
        pthread_join(thread1,NULL);
        show();
        cout<<"Number of enemy ships left: "<<NumberOfShipsRival()<<endl<<"Number of allies: "<<NumberOfShips()<<endl<<"Do you want to continue?(y/n)"<<endl<<endl;
        cin>> prompt;
        if(prompt == 'n')
        {
            break;
        }

        
    }
    showGame();
    cout<<"Game over!" <<endl;
    winner(NumberOfShips(),NumberOfShipsRival());
   
}