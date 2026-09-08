#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

/*
Valor Caracter: Convierte un carácter a su valor numérico correspondiente según la base.
c: Carácter a convertir ('0'-'9', 'A'-'F', 'a'-'f')
Retorna: Valor numérico del carácter (0-15) o -1 si el carácter no es válido para bases hasta 16.
*/
int valorCaracter(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return -1; // Carácter no válido
}

/*
Caracter Valor: Convierte un valor numérico decimal a su representación en carácter.
v: Valor numérico a convertir (0 a 15).
Retorna: El carácter correspondiente ('0'-'9' para valores menores a 10, 'A'-'F' para 10 a 15) o '?' si el valor está fuera del rango.
*/
char caracterValor(int v)
{
    if (v >= 0 && v <= 9)
        return (char)(v + '0');
    if (v >= 10 && v <= 15)
        return (char)(v - 10 + 'A');
    return '?';
}

/*
Es Entrada Valida: Verifica que cada dígito del número ingresado pertenezca realmente a la base de origen.
numero: Cadena de caracteres que contiene el número ingresado por el usuario.
baseOrigen: Base numérica en la que se supone está escrito el número (2-16).
Retorna: true si todos los caracteres son válidos y hay como máximo un punto decimal; false si encuentra un dígito inválido o múltiples puntos.
*/
bool esEntradaValida(const char *numero, int baseOrigen)
{
    int puntosDecimales = 0;

    for (int i = 0; numero[i] != '\0'; i++)
    {
        if (numero[i] == '.')
        {
            puntosDecimales++;
            if (puntosDecimales > 1)
                return false; // Solo se permite un punto
            continue;
        }

        int valor = valorCaracter(numero[i]);
        // Si no es un carácter válido o si es mayor/igual a la base (ej. '9' en base 9 es inválido)
        if (valor == -1 || valor >= baseOrigen)
        {
            return false;
        }
    }
    return true;
}

/*
Convertir Base: Ejecuta el algoritmo de "La Cuenta Larga" para transformar un número de una base a otra.
numeroStr: Cadena de texto con el número original a convertir.
baseOrigen: Base numérica del número original (2-16).
baseDestino: Base numérica a la que se desea llegar (2-16).
resultado: Puntero al arreglo de caracteres donde se guardará la cadena de texto con el resultado final.
Retorna: Nada (void). El valor convertido se almacena directamente en la variable 'resultado'.
*/
void convertirBase(const char *numeroStr, int baseOrigen, int baseDestino, char *resultado)
{
    // PASO A: Convertir de Base Origen a Base 10 (Decimal) manualmente
    double decimalTotal = 0.0;
    int i = 0;

    // Parte entera a decimal
    while (numeroStr[i] != '\0' && numeroStr[i] != '.')
    {
        decimalTotal = decimalTotal * baseOrigen + valorCaracter(numeroStr[i]);
        i++;
    }

    // Parte fraccionaria a decimal (si existe)
    if (numeroStr[i] == '.')
    {
        i++;
        double pesoFraccion = 1.0 / baseOrigen;
        while (numeroStr[i] != '\0')
        {
            decimalTotal += valorCaracter(numeroStr[i]) * pesoFraccion;
            pesoFraccion /= baseOrigen;
            i++;
        }
    }

    // PASO B: Convertir de Base 10 a Base Destino usando "La Cuenta Larga"
    long long parteEntera = (long long)decimalTotal;
    double parteFraccionaria = decimalTotal - parteEntera;

    char bufferEntero[100];
    int idxBuffer = 0;

    // - Divisiones sucesivas para la parte entera -
    if (parteEntera == 0)
    {
        bufferEntero[idxBuffer++] = '0';
    }
    else
    {
        while (parteEntera > 0)
        {
            int residuo = parteEntera % baseDestino;
            bufferEntero[idxBuffer++] = caracterValor(residuo);
            parteEntera /= baseDestino;
        }
    }
    bufferEntero[idxBuffer] = '\0';

    // Invertir el buffer entero ya que los residuos se obtienen al revés
    int inicio = 0, fin = idxBuffer - 1;
    while (inicio < fin)
    {
        char temp = bufferEntero[inicio];
        bufferEntero[inicio] = bufferEntero[fin];
        bufferEntero[fin] = temp;
        inicio++;
        fin--;
    }

    strcpy(resultado, bufferEntero);

    // - Multiplicaciones sucesivas para la parte fraccionaria -
    if (parteFraccionaria > 0.0)
    {
        strcat(resultado, ".");
        int lenRes = strlen(resultado);
        int precisionMaxima = 8; // Límite para evitar bucles infinitos en fracciones periódicas

        while (parteFraccionaria > 0.000001 && precisionMaxima > 0)
        {
            parteFraccionaria *= baseDestino;
            int digito = (int)parteFraccionaria;
            resultado[lenRes++] = caracterValor(digito);
            parteFraccionaria -= digito;
            precisionMaxima--;
        }
        resultado[lenRes] = '\0';
    }
}

/*
Main: Función principal que orquesta la ejecución del programa.
Se encarga de solicitar al usuario las bases y el número, validar los límites de las bases,
mandar a llamar a las validaciones y cálculos, y mostrar el formato final en consola.
Retorna: 0 si la ejecución fue exitosa, o 1 si hubo algún error en los datos ingresados.
*/
int main()
{
    int baseOrigen, baseDestino;
    char numero[100];
    char resultado[200];

    printf("=== Conversor de Bases Numericas ===\n");

    // Leer Base de Origen
    printf("Ingresa la base de origen (2-16): ");
    scanf("%d", &baseOrigen);
    if (baseOrigen < 2 || baseOrigen > 16)
    {
        printf("Error: La base debe estar entre 2 y 16.\n");
        return 1;
    }

    // Leer Base de Destino
    printf("Ingresa la base de destino (2-16): ");
    scanf("%d", &baseDestino);
    if (baseDestino < 2 || baseDestino > 16)
    {
        printf("Error: La base debe estar entre 2 y 16.\n");
        return 1;
    }

    // Leer Número
    printf("Ingresa el numero a convertir (puedes usar decimales): ");
    scanf("%99s", numero);

    // Validar el número según la base
    if (!esEntradaValida(numero, baseOrigen))
    {
        printf("ERROR DE VALIDACION: El numero '%s' contiene caracteres invalidos para la base %d.\n", numero, baseOrigen);
        return 1;
    }

    // Realizar conversión y mostrar
    convertirBase(numero, baseOrigen, baseDestino, resultado);
    printf("\nResultado: %s (Base %d) = %s (Base %d)\n", numero, baseOrigen, resultado, baseDestino);

    return 0;
}