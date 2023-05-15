#include "Sistema.h"
#include <iostream>
using namespace std;

Sistema::Sistema() {
    iniciarSistema();
}
void Sistema::iniciarSistema() {
    cout<<"Bienvenido al sistema de control de aeropuerto, por favor cree un usuario y contraseña y haga login" <<endl;
    Usuario admin("admin", "admin", "admin@admin", "admin", 99999);
    Usuario premium("Carlos", "Garibay", "carlos@garibay", "admin", 30);
    premium.kilometros=50001;
    usuarios.push_back(admin);
    usuarios.push_back(premium);
    // crearUsuario();
    string email;
    cout<<"usr(email): \n";
    cin>>email; 
    string psw;
    cout<<"psw: \n";
    cin>>psw; 
    login(email, psw);
    
}
void Sistema::crearUsuario() {
    string nombre;
    cout << "ingrese nombre" << endl;
    cin>>nombre;
    string apellido;
    cout << "ingrese apellido" << endl;
    cin>>apellido;
    string email;
    cout << "ingrese email" << endl;
    cin>>email;
    string contrasena;
    cout << "ingrese contraseña" << endl;
    cin>>contrasena;
    int edad;
    cout << "ingrese edad" << endl;
    cin>>edad;
    bool f=true;
    for(int i=0; i<usuarios.size();i++) {
        if(usuarios[i].getEmail()==email) {
            cout << "Usuario existente" <<endl;
            f=false;
        }
    }
    if (f){
        Usuario usr(nombre,apellido,email,contrasena,edad);
        usuarios.push_back(usr);
    }     
    f=true;
}

void Sistema::login(string email, string contrasena) {  
    for(int i=0; i<usuarios.size(); i++) {
        if(usuarios[i].getEmail()==email) {
            if(usuarios[i].getPass()==contrasena) {
                usuarioIndex=i;
                loggedIn=1;
                while(loggedIn) {
                    desplegarMenu();
                }
            }
            else {
                cout<<"Contraseña incorrecta\n";
                    string email;
                    cout<<"usr(email): \n";
                    cin>>email; 
                    string psw;
                    cout<<"psw: \n";
                    cin>>psw; 
                    login(email,psw);  
            }
        }
        else if (i==usuarios.size()-1) {
            cout<< "Usuario inexistente" << endl;
                string email;
                cout<<"usr(email): \n";
                cin>>email; 
                string psw;
                cout<<"psw: \n";
                cin>>psw;   
                login(email,psw);
        }
    }
    
}
void  Sistema::logout(){
    loggedIn=0;
    usuarioIndex=-1;
    cout<<"Logged out" << endl;
    string email;
    cout<<"login usr: \n";
    string psw;
    cin>>email; 
    cout<<"login psw: \n";
    cin>>psw; 
    login(email, psw);
}
void  Sistema::desplegarMenu(){
    // cout<< usuarios[0].getNombre()<< endl;
    // cout<< usuarios[1].getNombre()<< endl;
    // cout<< usuarioIndex<< endl;
    cout<<"Bienvenido " << usuarios[usuarioIndex].getNombre() << ", escoge una opción: "<< endl;
    cout<< "1) Reservar vuelo\n" << 
            "2) Comenzar Operaciones(admin)\n" << 
            "3) Agendar un vuelo\n"<< 
            "4) Actualizar aerolínea(admin)\n"<< 
            "5) Buscar Vuelo por Fecha\n" << 
            "6) Imprimir datos de la aerolínea\n" << 
            "7) Cerrar operaciones (admin)\n" << 
            "8) Mostrar todos los vuelos\n"<<
            "9) Mostrar vuelos de una sola aerolínea\n"<<
            "10) Agregar nuevo usuario (admin)\n"<<
            "11) Checar cuantos km tengo.\n"<<
            "12) Cerrar sesión"<<endl;
    int opt;
    cin>>opt;
    string wantedAir;
    if(cin.fail()) {
        cout<< "Pon solo el número "<<endl;
    } else {
        switch (opt) {
         case 1:
            reservarVuelo();
            break;
        case 2:
            if(usuarios[usuarioIndex].getEmail()=="admin@admin") {
                comenzarOperaciones();
            }
            else {
                cout<<"No eres administrador" << endl;
            }
            break;
        case 3:
            cout<<"¿En qué aerolinea?" << endl;
            cin>>wantedAir;
            agendarVuelos(wantedAir);
            break;
        case 4:
            if(usuarios[usuarioIndex].getEmail()=="admin@admin") {
                cin>>wantedAir;
                actualizarAerolinea(wantedAir);
            }
            else {
                cout<<"No eres administrador" << endl;
            }
            break;
        case 5: 
            cout<<"¿En qué fecha?" << endl;
            cin>>wantedAir;
            buscarVueloFecha(wantedAir);
            break;
        case 6:
            imprimeAerolinea();
            break;
        case 7:
             if(usuarios[usuarioIndex].getEmail()=="admin@admin") {
                cerrarOperaciones();
            }
            else {
                cout<<"No eres administrador" << endl;
            }
            break;
        case 8:
            imprimeAeropuerto();
            break;
        case 9:
            imprimeAerolinea();
            break;
        case 10:  
            if(usuarios[usuarioIndex].getEmail()=="admin@admin") {
                crearUsuario();
            }
            break;
        case 11:
            cout<< "Usted tiene: "<<usuarios[usuarioIndex].kilometros<<" km acumulados."<<endl;
            break;
        case 12: 
            logout();
            break;
        default:
            cout<<"Opción inválida";
        }
    }         
}
void Sistema::reservarVuelo(){
    string aeroL;
    cout<<"¿En qué aerolínea (nombre corto)?" << endl;
    cin>>aeroL;
    string vuelo;
    cout<<"¿En qué vuelo? (FromTo)" << endl;
    cin>>vuelo;
    for(int i=0; i<aeropuerto.airlines.size();i++) {
        if(aeropuerto.airlines[i].getShortName()==aeroL) {
            for(int j=0; j<aeropuerto.airlines[i].flights.size(); j++) {
                if(aeropuerto.airlines[i].flights[j].getFromTo()==vuelo) {
                    if(usuarios[usuarioIndex].kilometros>=50000) {
                        cout<<"Usted ha sido añadido a la lista premium, primera clase, con descuento del 20'%' en su boleto"<<endl;
                        aeropuerto.airlines[i].flights[j].reservaAsientoPremium();    
                        usuarios[usuarioIndex].incrementaKilometros(aeropuerto.airlines[i].flights[j].getDistance());       
                        break;
                    }
                    else {
                        aeropuerto.airlines[i].flights[j].reservaAsiento();
                        usuarios[usuarioIndex].incrementaKilometros(aeropuerto.airlines[i].flights[j].getDistance());   
                        break;
                    }

                } else if(j=aeropuerto.airlines[i].flights.size()-1) { 
                    cout<< "No hay vuelos para allá." << endl;
                }
            }
        }
    if(i=aeropuerto.airlines.size()-1) {
        cout<< "No existe esa aerolinea" <<endl;
        reservarVuelo();
    }
    }
}
void Sistema::comenzarOperaciones(){
    aeropuerto.startOperations("15/06/2022");
}
void Sistema::agendarVuelos(string wantedAir){
    for(int i=0; i<aeropuerto.airlines.size();i++) {
        if(aeropuerto.airlines[i].getShortName()==wantedAir) {
            aeropuerto.airlines[i].scheduleFlight();
        }
    }
}
void Sistema::actualizarAerolinea(std::string wantedAir){

}
void Sistema::buscarVueloFecha(string fecha){
    for(int i=0; i<aeropuerto.airlines.size(); i++) {
        for(int j=0; j<aeropuerto.airlines[i].flights.size(); j++) {
            if(aeropuerto.airlines[i].flights[j].getDate()==fecha) {
                cout<<"Hay uno o más vuelos en esa fecha: " << endl;
                aeropuerto.airlines[i].flights[j].info();
            }
        }
        if(i=aeropuerto.airlines.size()-1) {
            cout << "No hay vuelos en esa fecha\n";
        }
    }
}

void Sistema::cerrarOperaciones(){ 
    double tot{0};
    for(int i=0; i<aeropuerto.airlines.size(); i++ ) {
        tot+=aeropuerto.airlines[i].closeOperataion();
    }
    cout<< "Acaba el día con: "<< tot<< endl;
}

void Sistema::imprimeAeropuerto() {
    aeropuerto.printAllFlights();
}
void Sistema::imprimeAerolinea(){
    cout << "¿Qué aerolínea?" << endl;
    string aeroW;
    cin>> aeroW;
    for(int i=0; i<aeropuerto.airlines.size();i++) {
        if(aeropuerto.airlines[i].getShortName()==aeroW) {
            aeropuerto.airlines[i].printFlights();
        }
        if(i=aeropuerto.airlines.size()-1) {    
            cout << "no existe esa aerolínea" << endl;
            imprimeAerolinea();
        }
    }
    
}

//TODO: 