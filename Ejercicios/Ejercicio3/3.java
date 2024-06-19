import java.io.*;

class Persona implements Serializable 
{
    private String nombre;
    private int edad;
    private String direccion;

    public Persona() {}

    public Persona(String nombre, int edad, String direccion) 
    {
        this.nombre = nombre;
        this.edad = edad;
        this.direccion = direccion;
    }

    public void setNombre(String nombre)
     {
        this.nombre = nombre;
    }

    public void setEdad(int edad) 
    {
        this.edad = edad;
    }

    public void setDireccion(String direccion) 
    {
        this.direccion = direccion;
    }

    public String getNombre() 
    {
        return nombre;
    }

    public int getEdad() 
    {
        return edad;
    }

    public String getDireccion() 
    {
        return direccion;
    }

    public void serialize(String filename) 
    {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filename))) 
        {
            oos.writeObject(this);
        } catch (IOException e) 
        {
            System.err.println("Error abriendo el archivo para escritura.");
        }
    }

    public void deserialize(String filename) 
    {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(filename))) 
        {
            Persona obj = (Persona) ois.readObject();
            this.nombre = obj.nombre;
            this.edad = obj.edad;
            this.direccion = obj.direccion;
        } 
        catch (IOException | ClassNotFoundException e) 
        {
            System.err.println("Error abriendo el archivo para lectura.");
        }
    }
}

public class 3
{
    public static void main(String[] args) 
    {
        Persona p1 = new Persona("Adrian Shephard", 30, "BlacMesaEast-897");
        p1.serialize("persona.bin");

        Persona p2 = new Persona();
        p2.deserialize("persona.bin");

        System.out.println("Nombre: " + p2.getNombre());
        System.out.println("Edad: " + p2.getEdad());
        System.out.println("Direccion: " + p2.getDireccion());
    }
}
