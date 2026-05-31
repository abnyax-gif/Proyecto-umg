#pragma once

#include <iostream>
#include <mysql.h>
#include <regex>

#include "Persona.h"
#include "ConexionSPBD.h"

using namespace std;

class Empleado : public Persona {

private:

    int id_empleado = 0;

    string cui;
    string genero;
    string fecha_nacimiento;
    string fecha_inicio_laborales;

    int id_puesto = 0;

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

    void setDireccion(string d) {
        direccion = d;
    }

    void setTelefono(string t) {
        telefono = t;
    }

    void setCUI(string c) {
        cui = c;
    }

    void setGenero(string g) {
        genero = g;
    }

    void setFechaNacimiento(string f) {
        fecha_nacimiento = f;
    }

    void setFechaInicioLaborales(string f) {
        fecha_inicio_laborales = f;
    }

    void setIdPuesto(int idp) {
        id_puesto = idp;
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

    bool validarDireccion() {
        return !direccion.empty();
    }

    bool validarTelefonoEmpleado() {
        return validarTelefono(telefono);
    }

    bool validarCUIEmpleado() {
        return validarDPI(cui);
    }

    bool validarGeneroEmpleado() {

        regex formato("^[01]$");

        return regex_match(
            genero,
            formato
        );
    }

    bool validarFechaNacimiento() {
        return validarFecha(fecha_nacimiento);
    }

    bool validarFechaInicioLaborales() {
        return validarFecha(fecha_inicio_laborales);
    }

    // ==========================================
    // INSERTAR
    // ==========================================

    void insertar() {

        ConexionSPBD cn;

        cn.abrir_conexion();

        if (cn.getConector() != NULL) {

            string consulta =
                "INSERT INTO empleados("
                "nombre,"
                "apellidos,"
                "direccion,"
                "telefono,"
                "cui,"
                "genero,"
                "fecha_nacimiento,"
                "id_puesto,"
                "fecha_inicio_laborales,"
                "fecha_ingreso"
                ") VALUES('" +
                nombres + "','" +
                apellidos + "','" +
                direccion + "','" +
                telefono + "','" +
                cui + "',b'" +
                genero + "','" +
                fecha_nacimiento + "'," +
                to_string(id_puesto) + ",'" +
                fecha_inicio_laborales +
                "',NOW())";

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Empleado ingresado correctamente..." << endl;
            }
            else {

                cout << "Error al ingresar empleado..." << endl;
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
                "SELECT * FROM empleados";

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
            cout << "ID | NOMBRE | APELLIDOS | CUI" << endl;
            cout << "==========================================================" << endl;

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
                "UPDATE empleados SET "
                "nombre='" + nombres +
                "',apellidos='" + apellidos +
                "',direccion='" + direccion +
                "',telefono='" + telefono +
                "',cui='" + cui +
                "',genero=b'" + genero +
                "',fecha_nacimiento='" + fecha_nacimiento +
                "',id_puesto=" + to_string(id_puesto) +
                ",fecha_inicio_laborales='" + fecha_inicio_laborales +
                "' WHERE id_empleado=" +
                to_string(id);

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Empleado modificado correctamente..." << endl;
            }
            else {

                cout << "Error al modificar empleado..." << endl;
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
                "DELETE FROM empleados WHERE id_empleado=" +
                to_string(id);

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    consulta.c_str()
                );

            if (!q_estado) {

                cout << "Empleado eliminado correctamente..." << endl;
            }
            else {

                cout << "Error al eliminar empleado..." << endl;
                cout << mysql_error(cn.getConector()) << endl;
            }
        }

        cn.cerrar_conexion();
    }

    // ==========================================
    // BUSCAR
    // ==========================================

    void buscarEmpleado(int id) {

        ConexionSPBD cn;

        cn.abrir_conexion();

        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        string consulta =
            "SELECT * FROM empleados WHERE id_empleado=" +
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
            cout << "EMPLEADO ENCONTRADO" << endl;
            cout << "==============================" << endl;

            cout << "ID: " << fila[0] << endl;
            cout << "Nombre: " << fila[1] << endl;
            cout << "Apellidos: " << fila[2] << endl;
            cout << "Direccion: " << fila[3] << endl;
            cout << "Telefono: " << fila[4] << endl;
            cout << "CUI: " << fila[5] << endl;
            cout << "Genero: " << (fila[6][0] == '1' ? "Masculino" : "Femenino") << endl;
            cout << "Fecha Nacimiento: " << fila[7] << endl;
            cout << "ID Puesto: " << fila[8] << endl;
            cout << "Fecha Inicio Laborales: " << fila[9] << endl;
            cout << "Fecha Ingreso: " << fila[10] << endl;
        }
        else {

            cout << "Empleado no encontrado..." << endl;
        }

        mysql_free_result(resultado);

        cn.cerrar_conexion();
    }
};