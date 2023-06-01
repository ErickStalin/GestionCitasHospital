#include <iostream>
using namespace std;
#include <string>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include "estructurass.h"
string especialidades [4] = {"MEDICINA GENERAL", "FISIOTERAPIA", "PSICOLOGIA", "PEDIATRIA" };

void titulo (){
    cout<<setw(75)<<"|-^-|\t HOSPITAL GENERAL DEL SUR\t|-^-|\n";
    cout<<setw(88)<<"------------------------------------------------------"<<endl;
    cout<<setw(81)<<"! SOFTWARE DE GESTION DE CITAS MEDICAS !"<<endl;
    cout<<setw(88)<<"------------------------------------------------------"<<endl;
}

int menu_medicos (int opm){
    system ("cls");
    cout<<setw(78)<<"_______________________________"<<endl;
    cout<<setw(78)<<"|          MENU MEDICOS        |"<<endl;
    cout<<setw(78)<<"|                              |"<<endl;
    cout<<setw(78)<<"| 1.- AGREGAR INFORMACION      |"<<endl;
    cout<<setw(78)<<"| 2.- MODIFICAR INFORMACION    |"<<endl;
    cout<<setw(78)<<"| 3.- ELIMINAR INFORMACION     |"<<endl;
    cout<<setw(78)<<"| 4.- MOSTRAR ORDENADAMENTE    |"<<endl;
    cout<<setw(78)<<"| 5.- VOLVER AL MENU PRINCIPAL |"<<endl;
    cout<<setw(78)<<"|______________________________|"<<endl;
    cout<<"\n"<<setw(67)<<"> INGRESE SU OPCION: ";
    cin>>opm;
    while (opm<1 || opm>5){
        cout<<setw(77)<<" ! INGRESE UNA OPCION VALIDA !"<<endl;
        cout<<"\n"<<setw(67)<<"> INGRESE SU OPCION: ";
        cin>>opm;
    }
    system ("cls");
    return opm;
}

int menu_principal (int op){
    cout<<setw(76)<<"______________________________"<<endl;
    cout<<setw(76)<<"|       MENU PRINCIPAL       |"<<endl;
    cout<<setw(76)<<"|                            |"<<endl;
    cout<<setw(76)<<"| 1.- INFORMACION DE MEDICOS |"<<endl;
    cout<<setw(76)<<"| 2.- CONSULTA DE CITAS      |"<<endl;
    cout<<setw(76)<<"| 3.- CONSULTAR PACIENTES    |"<<endl;
    cout<<setw(76)<<"| 4.- SALIR DEL PROGRAMA     |"<<endl;
    cout<<setw(76)<<"|____________________________|"<<endl;
    cout<<"\n"<<setw(67)<<"> INGRESE SU OPCION: ";
    cin>>op;
    while (op<1 || op>4){
        cout<<setw(75)<<" ! INGRESE UNA OPCION VALIDA !"<<endl;
        cout<<"\n"<<setw(67)<<"> INGRESE SU OPCION: ";
        cin>>op;
    }
    return op;
}

void cargar_medicos (tLista2 &lista2){
    tDoctor doctor;
    ifstream cargardoctores;
    lista2.cont2 = 0;
    cargardoctores.open ("medicos.txt");
    if (!cargardoctores.is_open()){
        cout<<setw(70)<<"RECUERDE: SI ES NUEVO USANDO EL PROGRAMA PRIMERO INGRESE DATOS"<<endl;
    }
    else{
        getline(cargardoctores, doctor.nombre);
        while ((doctor.nombre != "-1") && lista2.cont2<MAX){
            getline(cargardoctores, doctor.apellido);
            getline(cargardoctores, doctor.titulo);
            getline(cargardoctores, doctor.nif);
            lista2.datosDoctor [lista2.cont2] = doctor;
            lista2.cont2++;
            getline(cargardoctores, doctor.nombre);
        }
        cargardoctores.close();  
    }
}

void agregar_medicos (tDoctor doctor, tLista2 &lista2){
    int i = 0, espe = 0,controlar = 0;
    cout<<setw(82)<<"|-^-| INGRESO DE DATOS DEL PERSONAL MEDICO |-^-|\n"<<endl;
    if (lista2.cont2<MAX){
        cout<<setw(65)<<"----------- DATOS DEL MEDICO #"<<lista2.cont2+1<<" ------------"<<endl;
        cin.ignore();
        cout<<setw(45)<<"> NOMBRE: ";
        getline (cin,doctor.nombre);
        cout<<setw(47)<<"> APELLIDO: ";
        getline (cin,doctor.apellido);
        cout<<setw(45)<<"> CEDULA: ";
        getline(cin,doctor.nif);
        while ((controlar == 0) && (i<lista2.cont2)){
            if (doctor.nif == lista2.datosDoctor[i].nif){controlar++;}
            i++;
        }
        if (controlar!= 0){
            cout<<setw(79)<<"--------------------------------------------"<<endl;
            cout<<setw(70)<<"! CEDULA YA REGISTRADA !"<<endl;
            sleep (3);
            system ("cls");
        }
        else{
            cout<<setw(70)<<"|-^-| ESPECIALIDADES |-^-|\n"<<endl;
            for (int i = 0; i<4; i++){
                cout <<setw(47)<<"| "<<i+1<<".- "<< especialidades [i] <<endl;
            }
            cout<<"\n"<<setw(61)<<"> ESPECIALIDAD: ";
            cin >> espe;
            for (int i = 0; i <4; i++){
                if (espe == i+1){
                    doctor.titulo = especialidades[i];
                }
            }
            while (espe<1 || espe>4){
                cout<<setw(65)<<"! OPCION NO VALIDA !"<<endl;
                cout<<"\n"<<setw(61)<<"> ESPECIALIDAD: ";
                cin >> espe;
                for (int i = 0; i <4; i++){
                    if (espe == i+1){
                        doctor.titulo = especialidades[i];
                    }
                }
            }
            lista2.datosDoctor[lista2.cont2] = doctor;
            lista2.cont2++;
            cout<<setw(79)<<"--------------------------------------------"<<endl;
            cout<<setw(67)<<"! REGISTRO EXITOSO !"<<endl;
            sleep (5);
            system ("cls");
        }
    }
    else{
        cout<<setw(79)<<"--------------------------------------------"<<endl;
        cout<<setw(75)<<"! LISTA DE MEDICOS LLENA !"<<endl;
    }
}

void modificar_medicos (tLista2 &lista2){
    int i = 0, opcion = 0;
    bool band = true;
    string aux;
    cout<<setw(82)<<"|-^-| MODIFICAR DATOS DEL PERSONAL MEDICO |-^-|\n"<<endl;
    cin.ignore();
    cout <<" > INGRESE LA CEDULA DEL MEDICO QUE DESEA MODIFICAR: ";
    getline (cin,aux);
    while(band == true && i<lista2.cont2){
        if (lista2.datosDoctor[i].nif == aux){
            cout<<setw(80)<<"-----------------------------------------------"<<endl;
            cout<<setw(76)<<"[-]  DATOS DEL MEDICO ENCONTRADO  [-] "<<endl;
            cout <<setw(53)<< "NOMBRE: " << lista2.datosDoctor[i].nombre<<endl;
            cout <<setw(53)<< "APELLIDO: " << lista2.datosDoctor[i].apellido<<endl;
            cout <<setw(53)<< "NIF: " << lista2.datosDoctor[i].nif<<endl;
            cout <<setw(53)<< "ESPECIALIDAD: " << lista2.datosDoctor[i].titulo<<endl;
            cout<<setw(80)<<"-----------------------------------------------"<<endl;
            cout<<setw(80)<<"-----------------------------------------------"<<endl;
            cout <<setw(74)<<"[-]  INGRESE LOS NUEVOS DATOS  [-]" <<endl;
            cout <<setw(53)<< "> NOMBRE: ";
            cin >> lista2.datosDoctor[i].nombre;
            cout <<setw(53)<< "> APELLIDO: ";
            cin >> lista2.datosDoctor[i].apellido;
            cout<<setw(70)<<"|-^-| ESPECIALIDADES |-^-|\n"<<endl;
            for (int z = 0; z<4; z++){
                cout <<setw(47)<<"| "<<z+1<<".- "<< especialidades [z] <<endl;
            }
            cout<<"\n"<<setw(60)<<"> ESPECIALIDAD: ";
            cin >> opcion;
            for (int z = 0; z <4; z++){
                if (opcion == z+1){
                    lista2.datosDoctor[i].titulo = especialidades[z];
                }
            }
            while (opcion<1 || opcion>4){
                cout<<setw(65)<<"! OPCION NO VALIDA !"<<endl;
                cout<<"\n"<<setw(60)<<"> ESPECIALIDAD: ";
                cin >> opcion;
                for (int z = 0; z <4; z++){
                    if (opcion == z+1){
                        lista2.datosDoctor[i].titulo = especialidades[z];
                    }
                }
            }
            cout<<setw(80)<<"-----------------------------------------------"<<endl;
            band = false;
        }
        i++;
    }
    if (band == false){
        cout<<setw(75)<<"! DATOS CAMBIADOS EXITOSAMENTE !"<<endl;
    }
    else{
        cout<<setw(70)<<"! NO SE ENCONTRO EL MEDICO !"<<endl;
    }
    sleep(5);
}

void eliminar_medicos (tLista2 &lista2){
    string aux;
    char decision;
    bool band = true;
    int i = 0, o = 0;
    cout<<setw(82)<<"|-^-| ELIMINAR DATOS DEL PERSONAL MEDICO |-^-|\n"<<endl;
    cout << "> INGRESE LA CEDULA DEL MEDICO QUE DESEA ELIMINAR: ";
    cin >> aux;
    while(band == true && i<lista2.cont2){
        if (lista2.datosDoctor[i].nif == aux){
            cout<<setw(80)<<"-----------------------------------------------"<<endl;
            cout<<setw(76)<<"[-]  DATOS DEL MEDICO ENCONTRADO  [-] "<<endl;
            cout<<setw(53)<<"NOMBRE: " << lista2.datosDoctor[i].nombre<<endl;
            cout<<setw(53)<<"APELLIDO: " << lista2.datosDoctor[i].apellido<<endl;
            cout<<setw(53)<<"CEDULA: " << lista2.datosDoctor[i].nif<<endl;
            cout<<setw(53)<<"ESPECIALIDAD: " << lista2.datosDoctor[i].titulo<<endl;
            cout<<setw(80)<<"-----------------------------------------------"<<endl;
            cout<<setw(70)<<"SEGURO QUE DESEA ELIMINAR? (s/n): ";
            cin>>decision;
            if (decision == 's' ){
                for (o = i;o<lista2.cont2-1;o++){
                    lista2.datosDoctor[o] = lista2.datosDoctor[o+1]; 
                }
                lista2.cont2--;
                cout<<setw(73)<<"! DOCTOR ELIMINADO EXITOSAMENTE !"<<endl;
                band = false;
            }
            else{
                band = false;
                cout<<setw(68)<<"! DOCTOR NO FUE ELIMINADO !"<<endl;
            }
        }
        i++;
    }
    if (band == true){
        cout<<setw(70)<<"! DOCTOR NO FUE ENCONTRADO !"<<endl;
    } 
    sleep (4);
}

void ordenar_medicos (tLista2 &lista2){
    tDoctor aux2;
    string intercambio;
    for (int i = 0;i<lista2.cont2;i++){
        for (int j = 0;j<lista2.cont2-1;j++){
            if (lista2.datosDoctor[j].apellido > lista2.datosDoctor[j+1].apellido){
                intercambio = lista2.datosDoctor[j].apellido;
                aux2 = lista2.datosDoctor[j];
                lista2.datosDoctor[j].apellido = lista2.datosDoctor[j+1].apellido;
                lista2.datosDoctor[j] = lista2.datosDoctor[j+1];
                lista2.datosDoctor[j+1].apellido = intercambio;
                lista2.datosDoctor[j+1] = aux2;
            }
        }
    }
}

void mostrar_medicos (tLista2 &lista2){
    char salir = 'y';
    cout<<setw(82)<<"|-^-| LISTA ORDENADA DE DOCTORES |-^-|"<<endl;
    cout<<setw(101)<<"-----------------------------------------------------------------------------------\n"<<endl;
    for (int i = 0;i<lista2.cont2;i++){
        cout<<setw(65)<<"---------------- DOCTOR #"<<i+1<<" ------------"<<endl;
        cout<<setw(60)<<"> NOMBRE: "<<lista2.datosDoctor[i].nombre<<endl;
        cout<<setw(60)<<"> APELLIDO: "<<lista2.datosDoctor[i].apellido<<endl;
        cout<<setw(60)<<"> CEDULA: "<<lista2.datosDoctor[i].nif<<endl;
        cout<<setw(60)<<"> ESPECIALIDAD: "<<lista2.datosDoctor[i].titulo<<endl;
        cout<<setw(79)<<"---------------------------------------"<<endl;
    }
    while (salir != 'X'){
        cout<<"\n"<<setw(78)<<"--> PRESIONE LA LETRA \"X\" PARA SALIR: ";
        cin>>salir;
    }
}

void archivar_medicos (tLista2 &lista2){
    ofstream archivar;
    archivar.open("medicos.txt");

    for (int i = 0;i<lista2.cont2;i++){
        archivar<<lista2.datosDoctor[i].nombre<<endl;
        archivar<<lista2.datosDoctor[i].apellido<<endl;
        archivar<<lista2.datosDoctor[i].titulo<<endl;
        archivar<<lista2.datosDoctor[i].nif<<endl;
    }
    archivar<<"-1"<<endl;
    archivar.close();
}