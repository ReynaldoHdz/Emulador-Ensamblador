José Emiliano Flores Martínez A00833160
Reynaldo Hernández González A00829814
Gabriel Ruiz Miller A00835179
Oscar Retes A01383653

Este emulador simula el uso del lenguaje ensamblador para hacer pequeños programas. 
A continuación se encuentran las instrucciones para usar el emulador con archivos de 
texto de ejemplos de programas en lenguaje ensamblador. Después está una breve descripción 
de las secciones más importantes del código fuente.

INSTRUCCIONES DE USO

Para mostrar la funcionalidad del emulador, se proporcionan ejemplos de archivos de texto. 
Para este ejemplo, utilizaremos los archivos example.txt (programa de ejemplo para sumar) 
y multiplication.txt (programa de ejemplo para multiplicar).

1. Asegúrese de que los archivos example.txt y multiplication.txt estén en el mismo directorio que el emulador
2. Ejecutar el emulador
3. Ingresar el nombre del archivo de la siguiente manera omitiendo las comillas “”: “example.txt”
4. Aparecen dos opciones para la ejecución del programa. Para este ejemplo elegimos la segunda opción. Ingresar “2”
5. Oprimir ENTER cada vez que se muestre el mensaje Enter to run instruction
6. Ingresar un valor numérico a sumar en la instrucción Running Operation: INPUTtoAC 20
7. Ingresar un valor numérico a sumar en la instrucción Running Operation: INPUTtoAD 21
8. Observar cómo se guarda el resultado de la suma en la dirección 50 (representado por un 5 en el emulador)
9. Repetir el paso 2
10. Ingresar el nombre del archivo de la siguiente manera omitiendo las comillas “”: “multiplication.txt”
11. Repetir el paso 4 y, cuando aplique, el paso 5
12. Ingresar un valor numérico a multiplicar en la instrucción Running Operation: INPUTtoAD 30
13. Ingresar un valor numérico a multiplicar en la instrucción Running Operation: INPUTtoAD 40
14. Observar cómo se guarda el resultado de la multiplicación en la dirección 50 (representado por un 5 en el emulador)

La ejecución del programa paso a paso permite visualizar cómo van cambiando los valores de los registros, 
sin embargo puede ser cansado estar oprimiendo ENTER todo el tiempo. Para evitar tener que hacer eso, 
se puede ingresar “1” en el paso 4.

Ahora que se tiene una mejor idea de cómo funciona el emulador, s
e puede generar un archivo de texto propio con instrucciones en lenguaje ensamblador. 
Solamente es importante escribir la instrucción con las siglas del código de operación, 
el tipo de direccionamiento, un espacio, y finalmente el valor numérico correspondiente.

Ejemplos correctos:
LDAA 020
STAI 050
ADDR 034

Ejemplos incorrectos:
LDA A 020
STA I050
ADDR034

Las únicas excepciones son ORG, HLT, CLA, y NOP.

Ejemplos correctos:
ORG 000
CLA
NOP
HLT


CODIGOS DE OPERACION

No operation
NOP = 0

Negative
NEG = 1

Clear accumulator
CLA = 2

Load immediate
LDAI = 100

Load relative
LDAR = 101

Load absolute
LDAA = 102

Load indirect
LDAD = 103

Store relative
STAR = 111

Store absolute
STAA = 112

Store indirect
STAD = 113

Add immediate
ADDI = 200

Add relative
ADDR = 201

Add absolute
ADDA = 202

Add indirect
ADDD = 203

Subtract immediate
SUBI = 210

Subtract relative
SUBR = 211

Subtract absolute
SUBA = 212

Subtract indirect
SUBD = 213

Jump unconditional
JMP = 300

Jump conditional zero
JMZ = 310

Jump conditional negative
JMN = 320

Jump conditional overflow
JMV = 330

*Input to accumulator
INPUTtoAC = 500

**Input to address
 INPUTtoAD = 502

ORG = 910

Halt
HLT = 990

*Esta operación es para cargar un valor numérico directamente al acumulador
**Esta operación es para cargar un valor numérico directamente a una dirección de memoria

