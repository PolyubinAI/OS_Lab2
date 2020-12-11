#include <stdio.h>
#include <unistd.h>


signed main() {

    int pipe1[2];
    int pipe2[2];
    int pipe3[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
        write(1,"Error creating pipe!",22) ;
        return 1;
    }
    int id2 = fork();
    int id1 = fork();
    if (id1 == -1) {
        write(1,"Error creating process!",25);
        return 2;
    }
    else if (id1 == 0) {
        close(pipe1[1]);
        close(pipe3[0]);
        close(pipe3[1]);
        close(pipe2[0]);
        if (dup2(pipe1[0], STDIN_FILENO) == -1) {
            write(1,"Error changing stdin!\n",24);
            return 3;
        }
        if(dup2(pipe2[1], STDOUT_FILENO) == -1){
            write(1,"Error changing stdout!\n",25);
            return 4;
        }
        char *argv[] = {"child1", NULL};;
        if (execv("child1", argv) == -1) {
            write(1,"Error executing child process!\n",33);
            return 4;
        }
    }
    else if (id2 == 0){
        close(pipe1[1]);
        close(pipe3[0]);
        close(pipe1[0]);
        close(pipe2[1]);
        if (dup2(pipe2[0], STDIN_FILENO) == -1) {
            write(1,"Error changing stdin!\n",24);
            return 3;
        }
        if(dup2(pipe3[1], STDOUT_FILENO) == -1){
            write(1,"Error changing stdout!\n",25);
            return 4;
        }
        char *argv[] = {"child2", NULL};;
        if (execv("child2", argv) == -1) {
            write(1,"Error executing child process!\n",34);
            return 4;
        }
    }
    else {
        close(pipe1[0]);
        close(pipe3[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        char c;
        while (read(STDIN_FILENO, &c, sizeof(char)) > 0) {
            write(pipe1[1], &c, sizeof(char));
        }
        close(pipe1[1]);
        while (read(pipe3[0], &c, sizeof(char)) > 0) {
            write(STDOUT_FILENO, &c, sizeof(char));
        }
        close(pipe3[0]);
        return 0;

    }
}