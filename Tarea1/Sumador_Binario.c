#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Sumar Un Bit: Calcula la suma y el acarreo de salida de dos bits individuales más un acarreo de entrada, utilizando exclusivamente operaciones aritméticas y condicionales simples.
bit_a: Primer bit a sumar (0 o 1).
bit_b: Segundo bit a sumar (0 o 1).
acarreo_in: Bit de acarreo de entrada proveniente de la suma de la columna anterior (0 o 1).
suma: Puntero a la variable entera donde se almacenará el bit resultante de la suma.
acarreo_out: Puntero a la variable entera donde se almacenará el bit de acarreo de salida.
Retorna: Nada (void). Los resultados se almacenan en las variables apuntadas por 'suma' y 'acarreo_out'.
*/
void sumar_un_bit(int bit_a, int bit_b, int acarreo_in, int *suma, int *acarreo_out)
{
    // 1. Cálculo de suma total (entero entre 0 y 3)
    int suma_total = bit_a + bit_b + acarreo_in;

    // 2. El bit de resultado se calcula como el residuo
    *suma = suma_total % 2;

    // 3. El bit de acarreo de salida
    *acarreo_out = (suma_total >= 2) ? 1 : 0;
}

/*
Decimal a Binario 6 bits: Convierte un número decimal entero a su representación binaria de 6 bits (1 bit de signo y 5 de magnitud). Si es negativo, aplica automáticamente la regla de Complemento a 2.
num: Número decimal entero a convertir (rango válido de -32 a 31).
binario: Arreglo de 6 enteros donde se almacenará la representación binaria. El índice [0] es el MSB (signo).
Retorna: Nada (void). El resultado se almacena directamente en el arreglo 'binario'.
*/
void decimal_a_binario_6bits(int num, int binario[6])
{
    int es_negativo = (num < 0) ? 1 : 0;
    int magnitud = abs(num);

    // Convertir la magnitud a su equivalente binario de 5 bits
    for (int i = 5; i >= 1; i--)
    {
        binario[i] = magnitud % 2;
        magnitud /= 2;
    }

    // Asignar el bit de signo (MSB)
    binario[0] = es_negativo;

    // Aplicar regla de Complemento a 2 si es negativo
    if (es_negativo)
    {
        // Invertir cada uno de los bits de magnitud (cambiar 1 por 0 y 0 por 1)
        for (int i = 1; i <= 5; i++)
        {
            binario[i] = (binario[i] == 0) ? 1 : 0;
        }

        // Sumar un uno al bit menos significativo (LSB)
        int acarreo_complemento = 1;
        for (int i = 5; i >= 1; i--)
        {
            int suma_temp = binario[i] + acarreo_complemento;
            binario[i] = suma_temp % 2;
            acarreo_complemento = suma_temp / 2;
        }
    }
}

/*
Imprimir Binario: Función auxiliar que muestra en consola un arreglo binario de 6 bits,
        agregando un espacio visual separador entre el bit de signo y los bits de magnitud.
etiqueta: Cadena de texto que sirve como título al imprimir el número (ej. "Numero A").
binario: Arreglo de 6 enteros que contiene la representación binaria a imprimir.
Retorna: Nada (void). Solo imprime los datos formateados en la consola.
*/
void imprimir_binario(const char *etiqueta, int binario[6])
{
    printf("%s: ", etiqueta);
    for (int i = 0; i < 6; i++)
    {
        if (i == 1)
            printf(" "); // Espacio visual entre signo y magnitud
        printf("%d", binario[i]);
    }
    printf("\n");
}

/*
Main: Función principal que orquesta el emulador del sumador binario.
Se encarga de solicitar y validar las entradas, transformar los números,
ejecutar el bucle de suma de 5 ciclos y la 6.ª operación para el signo,
y finalmente evaluar la condición de desbordamiento (overflow).
Retorna: 0 si la ejecución fue exitosa, o 1 si los números ingresados exceden los límites de 6 bits.
*/
int main()
{
    int num_a, num_b;
    int bin_a[6], bin_b[6], resultado[6];

    printf("=== Emulador de Sumador Binario de 6 bits ===\n");

    // Solicitar y validar entradas (Rango de 6 bits con signo: -32 a 31)
    printf("Ingresa el primer numero decimal (-32 a 31): ");
    scanf("%d", &num_a);
    if (num_a < -32 || num_a > 31)
    {
        printf("Error: Numero fuera del rango de 6 bits.\n");
        return 1;
    }

    printf("Ingresa el segundo numero decimal (-32 a 31): ");
    scanf("%d", &num_b);
    if (num_b < -32 || num_b > 31)
    {
        printf("Error: Numero fuera del rango de 6 bits.\n");
        return 1;
    }

    // Generar representaciones binarias
    decimal_a_binario_6bits(num_a, bin_a);
    decimal_a_binario_6bits(num_b, bin_b);

    printf("\nRepresentaciones (Signo | Magnitud):\n");
    imprimir_binario("Numero A", bin_a);
    imprimir_binario("Numero B", bin_b);
    printf("------------------------\n");

    int acarreo_in = 0;
    int acarreo_out = 0;

    // Bucle de Suma de Magnitud (5 ciclos) de derecha (LSB) a izquierda
    for (int i = 5; i >= 1; i--)
    {
        sumar_un_bit(bin_a[i], bin_b[i], acarreo_in, &resultado[i], &acarreo_out);
        acarreo_in = acarreo_out; // El acarreo de salida se inyecta como entrada a la siguiente columna
    }

    // Capturar el acarreo que entra a la celda de signo para evaluar desbordamiento
    int acarreo_entra_a_signo = acarreo_in;

    // Llamada de Signo (6.a operacion) para procesar los MSB
    sumar_un_bit(bin_a[0], bin_b[0], acarreo_in, &resultado[0], &acarreo_out);

    // Resultado y Overflow
    imprimir_binario("RESULTADO", resultado);

    // Evaluar desbordamiento aritmético (Overflow)
    bool hay_overflow = (acarreo_entra_a_signo != acarreo_out);

    printf("\n--- Reporte de Estado ---\n");
    printf("Acarreo entrando al signo: %d\n", acarreo_entra_a_signo);
    printf("Acarreo saliendo del signo: %d\n", acarreo_out);

    if (hay_overflow)
    {
        printf("[!] ADVERTENCIA: Ha ocurrido un desbordamiento aritmetico (OVERFLOW).\n");
        printf("El resultado binario mostrado no representa la suma matematica correcta.\n");
    }
    else
    {
        printf("[+] Estado: Operacion exitosa sin desbordamiento.\n");
    }

    return 0;
}
