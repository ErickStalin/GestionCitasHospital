#include <iostream>
using namespace std;
#include <string>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include "estructurass.h"

int menu_pacientes(int opcion){
    system ("cls");
    cout<<setw(78)<<"_______________________________"<<endl;
    cout<<setw(78)<<"|          MENU PACIENTES      |"<<endl;
    cout<<setw(78)<<"|                              |"<<endl;
    cout<<setw(78)<<"| 1.- AGREGAR INFORMACION      |"<<endl;
    cout<<setw(78)<<"| 2.- MODIFICAR INFORMACION    |"<<endl;
    cout<<setw(78)<<"| 3.- ELIMINAR INFORMACION     |"<<endl;
    cout<<setw(78)<<"| 4.- MOSTRAR INFORMACION      |"<<endl;
    cout<<setw(78)<<"| 5.- VOLVER AL MENU PRINCIPAL |"<<endl;
    cout<<setw(78)<<"|______________________________|"<<endl;
    cout<<"\n"<<setw(67)<<">INGRESE SU OPCION: ";
    cin>>opcion;
    while (opcion<1 || opcion>5){
        cout<<setw(75)<<" ! INGRESE UNA OPCION VALIDA !"<<endl;
        cout<<"\n"<<setw(67)<<" >INGRESE SU OPCION: ";
        cin>>opcion;
    }
    system ("cls");
    return opcion;
}

void cargar_pacientes (tRegpaciente &registro){
    tPaciente paciente;
    ifstream cargarpacientes;
    registro.contp = 0;
    cargarpacientes.open("paciente.txt");
    if (!cargarpacientes.is_open()){
        cout<<"NO SE CARGO EL ARCHIVO" << endl;
    }
    else{
        getline (cargarpacientes, paciente.cedula);
        while ((paciente.cedula != "-1") && registro.contp<MAX){
            getline(cargarpacientes, paciente.diagnostico);
            getline(cargarpacientes, paciente.medicina);
            getline(cargarpacientes, paciente.dosis);
            registro.regPaciente[registro.contp] = paciente;
            registro.contp++;
            getline (cargarpacientes, paciente.cedula);
        }
        cargarpacientes.close();
    }
}

void ingresar_pacientes(tLista &lista, tRegpaciente &registro, tPaciente paciente){
    string aux;
    int i = 0, o= 0;
    bool validar = true, verificar = true;
    cout<<setw(82)<<"|-^-| INGRESAR INFORMACION DE PACIENTES |-^-|"<<endl;
    cout<<setw(101)<<"-----------------------------------------------------------------------------------"<<endl;
    cin.ignore();
    cout <<" > INGRESE LA CEDULA DEL PACIENTE: ";
    getline (cin,aux);
    while (verificar == true && o<registro.contp){
        if (registro.regPaciente[o].cedula == aux){
            verificar = false;
        }
        o++;
    }
    if (verificar == true){
        cout<<"\n"<<setw(85)<<"------------ INFORMACION DEL PACIENTE -------------"<<endl;
        while (validar == true && i<lista.cont){
            if (lista.datos[i].cedula == aux){
                cout<<setw(53)<< "NOMBRE: "<<lista.datos[i].nombre_completo<<endl;
                cout <<setw(53)<<"CEDULA: "<<lista.datos[i].cedula<<endl;
                cout<<setw(53)<< "EDAD: "<<lista.datos[i].edad<<endl;
                cout<<setw(85)<<"---------------------------------------------------"<<endl;
                validar = false;  
            }
            i++;
        }
        if (validar == false &&  registro.contp < MAX){
            paciente.cedula = aux;
            cout<<setw(100)<<"---------------------- FORMULARIO DEL PACIENTE -----------------------------"<<endl;
            cout <<setw(39)<< "> DIAGNOSTICO: ";
            getline (cin, paciente.diagnostico);
            cout <<setw(39)<< "> MEDICINA: ";
            getline (cin, paciente.medicina);
            cout <<setw(39)<< "> DOSIS: ";
            getline (cin,paciente.dosis); 
            registro.regPaciente[registro.contp] = paciente;
            registro.contp++;
            cout<<setw(100)<<"--------------------------------------------------------------------------"<<endl;
            cout<<setw(80)<<"! INFORMACION GUARDAD CON EXITO !"<<endl;
        }
        else if (validar == true){cout<<setw(60)<<"! PACIENTE NO ENCONTRADO !"<<endl;}
        else{
        cout<<setw(60)<<"! IMPOSIBLE LLENAR INGRESO DE PACIENTES !"<<endl; 
        }
    }
    else{
        cout<<setw(50)<<"! YA EXISTE INFORMACION DEL PACIENTE !"<<endl;
    }
    sleep(4);
}

void modificar_pacientes(tLista &lista, tRegpaciente &registro){
    string aux, aux2, aux3, aux4;
    int i = 0, cont = 0, o = 0;
    char b;
    bool validar = true, band = true;
    cout<<setw(82)<<"|-^-| MODIFICAR INFORMACION DE PACIENTES |-^-|"<<endl;
    cout<<setw(101)<<"-----------------------------------------------------------------------------------"<<endl;
    cin.ignore();
    cout <<" > INGRESE LA CEDULA DEL PACIENTE: ";
    getline (cin,aux);
    cout<<endl<<setw(85)<<"---------------- INFORMACION PACIENTES -----------------"<<endl;
    while (validar == true && i < lista.cont){
        if (lista.datos[i].cedula == aux){
            while (band == true && o<registro.contp){
                if (aux == registro.regPaciente[o].cedula){
                    band = false;
                }
                o++;
            }
            o--;
            cout<<setw(53)<<"> NOMBRE: "<<lista.datos[i].nombre_completo<<endl;
            cout<<setw(53)<<"> CEDULA: "<< lista.datos[i].cedula<<endl;
            cout<<setw(53)<<"> EDAD: "<<lista.datos[i].edad<<endl;
            cout<<setw(53)<<"> DIAGNOSTICO: "<<registro.regPaciente[o].diagnostico<<endl;
            cout<<setw(53)<<"> MEDICINA: "<<registro.regPaciente[o].medicina<<endl;
            cout<<setw(53)<<"> DOSIS: "<<registro.regPaciente[o].dosis<<endl;
            cout<<setw(79)<<"--------------------------------------------"<<endl;
            cout <<setw(74)<<"[-]  INGRESE LOS NUEVOS DATOS  [-]" <<endl;
            cout<<setw(50)<< "> DIAGNOSTICO: ";
            getline(cin,aux2);
            cout<<setw(50)<< "> MEDICINA: ";
            getline(cin,aux3);
            cout<<setw(50)<< "> DOSIS: ";
            getline(cin,aux4);
            cout<<setw(53)<<"> ESTA SEGURO QUE DESEA MODIFICAR LOS DATOS (s/n): ";
            cin>>b;   
            while (b != 's' && b != 'n'){
                cout<<setw(60)<<"! OPCION NO VALIDA !"<<endl;
                cout<<setw(53)<<"> ESTA SEGURO QUE DESEA MODIFICAR LOS DATOS (s/n): ";
                cin>>b;
            }
            validar = false;
        }
        if(b == 's'){
            registro.regPaciente[o].diagnostico = aux2;
            registro.regPaciente[o].medicina = aux3;
            registro.regPaciente[o].dosis = aux4;
            cout<<setw(60)<<"! DATOS DEL PACIENTE  MODIFICADOS EXITOSAMENTE !"<<endl;
        }
        else if (b == 'n'){
            validar = false;
            cout<< "> DATOS DEL PACIENTE NO MODIFICADOS "<<endl;
        }
        i++;
    }
    if (validar == true){
        cout<<"NO ESTA REGISTRADO EL PACIENTE" << endl;
    }
    sleep(4);
}

void eliminar_paciente (tLista &lista, tRegpaciente &registro){
    string aux;
    char decision;
    bool band = true, band2 = true;
    int i = 0, o = 0;
    cout<<setw(82)<<"|-^-| ELIMINAR DATOS DE UN PACIENTE |-^-|\n"<<endl;
    cout << "> INGRESE LA CEDULA DEL PACIENTE QUE DESEA ELIMINAR: ";
    cin >> aux;
    while(band == true && i<lista.cont){
        if (lista.datos[i].cedula == aux){
            while (band2 == true && o<registro.contp){
                if (aux == registro.regPaciente[o].cedula){
                    band2 = false;
                }
                o++;
            }
            o--;
            if (band2 == false){
                cout<<setw(80)<<"-----------------------------------------------"<<endl;
                cout<<setw(76)<<"[-]  DATOS DEL PACIENTE ENCONTRADO  [-] "<<endl;
                cout <<setw(53)<< "NOMBRE: " << lista.datos[i].nombre_completo<<endl;
                cout <<setw(53)<< "EDAD: " << lista.datos[i].edad<<endl;
                cout <<setw(53)<< "CEDULA: " << lista.datos[i].cedula<<endl;
                cout<<setw(0)<< "> DIAGNOSTICO: "<< registro.regPaciente[o].diagnostico<<endl;
                cout<<setw(0)<< "> MEDICINA: "<< registro.regPaciente[o].medicina<<endl;
                cout<<setw(0)<< "> DOSIS: "<< registro.regPaciente[o].dosis<<endl;
                cout<<setw(80)<<"-----------------------------------------------"<<endl;
                cout<<setw(70)<<"SEGURO QUE DESEA ELIMINAR? (s/n): ";
                cin>>decision;
                while (decision != 'n' && decision != 's'){
                    cout<<setw(70)<<"! OPCION NO VALIDA !"<<endl;
                    cout<<setw(70)<<"SEGURO QUE DESEA ELIMINAR? (s/n): ";
                    cin>>decision;    
                }
                if (decision == 's'){
                    for (int o;o<registro.contp-1;o++){
                        registro.regPaciente[o] = registro.regPaciente[o+1];
                    }
                    registro.contp--;
                    cout<<setw(73)<<"! PACIENTE ELIMINADO EXITOSAMENTE !"<<endl;
                    band = false;
                }
                else{
                    band = false;
                    cout<<setw(68)<<"! PACIENTE NO FUE ELIMINADO !"<<endl; 
                }
            }
        }
        i++;
    }
    if (band2 == true){
        cout<<setw(70)<<"! PACIENTE NO FUE ENCONTRADO !"<<endl;
    } 
    sleep (4);
}

void ordenar_paciente (tLista &lista, tRegpaciente &registro){
    tPaciente aux3;
    string intercambio;
    for (int i = 0;i<registro.contp;i++){
        for (int j = 0;j<registro.contp-1;j++){
            if (registro.regPaciente[j].cedula > registro.regPaciente[j+1].cedula){
                intercambio = registro.regPaciente[j].cedula;
                aux3 = registro.regPaciente[j];
                registro.regPaciente[j].cedula = registro.regPaciente[j+1].cedula;
                registro.regPaciente[j] = registro.regPaciente[j+1];
                registro.regPaciente[j+1] = aux3;
                registro.regPaciente[j+1].cedula = intercambio;
            }
        }
    }    
}

void mostrar_pacientes (tLista &lista, tRegpaciente &registro){
    char salir = 'y';
    for (int i = 0; i<registro.contp; i++){
        for (int j = 0;j<lista.cont; j++){
            if (registro.regPaciente[i].cedula == lista.datos[j].cedula){
                cout << "NOMBRE: "<< lista.datos[j].nombre_completo << endl;
                cout << "CEDULA: "<< lista.datos[j].cedula << endl;
                cout << "EDAD: "<< lista.datos[j].edad<< endl;
                cout << "DIAGNOSTICO: "<< registro.regPaciente[i].diagnostico << endl;
                cout << "MEDICA: "<< registro.regPaciente[i].medicina << endl;
                cout << "DOSIS: "<< registro.regPaciente[i].dosis << endl;
            } 
        }
    }
    cout<<setw(78)<<"--> PRESIONE \"X\" PARA SALIR: ";
    cin>>salir;
}

void archivar_pacientes (tRegpaciente &registro){
    ofstream pacientes;
    pacientes.open("paciente.txt");
    for (int i = 0; i < registro.contp; i++){
        pacientes<<registro.regPaciente[i].cedula<<endl;
        pacientes<<registro.regPaciente[i].diagnostico<<endl;
        pacientes<<registro.regPaciente[i].medicina<<endl;
        pacientes<<registro.regPaciente[i].dosis<<endl;
    }
    pacientes<<"-1"<<endl;
    pacientes.close();
}