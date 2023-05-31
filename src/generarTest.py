import sys

def repeat_string(list, times):
    repeated_string = list * times
    return repeated_string

def save_to_file(filename, content):
    with open(filename, 'w') as file:
        for word in content:
            file.write(word + '\n')


def main(reps, filename):
    string = ["casa", "perro", "gato", "jardin", "arbol", "silla", "mesa", "libro", "lapiz", "cuaderno", "telefono", "computadora", "ventana", "puerta", "coche", "bicicleta", "pelota", "playa", "montaña", "rio", "sol", "luna", "estrella", "musica", "arte", "pintura", "pelicula", "teatro", "actor", "actriz", "cancion", "baile", "amor", "amistad", "familia", "hermano", "hermana", "madre", "padre", "hijo", "hija", "abuelo", "abuela", "comida", "bebida", "pan", "leche", "carne", "fruta", "vegetal", "cafe", "te", "agua", "fuego", "aire", "tierra", "mar", "oceano", "isla", "desierto", "cielo", "nube", "lluvia", "nieve", "viento", "niebla", "calor", "frio", "invierno", "primavera", "verano", "otoño", "dia", "noche", "mañana", "tarde", "hora", "minuto", "segundo", "semana", "mes", "año", "siglo", "historia", "geografia", "matematicas", "ciencia", "quimica", "fisica", "biologia", "medicina", "doctor", "enfermera", "paciente", "hospital", "escuela", "maestro", "estudiante", "universidad", "deporte"]
    repeated_string = repeat_string(string, reps)
    long = len(repeated_string)
    save_to_file("data/"+filename+"-"+str(long), repeated_string)

if __name__ == '__main__':
    rep = int(sys.argv[1])
    filename = sys.argv[2]
    main(rep, filename)
