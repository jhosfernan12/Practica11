def divide(a, b):
    if b == 0:
        raise RuntimeError("Error: No se puede dividir por cero.")
    return a / b


num1 = int(input("Ingrese el primer numero: "))
num2 = int(input("Ingrese el segundo numero: "))
    
try:
    resultado = divide(num1, num2)
    print(f"El resultado de la division es: {resultado}")
except RuntimeError as e:
    print(e)

