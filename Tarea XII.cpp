#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Producto {
    int codigo;
    char nombre[50];
    float precio;
    int stock;
    bool activo;
};

void menuPrincipal();
void menuProductos();

void registrarProducto();
void listarProductos();
void buscarPorCodigo();
void buscarPorNombre();
void modificarPrecio();
void actualizarStock();
void eliminarProducto();
void procesoVenta();

bool existeCodigo(int codigo);

int main() {

    int opcion;

    do {

        cout << "\n=====================================\n";
        cout << "   SISTEMA DE CONTROL DE VENTAS\n";
        cout << "   Hans Douglas Edenilzon Alvarado\n";
        cout << "=====================================\n";

        cout << "1. Gestion de productos\n";
        cout << "2. Proceso de venta\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1:
                menuProductos();
                break;

            case 2:
                procesoVenta();
                break;

            case 3:
                cout << "\nSaliendo del sistema...\n";
                break;

            default:
                cout << "\nOpcion invalida\n";
        }

    } while(opcion != 3);

    return 0;
}

void menuProductos() {

    int opcion;

    do {

        cout << "\n========== GESTION DE PRODUCTOS ==========\n";
        cout << "1. Registrar producto\n";
        cout << "2. Listar productos\n";
        cout << "3. Buscar por codigo\n";
        cout << "4. Buscar por nombre\n";
        cout << "5. Modificar precio\n";
        cout << "6. Actualizar stock\n";
        cout << "7. Eliminar / desactivar producto\n";
        cout << "8. Regresar\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1:
                registrarProducto();
                break;

            case 2:
                listarProductos();
                break;

            case 3:
                buscarPorCodigo();
                break;

            case 4:
                buscarPorNombre();
                break;

            case 5:
                modificarPrecio();
                break;

            case 6:
                actualizarStock();
                break;

            case 7:
                eliminarProducto();
                break;

            case 8:
                break;

            default:
                cout << "\nOpcion invalida\n";
        }

    } while(opcion != 8);
}

bool existeCodigo(int codigo) {

    Producto p;

    ifstream archivo("productos.dat", ios::binary);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

void registrarProducto() {

    Producto p;

    cout << "\n===== REGISTRAR PRODUCTO =====\n";

    cout << "Ingrese codigo: ";
    cin >> p.codigo;

    if(existeCodigo(p.codigo)) {
        cout << "El codigo ya existe\n";
        return;
    }

    cin.ignore();

    cout << "Ingrese nombre: ";
    cin.getline(p.nombre, 50);

    cout << "Ingrese precio: ";
    cin >> p.precio;

    if(p.precio <= 0) {
        cout << "Precio invalido\n";
        return;
    }

    cout << "Ingrese stock: ";
    cin >> p.stock;

    if(p.stock < 0) {
        cout << "Stock invalido\n";
        return;
    }

    p.activo = true;

    ofstream archivo("productos.dat", ios::binary | ios::app);

    archivo.write((char*)&p, sizeof(Producto));

    archivo.close();

    cout << "\nProducto registrado correctamente\n";
}

void listarProductos() {

    Producto p;

    ifstream archivo("productos.dat", ios::binary);

    cout << "\n===== LISTA DE PRODUCTOS =====\n";

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.activo) {

            cout << "\nCodigo: " << p.codigo;
            cout << "\nNombre: " << p.nombre;
            cout << "\nPrecio: Q" << p.precio;
            cout << "\nStock: " << p.stock;
            cout << "\n-----------------------------\n";
        }
    }

    archivo.close();
}

void buscarPorCodigo() {

    Producto p;
    int codigo;
    bool encontrado = false;

    cout << "\nIngrese codigo a buscar: ";
    cin >> codigo;

    ifstream archivo("productos.dat", ios::binary);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo) {

            cout << "\nProducto encontrado\n";
            cout << "Codigo: " << p.codigo << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << p.precio << endl;
            cout << "Stock: " << p.stock << endl;

            encontrado = true;
            break;
        }
    }

    archivo.close();

    if(!encontrado) {
        cout << "\nProducto no encontrado\n";
    }
}

void buscarPorNombre() {

    Producto p;
    char nombre[50];
    bool encontrado = false;

    cin.ignore();

    cout << "\nIngrese nombre a buscar: ";
    cin.getline(nombre, 50);

    ifstream archivo("productos.dat", ios::binary);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(strcmp(p.nombre, nombre) == 0 && p.activo) {

            cout << "\nProducto encontrado\n";
            cout << "Codigo: " << p.codigo << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << p.precio << endl;
            cout << "Stock: " << p.stock << endl;

            encontrado = true;
        }
    }

    archivo.close();

    if(!encontrado) {
        cout << "\nProducto no encontrado\n";
    }
}

void modificarPrecio() {

    Producto p;
    int codigo;
    bool encontrado = false;

    cout << "\nIngrese codigo del producto: ";
    cin >> codigo;

    fstream archivo("productos.dat", ios::binary | ios::in | ios::out);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo) {

            cout << "Precio actual: Q" << p.precio << endl;

            cout << "Nuevo precio: ";
            cin >> p.precio;

            archivo.seekp(archivo.tellg() - (long)sizeof(Producto));

            archivo.write((char*)&p, sizeof(Producto));

            cout << "\nPrecio actualizado correctamente\n";

            encontrado = true;
            break;
        }
    }

    archivo.close();

    if(!encontrado) {
        cout << "\nProducto no encontrado\n";
    }
}

void actualizarStock() {

    Producto p;
    int codigo;
    bool encontrado = false;

    cout << "\nIngrese codigo del producto: ";
    cin >> codigo;

    fstream archivo("productos.dat", ios::binary | ios::in | ios::out);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo) {

            cout << "Stock actual: " << p.stock << endl;

            cout << "Nuevo stock: ";
            cin >> p.stock;

            archivo.seekp(archivo.tellg() - (long)sizeof(Producto));

            archivo.write((char*)&p, sizeof(Producto));

            cout << "\nStock actualizado correctamente\n";

            encontrado = true;
            break;
        }
    }

    archivo.close();

    if(!encontrado) {
        cout << "\nProducto no encontrado\n";
    }
}

void eliminarProducto() {

    Producto p;
    int codigo;
    bool encontrado = false;

    cout << "\nIngrese codigo del producto a eliminar: ";
    cin >> codigo;

    fstream archivo("productos.dat", ios::binary | ios::in | ios::out);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo) {

            p.activo = false;

            archivo.seekp(archivo.tellg() - (long)sizeof(Producto));

            archivo.write((char*)&p, sizeof(Producto));

            cout << "\nProducto desactivado correctamente\n";

            encontrado = true;
            break;
        }
    }

    archivo.close();

    if(!encontrado) {
        cout << "\nProducto no encontrado\n";
    }
}

void procesoVenta() {

    Producto p;
    int codigo;
    int cantidad;

    bool encontrado = false;

    float subtotal;
    float iva;
    float total;

    cout << "\n===== PROCESO DE VENTA =====\n";

    cout << "Ingrese codigo del producto: ";
    cin >> codigo;

    fstream archivo("productos.dat", ios::binary | ios::in | ios::out);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo) {

            encontrado = true;

            cout << "\nProducto encontrado\n";
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << p.precio << endl;
            cout << "Stock disponible: " << p.stock << endl;

            cout << "\nIngrese cantidad: ";
            cin >> cantidad;

            if(cantidad <= 0) {
                cout << "Cantidad invalida\n";
                archivo.close();
                return;
            }

            if(cantidad > p.stock) {
                cout << "Stock insuficiente\n";
                archivo.close();
                return;
            }

            subtotal = p.precio * cantidad;
            iva = subtotal * 0.12;
            total = subtotal + iva;

            cout << "\n===== FACTURA =====\n";
            cout << "Subtotal: Q" << subtotal << endl;
            cout << "IVA: Q" << iva << endl;
            cout << "Total: Q" << total << endl;

            p.stock = p.stock - cantidad;

            archivo.seekp(archivo.tellg() - (long)sizeof(Producto));

            archivo.write((char*)&p, sizeof(Producto));

            cout << "\nVenta realizada correctamente\n";

            break;
        }
    }

    archivo.close();

    if(!encontrado) {
        cout << "\nProducto no encontrado\n";
    }
}
