# Taller 2 - Hospital Marmaja

# Integrantes
Gabriel Melero Montero 40017058-4 @rocojorge ICCI

# Requisitos a realizar:

- Cola FIFO de pacientes, implementada manualmente con nodos y punteros.
- Lista enlazada de servicios y un AVL balanceado de pacientes por servicio.
- Pila LIFO de atenciones con nodos y punteros.
- Herencia: `Paciente` hereda de `Persona`.
- Carga desde archivo, validacion de registros, control de duplicados y liberacion de memoria.
- Aritmetica de punteros para recorrer el catalogo fijo de servicios al crear y buscar servicios.
- Se ha implementado un arbol de decision para la asignacion de pacientes a servicios, basado en los sintomas que presentan.
- Operaciones de busqueda, insercion, eliminacion, recorridos InOrden, PreOrden, PostOrden, altura, factor de balance y rotaciones en las estructuras de datos implementadas.

## Diseño del Árbol de Decisión

El criterio utilizado busca derivar a cada paciente al área médica más adecuada utilizando diferentes atributos clínicos.

Reglas principales:

- Edad < 14 → Pediatría.
- Trauma + requiere cirugía → Cirugía.
- Trauma sin cirugía → Traumatología.
- Síntomas neurológicos → Neurología.
- Dolor en el pecho → Cardiología.
- Temperatura alta o dolor severo → Urgencias.
- Hospitalización prolongada → Hospitalización.
- Resto de casos → Medicina General.

Este criterio permite alcanzar los ocho servicios definidos en el enunciado utilizando múltiples atributos del paciente y genera una ruta de evaluación visible para cada clasificación.


# Estructuras de archivos:
```text
hospital/	
	├──	hospital/
	│		├──AVL.h
	│		├──AVL.cpp
	│		├──ArbolDecision.h
	│		├──ArbolDecision.cpp
	│		├──NodoAVL.h
	│		├──NodoAVL.cpp
	│		├──
	│		├── Persona.h
	│		├── Paciente.h
	│		├── ColaPacientes.h
	│		├── Servicio.h
	│		├── HistorialAtenciones.h
	│		├── Hospital_.h
	│		├── Persona.cpp
	│		├── Paciente.cpp
	│		├── ColaPacientes.cpp
	│		├── Servicio.cpp
	│		├── HistorialAtenciones.cpp
	│		├── Hospital_.cpp
	│		└── hospital.cpp (main)
	│		data/
	│		  ├──pacientes.txt
	│		  ├──pacientes_err.txt
	│		  ├──pacientes_errores_t2.txt
	|         └──pacientes_validos_t2.txt
	├── CMakeLists.txt
	├── README.md
	└── .gitignore
```

# Compilación y ejecución
#Para poder abrir del tirón el archivo de pacientes.txt, se debe hardcodear la ruta en el terminal. 
Habría que compilar el proyecto con CMake y luego ejecutar el binario generado.
Con VS Community, se abrir el proyecto y compilarlo desde el IDE.
	
