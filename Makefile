CC=gcc
CFLAGS=-pthread -Wall -Werror -Wextra
TARGETS=task_1_pipe task_2_serv task_2_cli

.PHONY: all clean

all: $(TARGETS)

task_1_pipe: pipe_hello.c
	$(CC) $(CFLAGS) -o task_1_pipe pipe_hello.c

task_2_serv: task2_server.c
	$(CC) $(CFLAGS) -o task_2_serv task2_server.c

task_2_cli: task2_client.c
	$(CC) $(CFLAGS) -o task_2_cli task2_client.c

clean:
	rm -f $(TARGETS)