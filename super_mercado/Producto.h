// ==========================================
// Producto.h
// ==========================================

#pragma once

#include <iostream>
#include <mysql.h>
#include <regex>

#include "ConexionSPBD.h"

using namespace std;

class Producto {

private:

    int id_producto = 0;

    string codigo;
    string producto;
    string descripcion;

    float precio_costo = 0;
    float precio_venta = 0;

    int existencia = 0;
    int id_marca = 0;

public:

    // ==========================================
    // SETTERS
    // ==========================================

    void setCodigo(string c) {

        codigo = c;
    }

    void setProducto(string p) {

        producto = p;
    }

    void setDescripcion(string d) {

        descripcion = d;
    }

    void setPrecioCosto(float pc) {

        precio_costo = pc;
    }

    void setPrecioVenta(float pv) {

        precio_venta = pv;
    }

    void setExistencia(int e) {

        existencia = e;
    }

    void setIdMarca(int idm) {

        id_marca = idm;
    }

    // ==========================================
    // VALIDACIONES
    // ==========================================

    bool validarCodigo() {

        regex formato(
            "^P[0-9]{3}$"
        );

        return regex_match(
            codigo,
            formato
        );
    }

    bool validarProducto() {

        regex formato(
            "^[A-Za-z0-9áéíóúÁÉÍÓÚñÑ ]+$"
        );

        return regex_match(
            producto,
            formato
        );
    }

    bool validarDescripcion() {

        return descripcion != "";
    }

    bool validarPrecio(float precio) {

        return precio > 0;
    }

    bool validarExistencia(int existencia) {

        return existencia >= 0;
    }

    // ==========================================
    // INSERTAR
    // ==========================================

    void insertar() {

        ConexionSPBD cn;

        cn.abrir_conexion();

        if (cn.getConector() != NULL) {

            string consulta =
                "INSERT INTO productos(codigo,producto,descripcion,precio_costo,precio_venta,existencia,id_marca) VALUES('" +
                codigo + "','" +
                producto + "','" +
                descripcion + "'," +
                to_string(precio_costo) + "," +
                to_string(precio_venta) + "," +
                to_string(existencia) + "," +
                to_string(id_marca) + ")";

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Producto ingresado..." << endl;
            }
            else {

                cout << "Error al ingresar producto..." << endl;
            }
        }
        else {

            cout << "Error en conexion..." << endl;
        }

        cn.cerrar_conexion();
    }

    // ==========================================
    // MOSTRAR
    // ==========================================

    void mostrar() {

        ConexionSPBD cn;

        cn.abrir_conexion();

        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        if (cn.getConector() != NULL) {

            string consulta =
                "SELECT * FROM productos";

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                resultado =
                    mysql_store_result(
                        cn.getConector()
                    );

                cout << endl;
                cout << "==============================================" << endl;
                cout << "ID | CODIGO | PRODUCTO | PRECIO | EXISTENCIA" << endl;
                cout << "==============================================" << endl;

                while (
                    (fila = mysql_fetch_row(resultado))
                    ) {

                    cout
                        << fila[0]
                        << " | "
                        << fila[1]
                        << " | "
                        << fila[2]
                        << " | "
                        << fila[5]
                        << " | "
                        << fila[6]
                        << endl;
                }
            }
            else {

                cout << "Error en consulta..." << endl;
            }
        }

        cn.cerrar_conexion();
    }

    // ==========================================
    // MODIFICAR
    // ==========================================

    void modificar(int id) {

        ConexionSPBD cn;

        cn.abrir_conexion();

        if (cn.getConector() != NULL) {

            string consulta =
                "UPDATE productos SET "
                "codigo='" + codigo +
                "',producto='" + producto +
                "',descripcion='" + descripcion +
                "',precio_costo=" + to_string(precio_costo) +
                ",precio_venta=" + to_string(precio_venta) +
                ",existencia=" + to_string(existencia) +
                ",id_marca=" + to_string(id_marca) +
                " WHERE id_producto=" + to_string(id);

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Producto modificado..." << endl;
            }
            else {

                cout << "Error al modificar..." << endl;
            }
        }

        cn.cerrar_conexion();
    }

    // ==========================================
    // ELIMINAR
    // ==========================================

    void eliminar(int id) {

        ConexionSPBD cn;

        cn.abrir_conexion();

        if (cn.getConector() != NULL) {

            string consulta =
                "DELETE FROM productos WHERE id_producto=" +
                to_string(id);

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Producto eliminado..." << endl;
            }
            else {

                cout << "Error al eliminar..." << endl;
            }
        }

        cn.cerrar_conexion();
    }

    // ==========================================
    // BUSCAR PRODUCTO
    // ==========================================

    void buscarProducto(int id) {

        ConexionSPBD cn;

        cn.abrir_conexion();

        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        string consulta =
            "SELECT * FROM productos WHERE id_producto=" +
            to_string(id);

        mysql_query(
            cn.getConector(),
            consulta.c_str()
        );

        resultado =
            mysql_store_result(
                cn.getConector()
            );

        fila =
            mysql_fetch_row(
                resultado
            );

        if (fila != NULL) {

            cout << endl;
            cout << "==========================" << endl;
            cout << "Producto Encontrado" << endl;
            cout << "==========================" << endl;

            cout << "ID: " << fila[0] << endl;
            cout << "Codigo: " << fila[1] << endl;
            cout << "Producto: " << fila[2] << endl;
            cout << "Descripcion: " << fila[3] << endl;
            cout << "Precio Costo: " << fila[4] << endl;
            cout << "Precio Venta: " << fila[5] << endl;
            cout << "Existencia: " << fila[6] << endl;
        }
        else {

            cout << "Producto no encontrado..." << endl;
        }

        cn.cerrar_conexion();
    }
};