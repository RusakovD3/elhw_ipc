#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "/tmp/my_fifo"

int main() {
    int fd;
    const char *message = "Hello!";

    // Создаем FIFO, если он еще не существует
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Открываем FIFO на запись
    fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Пишем сообщение в FIFO
    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd); // Закрываем файловый дескриптор
    unlink(FIFO_PATH); // Удаляем FIFO
    
    return 0;
}
