#include "Figura.h"
#include "Lista.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/* Implementacion de primitivas */

using namespace std;

void crearFigura(PtrFigura& mi_figura) {
    mi_figura = new Figura;

    /* figura->forma = "";
     figura->color = "";
     figura->valor1 = NULL;
     figura->valor2 = NULL;*/

}

string getForma(PtrFigura& figura) {
    return figura->forma;
}

void setForma(PtrFigura& figura, string forma) {
    figura->forma = forma;
}

string getColor(PtrFigura& figura) {
    return figura->color;
}

void setColor(PtrFigura& figura, string color) {
    figura->color = color;
}


float getValor1(PtrFigura& figura) {
    return figura->valor1;
}

void setValor1(PtrFigura& figura, float valor1) {
    figura->valor1 = valor1;
}


float getValor2(PtrFigura& figura) {
    return figura->valor2;
}

void setValor2(PtrFigura& figura, float valor2) {
    figura->valor2 = valor2;
}


void CargarDesdeArchivo(ifstream& Archivo, Lista& lista)
{
    string linea, Dato2, Dato1, Dato3, Dato4;

    while (!Archivo.eof())
    {
        string Dato1 = Dato3 = Dato2 = Dato4 = "";
        float a, b = 0.0;
        int separador = 0;
        string aux;
        getline(Archivo, linea);
        for (int i = 0; i < linea.size(); i++)
        {
            if (linea.at(i) == ' ')
                separador++;
            else
            {
                if (separador == 0)
                    Dato1 = Dato1 + linea.at(i);
                if (separador == 1)
                    Dato2 = Dato2 + linea.at(i);
                if (separador == 2)
                    aux = linea.at(i);
                Dato3.append(aux);
                aux = "";
            }
            if (linea.at(i) == ';') {
                i++;
                while (linea.size() > i)
                {
                    aux = linea.at(i);
                    Dato4.append(aux);
                    i++;
                }
            }
        }
        a = convertirStringAFloat(Dato3);
if (Dato4.size() > 0) {
    b = convertirStringAFloat(Dato4);
}
CargarListaFiguras(lista, Dato1, Dato2, a, b);
    }
}

/*Cargo uno a uno los valores mediante los Set */
void CargarListaFiguras(Lista& listaFiguras, string forma, string color, float  valor1, float valor2)
{
    PtrFigura nuevo;
    crearFigura(nuevo);
    setForma(nuevo, forma);
    setColor(nuevo, color);
    setValor1(nuevo, valor1);
    if (valor2 != 0) {
        setValor2(nuevo, valor2);
    }
    else {
        setValor2(nuevo, 0);
    }
    AdicionarFinal(listaFiguras, nuevo);
    /* delete (nuevo);*/
}

float convertirStringAFloat(string str) {
    float number = 0;
    int coma = str.find(',');
    if (coma == -1) {
        istringstream iss(str);
        iss >> number;
        return number;
    }
    string punto = ".";
    str.replace(coma, 1, punto);
    istringstream iss(str);
    iss >> number;
    return number;
}

/*Recorro la lista e imprimo */
void recorrerLista(Lista& listaFiguras) {
    PtrNodoLista cursor = listaFiguras.Primero;
    float areaTotal = 0;
    while (cursor != Fin_Lista()) {
        cout << ((Figura*)cursor->DatoLista)->forma << " ";
        cout << ((Figura*)cursor->DatoLista)->color << " ";
        cout << ((Figura*)cursor->DatoLista)->valor1 << "; ";
        if (((Figura*)cursor->DatoLista)->valor2 > 0) {
            cout << ((Figura*)cursor->DatoLista)->valor2;
        }
        cout << endl;
        float areaFiguraActual = calcularArea(((Figura*)cursor->DatoLista)->forma, ((Figura*)cursor->DatoLista)->valor1, ((Figura*)cursor->DatoLista)->valor2);
        ((Figura*)cursor->DatoLista)->area = areaFiguraActual;
        cout << "Area: " << areaFiguraActual << endl;
        cursor = cursor->SgteDL;
    }
    delete (cursor);
}

float calcularArea(string nombre, float valor1, float valor2) {

    float area = 0;

    if (nombre.compare("circulo") == false) {
        area = valor1 * 3.14;
    }
    if (nombre.compare("cubo") == false) {
        area = valor1 * valor1;
    }
    if (nombre.compare("triangulo") == false) {
        area = (valor1 * valor2) / 2;
    }
    if (nombre.compare("rectangulo") == false) {
        area = valor1 * valor2;
    }
    if (nombre.compare("cilindro") == false) {
        area = (valor1 * 3.14) * valor2;
    }
    return area;
}

/* calcula el total de plastico utilizado */
float calcularAreaTotal(Lista& listaFiguras) {
    float areaTotal = 0;
    PtrNodoLista cursor = listaFiguras.Primero;
    while (cursor != Fin_Lista()) {
        areaTotal = areaTotal + ((Figura*)cursor->DatoLista)->area;
        cursor = cursor->SgteDL;
    }
    delete (cursor);
    return areaTotal;
}

/* Busca los colores que hay y los coloca en un array sin repetir */
void coloresEnListaFiguras(Lista& listaFiguras, string colores[10]) {
    PtrNodoLista cursor = listaFiguras.Primero;
    string colorActual;
    int i = 0;

    while (cursor != Fin_Lista()) {
        colorActual = ((Figura*)cursor->DatoLista)->color;
        i = 0;
        for (i = 0; i <= 9; i++) {
            if (colorActual == colores[i]) {
                i = 10;
            } else {
                if (colores[i] == "") {
                    colores[i] = colorActual;
                    i = 10;
                }
            }
        }
        cursor = cursor->SgteDL;
    }

    cursor = nullptr;
    delete (cursor);
}

/* Calcula el total de las areas por figuras */
void totalPorFigura(Lista& listaFiguras) {
    PtrNodoLista cursor = listaFiguras.Primero;
    string figuras[5] = { "circulo", "cilindro", "cubo", "triangulo", "rectangulo" }; //Array con las figuras.
    float sumaAreas = 0;

    for (int i = 0; i <= 4; i++) { //Figuras
        cout << "\tDetalle: "<< figuras[i] << endl;
        while (cursor != Fin_Lista()) {
            if (((Figura*)cursor->DatoLista)->forma == figuras[i]) {
                cout << "\t  " << figuras[i] << ", " << ((Figura*)cursor->DatoLista)->color <<", "<<((Figura*)cursor->DatoLista)->area << endl;
                sumaAreas = sumaAreas + ((Figura*)cursor->DatoLista)->area;
            }
            cursor = cursor->SgteDL;
        }
        cout << "\t" << "    TOTAL: " << sumaAreas << " cm^2." << endl << endl;
        sumaAreas = 0;
        cursor = listaFiguras.Primero;
    }
    //Hay que ponerlo en null primero pq cuando lo deleteas sin esto creo que comprometes a la lista.
    cursor = nullptr;
    delete (cursor);
}

/* Calcula el total de las areas por figura-color */
void totalPorFiguraColor(Lista& listaFiguras) {
    PtrNodoLista cursor = listaFiguras.Primero;
    string figuras[5] = { "circulo", "cilindro", "cubo", "triangulo", "rectangulo" }; //Array con las figuras.
    string colores[10];
    coloresEnListaFiguras(listaFiguras, colores);
    float sumaAreas = 0;

    for (int j = 0; j <= 9; j++) { //Colores
        if (colores[j] != "") { //Si la posicion no esta vacia.
            cout << "----------------- Color " << colores[j] << " -----------------" << endl;
            for (int i = 0; i <= 4; i++) { //Figuras
                cout << "\tDetalle: " << figuras[i] << endl;
                while (cursor != Fin_Lista()) {
                    if (((Figura*)cursor->DatoLista)->forma == figuras[i] && ((Figura*)cursor->DatoLista)->color == colores[j]) {
                        cout << "\t~" << figuras[i] << ", " << ((Figura*)cursor->DatoLista)->color << ", " << ((Figura*)cursor->DatoLista)->area << endl;
                        sumaAreas = sumaAreas + ((Figura*)cursor->DatoLista)->area;
                    }
                    cursor = cursor->SgteDL;
                }
                cout << "\t" << "Total: " << sumaAreas << " cm^2." << endl << endl;
                sumaAreas = 0;
                cursor = listaFiguras.Primero;
            }

        }
        
    }
    //Hay que ponerlo en null primero pq cuando lo deleteas sin esto creo que comprometes a la lista.
    cursor = nullptr;
    delete (cursor);
}



/*
void guardarFiguraCompleja(string auxLinea, Lista &datos, Figura nuevaFigura){
    /* CON PUNTEROS
    stringstream ss(auxLinea); //No se muy bien como funciona todavia jejo

    //Obtengo los datos y los guardo donde corresponde

    getline(ss, nuevaFigura->forma, ' ' ); //Separo la forma
    getline(ss, nuevaFigura->color, ' ' ); //Separo los numeros

    string auxiliarStr;
    getline(ss, auxiliarStr, ';' ); //Separo los numeros
    float auxNumber = convertirStringAFloat(auxiliarStr);
    nuevaFigura->valor1 = auxNumber;

    getline(ss, auxiliarStr, ';' ); //Separo los numeros
    auxNumber = convertirStringAFloat(auxiliarStr);
    nuevaFigura->valor2 = auxNumber;

    adicionarFinal(datos,nuevaFigura); //Se guarda la figura al final de la lista
    /

    // CON GETS Y SETS

    stringstream ss(auxLinea); //No se muy bien como funciona todavia jejo

    //Obtengo los datos y los guardo donde corresponde
    string auxiliarStr;

    getline(ss, auxiliarStr, ' ' ); //Separo la forma
    setForma(nuevaFigura, auxiliarStr);
    getline(ss, auxiliarStr, ' ' ); //Separo los numeros
    setColor(nuevaFigura, auxiliarStr);

    getline(ss, auxiliarStr, ';' ); //Separo los numeros
    float auxNumber = convertirStringAFloat(auxiliarStr);
    setValor1(nuevaFigura,auxNumber);

    getline(ss, auxiliarStr, ';' ); //Separo los numeros
    auxNumber = convertirStringAFloat(auxiliarStr);
    setValor2(nuevaFigura,auxNumber);

    Figura* ptrFigura = &nuevaFigura;

    adicionarFinal(datos, ptrFigura); //Se guarda la figura al final de la lista
}
*/

