import sys

def repeat_string(list, times):
    repeated_string = list * times
    return repeated_string

def save_to_file(filename, content):
    with open(filename, 'w') as file:
        for word in content:
            file.write(word + '\n')


def main(reps, filename):
    string = ["casa", "perro", "gato", "jardín", "árbol", "silla", "mesa", "libro", "lápiz", "cuaderno", "teléfono", "computadora", "ventana", "puerta", "coche", "bicicleta", "pelota", "playa", "montaña", "río", "sol", "luna", "estrella", "música", "arte", "pintura", "película", "teatro", "actor", "actriz", "canción", "baile", "amor", "amistad", "familia", "hermano", "hermana", "madre", "padre", "hijo", "hija", "abuelo", "abuela", "comida", "bebida", "pan", "leche", "carne", "fruta", "vegetal", "café", "té", "agua", "fuego", "aire", "tierra", "mar", "océano", "isla", "desierto", "cielo", "nube", "lluvia", "nieve", "viento", "niebla", "calor", "frío", "invierno", "primavera", "verano", "otoño", "día", "noche", "mañana", "tarde", "hora", "minuto", "segundo", "semana", "mes", "año", "siglo", "historia", "geografía", "matemáticas", "ciencia", "química", "física", "biología", "medicina", "doctor", "enfermera", "paciente", "hospital", "escuela", "maestro", "estudiante", "universidad", "deporte"]
    repeated_string = repeat_string(string, reps)
    long = len(repeated_string)
    save_to_file("data/"+filename+"-"+str(long), repeated_string)

if __name__ == '__main__':
    rep = int(sys.argv[1])
    filename = sys.argv[2]
    main(rep, filename)
