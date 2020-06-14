#define _USE_MATH_DEFINES
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include <cmath>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>     /* strtof */
#include <iomanip>

#include "Lista.h"
#include "Figura.h"

using namespace std;

int main(int argc, char** argv) {

    bool on=true;
    Lista listaFiguras; // Lista donde voy a guardar las figuras.
    CrearLista(listaFiguras);   //constructor de la lista

    ifstream archivo_figuras;
    string archivo = "archtest.txt";
    archivo_figuras.open(archivo, ios::in);   // Abro el archivo (solo leida)

    CargarDesdeArchivo(archivo_figuras, listaFiguras);
    insertarArea(listaFiguras);

    while(on){
        int opcion;
        cout << "------------------------------------BIENVENIDO------------------------------------";
        cout << "\n\nSeleccione la operacion: \n\t1 - Imprimir la lista de todas las Figuras" << endl;
        cout << "\t2 - Cantidad de plastico total del lote"<<endl;
        cout << "\t3 - Totales por Figura" << endl;
        cout << "\t4 - Totales por Figura-Color" << endl;
        cout << "\t5 - Por cada color, mostrar el orden de produccion"<< endl;
        cout << "\t6 - Figuras ordenadas por area (descendente)" << endl;
        cout << "\t7 - Figuras ordenadas por area (ascendente)" << endl;
        cout << "\t0 - Salir" << endl;
        cin >> opcion;

        switch(opcion){
            case 1:{
                cout << "Lista de Figuras: " << endl;
                imprimirFiguras(listaFiguras);  //Imprime la lista y calcula el area de las figuras.
                break;}
            case 2:{
                cout << "Area Total: " << calcularAreaTotal(listaFiguras) << " cm^2" <<endl;
                break;}
            case 3:{
                cout << "Totales por Figura: " << endl;
                totalPorFigura(listaFiguras);
                break;}
            case 4:{
                cout << "Totales por Figura-Color: " << endl;
                totalPorFiguraColor(listaFiguras);
                break;}
            case 5:{
                cout << "Por cada color, las figuras en orden de produccion:" << endl;
                colorOrdenFiguras(listaFiguras);
                break;}
            case 6:{
                cout <<"Listado de figuras ordenadas por su area (orden descendente)" << endl;
                ordenDescendenteArea(archivo);
                archivo_figuras.close();
                break;}
            case 7:{
                cout <<"Listado de figuras ordenadas por su area (orden ascendente)" << endl;
                ordenAscendenteArea(archivo);
                archivo_figuras.close();
                break;}
            case 0:{
                on=false;
                break;}
            default:{
                cout <<"Error: opcion incorrecta, por favor vuelva a seleccionar una operacion"<<endl;
                break;
            }
        }
        system("pause");
        system("cls");
    }

    return 0;
}