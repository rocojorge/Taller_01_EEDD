# Taller 1 - Hospital Marmaja

# Integrantes
Gabriel Melero Montero 40017058-4 @rocojorge ICCI

# Requisitos a realizar:

- Cola FIFO de pacientes, implementada manualmente con nodos y punteros.
- Lista enlazada principal de servicios y una lista enlazada de pacientes por servicio.
- Pila LIFO de atenciones con nodos y punteros.
- Herencia: `Paciente` hereda de `Persona`.
- Carga desde archivo, validacion de registros, control de duplicados y liberacion de memoria.
- Aritmetica de punteros para recorrer el catalogo fijo de servicios al crear y buscar servicios.

# Estructuras de archivos:

hospital/	
	├──	hospital/
	│		│	
	│		├── Persona.h
	│		├── Paciente.h
	│		├── ColaPacientes.h
	│		├── Servicio.h
	│		├── HistorialAtenciones.h
	│		├── Hospital.h
	│		├── Persona.cpp
	│		├── Paciente.cpp
	│		├── ColaPacientes.cpp
	│		├── Servicio.cpp
	│		├── HistorialAtenciones.cpp
	│		├── Hospital.cpp
	│		└── hospital.cpp (main)
	│		data/
	│		 └── pacientes.txt
	├── CMakeLists.txt
	├── README.md
	└── .gitignore

# Todo esto es idea de ChatGPT, vamos a ello
	
