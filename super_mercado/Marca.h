    // ==========================================
    // Marca.h
    // ==========================================

    #pragma once

    #include <iostream>
    #include <mysql.h>
    #include <regex>

    #include "ConexionSPBD.h"

    using namespace std;

    class Marca {

    private:

        int id_marca = 0;

        string marca;

    public:

        // ==========================================
        // SETTERS
        // ==========================================

        void setMarca(string m) {

            marca = m;
        }

        // ==========================================
        // VALIDAR
        // ==========================================

        bool validarMarca() {

            regex formato(
                "^[A-Za-z0-9áéíóúÁÉÍÓÚñÑ ]+$"
            );

            return regex_match(
                marca,
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
                    "INSERT INTO marcas(marca) VALUES('" +
                    marca + "')";

                const char* c =
                    consulta.c_str();

                int q_estado =
                    mysql_query(
                        cn.getConector(),
                        c
                    );

                if (!q_estado) {

                    cout << "Marca ingresada..." << endl;
                }
                else {

                    cout << "Error al ingresar marca..." << endl;
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
                    "SELECT * FROM marcas";

                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

                resultado =
                    mysql_store_result(
                        cn.getConector()
                    );

                cout << endl;
                cout << "======================" << endl;
                cout << "ID | MARCA" << endl;
                cout << "======================" << endl;

                while (
                    (fila = mysql_fetch_row(resultado))
                    ) {

                    cout
                        << fila[0]
                        << " | "
                        << fila[1]
                        << endl;
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

            string consulta =
                "UPDATE marcas SET marca='" +
                marca +
                "' WHERE id_marca=" +
                to_string(id);

            mysql_query(
                cn.getConector(),
                consulta.c_str()
            );

            cout << "Marca modificada..." << endl;

            cn.cerrar_conexion();
        }

        // ==========================================
        // ELIMINAR
        // ==========================================

        void eliminar(int id) {

            ConexionSPBD cn;

            cn.abrir_conexion();

            string consulta =
                "DELETE FROM marcas WHERE id_marca=" +
                to_string(id);

            mysql_query(
                cn.getConector(),
                consulta.c_str()
            );

            cout << "Marca eliminada..." << endl;

            cn.cerrar_conexion();
        }
    };