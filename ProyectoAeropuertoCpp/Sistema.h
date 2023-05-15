#pragma once
#ifndef _SISTEMA_H_
#define _SISTEMA_H_
#include "Airport.h"
#include <vector>
#include "Usuario.h"
#include <string>

class Sistema {
    private:
        Airport aeropuerto;
        std::vector<Usuario> usuarios;

    public:
        Sistema();
        void crearUsuario();
        void login(std::string email, std::string pass);
        void logout();
        void desplegarMenu();
        void reservarVuelo();
        void comenzarOperaciones();
        void agendarVuelos(std::string wantedAir);
        void actualizarAerolinea(std::string wantedAir);
        void buscarVueloDestino(std::string destino);
        void buscarVueloFecha(std::string fecha);
        void cerrarOperaciones();
        void imprimeAeropuerto();
        void iniciarSistema();
        void imprimeAerolinea();
        bool loggedIn=0;
        int usuarioIndex=-1;
};

#endif