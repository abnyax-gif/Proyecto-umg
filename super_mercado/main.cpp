// ==========================================
// main.cpp
// ==========================================

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

            // ==========================================
            // MARCAS
            // ==========================================

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

                case 2: {

                    m.mostrar();

                    break;
                }

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

              // ==========================================
              // PRODUCTOS
              // ==========================================

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

                    cout << "Codigo: ";
                    getline(cin, codigo);

                    cout << "Producto: ";
                    getline(cin, producto);

                    cout << "Descripcion: ";
                    getline(cin, descripcion);

                    cout << "Precio Costo: ";
                    cin >> pc;

                    cout << "Precio Venta: ";
                    cin >> pv;

                    cout << "Existencia: ";
                    cin >> existencia;

                    cout << "ID Marca: ";
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

                case 2: {

                    p.mostrar();

                    break;
                }

                case 3: {

                    int id;

                    string codigo;
                    string producto;
                    string descripcion;

                    float pc;
                    float pv;

                    int existencia;
                    int id_marca;

                    cout << "ID Producto: ";
                    cin >> id;

                    cin.ignore();

                    cout << "Codigo: ";
                    getline(cin, codigo);

                    cout << "Producto: ";
                    getline(cin, producto);

                    cout << "Descripcion: ";
                    getline(cin, descripcion);

                    cout << "Precio Costo: ";
                    cin >> pc;

                    cout << "Precio Venta: ";
                    cin >> pv;

                    cout << "Existencia: ";
                    cin >> existencia;

                    cout << "ID Marca: ";
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

              // ==========================================
              // PROVEEDORES
              // ==========================================

        case 3: {

            Proveedor pr;

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

                system("pause");

            } while (op2 != 0);

            break;
        }

              // ==========================================
              // CLIENTES
              // ==========================================

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

                system("pause");

            } while (op2 != 0);

            break;
        }

              // ==========================================
              // PUESTOS
              // ==========================================

        case 5: {

            Puesto pu;

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

                system("pause");

            } while (op2 != 0);

            break;
        }

              // ==========================================
              // EMPLEADOS
              // ==========================================

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

                system("pause");

            } while (op2 != 0);

            break;
        }

              // ==========================================
              // VENTAS
              // ==========================================

        case 7: {

            Venta v;

            int idc;
            int ide;

            cout << "ID Cliente: ";
            cin >> idc;

            cout << "ID Empleado: ";
            cin >> ide;

            v.setIdCliente(idc);
            v.setIdEmpleado(ide);

            v.realizarVenta();

            system("pause");

            break;
        }

              // ==========================================
              // COMPRAS
              // ==========================================

        case 8: {

            Compra c;

            int idp;
            int ide;

            cout << "ID Proveedor: ";
            cin >> idp;

            cout << "ID Empleado: ";
            cin >> ide;

            c.setIdProveedor(idp);
            c.setIdEmpleado(ide);

            c.realizarCompra();

            system("pause");

            break;
        }
        }

    } while (op != 0);

    return 0;
}