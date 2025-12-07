CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -O2

OBJS = main.o \
       menu.o \
       paciente.o \
       procedimentos.o \
       historico.o \
       lista_pacientes.o \
       fila_triagem.o \
       IO.o

sistema: $(OBJS)
	$(CC) $(CFLAGS) -o sistema.exe $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	del /Q *.o sistema.exe

run: sistema
	./sistema.exe

all: sistema
