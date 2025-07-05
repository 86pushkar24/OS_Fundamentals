#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void pipeline(const char* p1, const char* p2) {
    int fd[2];
    pipe(fd); // Create a pipe
    int id = fork(); // Fork the process
    if(id != 0){
        // parent process
        close(fd[0]); // Close the read end of the pipe
        dup2(fd[1], STDOUT_FILENO); // Redirect stdout to the write end
        close(fd[1]); // Close the write end after duplicating

        execlp("/bin/cat", "cat", p1, NULL); // Execute the first command
        perror("execlp failed for cat");
    }
    else{
        // child process
        close(fd[1]); // Close the write end of the pipe
        dup2(fd[0], STDIN_FILENO); // Redirect stdin to the read end
        close(fd[0]); // Close the read end after duplicating

        execlp("/usr/bin/grep", "grep", p2, NULL); // Execute the second command
        perror("execlp failed for grep");
    }
}

int main(){
    pipeline("/Users/86pushkar24/Desktop/OS/execv.c", "int");
    return 0;
}

/*
    there is a pipe
    left end : fd[1] -> write end  parent process pointing to STDOUT
    right end : fd[0] -> read end  child process pointing to STDIN
    parent process writes to the pipe and child process reads from it
*/