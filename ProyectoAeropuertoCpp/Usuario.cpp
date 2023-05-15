#include "Usuario.h"

using namespace std;

Usuario::Usuario(string inNombre, string inApellido, string inEmail, string inContrasena, int inEdad) 
                    : nombre{inNombre}, apellido{inApellido}, email{inEmail}, contrasena{inContrasena}, edad{inEdad}
                        {
                            kilometros= 0;
                        }


void Usuario::incrementaKilometros(int k) {
    kilometros+=k;
}

string Usuario::getNombre() {
    return nombre;
}

string Usuario::getEmail() {
    return email;
}
string Usuario::getPass() {
    return contrasena;
}
