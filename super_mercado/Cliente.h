// ==========================================
// Cliente.h
// ==========================================

#pragma once

#include <iostream>
#include <mysql.h>
#include <regex>

#include "Persona.h"
#include "ConexionSPBD.h"

using namespace std;

class Cliente : public Persona {

private:

    int id_cliente = 0;

    string codigo;
    string nit;
    string correo;
    string genero;

public:

    // ==========================================
    // SETTERS
    // ==========================================

    void setCodigo(string c) {

        codigo = c;
    }

    void setNombres(string n) {

        nombres = n;
    }

    void setApellidos(string a) {

        apellidos = a;
    }

    void setDireccion(string d) {

        direccion = d;
    }

    void setTelefono(string t) {

        telefono = t;
    }

    void setNit(string n) {

        nit = n;
    }

    void setCorreo(string c) {

        correo = c;
    }

    void setGenero(string g) {

        genero = g;
    }

    // ==========================================
    // VALIDACIONES
    // ==========================================

    bool validarCodigo() {

        regex formato(
            "^C[0-9]{3}$"
        );

        return regex_match(
            codigo,
            formato
        );
    }

    bool validarNombres() {

        return validarTexto(
            nombres
        );
    }

    bool validarApellidos() {

        return validarTexto(
            apellidos
        );
    }

    bool validarDireccion() {

        return direccion != "";
    }

    bool validarTelefonoCliente() {

        return validarTelefono(
            telefono
        );
    }

    bool validarNitCliente() {

        return validarNIT(
            nit
        );
    }

    bool validarCorreoCliente() {

        return validarCorreo(
            correo
        );
    }

    bool validarGeneroCliente() {

        return validarGenero(
            genero
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
                "INSERT INTO clientes(codigo,nombres,apellidos,direccion,telefono,nit,correo,genero) VALUES('" +
                codigo + "','" +
                nombres + "','" +
                apellidos + "','" +
                direccion + "','" +
                telefono + "','" +
                nit + "','" +
                correo + "','" +
                genero + "')";

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Cliente ingresado..." << endl;
            }
            else {

                cout << "Error al ingresar cliente..." << endl;
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
                "SELECT * FROM clientes";

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
                cout << "========================================================" << endl;
                cout << "ID | CODIGO | NOMBRES | APELLIDOS | TELEFONO" << endl;
                cout << "========================================================" << endl;

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
                "UPDATE clientes SET "
                "codigo='" + codigo +
                "',nombres='" + nombres +
                "',apellidos='" + apellidos +
                "',direccion='" + direccion +
                "',telefono='" + telefono +
                "',nit='" + nit +
                "',correo='" + correo +
                "',genero='" + genero +
                "' WHERE id_cliente=" +
                to_string(id);

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Cliente modificado..." << endl;
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
                "DELETE FROM clientes WHERE id_cliente=" +
                to_string(id);

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Cliente eliminado..." << endl;
            }
            else {

                cout << "Error al eliminar..." << endl;
            }
        }

        cn.cerrar_conexion();
    }

    // ==========================================
    // BUSCAR CLIENTE
    // ==========================================

    void buscarCliente(int id) {

        ConexionSPBD cn;

        cn.abrir_conexion();

        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        string consulta =
            "SELECT * FROM clientes WHERE id_cliente=" +
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
            cout << "Cliente Encontrado" << endl;
            cout << "==============================" << endl;

            cout << "ID: " << fila[0] << endl;
            cout << "Codigo: " << fila[1] << endl;
            cout << "Nombres: " << fila[2] << endl;
            cout << "Apellidos: " << fila[3] << endl;
            cout << "Direccion: " << fila[4] << endl;
            cout << "Telefono: " << fila[5] << endl;
            cout << "NIT: " << fila[6] << endl;
            cout << "Correo: " << fila[7] << endl;
            cout << "Genero: " << fila[8] << endl;
        }
        else {

            cout << "Cliente no encontrado..." << endl;
        }

        cn.cerrar_conexion();
    }
};