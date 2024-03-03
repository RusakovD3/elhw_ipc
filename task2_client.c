#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/my_fifo"

int main() {
    int fd;
    char buf[1024];

    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Читаем сообщение из FIFO
    if (read(fd, buf, sizeof(buf)) == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Received: %s\n", buf);
    close(fd); // Закрываем файловый дескриптор
    unlink(FIFO_PATH);
    
    return 0;
}
