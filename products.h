#include <iostream>
#include <iomanip>
#ifndef HEADER_H
#define HEADER_H

using namespace std;
struct Product
{
    string Codp;
    string ProductName;
    float Price;
    int Cantidad;
    int Desc;
    int TypeProduct;
    bool Exento;
};

class ProductsController
{
public:
    Product Productos[256];
    int PrdQty;
    float Dolar;
    float IVA;
    float Descuento;
    string TipoDeProductos[6] = {
        "Comestible",
        "Bebidas",
        "Limpieza",
        "Electronicos",
    };
    void PrintTypeProd()
    {
        for (int i = 0; i < 4; i++)
        {
            cout << i << " - " << TipoDeProductos[i] << endl;
        }
    }
    string GetTypeProdByIndex(int index)
    {
        return TipoDeProductos[index];
    }
    ProductsController(){};
    Product GetProd(int i)
    {
        return Productos[i];
    };
    void AddProd(Product Item, int Index)
    {
        Productos[Index] = Item;
        PrdQty++;
    };
    void ModifyProd(int i, Product Item)
    {
        Productos[i] = Item;
    };
    void DeleteProd(int i)
    {
        Productos[i] = Product();
    };
    void Clear()
    {
        for (size_t i = 0; i < PrdQty; i++)
        {
            Productos[i] = Product();
        }
        PrdQty = 0;
    }
    void setDolar(float Dol)
    {
        Dolar = Dol;
    }
    void setDescuento(float Dol)
    {
        Descuento = Dol;
    }
    void setIVA(float Dol)
    {
        IVA = Dol;
    }
    bool checkCodp(string Codp)
    {
        for (int i = 0; i < 256; i++)
        {
            if (Productos[i].Codp == Codp)
            {
                return true;
            }
        }
        return false;
    }
    bool checkByIndex(int index)
    {
        if (Productos[index].Codp != "")
        {
            return true;
        }
        return false;
    }
    Product getByCodp(string Codp)
    {
        for (int i = 0; i < 256; i++)
        {
            if (Productos[i].Codp == Codp)
            {
                return Productos[i];
            }
        }
        return Product();
    }
    int getIndexByCodp(string Codp)
    {
        for (int i = 0; i < 256; i++)
        {
            if (Productos[i].Codp == Codp)
            {
                return i;
            }
        }
        return 0;
    }
    void totalBrutoNetoInventario(int mon)
    {
        string symbol = " Bs";
        float monFactor = 1;
        if (mon == 2)
        {
            monFactor = Dolar;
            symbol = "$";
        }
        float TotalBruto = 0;
        float TotalNeto = 0;
        float TotalInventario = 0;
        float TotalExento = 0;
        float TotalIva = 0;
        float SubTotal = 0;
        float Total = 0;
        float TotalDescuento = 0;
        int SinExisItem = 0;
        int DescuentoItem = 0;
        int MayorCantidad = 0;
        string ItemMayorCantidad = "";
        int MenorCantidad = 99999;
        string ItemMenorCantidad = "";
        string MasCostoso = "";
        float MasCostosoPrice = 0;
        string MasBarato = "";
        float MasBaratoPrice = 99999;

        for (size_t i = 0; i < CountProds(); i++)
        {
            if (MasCostosoPrice <= Productos[i].Price)
            {
                MasCostoso = Productos[i].ProductName;
                MasCostosoPrice = Productos[i].Price;
            }
            if (MasBaratoPrice >= Productos[i].Price)
            {
                MasBarato = Productos[i].ProductName;
                MasBaratoPrice = Productos[i].Price;
            }
            if (MayorCantidad <= Productos[i].Cantidad)
            {
                ItemMayorCantidad = Productos[i].ProductName;
                MayorCantidad = Productos[i].Cantidad;
            }
            if (MenorCantidad >= Productos[i].Cantidad)
            {
                ItemMenorCantidad = Productos[i].ProductName;
                MenorCantidad = Productos[i].Cantidad;
            }
            float Precio = Productos[i].Price / monFactor;
            int Cantidad = Productos[i].Cantidad;
            float Descuento = Productos[i].Desc;
            SubTotal += Precio * Cantidad;
            if (Productos[i].Cantidad <= 0)
                SinExisItem++;
            if (Descuento > 0)
            {
                DescuentoItem++;
                float DescuentoTotal = (SubTotal * Descuento) / 100;
                TotalDescuento += DescuentoTotal;
                Total = SubTotal - DescuentoTotal;
            }
            else
            {
                Total = SubTotal;
            }
            TotalBruto += Total;
            if (Productos[i].Exento == true)
            {
                TotalNeto += Total;
                TotalExento += Total;
            }
            else
            {
                float imp = (Total * IVA) / 100;
                TotalNeto += Total + imp;
                TotalIva += imp;
            }
            TotalInventario += Total;
        }
        cout << "Cantidad Items en el Inventario: " << PrdQty << endl;
        cout << "Productos con Descuento: " << DescuentoItem << endl;
        cout << "Productos con existencia 0: " << DescuentoItem << endl;
        cout << "Total Descuento: " << TotalDescuento << symbol << endl;
        cout << "Total Sin Descuento: " << SubTotal << symbol << endl;
        cout << "Total Exento: " << TotalExento << symbol << endl;
        cout << "Total IVA: " << TotalIva << symbol << endl;
        cout << "Total Bruto: " << TotalBruto << symbol << endl;
        cout << "Total Neto: " << TotalNeto << symbol << endl;

        cout << "Total Inventario: " << TotalInventario << symbol << endl;
        Utils::HeaderBonito("Cantidades y Precios");
        cout << "Producto con mayor cantidad:" << ItemMayorCantidad << " con cantidad de " << MayorCantidad << "\n";
        cout << "Producto con menor cantidad: " << ItemMenorCantidad << " con cantidad de " << MenorCantidad << "\n";
        cout << "Producto Mas Costoso: " << MasCostoso
             << " Precio: " << (MasCostosoPrice / monFactor) << symbol << "\n";
        cout << "Producto Mas Economico: " << MasBarato << " Precio: " << (MasBaratoPrice / monFactor) << symbol << "\n";
        PrintProds(monFactor, symbol);
    }
    // utils
    void PrintProds(float cambio, string symbol)
    {
        Utils::Line();
        PrintTable(99);
        for (size_t i = 0; i < CountProds(); i++)
        {
            cout << "Producto " << i + 1 << ":\n";
            cout << "Codigo: " << Productos[i].Codp << "\n";
            cout << "Nombre: " << Productos[i].ProductName << "\n";
            cout << "Precio: " << (Productos[i].Price / cambio) << symbol << "\n";
            cout << "Cantidad: " << Productos[i].Cantidad << "\n";
            cout << "Descuento: " << Productos[i].Desc << "\n";
            cout << "Tipo de Producto (Departamento): " << Productos[i].TypeProduct << " - " << this->GetTypeProdByIndex(Productos[i].TypeProduct) << "\n";
            cout << "Exento: " << Productos[i].Exento << "\n";
            if (Productos[i].Cantidad <= 0)
                cout << "Este producto esta en 0 \n";
            Utils::Line();
        }
    };
    void PrintProdsResumen()
    {
        Utils::Line();
        for (size_t i = 0; i < CountProds(); i++)
        {
            cout << "Producto " << i << ":" << Productos[i].ProductName << "\n";
            Utils::Line();
        }
    };
    int CountProds()
    {
        int count = 0;
        for (int i = 0; i < 256; i++)
        {
            if (Productos[i].Codp != "")
            {
                count++;
            }
        }
        return count;
    }
    string InfoProdItem(int i, int var)
    {
        if (Productos[i].Codp == "")
        {
            return "";
        }
        switch (var)
        {
        case 1:
            return "(" + Productos[i].Codp + ")";
            break;

        case 2:
            return "(" + Productos[i].ProductName + ")";
            break;
        case 3:
            return "(" + Utils::FloatAString(Productos[i].Price) + ")";
            break;
        case 4:
            return "(" + Utils::IntAString(Productos[i].Cantidad) + ")";
            break;
        case 5:
            return "(" + Utils::IntAString(Productos[i].Desc) + ")";
            break;
        case 6:
            return "(" + Utils::BoolAString(Productos[i].Exento) + ")";
            break;
        case 7:
            return "(" + this->GetTypeProdByIndex(Productos[i].TypeProduct) + ")";
            break;
        default:
            break;
        }
    };

    void PrintTable(int Type)
    {
        // Nombre precio cantidad tipoprod exento
        // hacer una matriz con los datos y luego imprimirlos
        string table[CountProds()][5];
        for (size_t i = 0; i < CountProds(); i++)
        {
            if (Productos[i].TypeProduct == Type || Type == 99)
            {
                for (size_t j = 0; j < 5; j++)
                {
                    table[i][j] = InfoProdItem(i, j + 1);

                    switch (j)
                    {
                    case 0:
                        table[i][j] = Productos[i].ProductName;
                        break;
                    case 1:
                        table[i][j] = InfoProdItem(i, 3);
                        break;
                    case 2:
                        table[i][j] = InfoProdItem(i, 4);
                        break;
                    case 3:
                        table[i][j] = this->GetTypeProdByIndex(Productos[i].TypeProduct);

                        break;
                    case 4:
                        table[i][j] = Productos[i].Exento ? "Si" : "No";
                        break;

                    default:
                        break;
                    }
                    if (j == 3)
                    {
                        table[i][j] = this->GetTypeProdByIndex(Productos[i].TypeProduct);
                    }
                    if (j == 4)
                    {
                        string exento = Productos[i].Exento ? "Si" : "No";
                        table[i][j] = exento;
                    }
                    if (table[i][j] == "()")
                    {
                        table[i][j] = "N/A";
                    }
                }
            }
        }
        Utils::LineWithCount(101);
        cout << setSpaces("|Nombre", 20) << setSpaces("|Precio", 20) << setSpaces("|Cantidad", 20) << setSpaces("|Tipo de Producto", 20) << setSpaces("|Exento", 20) << "|\n";
        //|Nombre             |Precio           |Cantidad   |Tipo de Producto             |Exento                  |
        Utils::LineWithCount(101);
        for (size_t i = 0; i < CountProds(); i++)
        {
            for (size_t j = 0; j < 5; j++)
            {
                cout << setSpaces(table[i][j], 20);
            }
            cout << endl;
            Utils::LineWithCount(101);
        }
    }
    // funcion que agrega espacios para que el texto se vea bien en la tabla
    string setSpaces(string str, int spaces)
    {
        int count = 0;
        for (size_t i = 0; i < str.length(); i++)
        {
            count++;
        }
        for (size_t i = 0; i < spaces - count; i++)
        {
            str += " ";
        }
        return str;
    }
};

#endif
