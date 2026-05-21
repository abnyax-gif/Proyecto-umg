#pragma once

#include <iostream>
#include <mysql.h>
#include <vector>
#include <string>   

#include "ConexionSPBD.h"

using namespace std;

class Venta {

private:

    int id_cliente = 0;
    int id_empleado = 0;

    int no_factura = 1;
    string serie = "A";

public:

    void setIdCliente(int idc) {
        id_cliente = idc;
    }

    void setIdEmpleado(int ide) {
        id_empleado = ide;
    }

    void realizarVenta() {

        ConexionSPBD cn;
        cn.abrir_conexion();

        if (cn.getConector() != NULL) {

            int id_producto;
            int cantidad;

            float precio = 0;
            float subtotal = 0;
            float total = 0;

            char continuar = 's';

            vector<int> productos;
            vector<int> cantidades;
            vector<float> precios;
            vector<float> subtotales;

            while (continuar == 's' || continuar == 'S') {

                cout << "\n==========================\n";
                cout << "       NUEVO PRODUCTO     \n";
                cout << "==========================\n";

                cout << "ID Producto: ";
                cin >> id_producto;

                cout << "Cantidad: ";
                cin >> cantidad;

                string consulta =
                    "SELECT precio_venta, existencia FROM productos WHERE id_producto=" +
                    to_string(id_producto);

                mysql_query(cn.getConector(), consulta.c_str());

                MYSQL_RES* resultado = mysql_store_result(cn.getConector());
                MYSQL_ROW fila = mysql_fetch_row(resultado);

                if (fila != NULL) {

                    precio = stof(string(fila[0])); // 👈 CORREGIDO
                    int stock = stoi(string(fila[1])); // 👈 CORREGIDO

                    if (cantidad <= stock) {

                        subtotal = precio * cantidad;
                        total += subtotal;

                        productos.push_back(id_producto);
                        cantidades.push_back(cantidad);
                        precios.push_back(precio);
                        subtotales.push_back(subtotal);

                        string actualizar =
                            "UPDATE productos SET existencia = existencia - " +
                            to_string(cantidad) +
                            " WHERE id_producto=" +
                            to_string(id_producto);

                        mysql_query(cn.getConector(), actualizar.c_str());

                        cout << "Producto agregado...\n";
                    }
                    else {
                        cout << "Stock insuficiente...\n";
                    }
                }
                else {
                    cout << "Producto no encontrado...\n";
                }

                cout << "\nDesea agregar otro producto? (s/n): ";
                cin >> continuar;
            }

            string venta =
                "INSERT INTO ventas(no_factura,serie,fecha,id_cliente,id_empleado,total) VALUES(" +
                to_string(no_factura) +
                ",'" + serie + "',NOW()," +
                to_string(id_cliente) +
                "," +
                to_string(id_empleado) +
                "," +
                to_string(total) +
                ")";

            mysql_query(cn.getConector(), venta.c_str());

            long long id_venta = mysql_insert_id(cn.getConector());

            for (int i = 0; i < productos.size(); i++) {

                string detalle =
                    "INSERT INTO ventas_detalle(id_venta,id_producto,cantidad,precio,subtotal) VALUES(" +
                    to_string(id_venta) + "," +
                    to_string(productos[i]) + "," +
                    to_string(cantidades[i]) + "," +
                    to_string(precios[i]) + "," +
                    to_string(subtotales[i]) +
                    ")";

                mysql_query(cn.getConector(), detalle.c_str());
            }

            cout << "\n======================================\n";
            cout << "              FACTURA                \n";
            cout << "======================================\n";
            cout << "Serie: " << serie << endl;
            cout << "Factura: " << no_factura << endl;

            for (int i = 0; i < productos.size(); i++) {
                cout << "Producto ID: " << productos[i]
                    << " Cantidad: " << cantidades[i]
                    << " Subtotal: Q" << subtotales[i] << endl;
            }

            cout << "TOTAL: Q" << total << endl;

            no_factura++;
        }
        else {
            cout << "Error en conexion...\n";
        }

        cn.cerrar_conexion();
    }
};