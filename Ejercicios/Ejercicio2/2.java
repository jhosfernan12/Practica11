import java.util.Scanner;

public class DivisionPorCero 
{

    public static int divide(int a, int b) throws RuntimeException 
    {
        if (b == 0) {
            throw new RuntimeException("Error: No se puede dividir por cero.");
        }
        return a / b;
    }

    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Ingrese el primer numero: ");
        int num1 = scanner.nextInt();
        System.out.print("Ingrese el segundo numero: ");
        int num2 = scanner.nextInt();
        scanner.close();
        
        try 
        {
            int resultado = divide(num1, num2);
            System.out.println("El resultado de la division es: " + resultado);
        } catch (RuntimeException e) 
        {
            System.err.println(e.getMessage());
        }
    }
}
