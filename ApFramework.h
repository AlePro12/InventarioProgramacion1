#include <any>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Utils
{

public:
    static string ObtenerInputUsuario_string(string title)
    {
        // getline
        string input = "";
        cout << " Ingrese " << title << ":";
        cin >> input;
        return input;
    }
    static int ObtenerInputUsuario_int(string title)
    {
        bool Valid = false;
        while (!Valid)
        {
            int input;
            cout << " Ingrese " << title << ":";
            cin >> input;
            if (Utils::ValidarEnteroPositivo(input))
            {
                Valid = true;
                return input;
            }
            else
            {
                Utils::Line();
                Utils::Print("ERROR: Numero Entero Invalido!");
                Utils::Print("Intenta nuevamente");
                Utils::Line();
            }
            return 0;
        }
        return 0;
    }
    static float ObtenerInputUsuario_float(string title)
    {
        bool Valid = false;
        while (!Valid)
        {
            float input;
            cout << " Ingrese " << title << ":";
            cin >> input;
            if (Utils::ValidarFloatPositivo(input))
            {
                Valid = true;
                return input;
            }
            else
            {
                Utils::Line();
                Utils::Print("ERROR: Numero Flotante Invalido!");
                Utils::Print("Intenta nuevamente");
                Utils::Line();
            }
            return 0;
        }
        return 0;
    }
    static bool ObtenerInputUsuario_bool(string title)
    {
        bool input;
        cout << " Ingrese " << title << ":";
        cin >> input;
        return input;
    }
    static bool Pregunta(string title)
    {
        bool input;
        cout << "" << title << "? \n";
        cout << "0 => No.\n"
             << "1 => Si.\n";
        cout << "   - ";
        cin >> input;
        return input;
    }
    static bool ValidarEnteroPositivo(int value)
    {
        if (value >= 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    static bool ValidarFloatPositivo(float value)
    {
        if (value >= 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // Conversiones
    static string IntAString(int num)
    {
        return to_string(num);
    }
    static string FloatAString(float num)
    {
        return to_string(num);
    }
    static int StringAEntero(string str)
    {
        return atoi(str.c_str());
    }

    static string BoolAString(bool bol)
    {
        if (bol)
        {
            return "Verdadero";
        }
        else
        {
            return "Falso";
        }
    }
    // Estetico
    static void
    Print(string str)
    {
        cout << str << endl;
    }
    static void Line()
    {
        cout << "----------------------------------------" << endl;
    }
    // funcion para imprimir unas lineas contadas por el usuario
    static void LineWithCount(int count)
    {
        for (size_t i = 0; i < count; i++)
        {
            cout << "-";
        }
        cout << endl;
    }
    static void HeaderBonito(string title)
    {
        float mid = (40 - (title.length() + 4)) / 2; // Aqui saco el calculo para ponerlo en el header
        cout
            << "|----------------------------------------|" << endl;
        cout << "|";
        for (size_t i = 0; i < mid; i++)
        {
            cout << "-";
        }
        cout << "* " << title << " *";
        for (size_t i = 0; i < mid; i++)
        {
            cout << "-";
        }
        cout << "|\n";
        cout << "|----------------------------------------|" << endl;
    }
    static void Alert(string p, string type)
    {
        string t = " Advertencia ";
        if (type == "error")
        {
            t = "    Error    ";
        }
        cout
            << "------------------* " << t << " *-----------------\n";
        cout << "- Detalles: " << p;
        for (size_t i = 0; i < (38 - p.length()); i++)
        {
            cout << " ";
        }
        cout << "-\n";
        cout << "-                                                 -\n";
        cout << "-                                                 -\n";
        cout << "---------------------------------------------------\n";
        cout << "------------------*      AP     *------------------\n";
        cout << "---------------------------------------------------\n";
    }
    // substraer
    /*
    static void PrintPrettyMatrix(int *Matrix, int Columnas, int Filas)
    {

        for (int Fil = 0; Fil < Filas; Fil++)
        {
            for (int Col = 0; Col < Columnas; Col++)
            {
                cout << "[" << Matrix[Fil][Col] << "]";
            }
            cout << "\n";
        }
    }*/
};