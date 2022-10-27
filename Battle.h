using namespace std;
int turno = 1;
class match
{
    protected:
        int filas;
        int columnas;
        int maximos;
    public:
        match(int,int,int);
        void MostrarDatos();//aqui solo las declaras
        
        int getRows();
        int getElements();
        int getMaxShips();
};
match::match (int _rows,int _elements,int _maxShips)
{
    filas = _rows;
    columnas = _elements;  
    maximos = _maxShips; 
}
int match::getRows()
{
    return filas;
}
int match::getElements()
{
    return columnas;
}
int match::getMaxShips()
{
    return maximos;
}



