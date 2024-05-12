# Usa una imagen de Linux como base
FROM ubuntu:latest

# Actualiza el sistema e instala el compilador de C (gcc)
RUN apt-get update && apt-get install -y gcc

# Establece el directorio de trabajo dentro del contenedor
WORKDIR /opt/app

# Copia tu código fuente de C al contenedor
COPY . .

# Compila el programa
RUN gcc -o programa programa.c

# Ejecuta el programa cuando se inicie el contenedor
CMD ["./programa"]
