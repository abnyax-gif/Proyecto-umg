// ==========================================
// Empleado.h
// ==========================================

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

    string codigo;
    string dpi;
    string genero;
    string fecha_nacimiento;

    int id_puesto = 0;

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

    void setDPI(string d) {

        dpi = d;
    }

    void setGenero(string g) {

        genero = g;
    }

    void setFechaNacimiento(string f) {

        fecha_nacimiento = f;
    }

    void setIdPuesto(int idp) {

        id_puesto = idp;
    }

    // ==========================================
    // VALIDACIONES
    // ==========================================

    bool validarCodigo() {

        regex formato(
            "^E[0-9]{3}$"
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

    bool validarTelefonoEmpleado() {

        return validarTelefono(
            telefono
        );
    }

    bool validarDPIEmpleado() {

        return validarDPI(
            dpi
        );
    }

    bool validarGeneroEmpleado() {

        return validarGenero(
            genero
        );
    }

    bool validarFechaNacimiento() {

        return validarFecha(
            fecha_nacimiento
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
                "INSERT INTO empleados(codigo,nombres,apellidos,direccion,telefono,dpi,genero,fecha_nacimiento,id_puesto) VALUES('" +
                codigo + "','" +
                nombres + "','" +
                apellidos + "','" +
                direccion + "','" +
                telefono + "','" +
                dpi + "','" +
                genero + "','" +
                fecha_nacimiento + "'," +
                to_string(id_puesto) + ")";

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Empleado ingresado..." << endl;
            }
            else {

                cout << "Error al ingresar empleado..." << endl;
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
                "SELECT * FROM empleados";

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
                cout << "ID | CODIGO | NOMBRES | APELLIDOS | DPI" << endl;
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
                "UPDATE empleados SET "
                "codigo='" + codigo +
                "',nombres='" + nombres +
                "',apellidos='" + apellidos +
                "',direccion='" + direccion +
                "',telefono='" + telefono +
                "',dpi='" + dpi +
                "',genero='" + genero +
                "',fecha_nacimiento='" + fecha_nacimiento +
                "',id_puesto=" + to_string(id_puesto) +
                " WHERE id_empleado=" +
                to_string(id);

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Empleado modificado..." << endl;
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
                "DELETE FROM empleados WHERE id_empleado=" +
                to_string(id);

            const char* c =
                consulta.c_str();

            int q_estado =
                mysql_query(
                    cn.getConector(),
                    c
                );

            if (!q_estado) {

                cout << "Empleado eliminado..." << endl;
            }
            else {

                cout << "Error al eliminar..." << endl;
            }
        }

        cn.cerrar_conexion();
    }

    // ==========================================
    // BUSCAR EMPLEADO
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
            cout << "===============================" << endl;
            cout << "Empleado Encontrado" << endl;
            cout << "===============================" << endl;

            cout << "ID: " << fila[0] << endl;
            cout << "Codigo: " << fila[1] << endl;
            cout << "Nombres: " << fila[2] << endl;
            cout << "Apellidos: " << fila[3] << endl;
            cout << "Direccion: " << fila[4] << endl;
            cout << "Telefono: " << fila[5] << endl;
            cout << "DPI: " << fila[6] << endl;
            cout << "Genero: " << fila[7] << endl;
            cout << "Fecha Nacimiento: " << fila[8] << endl;
            cout << "ID Puesto: " << fila[9] << endl;
        }
        else {

            cout << "Empleado no encontrado..." << endl;
        }

        cn.cerrar_conexion();
    }
};