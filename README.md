# Diseño-Digital-Moderno-2027-1

Repositorio del equipo para la materia Diseño Digital Moderno (Grupo 5), Facultad de Ingeniería, UNAM. Semestre 2027-1.

# Integrantes
---

- Carpizo Garduño Andrés
- Mata Ramírez Ximena
- Solís Fuentes José Enrique

## Tarea 1 — Sistemas numéricos y sumador binario
--- 

Son dos programas en C en donde el primer código llamado "Conversor_Numerico.c" que convierte números desde base 2 hasta base 16, ya sean enteros, fraccionarios y negativos en complemento a2 de 6 bits) y aparte está el código llamado "Sumador_Binario.c" el cual realiza la suma binaria de dos números de 6 bits, mostrando acarreos y el caso límite de desbordamiento. El reporte en formato PDF y los códigos fuentes se encuentran acá, aparte que hay videos demostrativos de su uso.

Para poder probar cada código se debe de usar su respectivo comando de compilación:

Para "Conversor_Numerico.c": gcc Conversor_Numerico.c -o Conversor_Numerico.exe -lm

Para "Sumador_Binario.c": gcc Sumador_Binario.c -o Sumador_Binario.exe


## Proyecto 1 y 2
Los siguientes proyectos son dos proyectos diferentes en donde cada se enfoca en un aspecto:

---

### Proyecto 1
--- 

Diseño y construcción de un sistema, únicamente con el uso de compuertas básicas, el cual debe contar con dos entradas, y solo cuando ambas entradas sean iguales se deberá encender una luz.

### Proyecto 2
---

El diseño de circuitos lógicos combinacionales constituye un pilar fundamental en la electrónica digital, permitiendo la toma de decisiones basada en combinaciones específicas de señales de entrada mediante el uso de compuertas lógicas como NOT y AND. En múltiples áreas de la ingeniería y la vida cotidiana, la gestión y ordenamiento de prioridades resultan esenciales para garantizar una respuesta ordenada frente a distintas condiciones. Un ejemplo claro se observa en los sistemas de atención hospitalaria en salas de urgencias, donde es imprescindible clasificar y canalizar eficientemente a los pacientes en función de la gravedad de su estado (súper-emergencia, emergencia o chequeo rutinario). En la presente práctica se aborda el diseño, análisis e implementación de un sistema combinacional de control de prioridad para la entrada a una sala de urgencias. A partir de las especificaciones requeridas, se formula la tabla de verdad y se realiza la simplificación de funciones booleanas mediante mapas de Karnaugh. Posteriormente, se lleva a cabo la implementación del circuito lógico haciendo uso de circuitos integrados discretos (74LS04 y 74LS08), verificando su correcto funcionamiento práctico mediante indicadores LED que representan visualmente la prioridad de acceso otorgada.
