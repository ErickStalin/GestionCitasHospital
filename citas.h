int menu_citas (int opc);
void cargar_citas (tLista &lista);
void agregarcitas (tFormulario formulario, tLista &lista,string especialidades[], string horarios[]);
void modificar_citas (tLista &lista,string especialidades[],string horarios[]);
void eliminar_citas (tLista &lista);
int menu_consultar_citas (int op);
void presentar_citas_especialidad (tLista &lista,string especialidades[]);
void mostrar_citas_fecha (tLista &lista);
void mostrar_citas_todo (tLista &lista);
void archivar_citas (tLista &lista);