# Ej 3

El comando time reporta el tiempo utilizado por un proceso discriminado por real (tiempo total), user (tiempo ejecutando en user space)
y sys (tiempo ejecutando en kernel space).

1. Ejecute time bash y luego ejecute comandos como si estuviera usando la shell, por ejemplo, listar el directorio (ls), compilar un
programa (gcc), ejecutarlo, copiar un archivo (cp), listar procesos (ps), etc. Al finalizar, presione CTRL + D para enviar el EOF y
que finalice el intérprete de comandos (bash).

a. Analice las proporciones de user y sys respecto de real.

b. ¿Qué cree que hace el proceso bash el resto del tiempo?

2. Ejecute time cat y tipee un texto lo más rápido que pueda. Al finalizar presione CTRL + D para enviar el EOF y que finalice el
comando cat.

a. Analice las proporciones de user y sys respecto de real.

3. Cree un archivo muy grande, por ejemplo, ejecutando cat /dev/random > big durante unos 10 segundos e interrumpiendo
con CTRL + C. (Con ls -lh puede consultar el tamaño). Luego ejecute time md5sum big.

a. Analice las proporciones de user y sys respecto de real.
Cree un programa simple cuyo tiempo de ejecución es kernel space predomine

a. Analice las proporciones de user y sys respecto de real.

## Respuesta Nash

El comando time reporta el tiempo utilizado por un proceso discriminado por real 
(tiempo total), user (tiempo ejecutando en user space) y sys (tiempo ejecutando en 
kernel space).

a. Ejecute time bash y luego ejecute comandos como si estuviera usando la shell, por 
ejemplo, listar el directorio (ls), compilar un programa (gcc), ejecutarlo, copiar 
un archivo (cp), listar procesos (ps), etc. Al finalizar, presione CTRL + D para 
enviar el EOF y que finalice el intérprete de comandos (bash).
    - Analice las proporciones de user y sys respecto de real.
    - ¿Qué cree que hace el proceso bash el resto del tiempo?

Respuesta: Para tareas como compilar, el tiempo de user fue mayor, mientras que para
otras como abrir o copiar archivos el tiempo de sys fue mayor. El resto del tiempo,
el proceso bash se encuentra esperando activamente la entrada del usuario o a un 
recutso del sistema.

b. Ejecute time cat y tipee un texto lo más rápido que pueda. Al finalizar presione 
CTRL + D para enviar el EOF y que finalice el comando cat.
    - Analice las proporciones de user y sys respecto de real.

Respuesta: Obtuvimos un tiempo real de aprox. 16seg mientras que los tiempo de user
y sys fueron muy bajos, con el sys un poco mayor al user. Esto sucede porque la 
funcion cat no realiza muchas operaciones en modo user. El sys es un poco más elevado
porque debe manejar la interacción con el teclado y con la salida estándar.

c. Cree un archivo muy grande, por ejemplo, ejecutando cat /dev/random > big durante 
unos 10 segundos e interrumpiendo con CTRL + C. (Con ls -lh puede consultar el 
tamaño). Luego ejecute time md5sum big.
    - Analice las proporciones de user y sys respecto de real.

Respuesta: Al realizar el hashing, el tiempo de user será muy alto porque demanda 
mucho procesamiento del CPU. Por el contrario, el tiempo de sys será bajo porque
únicamente se requiere que los datos sean traidos del disco a la memoria para ser
leidos y realizar el hashing.

d. Cree un programa simple cuyo tiempo de ejecución es kernel space predomine
    - Analice las proporciones de user y sys respecto de real.

Respuesta: Para realizar este punto, vamos a realizar un programa que incluya muchas
funciones que llamen a syscalls, para así aumentar el tiempo de sys. Ejemplo en 
Ej3.c
