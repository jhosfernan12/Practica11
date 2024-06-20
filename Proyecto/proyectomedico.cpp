#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

class DatoMedico 
{
protected:
    string fecha;
    int idPaciente;

public:
    DatoMedico(const string& f, int id) : fecha(f), idPaciente(id) {}

    int getIdPaciente() const
    {
        return idPaciente;
    }

    virtual void mostrarDetalles() const = 0;
    virtual void guardar(ofstream& out) const = 0;
    virtual ~DatoMedico() {}
};

class RegistroPaciente : public DatoMedico 
{
private:
    string nombre;
    int edad;

public:
    RegistroPaciente(const string& f, int id, const string& nom, int ed): DatoMedico(f, id), nombre(nom), edad(ed) {}

    void mostrarDetalles() const override 
    {
        cout << "Registro del Paciente:\n";
        cout << "Fecha: " << fecha << "\nID Paciente: " << idPaciente << "\n";
        cout << "Nombre: " << nombre << "\nEdad: " << edad << "\n";
    }

    void guardar(ofstream& out) const override
    {
        string encryptedFecha(fecha.rbegin(), fecha.rend());
        string encryptedNombre(nombre.rbegin(), nombre.rend());
        out << "RegistroPaciente " << encryptedFecha << " " << idPaciente << " " << encryptedNombre << " " << edad << "\n";
    }
};

class ResultadoExamen : public DatoMedico 
{
private:
    string tipoExamen;
    string resultado;

public:
    ResultadoExamen(const string& f, int id, const string& tipo, const string& res): DatoMedico(f, id), tipoExamen(tipo), resultado(res) {}

    void mostrarDetalles() const override 
    {
        cout << "Resultado de Examen:\n";
        cout << "Fecha: " << fecha << "\nID Paciente: " << idPaciente << "\n";
        cout << "Tipo de Examen: " << tipoExamen << "\nResultado: " << resultado << "\n";
    }

    void guardar(ofstream& out) const override
    {
        string encryptedFecha(fecha.rbegin(), fecha.rend());
        string encryptedTipoExamen(tipoExamen.rbegin(), tipoExamen.rend());
        string encryptedResultado(resultado.rbegin(), resultado.rend());
        out << "ResultadoExamen " << encryptedFecha << " " << idPaciente << " " << encryptedTipoExamen << " " << encryptedResultado << "\n";
    }
};

class HistorialClinico : public DatoMedico 
{
private:
    string descripcion;

public:
    HistorialClinico(const string& f, int id, const string& desc): DatoMedico(f, id), descripcion(desc) {}

    void mostrarDetalles() const override 
    {
        cout << "Historial Clinico:\n";
        cout << "Fecha: " << fecha << "\nID Paciente: " << idPaciente << "\n";
        cout << "Descripcion: " << descripcion << "\n";
    }

    void guardar(ofstream& out) const override
    {
        string encryptedFecha(fecha.rbegin(), fecha.rend());
        string encryptedDescripcion(descripcion.rbegin(), descripcion.rend());
        out << "HistorialClinico " << encryptedFecha << " " << idPaciente << " " << encryptedDescripcion << "\n";
    }
};

template <typename T>
class RegistroMedico 
{
private:
    static const int maxDatos = 100;
    T* datos[maxDatos];
    int numDatos;

public:
    RegistroMedico() : numDatos(0) {}

    bool agregarDato(T* dato) 
    {
        if (numDatos < maxDatos) 
        {
            datos[numDatos++] = dato;
            return true;
        }
        return false;
    }

    bool eliminarDato(int id) 
    {
        for (int i = 0; i < numDatos; ++i) 
        {
            if (datos[i]->getIdPaciente() == id) 
            {
                delete datos[i];
                for (int j = i; j < numDatos - 1; ++j) 
                {
                    datos[j] = datos[j + 1];
                }
                --numDatos;
                return true;
            }
        }
        return false;
    }

    T* buscarDato(int id) const 
    {
        for (int i = 0; i < numDatos; ++i)
        {
            if (datos[i]->getIdPaciente() == id) 
            {
                return datos[i];
            }
        }
        return nullptr;
    }

    void listarDatos() const 
    {
        for (int i = 0; i < numDatos; ++i) 
        {
            datos[i]->mostrarDetalles();
            cout << "-----------------------------\n";
        }
    }

    void guardarEnArchivo(const string& nombreArchivo) const
    {
        try 
        {
            ofstream out(nombreArchivo);
            if (!out)
            {
                throw runtime_error("Error al abrir el archivo para guardar");
            }
            for (int i = 0; i < numDatos; ++i)
            {
                datos[i]->guardar(out);
            }
            out.close();
            cout << "Datos guardados en " << nombreArchivo << ".\n";
        }
        catch (const exception& e)
        {
            cerr << "Excepcion: " << e.what() << "\n";
        }
    }

    void cargarDesdeArchivo(const string& nombreArchivo)
    {
        try 
        {
            ifstream in(nombreArchivo);
            if (!in)
            {
                throw runtime_error("Error al abrir el archivo para cargar");
            }
            while (!in.eof())
            {
                string tipo;
                in >> tipo;
                if (tipo == "RegistroPaciente")
                {
                    string fecha, nombre;
                    int id, edad;
                    in >> fecha >> id;
                    in.ignore();
                    getline(in, nombre, ' ');
                    in >> edad;
                    if (!in) throw runtime_error("Datos invalidos para RegistroPaciente");
                    string decryptedFecha(fecha.rbegin(), fecha.rend());
                    string decryptedNombre(nombre.rbegin(), nombre.rend());
                    agregarDato(new RegistroPaciente(decryptedFecha, id, decryptedNombre, edad));
                }
                else if (tipo == "ResultadoExamen")
                {
                    string fecha, tipoExamen, resultado;
                    int id;
                    in >> fecha >> id;
                    in.ignore();
                    getline(in, tipoExamen, ' ');
                    getline(in, resultado);
                    if (!in) throw runtime_error("Datos invalidos para ResultadoExamen");
                    string decryptedFecha(fecha.rbegin(), fecha.rend());
                    string decryptedTipoExamen(tipoExamen.rbegin(), tipoExamen.rend());
                    string decryptedResultado(resultado.rbegin(), resultado.rend());
                    agregarDato(new ResultadoExamen(decryptedFecha, id, decryptedTipoExamen, decryptedResultado));
                }
                else if (tipo == "HistorialClinico")
                {
                    string fecha, descripcion;
                    int id;
                    in >> fecha >> id;
                    in.ignore();
                    getline(in, descripcion);
                    if (!in) throw runtime_error("Datos invalidos para HistorialClinico");
                    string decryptedFecha(fecha.rbegin(), fecha.rend());
                    string decryptedDescripcion(descripcion.rbegin(), descripcion.rend());
                    agregarDato(new HistorialClinico(decryptedFecha, id, decryptedDescripcion));
                }
            }
            in.close();
            cout << "Datos cargados desde " << nombreArchivo << ".\n";
        }
        catch (const exception& e)
        {
            cerr << "Excepcion: " << e.what() << "\n";
        }
    }

    ~RegistroMedico() 
    {
        for (int i = 0; i < numDatos; ++i) 
        {
            delete datos[i];
        }
    }
};

void mostrarMenu() 
{
    cout << "Menu:\n";
    cout << "1. Listar todos los datos\n";
    cout << "2. Buscar dato por ID\n";
    cout << "3. Eliminar dato por ID\n";
    cout << "4. Agregar nuevo dato\n";
    cout << "5. Guardar datos en archivo\n";
    cout << "6. Cargar datos desde archivo\n";
    cout << "7. Salir\n";
    cout << "Seleccione una opcion: ";
}

void agregarNuevoDato(RegistroMedico<DatoMedico>& registro) 
{
    int tipoDato;
    cout << "Seleccione el tipo de dato a agregar:\n";
    cout << "1. Registro de Paciente\n";
    cout << "2. Resultado de Examen\n";
    cout << "3. Historial Clinico\n";
    cout << "Seleccione una opcion: ";
    cin >> tipoDato;

    string fecha;
    int idPaciente;
    cout << "Ingrese la fecha (DD-MM-AAAA): ";
    cin >> fecha;
    cout << "Ingrese el ID del paciente: ";
    cin >> idPaciente;
    cin.ignore(); // Para ignorar el salto de línea

    if (tipoDato == 1) 
    {
        string nombre;
        int edad;
        cout << "Ingrese el nombre del paciente: ";
        getline(cin, nombre);
        cout << "Ingrese la edad del paciente: ";
        cin >> edad;
        registro.agregarDato(new RegistroPaciente(fecha, idPaciente, nombre, edad));
    } 
    else if (tipoDato == 2)
    {
        string tipoExamen, resultado;
        cout << "Ingrese el tipo de examen: ";
        getline(cin, tipoExamen);
        cout << "Ingrese el resultado del examen: ";
        getline(cin, resultado);
        registro.agregarDato(new ResultadoExamen(fecha, idPaciente, tipoExamen, resultado));
    } 
    else if (tipoDato == 3) 
    {
        string descripcion;
        cout << "Ingrese la descripcion del historial clinico: ";
        getline(cin, descripcion);
        registro.agregarDato(new HistorialClinico(fecha, idPaciente, descripcion));
    } 
    else 
    {
        cout << "Opcion invalida.\n";
    }
}

int main() 
{
    RegistroMedico<DatoMedico> registro;
    // Datos de ejemplo
    registro.agregarDato(new RegistroPaciente("08-06-2005", 1, "Jorge Vasquez", 30));
    registro.agregarDato(new ResultadoExamen("04-09-2026", 2, "Sangre", "Normal"));
    registro.agregarDato(new HistorialClinico("10-12-2025", 3, "Paciente con historial de catatonia"));

    int opcion;
    do 
    {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) 
        {
            case 1:
                cout << "Listado de datos medicos:\n";
                registro.listarDatos();
                break;
            case 2: 
            {
                int idABuscar;
                cout << "Ingrese el ID del paciente a buscar: ";
                cin >> idABuscar;
                DatoMedico* encontrado = registro.buscarDato(idABuscar);
                if (encontrado) 
                {
                    cout << "Dato medico encontrado con ID " << idABuscar << ":\n";
                    encontrado->mostrarDetalles();
                } 
                else 
                {
                    cout << "No se encontro dato medico con el ID: " << idABuscar << ".\n";
                }
                break;
            }
            case 3: 
            {
                int idAEliminar;
                cout << "Ingrese el ID del paciente a eliminar: ";
                cin >> idAEliminar;
                if (registro.eliminarDato(idAEliminar)) 
                {
                    cout << "Dato medico con ID " << idAEliminar << " eliminado.\n";
                } 
                else 
                {
                    cout << "No se encontro dato medico con el ID: " << idAEliminar << ".\n";
                }
                break;
            }
            case 4:
                agregarNuevoDato(registro);
                break;
            case 5:
            {
                string nombreArchivo;
                cout << "Ingrese el nombre del archivo para guardar: ";
                cin >> nombreArchivo;
                registro.guardarEnArchivo(nombreArchivo);
                break;
            }
            case 6:
            {
                string nombreArchivo;
                cout << "Ingrese el nombre del archivo para cargar: ";
                cin >> nombreArchivo;
                registro.cargarDesdeArchivo(nombreArchivo);
                break;
            }
            case 7:
                cout << "Saliendo del programa\n";
                break;
            default:
                cout << "Opcion invalida \n";
        }

    } while (opcion != 7);

    return 0;
}
