//
// Created by Arseny
//
#include <unistd.h>
#include <ctype.h>

int main(){
    char c;
    while (read(STDIN_FILENO, &c, sizeof(char)) > 0) {
        c = (char)tolower(c);
        write(STDOUT_FILENO, &c, sizeof(char));
    }

    return 0;
}

