//
// Created by Arseny
//
#include <unistd.h>

int main(){
    char c;
    char space = ' ';
    int used = 0;
    while (read(STDIN_FILENO, &c, sizeof(char)) > 0) {
        if(c == ' ') {
            used++;
        }
        if(c != ' '){
            used = used%2;
            if(used){
                write(STDOUT_FILENO, &space, sizeof(char));
            }
            write(STDOUT_FILENO, &c, sizeof(char));
            used = 0;
        }
    }
    return 0;
}

