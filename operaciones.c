#include <stdio.h>
#include "operaciones.h"
#include "lectura.h"

char inventario_nombres[MAX_PRODUCTOS][MAX_NOMBRE_PRODUCTO];
int inventario_cantidades[MAX_PRODUCTOS];
float inventario_precios[MAX_PRODUCTOS];
int numProductos = 0;

char clientes_cedulas[MAX_CLIENTES][MAX_CEDULA];
char clientes_nombres[MAX_CLIENTES][MAX_NOMBRE_CLIENTE];
int numClientes = 0;

char facturas_fechas[MAX_FACTURAS][MAX_FECHA];
char facturas_cedulas[MAX_FACTURAS][MAX_CEDULA];
char facturas_nombres[MAX_FACTURAS][MAX_NOMBRE_CLIENTE];
float facturas_valores[MAX_FACTURAS];
int facturas_cantidades[MAX_FACTURAS];
int numFacturas = 0;

void copiarCadena(char* destino, const char* origen) {
    while (*origen) {
        *destino = *origen;
        destino++;
        origen++;
    }
    *destino = '\0';
}

int longitudCadena(const char* cadena) {
    int longitud = 0;
    while (*cadena) {
        longitud++;
        cadena++;
    }
    return longitud;
}

int compararCadenas(const char* cadena1, const char* cadena2) {
    while (*cadena1 && *cadena2 && *cadena1 == *cadena2) {
        cadena1++;
        cadena2++;
    }
    return (*cadena1 == '\0' && *cadena2 == '\0');
}

int revisaCedula(const char* cedula) {
    if (longitudCadena(cedula) == MAX_CEDULA - 1) {
        return 1;
    }
    return 0;
}

void ingresarProducto() {
    if (numProductos < MAX_PRODUCTOS) {
        printf("Ingresar nombre del producto: ");
        scanf(" %[^\n]", inventario_nombres[numProductos]);
        
        for (int i = 0; i < numProductos; i++) {
            if (compararCadenas(inventario_nombres[i], inventario_nombres[numProductos])) {
                printf("Ya existe un producto con este nombre.\n");
                return;
            }
        }
        
        inventario_cantidades[numProductos] = leerEnteroPositivo("Ingresar cantidad: ");
        inventario_precios[numProductos] = leerFlotantePositivo("Ingresar precio: ");
        
        numProductos++;
    } else {
        printf("Inventario lleno.\n");
    }
}

void editarProducto() {
    char nombreEditar[MAX_NOMBRE_PRODUCTO];
    printf("Ingresar nombre del producto a editar: ");
    scanf(" %[^\n]", nombreEditar);

    int encontrado = 0;
    for (int i = 0; i < numProductos; i++) {
        if (compararCadenas(inventario_nombres[i], nombreEditar)) {
            encontrado = 1;
            printf("Editar nombre del producto (anterior: %s): ", inventario_nombres[i]);
            scanf(" %[^\n]", inventario_nombres[i]);
            
            inventario_cantidades[i] = leerEnteroPositivo("Ingresar nueva cantidad: ");
            inventario_precios[i] = leerFlotantePositivo("Ingresar nuevo precio: ");
            break;
        }
    }

    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}

void eliminarProducto() {
    char nombreEliminar[MAX_NOMBRE_PRODUCTO];
    printf("Ingresar nombre del producto a eliminar: ");
    scanf(" %[^\n]", nombreEliminar);

    int encontrado = 0;
    for (int i = 0; i < numProductos; i++) {
        if (compararCadenas(inventario_nombres[i], nombreEliminar)) {
            encontrado = 1;
            for (int j = i; j < numProductos - 1; j++) {
                copiarCadena(inventario_nombres[j], inventario_nombres[j + 1]);
                inventario_cantidades[j] = inventario_cantidades[j + 1];
                inventario_precios[j] = inventario_precios[j + 1];
            }
            numProductos--;
            printf("Producto eliminado.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}

void listarProductos() {
    if (numProductos > 0) {
        printf("Lista de productos:\n");
        for (int i = 0; i < numProductos; i++) {
            printf("Nombre: %s\n", inventario_nombres[i]);
            printf("Cantidad: %d\n", inventario_cantidades[i]);
            printf("Precio: %.2f\n", inventario_precios[i]);
            printf("\n");
        }
    } else {
        printf("No hay productos en el inventario.\n");
    }
}

void ingresarCliente() {
    if (numClientes < MAX_CLIENTES) {
        printf("Ingresar cedula del cliente: ");
        scanf(" %[^\n]", clientes_cedulas[numClientes]);

        for (int i = 0; i < numClientes; i++) {
            if (compararCadenas(clientes_cedulas[i], clientes_cedulas[numClientes])) {
                printf("Ya existe un cliente con esta cedula.\n");
                return;
            }
        }

        while (!revisaCedula(clientes_cedulas[numClientes])) {
            printf("Cedula no valida. Ingrese nuevamente: ");
            scanf(" %[^\n]", clientes_cedulas[numClientes]);
        }

        printf("Ingresar nombre del cliente: ");
        scanf(" %[^\n]", clientes_nombres[numClientes]);

        numClientes++;
    } else {
        printf("Limite de clientes alcanzado.\n");
    }
}

void editarCliente() {
    char cedulaEditar[MAX_CEDULA];
    printf("Ingresar cedula del cliente a editar: ");
    scanf(" %[^\n]", cedulaEditar);

    int encontrado = 0;
    for (int i = 0; i < numClientes; i++) {
        if (compararCadenas(clientes_cedulas[i], cedulaEditar)) {
            encontrado = 1;
            printf("Editar nombre del cliente (anterior: %s): ", clientes_nombres[i]);
            scanf(" %[^\n]", clientes_nombres[i]);
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente no encontrado.\n");
    }
}

void consultarCliente() {
    char cedulaConsultar[MAX_CEDULA];
    printf("Ingresar cedula del cliente a consultar: ");
    scanf(" %[^\n]", cedulaConsultar);

    int encontrado = 0;
    for (int i = 0; i < numClientes; i++) {
        if (compararCadenas(clientes_cedulas[i], cedulaConsultar)) {
            encontrado = 1;
            printf("Nombre: %s\n", clientes_nombres[i]);
            printf("Cedula: %s\n", clientes_cedulas[i]);
            printf("\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente no encontrado.\n");
    }
}

void verListadoClientes() {
    if (numClientes > 0) {
        printf("Listado de clientes:\n");
        for (int i = 0; i < numClientes; i++) {
            printf("Nombre: %s\n", clientes_nombres[i]);
            printf("Cedula: %s\n", clientes_cedulas[i]);
            printf("\n");
        }
    } else {
        printf("No hay clientes registrados.\n");
    }
}

void adicionarCompraProducto() {
    char nombreProducto[MAX_NOMBRE_PRODUCTO];
    printf("Ingresar nombre del producto a aumentar stock: ");
    scanf(" %[^\n]", nombreProducto);

    int encontrado = 0;
    for (int i = 0; i < numProductos; i++) {
        if (compararCadenas(inventario_nombres[i], nombreProducto)) {
            encontrado = 1;
            int cantidadAumentar = leerEnteroPositivo("Ingrese la cantidad a aumentar: ");
            inventario_cantidades[i] += cantidadAumentar;
            printf("Stock actualizado.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}

void facturar() {
    char cedulaCliente[MAX_CEDULA];
    printf("Ingresar cedula del cliente para facturar: ");
    scanf(" %[^\n]", cedulaCliente);

    int encontrado = 0;
    for (int i = 0; i < numClientes; i++) {
        if (compararCadenas(clientes_cedulas[i], cedulaCliente)) {
            encontrado = 1;
            printf("Ingresar fecha de la factura (dd/mm/aaaa): ");
            scanf(" %[^\n]", facturas_fechas[numFacturas]);

            copiarCadena(facturas_cedulas[numFacturas], cedulaCliente);
            copiarCadena(facturas_nombres[numFacturas], clientes_nombres[i]);

            float totalFactura = 0.0;
            printf("Ingrese los productos a facturar (nombre y cantidad separados por espacio; terminar con '0 0'):\n");

            int productosFacturados = 0;
            while (1) {
                char nombreProducto[MAX_NOMBRE_PRODUCTO];
                int cantidadProducto;
                scanf(" %[^\n]", nombreProducto);
                scanf("%d", &cantidadProducto);

                if (compararCadenas(nombreProducto, "0") && cantidadProducto == 0) {
                    break;
                }

                int encontradoProducto = 0;
                for (int j = 0; j < numProductos; j++) {
                    if (compararCadenas(inventario_nombres[j], nombreProducto)) {
                        encontradoProducto = 1;
                        if (inventario_cantidades[j] >= cantidadProducto) {
                            float subtotal = cantidadProducto * inventario_precios[j];
                            totalFactura += subtotal;
                            facturas_valores[numFacturas] += subtotal;
                            facturas_cantidades[numFacturas] += cantidadProducto;
                            inventario_cantidades[j] -= cantidadProducto;
                            productosFacturados++;
                        } else {
                            printf("No hay suficiente stock de %s.\n", nombreProducto);
                        }
                        break;
                    }
                }

                if (!encontradoProducto) {
                    printf("Producto %s no encontrado.\n", nombreProducto);
                }
            }

            if (productosFacturados > 0) {
                printf("Factura registrada con exito.\n");
                numFacturas++;
            } else {
                printf("No se registraron productos en la factura.\n");
            }

            break;
        }
    }

    if (!encontrado) {
        printf("Cliente no encontrado.\n");
    }
}

void buscarFactura() {
    char fechaBuscar[MAX_FECHA];
    printf("Ingresar fecha de la factura a buscar (dd/mm/aaaa): ");
    scanf(" %[^\n]", fechaBuscar);

    int encontrado = 0;
    for (int i = 0; i < numFacturas; i++) {
        if (compararCadenas(facturas_fechas[i], fechaBuscar)) {
            encontrado = 1;
            printf("Fecha: %s\n", facturas_fechas[i]);
            printf("Cliente: %s (%s)\n", facturas_nombres[i], facturas_cedulas[i]);
            printf("Valor total: %.2f\n", facturas_valores[i]);
            printf("Cantidad de productos: %d\n", facturas_cantidades[i]);
            printf("\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Factura no encontrada.\n");
    }
}

void guardarDatos() {
    FILE *archivo;

    archivo = fopen("productos.txt", "w");
    if (archivo != NULL) {
        for (int i = 0; i < numProductos; i++) {
            fprintf(archivo, "%s %d %.2f\n", inventario_nombres[i], inventario_cantidades[i], inventario_precios[i]);
        }
        fclose(archivo);
        printf("Datos de productos guardados exitosamente.\n");
    } else {
        printf("Error al abrir el archivo de productos.\n");
    }

    archivo = fopen("clientes.txt", "w");
    if (archivo != NULL) {
        for (int i = 0; i < numClientes; i++) {
            fprintf(archivo, "%s %s\n", clientes_cedulas[i], clientes_nombres[i]);
        }
        fclose(archivo);
        printf("Datos de clientes guardados exitosamente.\n");
    } else {
        printf("Error al abrir el archivo de clientes.\n");
    }

    archivo = fopen("facturas.txt", "w");
    if (archivo != NULL) {
        for (int i = 0; i < numFacturas; i++) {
            fprintf(archivo, "%s %s %s %.2f %d\n", facturas_fechas[i], facturas_cedulas[i], facturas_nombres[i], facturas_valores[i], facturas_cantidades[i]);
        }
        fclose(archivo);
        printf("Datos de facturas guardados exitosamente.\n");
    } else {
        printf("Error al abrir el archivo de facturas.\n");
    }
}

void cargarDatos() {
    FILE *archivo;
    char buffer[MAX_NOMBRE_PRODUCTO + MAX_CEDULA + MAX_NOMBRE_CLIENTE + 50];

    archivo = fopen("productos.txt", "r");
    if (archivo != NULL) {
        while (fgets(buffer, sizeof(buffer), archivo)) {
            sscanf(buffer, "%s %d %f", inventario_nombres[numProductos], &inventario_cantidades[numProductos], &inventario_precios[numProductos]);
            numProductos++;
        }
        fclose(archivo);
        printf("Datos de productos cargados exitosamente.\n");
    } else {
        printf("No se pudo abrir el archivo de productos para cargar datos.\n");
    }

    archivo = fopen("clientes.txt", "r");
    if (archivo != NULL) {
        while (fgets(buffer, sizeof(buffer), archivo)) {
            sscanf(buffer, "%s %s", clientes_cedulas[numClientes], clientes_nombres[numClientes]);
            numClientes++;
        }
        fclose(archivo);
        printf("Datos de clientes cargados exitosamente.\n");
    } else {
        printf("No se pudo abrir el archivo de clientes para cargar datos.\n");
    }

    archivo = fopen("facturas.txt", "r");
    if (archivo != NULL) {
        while (fgets(buffer, sizeof(buffer), archivo)) {
            sscanf(buffer, "%s %s %s %f %d", facturas_fechas[numFacturas], facturas_cedulas[numFacturas], facturas_nombres[numFacturas], &facturas_valores[numFacturas], &facturas_cantidades[numFacturas]);
            numFacturas++;
        }
        fclose(archivo);
        printf("Datos de facturas cargados exitosamente.\n");
    } else {
        printf("No se pudo abrir el archivo de facturas para cargar datos.\n");
    }
}

