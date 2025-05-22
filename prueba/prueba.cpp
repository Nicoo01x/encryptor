#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Función para encriptar usando cifrado César
string encriptar(const string& texto, int desplazamiento) {
    string resultado = texto;
    for (char& c : resultado) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + desplazamiento) % 26 + base;
        }
    }
    return resultado;
}

// Función para desencriptar usando cifrado César
string desencriptar(const string& texto, int desplazamiento) {
    return encriptar(texto, 26 - (desplazamiento % 26));
}

int main() {
    ifstream archivo_lectura("cifrado.txt");
    if (archivo_lectura.good()) {
        // El archivo existe, preguntar si se desea desencriptar
        cout << "Se ha detectado un archivo encriptado (cifrado.txt)." << endl;
        cout << "¿Deseas desencriptar el archivo? (s/n): ";
        char opcion;
        cin >> opcion;
        cin.ignore(); // Limpiar buffer

        if (opcion == 's' || opcion == 'S') {
            int clave_guardada;
            string cifrado_leido;
            archivo_lectura >> clave_guardada;
            archivo_lectura.ignore(); // Ignorar el espacio o salto de línea
            getline(archivo_lectura, cifrado_leido);
            archivo_lectura.close();

            int clave_ingresada;
            cout << "Introduce la clave para desencriptar: ";
            cin >> clave_ingresada;

            if (clave_ingresada == clave_guardada) {
                string descifrado = desencriptar(cifrado_leido, clave_ingresada);
                cout << "Texto desencriptado: " << descifrado << endl;
            }
            else {
                cout << "Clave incorrecta. No se puede desencriptar." << endl;
            }
        }
        else {
            cout << "No se desencriptó el archivo." << endl;
        }
    }
    else {
        // El archivo no existe, proceder a encriptar
        string mensaje;
        int clave;

        cout << "Introduce el texto a encriptar: ";
        getline(cin, mensaje);

        cout << "Introduce la clave (número): ";
        cin >> clave;

        string cifrado = encriptar(mensaje, clave);

        ofstream archivo("cifrado.txt");
        if (archivo.is_open()) {
            archivo << clave << " " << cifrado;
            archivo.close();
            cout << "Texto encriptado guardado en cifrado.txt" << endl;
        }
        else {
            cout << "No se pudo abrir el archivo para escribir." << endl;
            return 1;
        }
    }

    return 0;
}
