CC = gcc -g
LDLIBS = -lm

# Arquivos fonte
SRCS = trab3.c Arquivo.c TST_pages.c TST_words.c TST_graph.c MaqBusca.c page.c

# Arquivos objeto correspondentes
OBJS = $(SRCS:.c=.o)

all: trab3

trab3: $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o trab3

%.o: %.c %.h
	$(CC) -c $< -o $@

clean:
	rm -f trab3 $(OBJS)
