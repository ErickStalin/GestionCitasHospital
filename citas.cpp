#include <iostream>
using namespace std;
#include <string>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include "estructurass.h"

int menu_citas (int opc){
    system ("cls");
    cout<<setw(78)<<"_______________________________"<<endl;
    cout<<setw(78)<<"|          MENU CITAS          |"<<endl;
    cout<<setw(78)<<"|                              |"<<endl;
    cout<<setw(78)<<"| 1.- AGREGAR CITA             |"<<endl;
    cout<<setw(78)<<"| 2.- MODIFICAR CITA           |"<<endl;
    cout<<setw(78)<<"| 3.- ELIMINAR CITA            |"<<endl;
    cout<<setw(78)<<"| 4.- CONSULTAR CITAS          |"<<endl;
    cout<<setw(78)<<"| 5.- VOLVER AL MENU PRINCIPAL |"<<endl;
    cout<<setw(78)<<"|______________________________|"<<endl;
    cout<<"\n"<<setw(67)<<"> INGRESE SU OPCION: ";
    cin>>opc;
    while (opc<1 || opc>5){
        cout<<setw(75)<<" ! INGRESE UNA OPCION VALIDA !"<<endl;
        cout<<"\n"<<setw(67)<<"> INGRESE SU OPCION: ";
        cin>>opc;
    }
    system ("cls");
    return opc;
}

void cargar_citas (tLista &lista){
    tFormulario formulario;
    ifstream cargarcitas;
    lista.cont = 0;
    cargarcitas.open ("citas.txt");
    if (!cargarcitas.is_open()){
    }
    else{
        getline(cargarcitas,formulario.nombre_completo);
        while (formulario.nombre_completo != "-1" && lista.cont<MAX){
            getline(cargarcitas,formulario.cedula);
            cargarcitas>>formulario.edad;
            cargarcitas.get();
            getline(cargarcitas, formulario.especialidad);
            cargarcitas>>formulario.dia;
            cargarcitas>>formulario.mes;
            cargarcitas>>formulario.year;
            cargarcitas.get();
            getline(cargarcitas,formulario.hora);
            lista.datos[lista.cont] = formulario;
            lista.cont++;
            getline(cargarcitas,formulario.nombre_completo);
        }
        cargarcitas.close();
    }
}

void agregarcitas (tFormulario formulario, tLista &lista, string especialidades[], string horarios[]){
    int opcion = 0, i = 0, controlar = 0, ophora = 0;
    if (lista.cont < MAX){
        cout<<setw(82)<<"|-^-| INGRESO DE DATOS PARA UNA CITA |-^-|"<<endl;
        cout<<setw(101)<<"-----------------------------------------------------------------------------------"<<endl;
        cout<<endl<<setw(85)<<"---------------- INFORMACION CITA -----------------"<<endl;
        cin.ignore();
        cout<<setw(53)<<"> NOMBRE COMPLETO: ";
        getline(cin,formulario.nombre_completo);
        cout<<setw(53)<<"> CEDULA: ";
        getline(cin,formulario.cedula);
        while ((controlar == 0) && (i<lista.cont)){
            if (formulario.cedula == lista.datos[i].cedula){controlar++;}
            i++;
        }
        if (controlar != 0){
            cout<<setw(79)<<"--------------------------------------------"<<endl;
            cout<<setw(70)<<"! CEDULA YA REGISTRADA !"<<endl;
            sleep (3);
            system ("cls");
        }
        else{
            cout<<setw(53)<<"> EDAD: ";
            cin>>formulario.edad;
            while (formulario.edad < 0){
                cout<<setw(65)<<"! INGRESE NUMEROS VALIDOS !"<<endl;
                cout<<setw(50)<<"> EDAD: ";
                cin>>formulario.edad;
            }
            cout<<setw(70)<<"|-^-| ESPECIALIDADES |-^-|\n"<<endl;
            for (int z = 0; z<4; z++){
                cout <<setw(47)<<"| "<<z+1<<".- "<< especialidades [z] <<endl;
            }
            cout<<"\n"<<setw(50)<<"> ESPECIALIDAD: ";
            cin >> opcion;
            for (int z = 0; z <4; z++){
                if (opcion == z+1){
                    formulario.especialidad = especialidades[z];
                }
            }
            while (opcion<1 || opcion>4){
                cout<<setw(65)<<"! OPCION NO VALIDA !"<<endl;
                cout<<"\n"<<setw(51)<<"> ESPECIALIDAD: ";
                cin >> opcion;
                for (int z = 0; z <4; z++){
                    if (opcion == z+1){
                        formulario.especialidad = especialidades[z];
                    }
                }
            }
            cout<<setw(62)<<"> FECHA (FORMATO dd-mm-aa): ";
            cin>>formulario.dia;
            cin.ignore();
            cin>>formulario.mes;
            cin.ignore();
            cin>>formulario.year;
            while ((formulario.dia<0 || formulario.dia >30) || (formulario.mes<0 || formulario.mes > 12) || (formulario.year<2021)){
                cout<<setw(70)<<"[FORMATO DE FECHA INCORRECTA]"<<endl;
                cout<<setw(62)<<"> FECHA (FORMATO dd-mm-aa): ";
                cin>>formulario.dia;
                cin.ignore();
                cin>>formulario.mes;
                cin.ignore();
                cin>>formulario.year;
            }
            cout<<"\n"<<setw(70)<<"|-^-| HORARIOS |-^-|\n"<<endl;
            for (int i = 0;i<6;i++){
                cout <<setw(47)<<"| "<<i+1<<".- "<< horarios [i] <<endl;
            }   
            cout<<"\n"<<setw(50)<<"> HORARIOS: ";
            cin >> ophora;
            for (int z = 0; z <6; z++){
                if (ophora == z+1){
                    formulario.hora = horarios[z];
                }
            }
            while (opcion<1 || opcion>6){
                cout<<setw(65)<<"! OPCION NO VALIDA !"<<endl;
                cout<<"\n"<<setw(50)<<"> HORARIOS: ";
                cin >> ophora;
                for (int z = 0; z <6; z++){
                    if (ophora == z+1){
                        formulario.hora = horarios[z];
                    }
                }
            }
            lista.datos[lista.cont] = formulario;
            lista.cont++;
        }
    }
    else{
        cout<<"! IMPOSIBLE LLENAR AGENDAR CITAS !"<<endl;
    }
}

void modificar_citas (tLista &lista, string especialidades[], string horarios[]){
    int i = 0, ok = 0, opcion = 0, ophora = 0;
    bool val = true;
    string aux;
    int anio = 0, mes = 0, dia = 0;
    cout<<setw(75)<<"|-^-| MODIFICAR CITA MEDICA|-^-|"<<endl;
    cout<<setw(101)<<"-----------------------------------------------------------------------------------\n"<<endl;
    cin.ignore();
    cout <<" > INGRESE LA CEDULA DEL PACIENTE: ";
    getline (cin,aux);
    while(val == true && i<lista.cont){
        if (lista.datos[i].cedula == aux){
            cout<<setw(80)<<"-----------------------------------------------"<<endl;
            cout<<setw(73)<<"[-]  CITA ENCONTRADA  [-] "<<endl;
            cout <<setw(53)<< "NOMBRE: " << lista.datos[i].nombre_completo<<endl;
            cout <<setw(53)<< "APELLIDO: " << lista.datos[i].cedula<<endl;
            cout <<setw(53)<< "EDAD: " << lista.datos[i].edad<<endl;
            cout <<setw(53)<< "ESPECIALIDAD: " << lista.datos[i].especialidad<<endl;
            cout <<setw(53)<< "FECHA: " << lista.datos[i].dia<<"-"<<lista.datos[i].mes<<"-"<<lista.datos[i].year<<endl;
            cout<<setw(53)<<"HORARIO: "<<lista.datos[i].hora<<endl;
            cout<<setw(80)<<"-----------------------------------------------"<<endl;
            cout<<setw(80)<<"-----------------------------------------------"<<endl;
            cout <<setw(74)<<"[-]  INGRESE LOS NUEVOS DATOS  [-]" <<endl;
            cout<<setw(70)<<"|-^-| ESPECIALIDADES |-^-|\n"<<endl;
            for (int z = 0; z<4; z++){
                cout <<setw(47)<<"| "<<z+1<<".- "<< especialidades [z] <<endl;
            }
            cout<<"\n"<<setw(62)<<"> ESPECIALIDAD: ";
            cin >> opcion;
            while (opcion<1 || opcion>4){
                cout<<setw(65)<<"! OPCION NO VALIDA !"<<endl;
                cout<<"\n"<<setw(62)<<"> ESPECIALIDAD: ";
                cin >> opcion;
            }
            cout <<setw(62)<< "> FECHA (FORMATO dd-mm-aa): ";
            cin>>dia;
            cin.ignore();
            cin>>mes;
            cin.ignore();
            cin>>anio;
            while ((dia<0 || dia >30) || (mes<0 ||mes > 12) || (anio<2021)){
                cout<<setw(70)<<"! FORMATO DE FECHA INCORRECTA !"<<endl;
                cout<<setw(62)<<"> FECHA (FORMATO dd-mm-aa): ";
                cin>>dia;
                cin.ignore();
                cin>>mes;
                cin.ignore();
                cin>>anio;
            }
            cout<<"\n"<<setw(70)<<"|-^-| HORARIOS |-^-|\n"<<endl;
            for (int i = 0;i<6;i++){
                cout <<setw(47)<<"| "<<i+1<<".- "<< horarios [i] <<endl;
            }   
            cout<<"\n"<<setw(50)<<"> HORARIOS: ";
            cin >> ophora;
            while (ophora<1 || ophora>6){
                cout<<setw(65)<<"! OPCION NO VALIDA !"<<endl;
                cout<<"\n"<<setw(50)<<"> HORARIOS: ";
                cin >> ophora;
            }
            cout<<setw(80)<<"-----------------------------------------------"<<endl;
            cout <<setw(80)<<"ESTA SEGURO QUE DESEA MODIFICAR LA CITA MEDICA"<<endl;
            cout <<setw(55)<<"1.- SI" << endl;
            cout <<setw(55)<<"2.- NO" << endl;
            cout <<setw(70)<<"> INGRESE SU OPCION: ";
            cin >> ok;
            while(ok <1 || ok >2){
                cout<<setw(55)<<"1.- SI" << endl;
                cout<<setw(55)<<"2.- NO" << endl;
                cout<<setw(70)<<"> INGRESE SU OPCION: ";
                cin>>ok;
            }
            val = false;  
        }
        i++;
    }
    if (val == false && ok == 1){
        lista.datos[i-1].especialidad = especialidades[opcion-1]; 
        lista.datos[i-1].dia = dia;
        lista.datos[i-1].mes = mes;
        lista.datos[i-1].year = anio;      
        lista.datos[i-1].hora = horarios[ophora-1];
        cout<<setw(70)<<"! CITA MODIFICADA EXITOSAMENTE !"<<endl;
    }
    else if (ok == 2){
        cout <<setw(75)<< "! LA CITA NO HA SIDO MODIFICADA !"<<endl;
    }
    else{
        cout<<setw(65)<<"! NO SE ENCONTRO EL PACIENTE !"<<endl;
    }
    sleep(5);
}

void eliminar_citas (tLista &lista){
    string aux;
    int ok = 0, i = 0;
    bool band = true;
    cout<<setw(73)<<"|-^-| ELIMINAR CITA |-^-|"<<endl;
    cout<<setw(101)<<"-----------------------------------------------------------------------------------\n"<<endl;
    cin.ignore();
    cout << "> INGRESE LA CEDULA DEL PACIENTE: ";
    getline(cin,aux);
    while(band == true && i<lista.cont){
        if (lista.datos[i].cedula == aux){
            cout<<setw(80)<<"-----------------------------------------------"<<endl;
            cout<<setw(73)<<"[-]  CITA ENCONTRADA  [-] "<<endl;
            cout <<setw(58)<< "NOMBRE: " << lista.datos[i].nombre_completo<<endl;
            cout <<setw(58)<< "APELLIDO: " << lista.datos[i].cedula<<endl;
            cout <<setw(58)<< "EDAD: " << lista.datos[i].edad<<endl;
            cout <<setw(58)<< "ESPECIALIDAD: " << lista.datos[i].especialidad<<endl;
            cout <<setw(58)<< "FECHA: " << lista.datos[i].dia<<"-"<<lista.datos[i].mes<<"-"<<lista.datos[i].year<<endl;
            cout<<setw(58)<<"HORARIO: "<<lista.datos[i].hora<<endl;
            cout<<setw(80)<<"-----------------------------------------------"<<endl;
            band = false;
        }
        i++;
    }
    i--;
    cout <<setw(75)<<"> ESTA SEGURO DE ELIMINAR LA CITA: "<<endl;
    cout <<setw(67)<<"1.- ELIMINAR CITA" << endl;
    cout <<setw(65)<<"2.- NO ELIMINAR" << endl;
    cout <<setw(65)<<"> INGRESE SU OPCION: ";
    cin >> ok;
    while (ok<1 || ok>2){
        cout<<setw(75)<<" ! INGRESE UNA OPCION VALIDA !"<<endl;
        cout<<setw(65)<<"> INGRESE SU OPCION: ";
        cin>>ok;
    }
    switch (ok){
        case 1:{
            int o = 0;
            for (o = i;o<lista.cont-1;o++){
                lista.datos[o] = lista.datos[o+1]; 
            }
            lista.cont--;
            cout<<setw(73)<<"! CITA ELIMINADA EXITOSAMENTE !"<<endl;
        }  
        break;
        case 2:
            cout<<setw(73)<< "NO SE HA ELIMINADO SU CITA PREVIA" << endl;
        break;
    }
    sleep (4);
}

int menu_consultar_citas (int op){
    system("cls");
    cout<<setw(75)<<"______________________________"<<endl;
    cout<<setw(75)<<"|   MENU BUSQUEDA DE CITAS   |"<<endl;
    cout<<setw(75)<<"|                            |"<<endl;
    cout<<setw(75)<<"| 1.- CITAS POR ESPECIALIDAD |"<<endl;
    cout<<setw(75)<<"| 2.- CITAS POR FECHA        |"<<endl;
    cout<<setw(75)<<"| 3.- TODAS LAS CITAS        |"<<endl;
    cout<<setw(75)<<"| 4.- SALIR AL MENU CITAS    |"<<endl;
    cout<<setw(75)<<"|____________________________|"<<endl;
    cout<<"\n"<<setw(67)<<"> INGRESE SU OPCION: ";
    cin>>op;
    while (op<1 || op>4){
        cout<<setw(70)<<" ! INGRESE UN OPCION VALIDA !"<<endl;
        cout<<"\n"<<setw(65)<<"> INGRESE SU OPCION: ";
        cin>>op;
    }
    system("cls");
    return op;
}
   
void presentar_citas_especialidad (tLista &lista, string especialidades[]){
    bool band = false;
    string buscar_especialidad;
    char salir = 'y';
    int opcion = 0;
    cout<<setw(82)<<"|-^-| BUSQUEDA POR ESPECIALIDAD DE CITAS |-^-|"<<endl;
    cout<<setw(101)<<"-----------------------------------------------------------------------------------"<<endl;
    cout<<setw(70)<<"|-^-| ESPECIALIDADES |-^-|\n"<<endl;
    for (int z = 0; z<4; z++){
        cout <<setw(47)<<"| "<<z+1<<".- "<< especialidades [z] <<endl;
    }
    cout<<"\n"<<setw(60)<<"> ESPECIALIDAD: ";
    cin >> opcion;
    while (opcion<1 || opcion>4){
        cout<<setw(65)<<"! OPCION NO VALIDA !"<<endl;
        cout<<"\n"<<setw(61)<<"> ESPECIALIDAD: ";
        cin >> opcion;
    }
    cout<<"\n";
    for (int i=0;i<lista.cont;i++){
        if (lista.datos[i].especialidad == especialidades[opcion-1]){
            cout<<setw(65)<<"--------------- PACIENTE #"<<i+1<<" ------------"<<endl;
            cout<<setw(60)<<"NOMBRE: "<<lista.datos[i].nombre_completo<< endl;
            cout<<setw(60)<<"CEDULA: "<<lista.datos[i].cedula<< endl;
            cout<<setw(60)<<"EDAD: "<<lista.datos[i].edad<< endl;
            cout<<setw(60)<<"ESPECIALIDAD: "<<lista.datos[i].especialidad<< endl;
            cout<<setw(60)<<"FECHA: "<<lista.datos[i].dia<<"-"<<lista.datos[i].mes<<"-"<<lista.datos[i].year<<endl;
            cout<<setw(60)<<"HORA: "<<lista.datos[i].hora<<endl;
            cout<<setw(79)<<"----------------------------------------"<<endl;
            band = true;
        }
    }
    if (band == false){
        cout<<setw(85)<<"! NO HAY CITAS REGISTRADAS CON ESA ESPECIALIDAD !"<<endl; 
    }
    while (salir != 'X'){
        cout<<"\n"<<setw(78)<<"--> PRESIONE LA LETRA \"X\" PARA SALIR: ";
        cin>>salir;
    }
    
}

void mostrar_citas_fecha (tLista &lista){
    tFormulario aux3;
    string intercambio;
    bool band = false;
    char salir = 'y';
    int opcion = 0, dd = 0, mm = 0, aa = 0, contador = 0;
    cout<<setw(82)<<"|-^-| BUSQUEDA DE CITAS POR FECHA |-^-|"<<endl;
    cout<<setw(101)<<"-----------------------------------------------------------------------------------"<<endl;
    cout<<setw(70)<<"> INGRESE LA FECHA (dd-mm-aa): ";
    cin>>dd;
    cin.ignore();
    cin>>mm;
    cin.ignore();
    cin>>aa;
    cout<<"\n";
    for (int i = 0;i<lista.cont;i++){
        for (int j = 0;j<lista.cont-1;j++){
            if (lista.datos[j].hora > lista.datos[j+1].hora){
                intercambio = lista.datos[j].hora;
                aux3 = lista.datos[j];
                lista.datos[j].hora = lista.datos[j+1].hora;
                lista.datos[j] = lista.datos[j+1];
                lista.datos[j+1] = aux3;
                lista.datos[j+1].hora = intercambio;
            }
        }
    }
    for (int i=0;i<lista.cont;i++){
        if ((lista.datos[i].dia == dd) && (lista.datos[i].mes == mm) && (lista.datos[i].year == aa)){
            cout<<setw(65)<<"---------------- PACIENTE #"<<i+1<<" ------------"<<endl;
            cout<<setw(60)<<"> NOMBRE: "<<lista.datos[i].nombre_completo<<endl;
            cout<<setw(60)<<"> CEDULA: "<<lista.datos[i].cedula<<endl;
            cout<<setw(60)<<"> EDAD: "<<lista.datos[i].especialidad<<endl;
            cout<<setw(60)<<"> FECHA: "<<lista.datos[i].dia<<"-"<<lista.datos[i].mes<<"-"<<lista.datos[i].year<<endl;
            cout<<setw(60)<<"> HORA: "<<lista.datos[i].hora<<endl;
            cout<<setw(79)<<"----------------------------------------"<<endl;
            contador++;
        }
    }
    if (contador == 0){
        cout<<setw(85)<<"! NO HAY CITAS REGISTRADAS EN ESA FECHA !"<<endl; 
    }
    while (salir != 'X'){
        cout<<"\n"<<setw(78)<<"--> PRESIONE LA LETRA \"X\" PARA SALIR: ";
        cin>>salir;
    }
}

void mostrar_citas_todo (tLista &lista){
    tFormulario aux4;
    string intercambio;
    char salir = 'y';
    for (int i = 0;i<lista.cont;i++){
        for (int j = 0;j<lista.cont-1;j++){
            if (lista.datos[j].nombre_completo > lista.datos[j+1].nombre_completo){
                intercambio = lista.datos[j].nombre_completo;
                aux4 = lista.datos[j];
                lista.datos[j].nombre_completo = lista.datos[j+1].nombre_completo;
                lista.datos[j] = lista.datos[j+1];
                lista.datos[j+1].nombre_completo = intercambio;
                lista.datos[j+1] = aux4;
            }
        }
    }
    cout<<setw(82)<<"|-^-| TODAS LAS CITAS REGISTRADAS |-^-|"<<endl;
    cout<<setw(101)<<"-----------------------------------------------------------------------------------\n"<<endl;
    for (int i = 0;i < lista.cont;i++){
        cout<<setw(65)<<"---------------- PACIENTE #"<<i+1<<" ------------"<<endl;
        cout<<setw(60)<<"> NOMBRE: "<<lista.datos[i].nombre_completo<<endl;
        cout<<setw(60)<<"> CEDULA: "<<lista.datos[i].cedula<<endl;
        cout<<setw(60)<<"> EDAD: "<<lista.datos[i].edad<<endl;
        cout<<setw(60)<<"> ESPECIALIDAD: "<<lista.datos[i].especialidad<<endl;
        cout<<setw(60)<<"> FECHA: "<<lista.datos[i].dia<<"-"<<lista.datos[i].mes<<"-"<<lista.datos[i].year<<endl;
        cout<<setw(60)<<"> HORA: "<<lista.datos[i].hora<<endl;
        cout<<setw(79)<<"----------------------------------------"<<endl;
    }
    while (salir != 'X'){
        cout<<"\n"<<setw(78)<<"--> PRESIONE LA LETRA \"X\" PARA SALIR: ";
        cin>>salir;
    }
}

void archivar_citas (tLista &lista){
    ofstream archivar_citas;
    archivar_citas.open("citas.txt");
    for (int i = 0;i<lista.cont;i++){
        archivar_citas<<lista.datos[i].nombre_completo<<endl;
        archivar_citas<<lista.datos[i].cedula<<endl;
        archivar_citas<<lista.datos[i].edad<<endl;
        archivar_citas<<lista.datos[i].especialidad<<endl;
        archivar_citas<<lista.datos[i].dia<<endl;
        archivar_citas<<lista.datos[i].mes<<endl;
        archivar_citas<<lista.datos[i].year<<endl;
        archivar_citas<<lista.datos[i].hora<<endl;
    }
    archivar_citas<<"-1"<<endl;
    archivar_citas.close();
}