#include<fstream>
#include <iostream>
#include <ctime>
#include <pthread.h>
#include<map>
#include<vector>
#include<windows.h>
#include"Battle.h"
using namespace std;
int rows; 
int elements;
int maxShips; //Cantidad maxima de naves
int victoria=0;
int victoriaRival = 0;
int turno = 1;
char matrixrival[15][15];
char matrixfinal[15][15];
char matrix[15][15];
void asignalos(match partida)
{
    rows = partida.getRows();
    elements = partida.getElements();
    maxShips = partida.getMaxShips();
}
void clear()
{
    for(int i = 0;i<rows;i++)
    {
        for(int j= 0;j<elements;j++)
        {
            matrixrival[i][j] = matrixfinal[i][j] = '.';
        }
    }
    for(int i = 0;i<rows;i++)
    {
        for(int j= 0;j<elements;j++)
        {
            matrix[i][j] = '.';
        }
    }
}

void show()
{
    cout<<" ";
    for(int k = 0;k<=rows-1;k++)
    {
        
        cout<<" "<<k;
    }
    cout<<endl;
    
    for(int i = 0;i<rows;i++)
    {
        cout<<i<<" ";
        for(int j= 0;j<elements;j++)
        {
            cout<<matrixrival[i][j] << " ";
        }
        cout<<endl;
    }

    int contador1 = rows +1 ;
    while(contador1>0)
    {
        cout<<"--";
        contador1--;
    }
    cout<<endl;
    
    cout<<" ";
    for(int k = 0;k<=rows-1;k++)
    {
        cout<<" "<<k;
    }
    cout<<endl;

    for(int i = 0;i<rows;i++)
    {
        cout<<i<<" ";
        for(int j= 0;j<elements;j++)
        {
            cout<<matrix[i][j]<< " ";
        }
        cout<<endl;
    }
}
void showGame()
{
    cout<<" ";
    for(int k = 0;k<=rows-1;k++)
    {
        cout<<" "<<k;
    }
    cout<<endl;
    
    for(int i = 0;i<rows;i++)
    {
        cout<<i<<" ";
        for(int j= 0;j<elements;j++)
        {
            cout<<matrixfinal[i][j]<< " ";
        }
        cout<<endl;
    }

    int contador1 = rows + 1;
    while(contador1>0)
    {
        cout<<"--";
        contador1--;
    }
    cout<<endl;

    cout<<" ";
    for(int k = 0;k<=rows-1;k++)//Eje x
    {
        cout<<" "<<k;
    }
    cout<<endl;

    
    for(int i = 0;i<rows;i++)
    {
        cout<<i<<" ";
        for(int j= 0;j<elements;j++)
        {
            cout<<matrix[i][j] << " ";
        }
        cout<<endl;
    }
}



int NumberOfShipsRival()
{
    int c= 0;
     for(int i = 0;i<rows;i++)
    {
        for(int j= 0;j<elements;j++)
        {
            if(matrixfinal[i][j] == 's')
            {
                c++;
            }
        }
    }
    return c;
}
int NumberOfShips()
{
    int c= 0;
     for(int i = 0;i<rows;i++)
    {
        for(int j= 0;j<elements;j++)
        {
            if(matrix[i][j] == 's')
            {
                c++;
            }
        }
    }
    return c;
}

void SetShipsRival()
{
    int s = 0; //BArcos puestos
    while(s<maxShips)
    {
        int x = rand() % rows;
        int y = rand() % elements;
        if(matrixfinal[x][y] != 's')
        {
            s++;
            matrixfinal[x][y] = 's';
        }
    }
}
void SetShips(string name)
{
    
        ifstream archivoLeer;
        string text;
        int x = 0;
        int y = 0;
        int s = 0;
            

        archivoLeer.open(name, ios::in);  //abrir archivo en modo lectura
        if(archivoLeer.fail())
        {
            cout<<"The file can not be open or doesn't exist, try again"<<endl<<"Closing program...";
            exit(0); //exit(1);
        } 
        while(!archivoLeer.eof() && s<maxShips) 
        { 
           

            archivoLeer>>x;
            archivoLeer>>y;
            if(matrix[x][y] != 's')
            {
                s++;
                matrix[x][y] = 's';
            }
            /*else if(matrix[x][y] == 's')
            {
                cout<<"There is already a ship in the coordenates ("<<x<<","<<y<<")\n Do you want to continue anyway? (y,n)"<<endl;
                char aux2 = 0;
                cin>>aux2;
                if(aux2 == 'n' || aux2 == 'N')
                {
                    cout<<"Closing game...";
                    exit(0);
                }
            }*/
        }
             
        
    
    if(s < maxShips)
    {
        cout<<"You can use "<<maxShips<<" ships but you only have "<<s<<" ships, do you want to continue? (y,n)";
        char aux = 0;
        cin>>aux;
        if(aux == 'n' || aux == 'N')
        {
            cout<<"Closing game...";
            exit(0);
        }
        
    }
    archivoLeer.close();
    
   
}

//Titulos Leer archivos
void Titulos(string name)
{
    ifstream archivoLeer;
    string text;
    archivoLeer.open(name, ios::in);  //abrir archivo en modo lectura
    if(archivoLeer.fail())
    {
        cout<<"The file can not be open or doesn't exist, try again"<<endl<<"Closing program...";
        exit(0); //exit(1);
    } 
    while(!archivoLeer.eof()) 
    {
        getline(archivoLeer,text);
        cout<<text<<endl;
    }
    archivoLeer.close();
}

//Vectores
vector<int> Hits;
vector<int> HitsRival;
void hits(int x)
{
    Hits.push_back(x);//Turnos en los que hubo hits
}
void hitsRival(int x)
{
    HitsRival.push_back(x);
}
void mostrarHits()
{
    vector<int>::iterator it = Hits.begin();
    for(auto it = Hits.begin();it != Hits.end(); it++)
    {
        cout<<"You hitted the enemy on turn: "<<*it<<endl;
    }
}
void mostrarHitsRival()
{
    vector<int>::iterator it = HitsRival.begin();
    for(auto it = HitsRival.begin();it != HitsRival.end(); it++)
    {
        cout<<"You were hitted by the enemy on turn:"<<*it<<endl;
    }
}


//maps
map<int,int> jugadas;
map<int,int> jugadasRival;
void mapitas(int x,int y)
{
    jugadas.insert(make_pair(x,y));
}
void mapitasRival(int x,int y)
{
    jugadasRival.insert(make_pair(x,y));
}
void mostrarMapitas()
{
    for(map<int,int>::iterator it = jugadas.begin(); it != jugadas.end(); it++)
    {
        pair<int,int> bbbb = *it;
        int i=1;
        cout<<" ( "<<bbbb.first << " , "<<bbbb.second <<" )"<<endl;
        i++;
    }
}
void mostrarMapitasRival()
{
    for(map<int,int>::iterator it = jugadasRival.begin(); it != jugadasRival.end(); it++)
    {
        pair<int,int> bbbb = *it;
        int i=1;
        cout<<" ( "<<bbbb.first << " , "<<bbbb.second <<" )"<<endl;
        i++;
    }
}


bool AttackRival()//No lo borres
{
    int x = rand() % rows;
    int y = rand() % elements;
    mapitasRival(x,y);
    if(matrix[x][y] == 's')
    {
        matrix[x][y] = 'H';
        cout<<endl<<"He got you :("<<endl;
        hitsRival(turno);
        victoriaRival++;
        return true;
    }
    else if(matrix[x][y] != 's')
    {
        matrix[x][y] = 'x';
        cout<<endl<<"No allied ship sunk :)"<<endl;
        return false;
    }
}

//Tu turno
bool Attack(int x,int y)
{
    mapitas(x,y);

    if(matrixfinal[x][y] == 's')
    {
        matrixfinal[x][y] = matrixrival[x][y] =  'H';
        hits(turno);
        turno++;
        victoria++;
        return true;
    }
    else if(matrixfinal[x][y] != 's')
    {
        matrixrival[x][y] = matrixfinal[x][y] =  'x';
        turno++;
    }
    return false;
}

//Te dice quien fue el ganador.
void winner(int you, int pc)
{
    if(you > pc)
    {
        cout<<"Congratulations!"<<endl<<"You are the winner!!"<<endl;
    }
    else if(you < pc)
    {
        cout<<"You lost, but you can always try again :)"<<endl;
    }
    else if(you == pc)
    {
        cout<<"The game was tied"<<endl;
    }
}
bool ciclo = true;//Condicion para que acabe el temporizador
//Temporizador (Hilo)
void *tempo(void *arg)
{
    int segundo = 0;
    int minutos = 0;
    int horas = 0;
    
    while(ciclo)
    {
        Sleep(1000);
        segundo++;
        if(segundo == 60)
        {
            minutos++;
            segundo =0;
        }
        if(minutos == 60)
        {
            horas++;
            minutos=0;
        }
    }
    cout<<"Time:"<<endl<<horas<<" hours."<<endl<<minutos<<" minutes."<<endl<<segundo<<" seconds."<<endl;
    //cout<<"Tiempo de juego: "<<horas<<":"<<minutos<<":"<<segundo;
    pthread_exit(NULL);
}











