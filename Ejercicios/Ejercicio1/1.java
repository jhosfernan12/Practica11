import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class LeerArchivoTexto 
{
    public static void main(String[] args)
  {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Ingrese el nombre del archivo de texto: ");
        String nombreArchivo = scanner.nextLine();
        scanner.close();
        
        try (BufferedReader archivo = new BufferedReader(new FileReader(nombreArchivo))) 
        {
            String linea;
            while ((linea = archivo.readLine()) != null) 
            {
                System.out.println(linea);
            }
        } catch (IOException e) 
        {
            System.err.println("Error: no se pudo abrir el archivo " + nombreArchivo);
        }
    }
}
