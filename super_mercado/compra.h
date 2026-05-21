// ==========================================
// Compra.h
// ==========================================

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
    int id_empleado = 0;

    int no_orden_compra = 1;

public:

    void setIdProveedor(int idp) {
        id_proveedor = idp;
    }

    void setIdEmpleado(int ide) {
        id_empleado = ide;
    }

    void realizarCompra() {

        ConexionSPBD cn;
        cn.abrir_conexion();

        if (cn.getConector() != NULL) {

            int id_producto;
            int cantidad;

            float precio_costo = 0;
            float subtotal = 0;
            float total = 0;

            char continuar = 's';

            vector<int> productos;
            vector<int> cantidades;
            vector<float> precios;
            vector<float> subtotales;

            while (continuar == 's' || continuar == 'S') {

                cout << "\n==========================\n";
                cout << "      NUEVA COMPRA        \n";
                cout << "==========================\n";

                cout << "ID Producto: ";
                cin >> id_producto;

                cout << "Cantidad: ";
                cin >> cantidad;

                string consulta =
                    "SELECT precio_costo FROM productos WHERE id_producto=" +
                    to_string(id_producto);

                mysql_query(cn.getConector(), consulta.c_str());

                MYSQL_RES* resultado = mysql_store_result(cn.getConector());
                MYSQL_ROW fila = mysql_fetch_row(resultado);

                if (fila != NULL) {

                    precio_costo = stof(string(fila[0])); 

                    subtotal = precio_costo * cantidad;
                    total += subtotal;

                    productos.push_back(id_producto);
                    cantidades.push_back(cantidad);
                    precios.push_back(precio_costo);
                    subtotales.push_back(subtotal);

                    string actualizar =
                        "UPDATE productos SET existencia = existencia + " +
                        to_string(cantidad) +
                        " WHERE id_producto=" +
                        to_string(id_producto);

                    mysql_query(cn.getConector(), actualizar.c_str());

                    cout << "Producto agregado...\n";
                }
                else {
                    cout << "Producto no encontrado...\n";
                }

                cout << "\nDesea agregar otro producto? (s/n): ";
                cin >> continuar;
            }

            string compra =
                "INSERT INTO compras(no_orden_compra,fecha,id_proveedor,id_empleado,total) VALUES(" +
                to_string(no_orden_compra) +
                ",NOW()," +
                to_string(id_proveedor) +
                "," +
                to_string(id_empleado) +
                "," +
                to_string(total) +
                ")";

            mysql_query(cn.getConector(), compra.c_str());

            long long id_compra = mysql_insert_id(cn.getConector());

            for (int i = 0; i < productos.size(); i++) {

                string detalle =
                    "INSERT INTO compras_detalle(id_compra,id_producto,cantidad,costo,subtotal) VALUES(" +
                    to_string(id_compra) + "," +
                    to_string(productos[i]) + "," +
                    to_string(cantidades[i]) + "," +
                    to_string(precios[i]) + "," +
                    to_string(subtotales[i]) +
                    ")";

                mysql_query(cn.getConector(), detalle.c_str());
            }

            cout << "\n======================================\n";
            cout << "          COMPRA REALIZADA           \n";
            cout << "======================================\n";
            cout << "Orden Compra: " << no_orden_compra << endl;

            for (int i = 0; i < productos.size(); i++) {
                cout << "Producto ID: " << productos[i]
                    << " Cantidad: " << cantidades[i]
                    << " Subtotal: Q" << subtotales[i] << endl;
            }

            cout << "TOTAL: Q" << total << endl;

            no_orden_compra++;
        }
        else {
            cout << "Error en conexion...\n";
        }

        cn.cerrar_conexion();
    }
};
