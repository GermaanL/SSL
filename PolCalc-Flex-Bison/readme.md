# TP N.° 3 - Calculadora Polaca - Léxico

Pre-condiciones -siempre tiene que haber un \n antes de un EOF -Siempre que venga un punto, debe haber un digito despues

## a. ¿Es necesario modificar StackModule.h? ¿Por qué?
Si, es necesario modificarlo ya que en nuestro StackModule.h define a StackItem como token ademas de definir explícitamente una estructura llamada Stack que contiene un arreglo de elementos stack y un campo offset. Esto proporciona una estructura de datos para la pila en el archivo de encabezado.

StackModule.h es el archivo de encabezado (header file) que se utiliza para definir la interfaz de un módulo relacionado con pilas (stack module). Este archivo de encabezado contiene las declaraciones de funciones, tipos de datos y cualquier otro detalle necesario para que otros programas o módulos puedan interactuar con la pila de manera abstracta, sin conocer los detalles internos de su implementación.

## b. ¿Es necesario recompilar la implementación de Stack? ¿Por qué?

Sí, si se realizan modificaciones en la interfaz pública de la pila en "StackModule.h", se debe recompilar la implementación de la pila para que sea coherente con los cambios en la interfaz.

## c. ¿Es necesario que Calculator muestre el lexema que originó el error léxico? Justifique su decisión.

No es necesario, es una desicion de gustos, en caso de querer saber especificamente el error de puede mostrar.

Ventajas de mostrarlo:

- Mejora la claridad: Mostrar el lexema puede ayudar a entender por qué ocurrió el error y a corregirlo de manera más eficiente.
- Facilita la identificación del problema: puede ser útil para identificar problemas en la entrada del usuario.

Desventajas de mostrarlo:

- Puede ser confuso: Mostrar el lexema podría ser confuso para usuarios que no estén familiarizados con el término "lexema."
- Código extra: Mostrar el lexema podría requerir un manejo adicional de cadenas y recursos de memoria.

## c. i) Si decide hacerlo, ¿de qué forma debería exponerse el lexema? Algunas opciones:

- Tercer componente lexeme en Token: incluir el lexema en la estructura Token, se podría exponer directamente al usuario en caso de un error léxico. Sin embargo, podría prestarse a confusion para un usuarios que no entiendan estos conceptos.

- Cambiar el tipo de val a un union: modificar la estructura Token para que tenga un campo val que sea un union capaz de representar tanto el valor numérico como el lexema en caso de un error léxico. Esto proporcionaría flexibilidad para almacenar diferentes tipos de datos según el contexto.

## c. ii) Implemente la solución según su decisión.

## BNF
```
    <cuenta>  ::=   <expresion> ' \n '

    <expresion> ::= <numero> ' ' <numero> <operador>
                    | <expresion> <numero> <operador>
                    | <numero> ' ' <expresion> <operador>
                    | <expresion> <expresion> <operador>

    <operador>::=   + | - | * | /

    <numero> ::=    <entero> 
                    | - <entero>
                    | <decimal>
                    | - <decimal>

    <decimal> ::=   <entero> . <entero> 
                    | . <entero>

    <entero> ::=    <digito> <entero>
                    | <digito>

    <digito> ::=    0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
```
