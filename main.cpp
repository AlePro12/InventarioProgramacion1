#include <iostream>
#include "ApFramework.h"

#include "products.h"
#include "opc.h"
using namespace std;

string opc[6] = {
    "Inventario",
    "Estadisticas (Bs)",
    "Estadisticas ($)",
    "Limpiar Registros",
    "Configuraciones",
    "Salir",
};

void PrintOpc() // Dont repeat the code!
{
    for (size_t i = 0; i < 6; i++)
    {
        cout << "" << i + 1
             << " | " << opc[i] << "\n";
    }
}

int main()
{
    bool Exit = true;
    bool Confirm = false;
    int opc = 100;
    while (Exit == true)
    {
        cout << "\n";
        Utils::HeaderBonito("Examen 4 (1.3) Alejandro Sanchez");
        // print opcs
        PrintOpc();
        opc = Utils::ObtenerInputUsuario_int("Seleccione una opcion");
        switch (opc)
        {
        case 1:
            AnadirProductos();
            break;
        case 2:
            Estadistica(1);
            break;
        case 3:
            Estadistica(2);
            // Al Cambio
            break;
        case 4:
            Utils::Line();
            Confirm = Utils::Pregunta("Estas seguro de eliminar todo los datos");
            if (Confirm)
            {
                Clear();
            }
            else
            {
                Utils::Print("Proceso abortado");
            }
            // Limpiar
            break;
        case 5:
            Config();
            // Configs
            break;
        case 6:
            // salir
            Utils::HeaderBonito("Gracias por usar el programa!");
            Exit = false;
            break;
        default:
            Utils::Alert("Opcion no valida: " + Utils::IntAString(opc), "string");
            break;
        }
    }
    return 0;
}