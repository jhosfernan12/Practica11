nombrearchivo = input("Ingrese el nombre del archivo de texto: ")

try:
    with open(nombrearchivo, 'r') as archivo:
        for linea in archivo:
             print(linea, end='')
except FileNotFoundError:
    print(f"Error: no se pudo abrir el archivo {nombrearchivo}")


