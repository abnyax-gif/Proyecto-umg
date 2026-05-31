#pragma once

#include <iostream>
#include <mysql.h>
#include <vector>
#include <string>

#include "ConexionSPBD.h"

using namespace std;

class Compra {

private:

    int id_proveedor = 0;

public:

    void setIdProveedor(int idp) {
        id_proveedor = idp;
    }

    void realizarCompra() {

        ConexionSPBD cn;

        cn.abrir_conexion();

        if (cn.getConector() == NULL) {

            cout << "Error en conexion..." << endl;
            return;
        }

        mysql_query(
            cn.getConector(),
            "START TRANSACTION"
        );

        int no_orden_compra = 1;

        string consultaOrden =
            "SELECT IFNULL(MAX(no_orden_compra),0)+1 FROM compras";

        mysql_query(
            cn.getConector(),
            consultaOrden.c_str()
        );

        MYSQL_RES* resOrden =
            mysql_store_result(
                cn.getConector()
            );

        MYSQL_ROW filaOrden =
            mysql_fetch_row(
                resOrden
            );

        if (filaOrden != NULL) {

            no_orden_compra =
                stoi(
                    string(filaOrden[0])
                );
        }

        mysql_free_result(
            resOrden
        );

        vector<int> productos;
        vector<int> cantidades;
        vector<float> precios;
        vector<string> nombres;

        char continuar = 's';

        while (
            continuar == 's' ||
            continuar == 'S'
            ) {

            int id_producto;
            int cantidad;

            cout << "\n==========================" << endl;
            cout << "       NUEVA COMPRA" << endl;
            cout << "==========================" << endl;

            cout << "ID Producto: ";
            cin >> id_producto;

            cout << "Cantidad: ";
            cin >> cantidad;

            string consultaProducto =
                "SELECT producto,precio_costo "
                "FROM productos WHERE id_producto=" +
                to_string(id_producto);

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consultaProducto.c_str()
                );

            if (!q_estado) {

                MYSQL_RES* resultado =
                    mysql_store_result(
                        cn.getConector()
                    );

                MYSQL_ROW fila =
                    mysql_fetch_row(
                        resultado
                    );

                if (fila != NULL) {

                    string nombre =
                        fila[0];

                    float precio =
                        stof(
                            string(fila[1])
                        );

                    productos.push_back(
                        id_producto
                    );

                    cantidades.push_back(
                        cantidad
                    );

                    precios.push_back(
                        precio
                    );

                    nombres.push_back(
                        nombre
                    );

                    string actualizarStock =
                        "UPDATE productos "
                        "SET existencia = existencia + " +
                        to_string(cantidad) +
                        " WHERE id_producto=" +
                        to_string(id_producto);

                    mysql_query(
                        cn.getConector(),
                        actualizarStock.c_str()
                    );

                    cout << "Producto agregado..." << endl;
                }
                else {

                    cout << "Producto no encontrado..." << endl;
                }

                mysql_free_result(
                    resultado
                );
            }
            else {

                cout << "Error SQL..." << endl;

                cout << mysql_error(
                    cn.getConector()
                ) << endl;
            }

            cout << "\nAgregar otro producto? (s/n): ";
            cin >> continuar;
        }
        if (productos.empty()) {

            cout << "\nNo se agregaron productos a la compra.\n";

            mysql_query(
                cn.getConector(),
                "ROLLBACK"
            );

            cn.cerrar_conexion();

            return;
        }

        string insertarCompra =
            "INSERT INTO compras("
            "no_orden_compra,"
            "id_proveedor,"
            "fecha_orden,"
            "fecha_ingreso"
            ") VALUES(" +
            to_string(no_orden_compra) +
            "," +
            to_string(id_proveedor) +
            ",CURDATE(),NOW())";

        int q_compra =
            mysql_query(
                cn.getConector(),
                insertarCompra.c_str()
            );

        if (!q_compra) {

            long long id_compra =
                mysql_insert_id(
                    cn.getConector()
                );

            for (
                int i = 0;
                i < productos.size();
                i++
                ) {

                string detalle =
                    "INSERT INTO compras_detalle("
                    "id_compra,"
                    "id_producto,"
                    "cantidad,"
                    "precio_costo_unitario"
                    ") VALUES(" +
                    to_string(id_compra) +
                    "," +
                    to_string(productos[i]) +
                    "," +
                    to_string(cantidades[i]) +
                    "," +
                    to_string(precios[i]) +
                    ")";

                mysql_query(
                    cn.getConector(),
                    detalle.c_str()
                );
            }

            mysql_query(
                cn.getConector(),
                "COMMIT"
            );

            cout << "\n==================================" << endl;
            cout << "       COMPRA REGISTRADA" << endl;
            cout << "==================================" << endl;

            cout << "No. Orden: "
                << no_orden_compra
                << endl;

            float total = 0;

            for (
                int i = 0;
                i < productos.size();
                i++
                ) {

                float subtotal =
                    cantidades[i] *
                    precios[i];

                total += subtotal;

                cout
                    << nombres[i]
                    << " | Cantidad: "
                    << cantidades[i]
                    << " | Precio Costo: Q"
                    << precios[i]
                    << " | Subtotal: Q"
                    << subtotal
                    << endl;
            }

            cout << "==================================" << endl;
            cout << "TOTAL: Q" << total << endl;
        }
        else {

            mysql_query(
                cn.getConector(),
                "ROLLBACK"
            );

            cout << "Error al registrar compra..." << endl;

            cout << mysql_error(
                cn.getConector()
            ) << endl;
        }

        cn.cerrar_conexion();
    }
};