# Taller3

Benjamín Garcés 215459144 benjamin.garces@alumnos.ucn.cl Pablo Jorquera 215455637 pablo.jorquera@alumnos.ucn.cl

Datos presentes en el txt:
Transferencia(10000, "12345678-9", "98765432-1", 1500000, "Ciudad de México", "2024-07-03", "08:30"),
Transferencia(13000, "12345678-9", "98765432-1", 1500000, "Ciudad de México", "2024-06-01", "08:30"),
Transferencia(14000, "12345678-9", "98765432-1", 1500000, "Ciudad de México", "2024-07-01", "08:30"),
Transferencia(15000, "12345678-9", "98765432-1", 500000, "Ciudad de México", "2024-07-05", "08:00"),
Transferencia(16000, "12345678-9", "98765432-1", 510000, "Ciudad de México", "2024-07-05", "08:35"),
Transferencia(20000, "12345678-0", "98765432-2", 500, "Nueva York", "2024-07-03", "09:15"),
Transferencia(30000, "12345678-1", "98765432-3", 2000, "Tokio", "2024-07-03", "10:45"),
Transferencia(40000, "12345678-2", "98765432-4", 750, "Londres", "2024-07-03", "11:20"),
Transferencia(50000, "12345678-3", "98765432-5", 1800, "París", "2024-07-03", "12:35"),
Transferencia(60000, "12345678-4", "98765432-6", 300, "Berlín", "2024-07-03", "13:50"),
Transferencia(70000, "12345678-5", "98765432-7", 950, "Moscú", "2024-07-03", "14:10"),
Transferencia(80000, "12345678-6", "98765432-8", 1200, "Sídney", "2024-07-03", "15:25"),
Transferencia(90000, "12345678-7", "98765432-9", 450, "Toronto", "2024-07-03", "16:45"),
Transferencia(12000, "12345678-8", "98765433-0", 1600, "Buenos Aires", "2024-07-03", "17:55")

Funciones y métodos:

Cliente:

Cliente::~Cliente();
// Destructor de la clase Cliente.

void Cliente::agregarSospecha(Transaccion* datos);
// Método para agregar una transacción sospechosa a la lista de sospechas del cliente.

void Cliente::setListaTransac(Transaccion* datos);
// Método para agregar una transacción a la lista de transacciones del cliente.

Transaccion* sospechaTiempo(queue<Transaccion*>& transacciones, Transaccion*& datos, int hora, int minutos);
// Función que evalúa si una transacción es sospechosa en función del tiempo y la ubicación. (Si es mayor a $1000000 es sospechosa, si ocurre un el mismo lugar y suma más de $1000000 en menos de una hora es sospechosa, y si suma más de $1000000 en 2 horas y ocurre en lugares distintos, también es sospechosa).

bool Cliente::confirmarTransferenciaSospechosa(Cliente*& cliente, Transaccion* datos)
// Método para confirmar si una transacción es sospechosa basándose en varios criterios.

bool compareDates(const string& date1, const string& date2);
// Función para comparar dos fechas.
// Devuelve verdadero si la primera fecha es menor o igual que la segunda.

void Cliente::ordenarQueue(queue<Transaccion*>& transacciones);
// Método para ordenar una cola de transacciones en orden cronológico.

void Cliente::explorarOrdenar(queue<Cliente*>& clientes);
// Método para ordenar las colas de transacciones y sospechas de cada cliente.

void Cliente::buscarTransacciones(Cliente*& cliente, Nodo* raiz);
// Método para buscar transacciones de un cliente en un árbol y verificar si son sospechosas.

void Cliente::agregarTransaccionClienteExistente(queue<Cliente*>& clientes, Transaccion* transaccion, string rut);
// Método para agregar una transacción a un cliente existente.

void Cliente::agregarTransacciones(queue<Cliente*>& clientes, Nodo* raiz);
// Método para agregar transacciones de un árbol a todos los clientes en una cola.

void Cliente::cargarClientes(queue<Cliente*>& clientes, Nodo* raiz)
// Método para cargar clientes desde un árbol a una pila.

void Cliente::agregarTransaccion(queue<Cliente*>& clientes, Transaccion* datos, string rut);
// Método para agregar una transacción a un cliente específico en una cola de clientes.

bool Cliente::buscarRut(queue<Cliente*> clientes, string rut);
// Método para buscar si un RUT ya está presente en una cola de clientes.

queue<Transaccion*> Cliente::getListaSospechosa();
// Método para obtener la lista de transacciones sospechosas del cliente.

void Cliente::vaciarCola(queue<Cliente*>& clientes);
// Función para vaciar una cola


Transacción:

Transaccion::~Transaccion();
// Destructor de la clase Transaccion.

Transaccion* Transaccion::subirTransacciones(string datosTransaccion);
// Método para crear una nueva transacción.

void Transaccion::setSospechosa(string sospechosa);
// Método para establecer el valor de la variable "sospechosa" de una transacción.

int Transaccion::getMonto();
// Método para obtener el monto de la transacción.


string Transaccion::getFecha();
// Método para obtener la fecha de la transacción.


string Transaccion::datosTransaccion();
// Método para obtener los datos de la transacción.

void Transaccion::actualizarDatosTransacciones(string transferenciasActualizacion);
// Actualiza los datos del txt.



Main:

Nodo* busquedaRec(Nodo* &raiz, int datoABuscar);
// Realiza una búsqueda recursiva en el árbol binario.

void inOrdenRecursivo(Nodo* &raiz);
// Recorre el árbol binario en orden (in-order) de forma recursiva.

int crearIDRandom(Nodo* &raiz);
// Genera un ID aleatorio único para una transacción.

bool datoExiste(string rutSelect, queue<Cliente*> clientes);
// Verifica si un RUT específico existe en la cola de clientes.

bool idExiste(int id, queue<Transaccion*> listaSus);
// Verifica si un ID específico existe en una cola de transacciones.

void transaccionesSospechosas(queue<Cliente*> &clientes)
// Función para mostrar y revisar las transacciones sospechosas de un cliente.

void crearTransaccion(Nodo* &raiz, queue<Cliente*> &clientes);
// Crea una nueva transacción y la agrega al árbol y a la cola de clientes.

void revisarTransacciones(Nodo* &raiz);
// Permite revisar las transacciones en el árbol buscando por ID.

int menu(Nodo* &raiz, queue<Cliente*> &clientes);
// Menú principal del programa para realizar diferentes operaciones.

Nodo* cargarDatos();
// Carga las transacciones desde un archivo de texto y las inserta en el árbol.

void actualizarDatos(Nodo* raiz, int cantidadNodos, int& saltosDeLinea, string& actualizacionTransferencias)
// Función para actualizar datos de las transacciones.

int main();
// Función principal del programa.


Nodo:

Nodo(int key, Producto* value);
//Constructor de Nodo.

int Nodo::altura(Nodo* N);
// Método para obtener la altura de un nodo. Si el nodo es nulo, retorna 0.

int Nodo::max(int a, int b);
// Método para obtener el máximo de dos enteros.

Nodo* Nodo::rotacionDerecha(Nodo* y);
// Realiza una rotación a la derecha en el subárbol.

Nodo* Nodo::rotacionIzquierda(Nodo* x);
// Realiza una rotación a la izquierda en el subárbol.

Nodo* Nodo::rotacionIzquierdaDerecha(Nodo* z);
// Realiza una rotación a la izquierda seguida de una rotación a la derecha.

Nodo* Nodo::rotacionDerechaIzquierda(Nodo* z);
// Realiza una rotación a la derecha seguida de una rotación a la izquierda.

int Nodo::obtenerBalance(Nodo* N);
// Calcula el Factor de balanceo.

Nodo* Nodo::insertar(Nodo* nodo, Transaccion* datos);
// Inserta un nuevo nodo con los datos proporcionados.

void Nodo::cantidadNodos(Nodo* raiz, int& suma)
// Calcula el número de nodos en el árbol.

void Nodo::vaciarAVL(Nodo*& raiz);
// Función para vaciar un árbol AVL liberando la memoria.
