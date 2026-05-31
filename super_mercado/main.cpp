#define _HAS_STD_BYTE 0

#include <iostream>
#include <Windows.h>

#include "Marca.h"
#include "Producto.h"
#include "Proveedor.h"
#include "Cliente.h"
#include "Puesto.h"
#include "Empleado.h"
#include "Venta.h"
#include "Compra.h"

using namespace std;

int main() {

    int op;

    do {

        system("cls");

        cout << "\n========== SUPERMERCADO ==========";
        cout << "\n1. Marcas";
        cout << "\n2. Productos";
        cout << "\n3. Proveedores";
        cout << "\n4. Clientes";
        cout << "\n5. Puestos";
        cout << "\n6. Empleados";
        cout << "\n7. Ventas";
        cout << "\n8. Compras";
        cout << "\n0. Salir";

        cout << "\nSeleccione: ";
        cin >> op;

        cin.ignore();

        switch (op) {

        case 1: {

            Marca m;

            int op2;

            do {

                system("cls");

                cout << "\n===== MARCAS =====";
                cout << "\n1. Insertar";
                cout << "\n2. Mostrar";
                cout << "\n3. Modificar";
                cout << "\n4. Eliminar";
                cout << "\n0. Regresar";

                cout << "\nSeleccione: ";
                cin >> op2;

                cin.ignore();

                switch (op2) {

                case 1: {

                    string marca;

                    cout << "Ingrese Marca: ";
                    getline(cin, marca);

                    m.setMarca(marca);

                    if (m.validarMarca()) {
                        m.insertar();
                    }
                    else {
                        cout << "Marca invalida..." << endl;
                    }

                    break;
                }

                case 2:
                    m.mostrar();
                    break;

                case 3: {

                    int id;
                    string marca;

                    cout << "ID Marca: ";
                    cin >> id;

                    cin.ignore();

                    cout << "Nueva Marca: ";
                    getline(cin, marca);

                    m.setMarca(marca);
                    m.modificar(id);

                    break;
                }

                case 4: {

                    int id;

                    cout << "ID Marca: ";
                    cin >> id;

                    m.eliminar(id);

                    break;
                }

                }

                system("pause");

            } while (op2 != 0);

            break;
        }

        case 2: {

            Producto p;

            int op2;

            do {

                system("cls");

                cout << "\n===== PRODUCTOS =====";
                cout << "\n1. Insertar";
                cout << "\n2. Mostrar";
                cout << "\n3. Modificar";
                cout << "\n4. Eliminar";
                cout << "\n5. Buscar";
                cout << "\n0. Regresar";

                cout << "\nSeleccione: ";
                cin >> op2;

                cin.ignore();

                switch (op2) {

                case 1: {

                    string codigo;
                    string producto;
                    string descripcion;

                    float pc;
                    float pv;

                    int existencia;
                    int id_marca;

                    // Ejemplos visuales agregados para evitar errores de formato
                    cout << "Codigo (Ej. P001, P002): ";
                    getline(cin, codigo);

                    cout << "Producto (Ej. Coca Cola 3L): ";
                    getline(cin, producto);

                    cout << "Descripcion (Ej. Bebida gaseosa): ";
                    getline(cin, descripcion);

                    cout << "Precio Costo (Ej. 15.50): ";
                    cin >> pc;

                    cout << "Precio Venta (Ej. 18.00): ";
                    cin >> pv;

                    cout << "Existencia (Ej. 90): ";
                    cin >> existencia;

                    cout << "ID Marca (Debe existir en Marcas. Ej. 1): ";
                    cin >> id_marca;

                    p.setCodigo(codigo);
                    p.setProducto(producto);
                    p.setDescripcion(descripcion);
                    p.setPrecioCosto(pc);
                    p.setPrecioVenta(pv);
                    p.setExistencia(existencia);
                    p.setIdMarca(id_marca);

                    p.insertar();

                    break;
                }

                case 2:
                    p.mostrar();
                    break;

                case 3: {

                    int id;

                    string codigo;
                    string producto;
                    string descripcion;

                    float pc;
                    float pv;

                    int existencia;
                    int id_marca;

                    cout << "ID Producto a modificar: ";
                    cin >> id;

                    cin.ignore();

                    // Ejemplos visuales agregados también en la modificación
                    cout << "Nuevo Codigo (Ej. P002): ";
                    getline(cin, codigo);

                    cout << "Nuevo Producto: ";
                    getline(cin, producto);

                    cout << "Nueva Descripcion: ";
                    getline(cin, descripcion);

                    cout << "Nuevo Precio Costo: ";
                    cin >> pc;

                    cout << "Nuevo Precio Venta: ";
                    cin >> pv;

                    cout << "Nueva Existencia: ";
                    cin >> existencia;

                    cout << "Nuevo ID Marca (Debe existir): ";
                    cin >> id_marca;

                    p.setCodigo(codigo);
                    p.setProducto(producto);
                    p.setDescripcion(descripcion);
                    p.setPrecioCosto(pc);
                    p.setPrecioVenta(pv);
                    p.setExistencia(existencia);
                    p.setIdMarca(id_marca);

                    p.modificar(id);

                    break;
                }

                case 4: {

                    int id;

                    cout << "ID Producto: ";
                    cin >> id;

                    p.eliminar(id);

                    break;
                }

                case 5: {

                    int id;

                    cout << "ID Producto: ";
                    cin >> id;

                    p.buscarProducto(id);

                    break;
                }

                }

                system("pause");

            } while (op2 != 0);

            break;
        }

        case 3: {

            Proveedor p;

            int op2;

            do {

                system("cls");

                cout << "\n===== PROVEEDORES =====";
                cout << "\n1. Insertar";
                cout << "\n2. Mostrar";
                cout << "\n3. Modificar";
                cout << "\n4. Eliminar";
                cout << "\n5. Buscar";
                cout << "\n0. Regresar";

                cout << "\nSeleccione: ";
                cin >> op2;

                cin.ignore();

                switch (op2) {

                case 1: {

                    string proveedor;
                    string nit;
                    string direccion;
                    string telephone; // cambiado internamente para no chocar si fuera necesario

                    cout << "Proveedor: ";
                    getline(cin, proveedor);

                    cout << "NIT: ";
                    getline(cin, nit);

                    cout << "Direccion: ";
                    getline(cin, direccion);

                    cout << "Telefono: ";
                    getline(cin, telephone);

                    p.setProveedor(proveedor);
                    p.setNit(nit);
                    p.setDireccion(direccion);
                    p.setTelefono(telephone);

                    p.insertar();

                    break;
                }

                case 2:
                    p.mostrar();
                    break;

                case 3: {

                    int id;

                    string proveedor;
                    string nit;
                    string direccion;
                    string telephone;

                    cout << "ID Proveedor: ";
                    cin >> id;

                    cin.ignore();

                    cout << "Proveedor: ";
                    getline(cin, proveedor);

                    cout << "NIT: ";
                    getline(cin, nit);

                    cout << "Direccion: ";
                    getline(cin, direccion);

                    cout << "Telefono: ";
                    getline(cin, telephone);

                    p.setProveedor(proveedor);
                    p.setNit(nit);
                    p.setDireccion(direccion);
                    p.setTelefono(telephone);

                    p.modificar(id);

                    break;
                }

                case 4: {

                    int id;

                    cout << "ID Proveedor: ";
                    cin >> id;

                    p.eliminar(id);

                    break;
                }

                case 5: {

                    int id;

                    cout << "ID Proveedor: ";
                    cin >> id;

                    p.buscarProveedor(id);

                    break;
                }

                }

                system("pause");

            } while (op2 != 0);

            break;
        }

        case 4: {

            Cliente c;

            int op2;

            do {

                system("cls");

                cout << "\n===== CLIENTES =====";
                cout << "\n1. Insertar";
                cout << "\n2. Mostrar";
                cout << "\n3. Modificar";
                cout << "\n4. Eliminar";
                cout << "\n5. Buscar";
                cout << "\n0. Regresar";

                cout << "\nSeleccione: ";
                cin >> op2;

                cin.ignore();

                switch (op2) {

                case 1: {

                    string nombres;
                    string apellidos;
                    string nit;
                    string genero;
                    string telefono;
                    string correo;

                    cout << "Nombres: ";
                    getline(cin, nombres);

                    cout << "Apellidos: ";
                    getline(cin, apellidos);

                    cout << "NIT: ";
                    getline(cin, nit);

                    cout << "Genero (1=M,0=F): ";
                    getline(cin, genero);

                    cout << "Telefono: ";
                    getline(cin, telefono);

                    cout << "Correo: ";
                    getline(cin, correo);

                    c.setNombres(nombres);
                    c.setApellidos(apellidos);
                    c.setNit(nit);
                    c.setGenero(genero);
                    c.setTelefono(telefono);
                    c.setCorreo(correo);

                    c.insertar();

                    break;
                }

                case 2:
                    c.mostrar();
                    break;

                case 3: {

                    int id;

                    string nombres;
                    string apellidos;
                    string nit;
                    string genero;
                    string telefono;
                    string correo;

                    cout << "ID Cliente: ";
                    cin >> id;

                    cin.ignore();

                    cout << "Nombres: ";
                    getline(cin, nombres);

                    cout << "Apellidos: ";
                    getline(cin, apellidos);

                    cout << "NIT: ";
                    getline(cin, nit);

                    cout << "Genero (1=M,0=F): ";
                    getline(cin, genero);

                    cout << "Telefono: ";
                    getline(cin, telefono);

                    cout << "Correo: ";
                    getline(cin, correo);

                    c.setNombres(nombres);
                    c.setApellidos(apellidos);
                    c.setNit(nit);
                    c.setGenero(genero);
                    c.setTelefono(telefono);
                    c.setCorreo(correo);

                    c.modificar(id);

                    break;
                }

                case 4: {

                    int id;

                    cout << "ID Cliente: ";
                    cin >> id;

                    c.eliminar(id);

                    break;
                }

                case 5: {

                    int id;

                    cout << "ID Cliente: ";
                    cin >> id;

                    c.buscarCliente(id);

                    break;
                }

                }

                system("pause");

            } while (op2 != 0);

            break;
        }

        case 5: {

            Puesto p;

            int op2;

            do {

                system("cls");

                cout << "\n===== PUESTOS =====";
                cout << "\n1. Insertar";
                cout << "\n2. Mostrar";
                cout << "\n3. Modificar";
                cout << "\n4. Eliminar";
                cout << "\n5. Buscar";
                cout << "\n0. Regresar";

                cout << "\nSeleccione: ";
                cin >> op2;

                cin.ignore();

                switch (op2) {

                case 1: {

                    string puesto;

                    cout << "Puesto: ";
                    getline(cin, puesto);

                    p.setPuesto(puesto);

                    p.insertar();

                    break;
                }

                case 2:
                    p.mostrar();
                    break;

                case 3: {

                    int id;
                    string puesto;

                    cout << "ID Puesto: ";
                    cin >> id;

                    cin.ignore();

                    cout << "Nuevo Puesto: ";
                    getline(cin, puesto);

                    p.setPuesto(puesto);

                    p.modificar(id);

                    break;
                }

                case 4: {

                    int id;

                    cout << "ID Puesto: ";
                    cin >> id;

                    p.eliminar(id);

                    break;
                }

                case 5: {

                    int id;

                    cout << "ID Puesto: ";
                    cin >> id;

                    p.buscarPuesto(id);

                    break;
                }

                }

                system("pause");

            } while (op2 != 0);

            break;
        }

        case 6: {

            Empleado e;

            int op2;

            do {

                system("cls");

                cout << "\n===== EMPLEADOS =====";
                cout << "\n1. Insertar";
                cout << "\n2. Mostrar";
                cout << "\n3. Modificar";
                cout << "\n4. Eliminar";
                cout << "\n5. Buscar";
                cout << "\n0. Regresar";

                cout << "\nSeleccione: ";
                cin >> op2;

                cin.ignore();

                switch (op2) {

                case 1: {

                    string nombres;
                    string apellidos;
                    string direccion;
                    string telefono;
                    string cui;
                    string genero;
                    string fechaNacimiento;
                    string fechaInicio;

                    int idPuesto;

                    cout << "Nombres: ";
                    getline(cin, nombres);

                    cout << "Apellidos: ";
                    getline(cin, apellidos);

                    cout << "Direccion: ";
                    getline(cin, direccion);

                    cout << "Telefono: ";
                    getline(cin, telefono);

                    cout << "CUI: ";
                    getline(cin, cui);

                    cout << "Genero (1=M,0=F): ";
                    getline(cin, genero);

                    cout << "Fecha Nacimiento (YYYY-MM-DD): ";
                    getline(cin, fechaNacimiento);

                    cout << "ID Puesto: ";
                    cin >> idPuesto;

                    cin.ignore();

                    cout << "Fecha Inicio Laborales (YYYY-MM-DD): ";
                    getline(cin, fechaInicio);

                    e.setNombres(nombres);
                    e.setApellidos(apellidos);
                    e.setDireccion(direccion);
                    e.setTelefono(telefono);
                    e.setCUI(cui);
                    e.setGenero(genero);
                    e.setFechaNacimiento(fechaNacimiento);
                    e.setIdPuesto(idPuesto);
                    e.setFechaInicioLaborales(fechaInicio);

                    cout << "\nValidando...\n";

                    cout << "Nombres: " << e.validarNombres() << endl;
                    cout << "Apellidos: " << e.validarApellidos() << endl;
                    cout << "Direccion: " << e.validarDireccion() << endl;
                    cout << "Telefono: " << e.validarTelefonoEmpleado() << endl;
                    cout << "CUI: " << e.validarCUIEmpleado() << endl;
                    cout << "Genero: " << e.validarGeneroEmpleado() << endl;
                    cout << "Fecha Nacimiento: " << e.validarFechaNacimiento() << endl;
                    cout << "Fecha Inicio: " << e.validarFechaInicioLaborales() << endl;

                    e.insertar();

                    break;
                }

                case 2:
                    e.mostrar();
                    break;

                case 3: {

                    int id;

                    string nombres;
                    string apellidos;
                    string direccion;
                    string telefono;
                    string cui;
                    string genero;
                    string fechaNacimiento;
                    string fechaInicio;

                    int idPuesto;

                    cout << "ID Empleado: ";
                    cin >> id;

                    cin.ignore();

                    cout << "Nombres: ";
                    getline(cin, nombres);

                    cout << "Apellidos: ";
                    getline(cin, apellidos);

                    cout << "Direccion: ";
                    getline(cin, direccion);

                    cout << "Telefono: ";
                    getline(cin, telefono);

                    cout << "CUI: ";
                    getline(cin, cui);

                    cout << "Genero (1=M,0=F): ";
                    getline(cin, genero);

                    cout << "Fecha Nacimiento (YYYY-MM-DD): ";
                    getline(cin, fechaNacimiento);

                    cout << "ID Puesto: ";
                    cin >> idPuesto;

                    cin.ignore();

                    cout << "Fecha Inicio Laborales (YYYY-MM-DD): ";
                    getline(cin, fechaInicio);

                    e.setNombres(nombres);
                    e.setApellidos(apellidos);
                    e.setDireccion(direccion);
                    e.setTelefono(telefono);
                    e.setCUI(cui);
                    e.setGenero(genero);
                    e.setFechaNacimiento(fechaNacimiento);
                    e.setIdPuesto(idPuesto);
                    e.setFechaInicioLaborales(fechaInicio);

                    e.modificar(id);

                    break;
                }

                case 4: {

                    int id;

                    cout << "ID Empleado: ";
                    cin >> id;

                    e.eliminar(id);

                    break;
                }

                case 5: {

                    int id;

                    cout << "ID Empleado: ";
                    cin >> id;

                    e.buscarEmpleado(id);

                    break;
                }

                }

                system("pause");

            } while (op2 != 0);

            break;
        }

        case 7: {

            Venta v;

            int idEmpleado;

            cout << "ID Empleado que realiza la venta: ";
            cin >> idEmpleado;

            cin.ignore();

            v.setIdEmpleado(idEmpleado);

            v.realizarVenta();

            system("pause");

            break;
        }

        case 8: {

            Compra c;

            int idp;

            cout << "ID Proveedor: ";
            cin >> idp;

            c.setIdProveedor(idp);

            c.realizarCompra();

            system("pause");

            break;
        }

        }

    } while (op != 0);

    return 0;
}