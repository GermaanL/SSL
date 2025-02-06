 ## 7.3. Tareas
1. La primera tarea es investigar las funcionalidades y opciones que su compilador presenta para limitar el inicio y fin de las fases de traducción.


Opciones del compilador para detener la compilación en las distintas etapas:

``` c 
-E 
```
Detenerse luego de la etapa de preprocesamiento. Si se utiliza la opción -o file escribe el código pre-procesado a un archivo, de lo contrario lo envía a salida estándar. Los archivos que no requieren preprocesamiento son ignorados.

Si quiero solo preprocesar un archivo ejemplo.c:
``` c 
gcc ejemplo.c -E -o ejemplo.i 
```

``` c 
-S
```

Detenerse luego de la etapa de compilación, pero no ensamblar. La salida es un archivo en  código ensamblador para cada archivo de entrada no-ensamblada especificada.  Se reemplazan los sufijos ‘.c’, ‘.i’, etc., con ‘.s’. Los archivos de entrada que no requieran compilación son ignorados.

Si quiero detenerme en la etapa de ensamblado:
``` c 
gcc ejemplo.c -S
```
```c
-c
```
Compilar o ensamblar los archivos fuente, pero no linkear. La etapa de linkeo no se realiza. La última salida es un archivo objeto de cada archivo fuente. Se reemplazan los sufijos ‘.c’, ‘.i’, ‘.s’, etc., con ‘.o’. Los archivos de entrada no reconocidos que no requieran compilación o ensamblado, son ignorados.

Si quiero que no se linkee el archivo ensamblado:
```c
gcc ejemplo.c -c
```

2. La siguiente tarea es poner en uso lo que se encontró. Para eso se debe transcribir al readme.md cada comando ejecutado y su resultado o error correspondiente a la siguiente secuencia de pasos. También en readme.md se vuelcan las conclusiones y se resuelven los puntos solicitados. Para claridad,mantener en readme.md la misma numeración de la secuencia de pasos.



## 1. Preprocesador
### hello2.c

b) Acá se ve el output de la imprementación del lenguaje que hace GCC
- Al principio del archivo se ve una especie de log, lineas precedidas por numeral
- Tambien se ve definiciones (typedef) de datos propios de la implementacion como por ejemplo __gnuc_va_list
- Se incluye contenido de los headers, en particular buscando en dichos headers se inserto bloques que tiene un condicional de preprocesador #ifdef _ISOC99SOURCE, al incluir stdio.h este tambien expande sus propios includes.
- Nuestro código con errores esta intacto al final del archivo.

### hello3.c

d) En la primera línea,
``` c
int printf(const char * restrict s, ...);
```
se declara la existencia de una función `printf` que recibe como argumento un puntero a un `const char` de nombre `s`, y a continuación una lista variable de argumentos.

e) Para éste punto, se ejecutó el comando

``` c
gcc -E hello3.c -o hello3.i
```

A diferencia de `hello2.i`, el archivo `hello3.i` contiene sustancialmente menos líneas del preprocesador debido a la ausencia de otras instrucciones como `#include`s. Sin embargo, en la línea 4 de `hello3.i` se puede ver la línea
``` c
# 1 "/usr/include/stdc-predef.h" 1 3 4
```
que indica que se está haciendo una inclusión por defecto de la librería en la línea 1 del archivo, con los flags que indican: 
1- Comienzo de archivo
3- `stdc-predef.h` proviene de un header del sistema, y que algunos warnings deben ser ignorados.
4- El texto dentro del archivo debe considerarse como encerrado en un bloque `extern "C"`.
La línea siguiente,
``` c
# 0 "<command-line>" 2
```
indica al compilador que, haciendo uso del pseudo archivo `<command-line>`, se vuelve al archivo padre de donde se realizó la inclusión (en éste caso, a `hello3.i`).

Finalmente, al final del archivo se encuentra el código contenido en `hello3.c` sin otras modificaciones.

## 2. Compilación
a) Se intenta compilar `hello3.c` hasta generar `hello3.s` con el siguiente comando:
``` c
gcc -c -S hello3.c -o hello3.s
```
Sin embargo, el proceso falla con el siguiente mensaje:
``` c
hello3.c:5:6: error: expected declaration or statement at end of input
```
### hello4.c

b) El error corresponde a la falta de una llave, esto es un tipo de error sintáctico. Esto es debido a que la función main no contiene una llave de cierre de bloque. De esta forma, el compilador sigue esperando nuevas líneas de sentencias/expresiones pero sólo encuentra el final del archivo.

``` c
gcc -S hello4.c -o hello4.s
```

c) Lo que se ve en `hello4.s` es el código assembler. El objetivo de ese código es llamar a la función prontf.


d) Al ensamblar `hello4.s`, se genera `hello4.o` que es el código hexadecimal.


## 3. Vinculacion
### hello5.c
c) Se realizó la compilación de `hello5.c`, pero al ejecutarlo, se observó que el funcinoamiento no fue el correcto.
Comandos de compilación:

``` c
gcc hello5.c -o hello5 -std=c18
```

Respuesta:
``` c
La respuesta es 4200880
```

Preprocesó, compiló, vinculó y se generó el ejecutable. Sin embargo no dio el resultado esperado, ya que hay un argumento que no pasamos (bug). El valor mostrado es lo que encontró en memoria al momento de ejecutarse la función.

## 4. Corrección de Bug

### hello6.c
a) Se realizó la compilación y funciono correctamente
Comandos de compilación:

``` c
gcc hello6.c -o hello6
```

Respuesta:

``` c
La respuesta es 42
```

Preprocesó, compiló, vinculó y se generó el ejecutable, mostrando el resultado esperado.


## 5. Remoción de prototipo
### hello7.c
b)
 - i. Usando GCC, arroja un warning
 - ii. Un prototipo es la declaración previa de una función antes de ser definida. Estas pueden ser declaradas de manera explícita donde se la declara en el código fuente, o en encabezados.
 - iii. Una declaracion implícita es cuando se utiliza una función sin haberla declarado antes.
 - iv. La especificación de c, indica que no está soportado.
 - v. Las principales implementaciones arrojan warning como GCC o mingw, sin embargo otros como Clang 15.0.0 en adelante arrojan error que que definió que esté prohibido declarar implíctamente una función.
 - vi. Las funciones built-in son funciones que ya están predefinidas en el lenguaje y forman parte del conjunto de funciones que proporciona el compilador.
 - vii. Una razón por la que GCC arroja warning en vez de error es con el fin que se pueda seguir compilando código viejo en donde se utilizan declaraciones implícitas ya que en especificaciones anteriores estaba permitido. Un ejemplo de esto es el proyecto Linux en donde se utilizan declaraciones implícitas en código legacy. GCC no va en contra de la especificación actual dado que la misma indica que las declaraciones implícitas no estan soportadas, sin embargo no están prohibidas.

## 6. Compilación Separada: Contratos y Módulos
b) Para poder compilarlo sin el header, compilamos por separado `studio1.c` y `hello8.c` a archivos de objeto, y luego enlazamos ambos a un ejecutable.

``` c
gcc -g -O -c ./studio1.c
gcc -g -O -c ./hello8.c
gcc -o ./hello8 ./hello8.o ./studio1.o
```
``` c
hello8.c: In function 'main':
hello8.c:4:5: warning: implicit declaration of function 'prontf' [-Wimplicit-function-declaration]
    4 |     prontf("La respuesta es %d\n", i);
      |     ^~~~~~
studio1.c: In function 'prontf':
studio1.c:2:5: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
    2 |     printf("La respuesta es %d\n", i);
      |     ^~~~~~
studio1.c:2:5: warning: incompatible implicit declaration of built-in function 'printf'
studio1.c:1:1: note: include '<stdio.h>' or provide a declaration of 'printf'
  +++ |+#include <stdio.h>
    1 | void prontf(const char* s, int i){
```
Se puede observar que se compila y se linkea correctamente, a pesar de las declaraciones implicitas
   
### Salida del programa:
``` c
$ ./hello8
La respuesta es 42
```

c)
- Si invoco a prontf con argumentos adicionales, el programa se ejecuta normalmente ya que estos argumentos son ignorados al no estar definidos en la lista de parametros que recibe la función. Se permitio generar el ejecutable, ya que el compilador GCC lo permite a pesar de haber declaraciones implícitas. Si se utilizara el compilador CLANG no pasaria ya que no permite las declaraciones implícitas. En la compilacion se pueden observar los mismos warnings que se obtuvieron en el punto c).
- Si llamo a prontf con un solo parámetro (tipo char) el programa muestra el mensaje en pantalla pero con el valor numérico en 0. Esto es comportamiento indefinido porque al pasar diferente cantidad de argumentos que lo definido, el comportamiento depende de la implementación. 
``` c
$ ./hello8
"La respuesta es 0"
```
- Si llamo a prontf sin parámetros, el programa ejecuta pero su salida es un mensaje con un número con un valor indefinido (varía en cada ejecución).
- Al ser un valor del tipo puntero es posible que la función acceda a direcciones de memoria no válidas o produzca resultados inesperados o resultados incorrectos. 
``` c
$ ./hello8
"La respuesta es 2170880"
```
d) ¿Qué ventaja da incluir el contrato en los clientes y en el proveedor?
El contrato permite describir restricciones requisitos y comportamientos esperados de una función o una clase, para garantizar un funcionamiento correcto y predecible.
Por ejemplo pueden incluir restricciones sobre los valores de los parámetros de entrada, el estado de los objetos o cualquier otra dependencia externa necesaria, también puede incluir restricciones a los valores de retorno o estado de los objetos.
Finalmente el contrato también puede especificar las excepciones que pueden ser lanzadas por una función y cómo deben ser tratadas.


## Investigue sobre bibliotecas. ¿Qué son? ¿Se pueden distribuir? ¿Son portables? ¿Cuáles son sus ventajas y desventajas?

Las bibliotecas son colecciones de codigo pre compilado y recursos que proporcionan funciones, modulos, clases y estructuras de datos reutilizables. Estas ayudan a los programadores a ahorrar tiempo y esfuerzo al proporcionar soluciones preimplementadas a tareas y desafios comunes.

Las bibliotecas suelen contener recursos para resolver problemas especificos, al usarlas los programadores pueden centrarse en aspectos de mayor nivel y evitar volver a construir un algoritmo existente.

Los tipos de bibliotecas son:
- Bibliotecas estandar: Son incluidas con el lenguaje de programacion y proporcionan funciones fundamentales como operaciones de entrada/salida, manipulacion de cadenas, operaciones matematicas y de estructuras de datos.
- Bibliotecas de terceros: Son creadas por terceros y ofrecen todo tipo de funciones generalmente enfocadas al un area de programacion especifica como: Desarollo web, manejo de bases de dato y graficos.
- Frameworks: son colecciones de bibliotecas y herramientas que proporcionan una forma especifica para desarrollar aplicaciones ademas tienen reglas o convenciones que los desarrolladores deben seguir.
- Bibliotecas dinamicas: Estas generalmente son incluidas en el sistema operativo y las aplicaciones las utilizan en tiempo de ejecucion.

Las bibliotecas de terceros generalmente se distribuyen como paquetes precompilados pero tambien pueden obtenerse como codigo fuente que usualmente debe ser pro compilado o pre procesado localmente antes de incluirse en la aplicacion. Tambien pueden distribuirse con el sistema operativo, estas bibliotecas se llaman dinamicas y las aplicaciones las ustilizan en tiempo de ejecucion.

Respecto a su portabilidad en la medida en que estén diseñadas para funcionar en diferentes plataformas y sistemas operativos. Sin embargo, la portabilidad puede depender de factores como las dependencias externas, las características específicas del compilador o las APIs utilizadas en la biblioteca.

Ventajas:

- Retilización de código: Las bibliotecas ofrecen funcionalidades y componentes listos para usar, lo que permite a los programadores ahorrar tiempo y esfuerzo al no tener que desarrollar desde cero implementaciones comunes.
- Eficiencia: Las bibliotecas en C++ suelen estar optimizadas y ofrecen un rendimiento eficiente, lo que es especialmente útil en aplicaciones que requieren alto rendimiento o consumo de recursos.
- Mayor productividad: Al utilizar bibliotecas, los desarrolladores pueden enfocarse en la lógica de su aplicación en lugar de preocuparse por implementar detalles técnicos, lo que agiliza el desarrollo y reduce la posibilidad de errores.

Desventajas:

- Dependencias: Al utilizar bibliotecas, es posible que se generen dependencias externas en el proyecto, lo que puede aumentar la complejidad de gestión y configuración.
- Tamaño del ejecutable: Si una biblioteca tiene un tamaño considerable, puede aumentar el tamaño del ejecutable final de la aplicación.
- Incompatibilidad: En algunos casos, las bibliotecas pueden ser incompatibles con determinadas plataformas o versiones de compiladores, lo que puede generar problemas de portabilidad y requerir esfuerzos adicionales de adaptación o solución de problemas.
