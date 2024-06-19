#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() 
{
	string nombreArchivo;
	
	cout << "Ingrese el nombre del archivo de texto: ";
	cin >> nombreArchivo;
	
	
	ifstream archivo(nombreArchivo);
	
	
	if (!archivo.is_open()) 
	{
		cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << endl;
	}
	
	
	string linea;
	while (getline(archivo, linea)) 
	{
		cout << linea << endl;
	}
	
	
	archivo.close();
	
	return 0;
}
