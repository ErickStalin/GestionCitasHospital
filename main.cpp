#include <iostream>
#include <string>
using namespace std;
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include "estructurass.h"
#include "medicos.h"
#include "citas.h"
#include "pacientes.h"

int main (){
    tFormulario formulario;
    tLista lista;
    tDoctor doctor;
    tLista2 lista2;
    tPaciente paciente;
    tRegpaciente registro;
    string especialidades [4] = {"MEDICINA GENERAL", "FISIOTERAPIA", "PSICOLOGIA", "PEDIATRIA" };
    string horarios [6] = {"09:00--10:00", "10:30--11:30", "12:00--13:00", "13:30--14:30", "15:00--16:00", "16:30--17:30"};
    int op = 0;
    while (op != 4){
        titulo();
        op = menu_principal(op);
        switch (op){
        case 1:{
            int opm = 0;
            while (opm !=5){
                cargar_medicos (lista2);
                cout<<"CONTADOR: "<< lista.cont<<endl;
                opm = menu_medicos(opm);
                switch(opm){
                    case 1:
                        agregar_medicos(doctor,lista2);
                    break;
                    case 2:
                        modificar_medicos (lista2);
                    break;
                    case 3:
                        eliminar_medicos (lista2);
                    break;
                    case 4:
                        ordenar_medicos (lista2);
                        mostrar_medicos (lista2);
                    break;
                }
                archivar_medicos (lista2);
            }
        }
            break;
        case 2:{
            int opc = 0;
            while (opc != 5){
                cargar_citas (lista);
                opc = menu_citas(opc);
                switch (opc){
                    case 1:
                        agregarcitas(formulario,lista,especialidades, horarios);
                    break;
                    case 2:
                        modificar_citas (lista,especialidades,horarios);
                    break;
                    case 3: 
                        eliminar_citas (lista);
                    break;
                    case 4:{
                        int op = 0;
                        while(op != 4){
                            op = menu_consultar_citas(op);
                            switch (op){
                                case 1:
                                    presentar_citas_especialidad (lista, especialidades);
                                break;
                                case 2:
                                    mostrar_citas_fecha(lista);
                                break;
                                case 3:
                                    mostrar_citas_todo(lista);
                                break;
                            }
                        }
                    }
                    break;
                }
                archivar_citas(lista);
            }
        }
            break;
        case 3:{
            int opx = 0;
            cargar_citas (lista);
            while (opx != 5){ 
                cargar_pacientes (registro);
                opx = menu_pacientes (opx);
                switch (opx){
                case 1:
                    ingresar_pacientes (lista,registro,paciente);
                    break;
                case 2:
                    modificar_pacientes (lista,registro);
                    break;
                case 3:
                    eliminar_paciente (lista,registro);
                break;
                case 4:
                    ordenar_paciente (lista,registro);
                    mostrar_pacientes (lista,registro);
                break;
                default:
                    break;
                }
                archivar_pacientes(registro);
            }
        }
            break;
        case 4:
            exit (4);
        default:
            break;
        } 
    }
    system ("pause");
    return 0; 
}