// ==========================================
// Persona.h
// ==========================================

#pragma once

#include <iostream>
#include <regex>
#include <ctime>

using namespace std;

class Persona {

protected:

    string nombres;
    string apellidos;
    string direccion;
    string telefono;

public:

    Persona() {}

    bool validarTexto(string texto) {

        regex formato(
            "^[A-Za-záéíóúÁÉÍÓÚñÑ ]+$"
        );

        return regex_match(texto, formato);
    }

    bool validarTelefono(string telefono) {

        regex formato(
            "^[0-9]{8}$"
        );

        return regex_match(
            telefono,
            formato
        );
    }

    bool validarFecha(string fecha) {

        regex formato(
            "^\\d{4}-\\d{2}-\\d{2}$"
        );

        return regex_match(
            fecha,
            formato
        );
    }

    bool validarGenero(string genero) {

        regex formato(
            "^[MFmf]{1}$"
        );

        return regex_match(
            genero,
            formato
        );
    }

    bool validarCorreo(string correo) {

        regex formato(
            "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"
        );

        return regex_match(
            correo,
            formato
        );
    }

    bool validarDPI(string dpi) {

        regex formato(
            "^[0-9]{13}$"
        );

        return regex_match(
            dpi,
            formato
        );
    }

    bool validarNIT(string nit) {

        regex formato(
            "^[0-9CFcf-]+$"
        );

        return regex_match(
            nit,
            formato
        );
    }
};