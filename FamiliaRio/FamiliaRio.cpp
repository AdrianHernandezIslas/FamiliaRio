// FamiliaRio.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <vector>
#include <conio.h>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

vector<bool> familia;
vector<string> alias = {"Papa","Mama","Hijo1","Hijo2","Hija1","Hija2","Policia","Ladron"};
stack<vector<bool>> pila;
int profundidadMaxima;
/*
0 Papa
1 Mama
2 Hijo1
3 Hijo2
4 Hija1
5 Hija2
6 Policia 
7 Ladron
*/

void imprimirFamilia(vector<bool> familia) {
	for (size_t i = 0; i < familia.size(); i++)
	{
		if (familia[i]) {
			cout << "\t\t" << alias[i] << endl;
		}
		else {
			cout << alias[i] << endl;
		}
	}
}

void imprimirPila(stack<vector<bool>> pila) {
	while (!pila.empty())
	{
		imprimirFamilia(pila.top());
		pila.pop();
		cout << "___________________________________" << endl;
	}
}

vector <bool> moverFamilia(vector <bool> familia, int indexO, int indexD) {
	if (indexD != -1) {
		if (!familia[indexO]) {
			familia[indexO] = 1;
			familia[indexD] = 1;
		}
		else {
			familia[indexO] = 0;
			familia[indexD] = 0;
		}
	}
	else {
		if (!familia[indexO]) {
			familia[indexO] = 1;
		}
		else {
			familia[indexO] = 0;
		}
	}
	return familia;
}

bool cambiaOrigen(bool origen) {
	if (origen) {
		return origen = 0;
	}
	else {
		return origen = 1;
	}
}

bool movimientoValido(vector<bool> familia) {
	if ((familia[0] != familia[1]) && (familia[0] == familia[2] || familia[0] == familia[3])) {
		return false;
	}

	if ((familia[0] != familia[1]) && (familia[1] == familia[4] || familia[1] == familia[5])) {
		return false;
	}

	if ((familia[7] != familia[6]) && (familia[7] == familia[0] || familia[7] == familia[1]
										|| familia[7] == familia[2] || familia[7] == familia[3]
										|| familia[7] == familia[4] || familia[7] == familia[5]
										|| familia[7] == familia[6])) {
		return false;
	}
	

	return true;
}

bool pasaronTodos(vector<bool> personas) {
	for (size_t i = 0; i < personas.size(); i++)
	{
		if (!personas[i]) {
			return false;
		}
	}

	return true;
}

bool busqueda(vector<bool> familia,int profundidad, bool origen) {
	pila.push(familia);
	if (movimientoValido(familia)) {
		if (pasaronTodos(familia)) {
			return true;
		}
		else if (profundidad <= profundidadMaxima) {
			profundidad++;
			for (int i = 4 ; i < 8 ; i++) {
				if (familia[i] == origen) {
					for (int j = 0; j < 9; i++) {
						if (j == 8) {
							if (busqueda(moverFamilia(familia,i,-1),profundidad,cambiaOrigen(origen))) {
								return true;
							}
							else if (i != j) {
								if (familia[j] == origen) {
									if (busqueda(moverFamilia(familia, i,j), profundidad, cambiaOrigen(origen))) {
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	pila.pop();
	return false;
}

int main()
{

	vector<bool> miembros = {0,0,0,0,0,0,1,1};
	profundidadMaxima = 17;
	imprimirFamilia(miembros);
	cout << "Buscando Solucion...";
	if (busqueda(miembros,0,false)) {
		cout << "Solucion encontrada" << endl;
		imprimirPila(pila);
	}
	else {
		cout << "Sin solucion Encontrada" << endl;
	}
	system("pause");
    return 0;
}

