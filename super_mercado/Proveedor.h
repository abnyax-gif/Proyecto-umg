#pragma once

#include <iostream>
#include <mysql.h>
#include <regex>

#include "ConexionSPBD.h"

using namespace std;

class Proveedor {

private:

    int id_proveedor = 0;

    string proveedor;
    string nit;
    string direccion;
    string telefono;

public:

    // ==========================================
    // SETTERS
    // ==========================================

    void setProveedor(string p) {
        proveedor = p;
    }

    void setNit(string n) {
        nit = n;
    }

    void setDireccion(string d) {
        direccion = d;
    }

    void setTelefono(string t) {
        telefono = t;
    }

    // ==========================================
    // VALIDACIONES
    // ==========================================

    bool validarProveedor() {

        regex formato(
            "^[A-Za-z0-9áéíóúÁÉÍÓÚñÑ ]+$"
        );

        return regex_match(
            proveedor,
            formato
        );
    }

    bool validarNIT() {

        regex formato(
            "^(C/F|c/f|CF|cf|[0-9-]+)$"
        );

        return regex_match(
            nit,
            formato
        );
    }

    bool validarTelefono() {

        regex formato(
            "^[0-9]{8}$"
        );

        return regex_match(
            telefono,
            formato
        );
    }

    bool validarDireccion() {

        return !direccion.empty();
    }

    // ==========================================
    // INSERTAR
    // ==========================================

    void insertar() {

        ConexionSPBD cn;

        cn.abrir_conexion();

        if (cn.getConector() != NULL) {

            string consulta =
                "INSERT INTO proveedores(proveedor,nit,direccion,telefono) VALUES('" +
                proveedor + "','" +
                nit + "','" +
                direccion + "','" +
                telefono + "')";

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Proveedor ingresado correctamente..." << endl;
            }
            else {

                cout << "Error al ingresar proveedor..." << endl;
                cout << mysql_error(cn.getConector()) << endl;
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
                "SELECT * FROM proveedores";

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                resultado =
                    mysql_store_result(
                        cn.getConector()
                    );

                cout << endl;
                cout << "============================================================" << endl;
                cout << "ID | PROVEEDOR | NIT | TELEFONO" << endl;
                cout << "============================================================" << endl;

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
                        << fila[4]
                        << endl;
                }

                mysql_free_result(resultado);
            }
            else {

                cout << "Error en consulta..." << endl;
                cout << mysql_error(cn.getConector()) << endl;
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
                "UPDATE proveedores SET "
                "proveedor='" + proveedor +
                "',nit='" + nit +
                "',direccion='" + direccion +
                "',telefono='" + telefono +
                "' WHERE id_proveedor=" +
                to_string(id);

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Proveedor modificado correctamente..." << endl;
            }
            else {

                cout << "Error al modificar proveedor..." << endl;
                cout << mysql_error(cn.getConector()) << endl;
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
                "DELETE FROM proveedores WHERE id_proveedor=" +
                to_string(id);

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Proveedor eliminado correctamente..." << endl;
            }
            else {

                cout << "Error al eliminar proveedor..." << endl;
                cout << mysql_error(cn.getConector()) << endl;
            }
        }

        cn.cerrar_conexion();
    }

    // ==========================================
    // BUSCAR
    // ==========================================

    void buscarProveedor(int id) {

        ConexionSPBD cn;

        cn.abrir_conexion();

        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        string consulta =
            "SELECT * FROM proveedores WHERE id_proveedor=" +
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
            cout << "PROVEEDOR ENCONTRADO" << endl;
            cout << "==============================" << endl;

            cout << "ID: " << fila[0] << endl;
            cout << "Proveedor: " << fila[1] << endl;
            cout << "NIT: " << fila[2] << endl;
            cout << "Direccion: " << fila[3] << endl;
            cout << "Telefono: " << fila[4] << endl;
        }
        else {

            cout << "Proveedor no encontrado..." << endl;
        }

        mysql_free_result(resultado);

        cn.cerrar_conexion();
    }
};