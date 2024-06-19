#include <iostream>
#include <stdexcept> // proporciona acceso a las clases de excepción estandar

using namespace std;


int divide(int a, int b) 
{
    if (b == 0) 
    {
        throw runtime_error("Error: No se puede dividir por cero.");
    }
    return a / b;
}

int main() 
{
    int num1, num2;
    
    cout << "Ingrese el primer numero: ";
    cin >> num1;
    cout << "Ingrese el segundo numero: ";
    cin >> num2;
    
    try 
    {
        int resultado = divide(num1, num2);
        cout << "El resultado de la division es: " << resultado << endl;
    } 
    catch (const runtime_error& e) 
    {
        cerr << e.what() << endl;
    }



    return 0;
}
