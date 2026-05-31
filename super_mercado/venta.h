#pragma once

#include <iomanip>
#include <regex>
#include <iostream>
#include <mysql.h>
#include <vector>
#include <string>

#include "ConexionSPBD.h"

using namespace std;

class Venta {

private:

    int id_empleado = 0;
    string serie = "A";

public:

    void setIdEmpleado(int ide) {
        id_empleado = ide;
    }

    void realizarVenta() {

        ConexionSPBD cn;
        cn.abrir_conexion();

        if (cn.getConector() == NULL) {
            cout << "Error de conexion..." << endl;
            return;
        }

        mysql_query(cn.getConector(), "START TRANSACTION");

        // ==========================================
        // BUSCAR CLIENTE POR NIT
        // ==========================================

        string nit;
        int id_cliente = 0;

        cout << "\nNIT Cliente: ";
        getline(cin, nit);

        regex formatoNit(
            "^(C/F|c/f|CF|cf|[0-9-]+)$"
        );

        if (!regex_match(nit, formatoNit)) {

            cout << "NIT invalido..." << endl;

            cn.cerrar_conexion();

            return;
        }

        string buscarCliente =
            "SELECT id_cliente,nombres,apellidos "
            "FROM clientes WHERE nit='" + nit + "'";

        mysql_query(
            cn.getConector(),
            buscarCliente.c_str()
        );

        MYSQL_RES* resCliente =
            mysql_store_result(
                cn.getConector()
            );

        MYSQL_ROW filaCliente =
            mysql_fetch_row(
                resCliente
            );

        if (filaCliente != NULL) {

            id_cliente =
                stoi(filaCliente[0]);

            cout << "\nCliente encontrado: "
                << filaCliente[1]
                << " "
                << filaCliente[2]
                << endl;
        }
        else {

            string nombres;
            string apellidos;
            string telefono;
            string correo;

            cout << "\nCliente no existe." << endl;

            cout << "Nombres: ";
            getline(cin, nombres);

            cout << "Apellidos: ";
            getline(cin, apellidos);

            cout << "Telefono: ";
            getline(cin, telefono);

            cout << "Correo: ";
            getline(cin, correo);

            string insertarCliente =
                "INSERT INTO clientes("
                "nombres,"
                "apellidos,"
                "nit,"
                "genero,"
                "telefono,"
                "correo_electronico,"
                "fecha_ingreso"
                ") VALUES('"
                + nombres + "','"
                + apellidos + "','"
                + nit + "',b'1','"
                + telefono + "','"
                + correo + "',NOW())";

            mysql_query(
                cn.getConector(),
                insertarCliente.c_str()
            );

            id_cliente =
                mysql_insert_id(
                    cn.getConector()
                );

            cout << "\nCliente registrado correctamente.\n";
        }

        mysql_free_result(resCliente);

        // ==========================================
        // NUMERO FACTURA
        // ==========================================

        int no_factura = 1;

        string consultaFactura =
            "SELECT IFNULL(MAX(no_factura),0)+1 "
            "FROM ventas";

        mysql_query(
            cn.getConector(),
            consultaFactura.c_str()
        );

        MYSQL_RES* resFactura =
            mysql_store_result(
                cn.getConector()
            );

        MYSQL_ROW filaFactura =
            mysql_fetch_row(
                resFactura
            );

        if (filaFactura != NULL) {
            no_factura =
                stoi(filaFactura[0]);
        }

        mysql_free_result(resFactura);

        // ==========================================
        // DETALLE VENTA
        // ==========================================

        vector<int> productos;
        vector<int> cantidades;
        vector<float> precios;
        vector<string> nombresProductos;

        char continuar = 's';

        while (
            continuar == 's' ||
            continuar == 'S'
            ) {

            int id_producto;
            int cantidad;

            cout << "\nID Producto: ";
            cin >> id_producto;

            cout << "Cantidad: ";
            cin >> cantidad;

            string consultaProducto =
                "SELECT producto,"
                "precio_venta,"
                "existencia "
                "FROM productos "
                "WHERE id_producto=" +
                to_string(id_producto);

            mysql_query(
                cn.getConector(),
                consultaProducto.c_str()
            );

            MYSQL_RES* resultado =
                mysql_store_result(
                    cn.getConector()
                );

            MYSQL_ROW fila =
                mysql_fetch_row(
                    resultado
                );

            if (fila != NULL) {

                string nombre = fila[0];

                float precio =
                    stof(fila[1]);

                int stock =
                    stoi(fila[2]);

                if (cantidad <= stock) {

                    productos.push_back(id_producto);
                    cantidades.push_back(cantidad);
                    precios.push_back(precio);
                    nombresProductos.push_back(nombre);

                    string actualizar =
                        "UPDATE productos "
                        "SET existencia = existencia - "
                        + to_string(cantidad) +
                        " WHERE id_producto="
                        + to_string(id_producto);

                    mysql_query(
                        cn.getConector(),
                        actualizar.c_str()
                    );

                    cout << "Producto agregado.\n";
                }
                else {

                    cout << "Stock insuficiente.\n";
                }
            }
            else {

                cout << "Producto no encontrado.\n";
            }

            mysql_free_result(resultado);

            cout << "\nAgregar otro producto (s/n): ";
            cin >> continuar;

            cin.ignore();
        }
        if (productos.empty()) {

            cout << "\nNo se agregaron productos a la venta.\n";

            mysql_query(
                cn.getConector(),
                "ROLLBACK"
            );

            cn.cerrar_conexion();

            return;
        }

        // ==========================================
        // INSERTAR VENTA
        // ==========================================

        string insertarVenta =
            "INSERT INTO ventas("
            "no_factura,"
            "serie,"
            "fecha_factura,"
            "id_cliente,"
            "id_empleado,"
            "fecha_ingreso"
            ") VALUES("
            + to_string(no_factura)
            + ",'"
            + serie
            + "',CURDATE(),"
            + to_string(id_cliente)
            + ","
            + to_string(id_empleado)
            + ",NOW())";

        int q_estado =
            mysql_query(
                cn.getConector(),
                insertarVenta.c_str()
            );

        if (!q_estado) {

            long long id_venta =
                mysql_insert_id(
                    cn.getConector()
                );

            float total = 0;

            for (
                int i = 0;
                i < productos.size();
                i++
                ) {

                string detalle =
                    "INSERT INTO ventas_detalle("
                    "id_venta,"
                    "id_producto,"
                    "cantidad,"
                    "precio_unitario"
                    ") VALUES("
                    + to_string(id_venta)
                    + ","
                    + to_string(productos[i])
                    + ","
                    + to_string(cantidades[i])
                    + ","
                    + to_string(precios[i])
                    + ")";

                mysql_query(
                    cn.getConector(),
                    detalle.c_str()
                );

                total +=
                    cantidades[i]
                    * precios[i];
            }

            mysql_query(
                cn.getConector(),
                "COMMIT"
            );

            cout << "\n=========================================\n";
            cout << "             FACTURA\n";
            cout << "=========================================\n";
            cout << "Serie: " << serie << endl;
            cout << "Factura No: " << no_factura << endl;
            cout << "NIT: " << nit << endl;

            cout << "\nPRODUCTOS\n";

            for (
                int i = 0;
                i < productos.size();
                i++
                ) {

                cout
                    << nombresProductos[i]
                    << " | "
                    << cantidades[i]
                    << " x Q"
                    << precios[i]
                    << " = Q"
                    << cantidades[i] * precios[i]
                    << endl;
            }

            cout << "-----------------------------------------\n";
            cout << "TOTAL: Q" << total << endl;
            cout << "=========================================\n";
        }
        else {

            mysql_query(
                cn.getConector(),
                "ROLLBACK"
            );

            cout << "Error al registrar venta.\n";

            cout << mysql_error(
                cn.getConector()
            ) << endl;
        }

        cn.cerrar_conexion();
    }
};