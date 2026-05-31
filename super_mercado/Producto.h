#pragma once

#include <iostream>
#include <mysql.h>
#include <regex>
#include <string>

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

        regex formato("^P[0-9]{3}$");

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

    bool validarPrecioCosto() {

        return precio_costo > 0;
    }

    bool validarPrecioVenta() {

        return precio_venta > 0;
    }

    bool validarExistencia() {

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
                "INSERT INTO productos(producto,id_marca,descripcion,precio_costo,precio_venta,existencia,codigo) VALUES('" +
                producto + "'," +
                to_string(id_marca) + ",'" +
                descripcion + "'," +
                to_string(precio_costo) + "," +
                to_string(precio_venta) + "," +
                to_string(existencia) + ",'" +
                codigo + "')";

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Producto ingresado..." << endl;
            }
            else {

                cout << "Error al ingresar producto..." << endl;

                cout << mysql_error(
                    cn.getConector()
                ) << endl;
            }
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

            mysql_query(
                cn.getConector(),
                consulta.c_str()
            );

            resultado =
                mysql_store_result(
                    cn.getConector()
                );

            cout << endl;

            cout << "==========================================================" << endl;
            cout << "ID | CODIGO | PRODUCTO | PRECIO VENTA | EXISTENCIA" << endl;
            cout << "==========================================================" << endl;

            while (
                (fila = mysql_fetch_row(resultado))
                ) {

                cout
                    << fila[0]
                    << " | "
                    << fila[9]
                    << " | "
                    << fila[1]
                    << " | "
                    << fila[6]
                    << " | "
                    << fila[7]
                    << endl;
            }

            mysql_free_result(resultado);
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
                "producto='" + producto +
                "',id_marca=" + to_string(id_marca) +
                ",descripcion='" + descripcion +
                "',precio_costo=" + to_string(precio_costo) +
                ",precio_venta=" + to_string(precio_venta) +
                ",existencia=" + to_string(existencia) +
                ",codigo='" + codigo +
                "' WHERE id_producto=" +
                to_string(id);

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Producto modificado..." << endl;
            }
            else {

                cout << "Error al modificar..." << endl;

                cout << mysql_error(
                    cn.getConector()
                ) << endl;
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

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Producto eliminado..." << endl;
            }
            else {

                cout << "Error al eliminar..." << endl;

                cout << mysql_error(
                    cn.getConector()
                ) << endl;
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

            cout << "==============================" << endl;
            cout << "Producto Encontrado" << endl;
            cout << "==============================" << endl;

            cout << "ID: " << fila[0] << endl;
            cout << "Producto: " << fila[1] << endl;
            cout << "ID Marca: " << fila[2] << endl;
            cout << "Descripcion: " << fila[3] << endl;
            cout << "Precio Costo: " << fila[5] << endl;
            cout << "Precio Venta: " << fila[6] << endl;
            cout << "Existencia: " << fila[7] << endl;
            cout << "Codigo: " << fila[9] << endl;
        }
        else {

            cout << "Producto no encontrado..." << endl;
        }

        mysql_free_result(resultado);

        cn.cerrar_conexion();
    }
};