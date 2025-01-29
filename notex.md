# NOTAS

## Mecánica del programa:

1. Abres archivo1 y lo lees.
2. Usas una tubería para enviar su contenido a través de comando1 (usando fork y exec).
   - Busca el path. Verificamos que el comando está en las variables de entorno.
3. El resultado de comando1 se pasa a través de otra tubería a comando2.
4. El resultado final se escribe en archivo2.

## Herramientas

### Tuberías (pipes)

```bash
    pipe()
```

Necesario para conectar dos procesos entre sí. Se debe realizar antes del fork().

    int pipe(int pipefd[2]);

- pipefd[0] : fd de lectura (lee los datos que el otro proceso escribe);
- pipefd[1] : fd de escritura (escribe los datos que otro proceso leerá)

Su retorno será:

- 0 : si tiene éxito.
- -1 : algo falló y usa errno para indicar el error.

### Fork (procesos padre e hijo)

```bash
    fork()
```

Crea un proceso en C con un espacio de memoria independiente.
Cuando llamamos a la función, se ejecuta en los procesos padre e hijo, y se distingue por el retorno:

- -1 : si ha habido un error.
- 0 : si estamos en el proceso hijo.
- > 0 : si estamos en el proceso padre.

### Exec

```bash
    exec()
```

Reemplaza el proceso actual con otro proceso. Usaremos exec() para ejecutar comando1 y comando2 en los procesos hijos que se haya creado con fork().

    int execlp(const char *file, const char *arg, ..., NULL);

- file : nombre del programa a ejecutar.
- arg : argumenos que se le pasan, el primero suele ser el nombre del programa.
- NULL : obligatorio para finalizar los argumentos.

#### Execlp:

    int execlp(const char *file, const char *arg, ..., NULL);

    execlp("ls", "ls", "-l", NULL)

- "ls" : El programa a ejecutar es el comando.
- "ls" : El primer argumento es el nombre del programa.
- "-l" : El argumento adicional.
- NULL : cierre de argumentos.

Execlp es útil para ejecutar un comando sin tener que escribir la ruta completa, sin variables. Busca en PATH y ejecuta el programa, siempre que estén en PATH.

#### Execl:

    int execl(const char *path, const char *arg, ..., NULL);

    execl("/bin/ls", "ls", "-l", NULL);

- "/bin/ls" : ruta donde econtrará el comando.
- "ls" : comando a ejecutar.
- "-l" : argumento.

Execl ejecuta el comando después de buscarlo en la ruta proporcionada.

#### Execv

    int execv(const char *path, char *const argv[]);
    char *args[] = {"ls", "-l", NULL};

    execv("/bin/ls", args);

Execv es similar a Execl. Se le debe pasar la ruta, pero los argumentos se le pasa por array de strings. Útil para cuando se desconoce el número de argumentos.

#### Execvp

    int execvp(const char *file, char *const argv[]);

    char *args[] = {"ls", "-l", NULL};

execvp("ls", args);

Es similar al Execlp, ya que no hace falta indicar la ruta del PATH donde buscará el comando. Y se le puede pasar los argumentos como un array.

#### Errores

Al ejecutar el proceso, pueden haber errores, así como no encontrar el programa (comando), por lo que podemos averiguarlo con:

    perror("---nombre del exec utilizado antes---")

este nos retornaría un -1 y finalizaría el programa.

### Resumen

1. Crear un proceso hijo con fork().
2. En el hijo, usar exec() para ejecutar el comando (comando1 o comando2).
3. En el padre, manejar las tuberías para pasar los datos entre los comandos.
