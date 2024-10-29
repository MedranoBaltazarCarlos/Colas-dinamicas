#include <iostream>
#include <string>
#include <locale> // Biblioteca necesaria para configurar la localización

using namespace std;

// Estructura para almacenar la información de cada solicitud
struct Solicitud {
    string nombreAlumno;
    string carrera;
    int materiasAprobadas;
    float promedioGeneral;
};

// Clase Nodo para almacenar un elemento en la cola dinámica
struct Nodo {
    Solicitud solicitud;
    Nodo* siguiente;

    Nodo(Solicitud s) : solicitud(s), siguiente(nullptr) {}
};

// Clase ColaDinamica, adaptada de una lista dinámica
class ColaDinamica {
private:
    Nodo* frente;
    Nodo* fin;

public:
    ColaDinamica() : frente(nullptr), fin(nullptr) {}

    // Verificar si la cola está vacía
    bool estaVacia() const {
        return frente == nullptr;
    }

    // Agregar una solicitud al final de la cola
    void encolar(const Solicitud& nuevaSolicitud) {
        Nodo* nuevoNodo = new Nodo(nuevaSolicitud);
        if (estaVacia()) {
            frente = fin = nuevoNodo;
        } else {
            fin->siguiente = nuevoNodo;
            fin = nuevoNodo;
        }
        cout << "Solicitud de " << nuevaSolicitud.nombreAlumno << " encolada exitosamente.\n";
    }

    // Eliminar una solicitud del frente de la cola y mostrar los datos
    void elaborarConstancia() {
        if (estaVacia()) {
            cout << "No hay solicitudes pendientes para elaborar constancia.\n";
            return;
        }

        Nodo* nodoAtendido = frente;
        Solicitud solicitudAtendida = nodoAtendido->solicitud;

        // Mostrar la constancia
        cout << "\n--- Constancia de Estudio ---\n";
        cout << "Alumno: " << solicitudAtendida.nombreAlumno << endl;
        cout << "Carrera: " << solicitudAtendida.carrera << endl;
        cout << "Total de materias aprobadas: " << solicitudAtendida.materiasAprobadas << endl;
        cout << "Promedio general: " << solicitudAtendida.promedioGeneral << endl;
        cout << "-----------------------------\n";

        // Eliminar el nodo del frente de la cola
        frente = frente->siguiente;
        delete nodoAtendido;

        if (frente == nullptr) {
            fin = nullptr;
        }
    }

    // Destructor para liberar memoria
    ~ColaDinamica() {
        while (!estaVacia()) {
            elaborarConstancia();  // Libera cada nodo del frente
        }
    }
};

// Función para dar de alta una solicitud
void darDeAltaSolicitud(ColaDinamica& cola) {
    Solicitud nuevaSolicitud;

    cout << "Ingrese el nombre del alumno: ";
    getline(cin, nuevaSolicitud.nombreAlumno);
    cout << "Ingrese el nombre de la carrera: ";
    getline(cin, nuevaSolicitud.carrera);
    cout << "Ingrese el total de materias aprobadas: ";
    cin >> nuevaSolicitud.materiasAprobadas;
    cout << "Ingrese el promedio general: ";
    cin >> nuevaSolicitud.promedioGeneral;
    cin.ignore();  // Limpiar el buffer de entrada

    cola.encolar(nuevaSolicitud);
}

// Función para mostrar el menú de opciones
void mostrarMenu() {
    cout << "\n--- Menu de Opciones ---\n";
    cout << "1. Dar de alta una solicitud\n";
    cout << "2. Elaborar una constancia\n";
    cout << "3. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    // Configurar la localización a español para admitir caracteres especiales
    setlocale(LC_ALL, "es_ES.UTF-8");

    ColaDinamica colaSolicitudes;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();  // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                darDeAltaSolicitud(colaSolicitudes);
                break;
            case 2:
                colaSolicitudes.elaborarConstancia();
                break;
            case 3:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida, intente nuevamente.\n";
        }
    } while (opcion != 3);

    return 0;
}
