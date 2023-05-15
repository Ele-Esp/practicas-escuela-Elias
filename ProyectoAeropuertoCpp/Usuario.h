#pragma once
#ifndef _USUARIO_H_
#define _USUARIO_H_
#include <string>

class Usuario {
    private:
        std::string nombre;
        std::string apellido;
        std::string email;
        std::string contrasena;
        int edad;
        
    public:
        Usuario(std::string inNombre = "", std::string inApellido = "", std::string inEmail = "", std::string inContrasena = "", int inEdad = 18);
        int kilometros;
        void incrementaKilometros(int k);
        std::string getNombre();
        std::string getEmail();
        std::string getPass();
};

#endif