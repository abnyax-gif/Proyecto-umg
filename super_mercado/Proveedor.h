// ==========================================
// Proveedor.h
// ==========================================

#pragma once

#include <iostream>
#include <mysql.h>
#include <regex>

#include "ConexionSPBD.h"

using namespace std;

class Proveedor {

private:

    int id_proveedor = 0;

    string codigo;
    string proveedor;
    string nit;
    string direccion;
    string telefono;

public:

    // ==========================================
    // SETTERS
    // ==========================================

    void setCodigo(string c) {

        codigo = c;
    }

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

    bool validarCodigo() {

        regex formato(
            "^PR[0-9]{3}$"
        );

        return regex_match(
            codigo,
            formato
        );
    }

    bool validarProveedor() {

        regex formato(
            "^[A-Za-z0-9áéíóúÁÉÍÓÚñÑ ]+$"
        );

        return regex_match(
            proveedor,
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

    bool validarNIT() {

        regex formato(
            "^[0-9CFcf-]+$"
        );

        return regex_match(
            nit,
            formato
        );
    }

    bool validarDireccion() {

        return direccion != "";
    }

    // ==========================================
    // INSERTAR
    // ==========================================

    void insertar() {

        ConexionSPBD cn;

        cn.abrir_conexion();

        if (cn.getConector() != NULL) {

            string consulta =
                "INSERT INTO proveedores(codigo,proveedor,nit,direccion,telefono) VALUES('" +
                codigo + "','" +
                proveedor + "','" +
                nit + "','" +
                direccion + "','" +
                telefono + "')";

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Proveedor ingresado..." << endl;
            }
            else {

                cout << "Error al ingresar proveedor..." << endl;
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
                "SELECT * FROM proveedores";

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
                cout << "======================================================" << endl;
                cout << "ID | CODIGO | PROVEEDOR | NIT | TELEFONO" << endl;
                cout << "======================================================" << endl;

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
                        << fila[3]
                        << " | "
                        << fila[5]
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
                "UPDATE proveedores SET "
                "codigo='" + codigo +
                "',proveedor='" + proveedor +
                "',nit='" + nit +
                "',direccion='" + direccion +
                "',telefono='" + telefono +
                "' WHERE id_proveedor=" +
                to_string(id);

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Proveedor modificado..." << endl;
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
                "DELETE FROM proveedores WHERE id_proveedor=" +
                to_string(id);

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Proveedor eliminado..." << endl;
            }
            else {

                cout << "Error al eliminar..." << endl;
            }
        }

        cn.cerrar_conexion();
    }

    // ==========================================
    // BUSCAR PROVEEDOR
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
            cout << "===============================" << endl;
            cout << "Proveedor Encontrado" << endl;
            cout << "===============================" << endl;

            cout << "ID: " << fila[0] << endl;
            cout << "Codigo: " << fila[1] << endl;
            cout << "Proveedor: " << fila[2] << endl;
            cout << "NIT: " << fila[3] << endl;
            cout << "Direccion: " << fila[4] << endl;
            cout << "Telefono: " << fila[5] << endl;
        }
        else {

            cout << "Proveedor no encontrado..." << endl;
        }

        cn.cerrar_conexion();
    }
};