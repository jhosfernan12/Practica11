#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Persona 
{
    private:
        string nombre;
        int edad;
        string direccion;

    public:
   
        Persona() {}


        Persona(string nom, int ed, string dir) : nombre(nom), edad(ed), direccion(dir) {}


        void setNombre(string nom)  // Setters
        { 
            nombre = nom; 
        }
        void setEdad(int ed) 
        { 
            edad = ed; 
        }
        void setDireccion(string dir) 
        { 
            direccion = dir;
        }


        string getNombre() const  //Getters
        { 
            return nombre; 
        }
        int getEdad() const 
        { 
            return edad; 
        }
        string getDireccion() const 
        { 
            return direccion; 
        }


        void serialize(const string& filename) const  // serializar el objeto a un archivo
        {
            ofstream ofs(filename, ios::binary);
            if (!ofs) 
            {
                cerr << "Error abriendo el archivo para escritura." << endl;
                return;
            }
            size_t nombreLen = nombre.size();
            ofs.write(reinterpret_cast<const char*>(&nombreLen), sizeof(nombreLen));
            ofs.write(nombre.c_str(), nombreLen);
            ofs.write(reinterpret_cast<const char*>(&edad), sizeof(edad));
            size_t direccionLen = direccion.size();
            ofs.write(reinterpret_cast<const char*>(&direccionLen), sizeof(direccionLen));
            ofs.write(direccion.c_str(), direccionLen);
        }


        void deserialize(const string& filename)         // deserializar el objeto desde un archivo
        {
            ifstream ifs(filename, ios::binary);
            if (!ifs) 
            {
                cerr << "Error abriendo el archivo para lectura." << endl;
                return;
            }
            size_t nombreLen;
            ifs.read(reinterpret_cast<char*>(&nombreLen), sizeof(nombreLen));
            nombre.resize(nombreLen);
            ifs.read(&nombre[0], nombreLen);
            ifs.read(reinterpret_cast<char*>(&edad), sizeof(edad));
            size_t direccionLen;
            ifs.read(reinterpret_cast<char*>(&direccionLen), sizeof(direccionLen));
            direccion.resize(direccionLen);
            ifs.read(&direccion[0], direccionLen);
        }
};

int main() 
{

    Persona p1("Adrian Shephard", 30, "BlacMesaEast-897");
    p1.serialize("persona.bin"); //Serializmos desde un archivo

    Persona p2; 
    p2.deserialize("persona.bin"); //Deserializmos desde un archivo


    cout << "Nombre: " << p2.getNombre() << endl;
    cout << "Edad: " << p2.getEdad() << endl;
    cout << "Direccion: " << p2.getDireccion() << endl;

    return 0;
}
