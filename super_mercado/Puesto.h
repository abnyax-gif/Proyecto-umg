#pragma once

#include <iostream>
#include <mysql.h>
#include <regex>

#include "ConexionSPBD.h"

using namespace std;

class Puesto {

private:

    int id_puesto = 0;
    string puesto;

public:

    // ==========================================
    // SETTER
    // ==========================================

    void setPuesto(string p) {
        puesto = p;
    }

    // ==========================================
    // VALIDACION
    // ==========================================

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
                "INSERT INTO puestos(puesto) VALUES('" +
                puesto + "')";

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Puesto ingresado correctamente..." << endl;
            }
            else {

                cout << "Error al ingresar puesto..." << endl;
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
                "SELECT * FROM puestos";

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
                cout << "==========================" << endl;
                cout << "ID | PUESTO" << endl;
                cout << "==========================" << endl;

                while (
                    (fila = mysql_fetch_row(resultado))
                    ) {

                    cout
                        << fila[0]
                        << " | "
                        << fila[1]
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
                "UPDATE puestos SET "
                "puesto='" + puesto +
                "' WHERE id_puesto=" +
                to_string(id);

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Puesto modificado correctamente..." << endl;
            }
            else {

                cout << "Error al modificar puesto..." << endl;
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
                "DELETE FROM puestos WHERE id_puesto=" +
                to_string(id);

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Puesto eliminado correctamente..." << endl;
            }
            else {

                cout << "Error al eliminar puesto..." << endl;
                cout << mysql_error(cn.getConector()) << endl;
            }
        }

        cn.cerrar_conexion();
    }

    // ==========================================
    // BUSCAR
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
            cout << "PUESTO ENCONTRADO" << endl;
            cout << "==========================" << endl;

            cout << "ID: "
                << fila[0]
                << endl;

            cout << "Puesto: "
                << fila[1]
                << endl;
        }
        else {

            cout << "Puesto no encontrado..." << endl;
        }

        mysql_free_result(resultado);

        cn.cerrar_conexion();
    }
};