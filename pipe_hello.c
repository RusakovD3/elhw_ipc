#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    pid_t child_pid;
    int status;

    int pipefd[2];
    char buf;
    const char *msg = "Hello!";
    
    if (pipe(pipefd) == -1) { 
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();

    if(child_pid == -1){
        perror("Error in creating process");
        exit(EXIT_FAILURE);
    }

    if(child_pid == 0){
        close(pipefd[1]);

        while (read(pipefd[0], &buf, 1) > 0) {
            write(STDOUT_FILENO, &buf, 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]); 
        
        exit(EXIT_SUCCESS);
    } else {
        close(pipefd[0]);
        write(pipefd[1], msg, strlen(msg));
        close(pipefd[1]);
        wait(&status);
        printf("child status = %d\n", WEXITSTATUS(status));
        
        exit(EXIT_SUCCESS);
    }
}
