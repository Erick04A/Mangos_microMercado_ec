#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "lectura.h"

#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_FACTURAS 100
#define MAX_NOMBRE_PRODUCTO 50
#define MAX_NOMBRE_CLIENTE 50
#define MAX_CEDULA 11
#define MAX_FECHA 20

extern char inventario_nombres[MAX_PRODUCTOS][MAX_NOMBRE_PRODUCTO];
extern int inventario_cantidades[MAX_PRODUCTOS];
extern float inventario_precios[MAX_PRODUCTOS];
extern int numProductos;

extern char clientes_cedulas[MAX_CLIENTES][MAX_CEDULA];
extern char clientes_nombres[MAX_CLIENTES][MAX_NOMBRE_CLIENTE];
extern int numClientes;

extern char facturas_fechas[MAX_FACTURAS][MAX_FECHA];
extern char facturas_cedulas[MAX_FACTURAS][MAX_CEDULA];
extern char facturas_nombres[MAX_FACTURAS][MAX_NOMBRE_CLIENTE];
extern float facturas_valores[MAX_FACTURAS];
extern int facturas_cantidades[MAX_FACTURAS];
extern int numFacturas;

void copiarCadena(char* destino, const char* origen);
int longitudCadena(const char* cadena);
int compararCadenas(const char* cadena1, const char* cadena2);
int revisaCedula(const char* cedula);

void ingresarProducto();
void editarProducto();
void eliminarProducto();
void listarProductos();

void ingresarCliente();
void editarCliente();
void consultarCliente();
void verListadoClientes();

void adicionarCompraProducto();
void facturar();
void buscarFactura();
void verListadoFacturas();

void cargarDatos();
void guardarDatos();

#endif 
