#include <iostream>

using namespace std;

ProductsController Controlador;

// esta funcion solo resuelve un problema de redundacia de codigo pero no es algo optimo,
// Pero puedo decir que para este caso esta bien.
float IsUndefined(float Crollr, string title, string Item)
{
    if (Crollr == 0)
    {
        bool defineCr = false;
        Utils::Line();
        defineCr = Utils::Pregunta("El " + Item + " esta en 0. Deseas definirlo ahora");
        Utils::Line();
        if (defineCr)
        {
            // Lastima que en C++ no existe las promises o los callbacks :"(
            float callbackFloat = Utils::ObtenerInputUsuario_float("Ingrese " + title);
            return callbackFloat;
        }
        else
        {
            Utils::Print("No se puede continuar con el " + Item + " no definido");
            Utils::Line();
            return 0;
        }
    }
    else
    {
        return Crollr;
    }
}
void AddP(int index)
{
    Product tmpItem;
    bool validateCodp = true;
    if (Controlador.checkByIndex(index))
        validateCodp = false;
    while (validateCodp)
    {
        /* code */
        tmpItem.Codp = Utils::ObtenerInputUsuario_string("Codigo del producto " + Controlador.InfoProdItem(index, 1));
        if (!Controlador.checkCodp(tmpItem.Codp))
        {
            validateCodp = false;
        }
        else
        {
            bool AddorEdit;
            AddorEdit = Utils::Pregunta("Este codigo ya esta utilizado desea editar el producto (1)? o cambiar el codigo(0)");
            if (AddorEdit)
            {
                AddP(Controlador.getIndexByCodp(tmpItem.Codp));
                return;
            }
        }
    }
    tmpItem.ProductName = Utils::ObtenerInputUsuario_string("Descripcion del producto" + Controlador.InfoProdItem(index, 2));
    tmpItem.Cantidad = Utils::ObtenerInputUsuario_int("Cantidad del producto" + Controlador.InfoProdItem(index, 4));
    Controlador.PrintTypeProd();
    tmpItem.TypeProduct = Utils::ObtenerInputUsuario_int("Tipo de producto" + Controlador.InfoProdItem(index, 7));

    // tmpItem.Exento = Utils::ObtenerInputUsuario_bool("Es Exento?, 0 = No, 1 = Si");
    tmpItem.Price = Utils::ObtenerInputUsuario_float("Precio del producto" + Controlador.InfoProdItem(index, 3));

    tmpItem.Exento = Utils::Pregunta("Es exento" + Controlador.InfoProdItem(index, 6));

    tmpItem.Desc = Utils::ObtenerInputUsuario_int("Descuento del producto ((Ej)=> 30) " + Controlador.InfoProdItem(index, 5));
    Controlador.AddProd(tmpItem, index);
    Utils::Line();
    Utils::Print("Producto Anadido o editado con exito!!");
    Utils::Line();
}
void PrintProdByDP()
{
    Utils::Line();
    Utils::Print("Productos por tipo de producto");
    Utils::Line();
    Controlador.PrintTypeProd();
    int type = Utils::ObtenerInputUsuario_int("Seleccione un tipo de producto");
    Utils::Line();
    Utils::Print("Productos por tipo de producto");
    Utils::Line();
    Controlador.PrintTable(type);
    Utils::Line();
}
void PrintListaItems()
{
    bool dol;
    dol = Utils::Pregunta("En dolares");
    if (dol == true)
    {
        float Dolartmp;
        Dolartmp = IsUndefined(Controlador.Dolar, "Dolar", "Precio del Dolar");
        if (Dolartmp == 0)
        {
            return;
        }
        else
        {
            if (Dolartmp != Controlador.Dolar)
            {
                Controlador.setDolar(Dolartmp);
            }
        }
        Controlador.PrintProds(Controlador.Dolar, " $");
    }
    else
    {
        Controlador.PrintProds(1, " Bs");
    }
}
void AnadirProductos()
{

    string opciones[5] = {
        "Anadir Producto",
        "Editar Producto",
        "Lista de productos",
        "Productos por tipo",
        "<-Atras",
    };
    int opc = 256;
    bool Continue = true;
    int tmpIndex = 0;

    while (Continue == true)
    {
        Utils::HeaderBonito("Inventario");
        for (size_t i = 0; i < 5; i++)
        {
            cout << "" << i + 1
                 << " | " << opciones[i] << "\n";
        }
        opc = Utils::ObtenerInputUsuario_int("Seleccione una opcion");
        switch (opc)
        {
        case 1:
            AddP(Controlador.PrdQty);
            break;
        case 2:
            Controlador.PrintProdsResumen();
            tmpIndex = Utils::ObtenerInputUsuario_int("Index del producto");
            AddP(tmpIndex);
            break;
        case 3:
            PrintListaItems();
            break;
        case 4:
            PrintProdByDP();
            break;
        case 5:
            Continue = false;
            break;
        default:
            break;
        }
    }
}
void Estadistica(int Moneda)
{
    // 1 es Bs y 2 Es $
    // Validaciones
    Utils::HeaderBonito("Estadistica");
    if (Moneda != 1 && Moneda != 2)
    {
        Utils::Print("Moneda Invalida -- Error Interno");
        Utils::Line();
        return;
    }
    if (Moneda == 2)
    {
        float Dolartmp;
        Dolartmp = IsUndefined(Controlador.Dolar, "Dolar", "Precio del Dolar");
        if (Dolartmp == 0)
        {
            return;
        }
        else
        {
            if (Dolartmp != Controlador.Dolar)
            {
                Controlador.setDolar(Dolartmp);
            }
        }
    }
    float IVAtmp;
    IVAtmp = IsUndefined(Controlador.IVA, "IVA", "Porcentaje del IVA");
    if (IVAtmp == 0)
    {
        return;
    }
    else
    {
        if (IVAtmp != Controlador.IVA)
        {
            Controlador.setIVA(IVAtmp);
        }
    }
    // Total Neto
    // Total Bruto
    // Catidad de art con desc
    // Cantidad de Items
    Utils::Line();
    Controlador.totalBrutoNetoInventario(Moneda);
    Utils::Line();
    bool continuar = false;
    while (continuar == false)
    {
        continuar = Utils::Pregunta("Desea continuar");
    }

    // Art con mayor cant
    // Art con Menor cant
    // Art con Menor Precio
    // Art con Mayo Precio
};
void Clear()
{
    Controlador.Clear();
    Utils::HeaderBonito("El inventario se ha limpiado");
}
void MostrarConfig()
{
    Utils::HeaderBonito("Configuracion");
    Utils::Print("IVA: " + Utils::FloatAString(Controlador.IVA));
    Utils::Print("Dolar: " + Utils::FloatAString(Controlador.Dolar));
    Utils::Print("Descuento: " + Utils::FloatAString(Controlador.Descuento));
    Utils::Line();
}
void EditConfigValue(string title, int Type)
{
    float callbackFloat = Utils::ObtenerInputUsuario_float("Ingrese " + title);
    switch (Type)
    {
    case 1:
        Controlador.setIVA(callbackFloat);
        break;
    case 2:
        Controlador.setDolar(callbackFloat);
        break;
    case 3:
        Controlador.setDescuento(callbackFloat);
        break;
    default:
        break;
    }
}
void Config()
{
    Utils::HeaderBonito("Configuraciones");
    int opc = 256;
    bool exit = false;
    string opciones[6] = {
        "Editar IVA",
        "Editar Dolar",
        "Editar Descuento",
        "Muestrame la configuracion",
        "<-Atras",
    };
    while (exit == false)
    {

        for (size_t i = 0; i < 5; i++)
        {
            cout << "" << i + 1
                 << " | " << opciones[i] << "\n";
        }
        opc = Utils::ObtenerInputUsuario_int("Seleccione una opcion");
        switch (opc)
        {
        case 1:
            EditConfigValue("IVA", 1);
            break;
        case 2:
            EditConfigValue("Dolar", 2);

            break;
        case 3:
            EditConfigValue("Descuento", 3);

            break;
        case 4:
            MostrarConfig();
            break;
        case 5:
            exit = true;
            break;
        default:
            Utils::Alert("Opcion no valida: " + Utils::IntAString(opc), "string");
            break;
        }

        /* code */
    }
    Utils::Line();
}
