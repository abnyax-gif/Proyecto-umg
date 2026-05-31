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

    string nit;
    string correo_electronico;
    string genero;

public:

    // ==========================================
    // SETTERS
    // ==========================================

    void setNombres(string n) {
        nombres = n;
    }

    void setApellidos(string a) {
        apellidos = a;
    }

    void setTelefono(string t) {
        telefono = t;
    }

    void setNit(string n) {
        nit = n;
    }

    void setCorreo(string c) {
        correo_electronico = c;
    }

    void setGenero(string g) {
        genero = g;
    }

    // ==========================================
    // VALIDACIONES
    // ==========================================

    bool validarNombres() {
        return validarTexto(nombres);
    }

    bool validarApellidos() {
        return validarTexto(apellidos);
    }

    bool validarTelefonoCliente() {
        return validarTelefono(telefono);
    }

    bool validarNitCliente() {

        regex formato(
            "^(C/F|c/f|CF|cf|[0-9-]+)$"
        );

        return regex_match(
            nit,
            formato
        );
    }

    bool validarCorreoCliente() {
        return validarCorreo(correo_electronico);
    }

    bool validarGeneroCliente() {

        regex formato("^[01]$");

        return regex_match(
            genero,
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
                "INSERT INTO clientes("
                "nombres,"
                "apellidos,"
                "nit,"
                "genero,"
                "telefono,"
                "correo_electronico,"
                "fecha_ingreso"
                ") VALUES('" +
                nombres + "','" +
                apellidos + "','" +
                nit + "',b'" +
                genero + "','" +
                telefono + "','" +
                correo_electronico +
                "',NOW())";

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Cliente ingresado correctamente..." << endl;
            }
            else {

                cout << "Error al ingresar cliente..." << endl;
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
                "SELECT * FROM clientes";

            mysql_query(
                cn.getConector(),
                consulta.c_str()
            );

            resultado =
                mysql_store_result(
                    cn.getConector()
                );

            cout << endl;
            cout << "============================================================" << endl;
            cout << "ID | NOMBRES | APELLIDOS | NIT | TELEFONO" << endl;
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
                    << fila[3]
                    << " | "
                    << fila[5]
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
                "UPDATE clientes SET "
                "nombres='" + nombres +
                "',apellidos='" + apellidos +
                "',nit='" + nit +
                "',genero=b'" + genero +
                "',telefono='" + telefono +
                "',correo_electronico='" + correo_electronico +
                "' WHERE id_cliente=" +
                to_string(id);

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Cliente modificado correctamente..." << endl;
            }
            else {

                cout << "Error al modificar cliente..." << endl;
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
                "DELETE FROM clientes WHERE id_cliente=" +
                to_string(id);

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Cliente eliminado correctamente..." << endl;
            }
            else {

                cout << "Error al eliminar cliente..." << endl;
                cout << mysql_error(cn.getConector()) << endl;
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
            cout << "CLIENTE ENCONTRADO" << endl;
            cout << "==============================" << endl;

            cout << "ID: " << fila[0] << endl;
            cout << "Nombres: " << fila[1] << endl;
            cout << "Apellidos: " << fila[2] << endl;
            cout << "NIT: " << fila[3] << endl;
            cout << "Genero: " << (fila[4][0] == '1' ? "Masculino" : "Femenino") << endl;
            cout << "Telefono: " << fila[5] << endl;
            cout << "Correo: " << fila[6] << endl;
            cout << "Fecha Ingreso: " << fila[7] << endl;
        }
        else {

            cout << "Cliente no encontrado..." << endl;
        }

        mysql_free_result(resultado);

        cn.cerrar_conexion();
    }
};