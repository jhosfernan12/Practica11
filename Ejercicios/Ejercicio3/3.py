import pickle

class Persona:
    def __init__(self, nombre="", edad=0, direccion=""):
        self.nombre = nombre
        self.edad = edad
        self.direccion = direccion

    def setNombre(self, nombre):
        self.nombre = nombre

    def setEdad(self, edad):
        self.edad = edad

    def setDireccion(self, direccion):
        self.direccion = direccion

    def getNombre(self):
        return self.nombre

    def getEdad(self):
        return self.edad

    def getDireccion(self):
        return self.direccion

    def serialize(self, filename):
        try:
            with open(filename, 'wb') as ofs:
                pickle.dump(self, ofs)
        except IOError:
            print("Error abriendo el archivo para escritura.")

    def deserialize(self, filename):
        try:
            with open(filename, 'rb') as ifs:
                obj = pickle.load(ifs)
                self.nombre = obj.nombre
                self.edad = obj.edad
                self.direccion = obj.direccion
        except IOError:
            print("Error abriendo el archivo para lectura.")


p1 = Persona("Adrian Shephard", 30, "BlacMesaEast-897")
p1.serialize("persona.bin")

p2 = Persona()
p2.deserialize("persona.bin")

print(f"Nombre: {p2.getNombre()}")
print(f"Edad: {p2.getEdad()}")
print(f"Direccion: {p2.getDireccion()}")
