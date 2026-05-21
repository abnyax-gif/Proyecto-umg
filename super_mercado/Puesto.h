// ==========================================
// Puesto.h
// ==========================================

#pragma once

#include <iostream>
#include <mysql.h>
#include <regex>

#include "ConexionSPBD.h"

using namespace std;

class Puesto {

private:

    int id_puesto = 0;

    string codigo;
    string puesto;

public:

    // ==========================================
    // SETTERS
    // ==========================================

    void setCodigo(string c) {

        codigo = c;
    }

    void setPuesto(string p) {

        puesto = p;
    }

    // ==========================================
    // VALIDACIONES
    // ==========================================

    bool validarCodigo() {

        regex formato(
            "^PU[0-9]{3}$"
        );

        return regex_match(
            codigo,
            formato
        );
    }

    bool validarPuesto() {

        regex formato(
            "^[A-Za-záéíóúÁÉÍÓÚñÑ ]+$"
        );

        return regex_match(
            puesto,
            formato
        );
    }

    // ==========================================
    // INSERTAR
    // ==========================================

    void insertar() {

        ConexionSPBD cn;

        cn.abrir_conexion();

        if (cn.getConector() != NULL) {

            string consulta =
                "INSERT INTO puestos(codigo,puesto) VALUES('" +
                codigo + "','" +
                puesto + "')";

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Puesto ingresado..." << endl;
            }
            else {

                cout << "Error al ingresar puesto..." << endl;
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
                "SELECT * FROM puestos";

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
                cout << "===================================" << endl;
                cout << "ID | CODIGO | PUESTO" << endl;
                cout << "===================================" << endl;

                while (
                    (fila = mysql_fetch_row(resultado))
                    ) {

                    cout
                        << fila[0]
                        << " | "
                        << fila[1]
                        << " | "
                        << fila[2]
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
                "UPDATE puestos SET "
                "codigo='" + codigo +
                "',puesto='" + puesto +
                "' WHERE id_puesto=" +
                to_string(id);

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Puesto modificado..." << endl;
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
                "DELETE FROM puestos WHERE id_puesto=" +
                to_string(id);

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Puesto eliminado..." << endl;
            }
            else {

                cout << "Error al eliminar..." << endl;
            }
        }

        cn.cerrar_conexion();
    }

    // ==========================================
    // BUSCAR PUESTO
    // ==========================================

    void buscarPuesto(int id) {

        ConexionSPBD cn;

        cn.abrir_conexion();

        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        string consulta =
            "SELECT * FROM puestos WHERE id_puesto=" +
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
            cout << "Puesto Encontrado" << endl;
            cout << "==========================" << endl;

            cout << "ID: " << fila[0] << endl;
            cout << "Codigo: " << fila[1] << endl;
            cout << "Puesto: " << fila[2] << endl;
        }
        else {

            cout << "Puesto no encontrado..." << endl;
        }

        cn.cerrar_conexion();
    }
};