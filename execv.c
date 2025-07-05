#include <stdio.h>
#include <unistd.h>

int main()
{
    char *args[] = {"/bin/ls", "-la", NULL};
    char *env[] = {NULL};

    execve("/bin/ls", args, env);

    // This line only runs if execve fails
    perror("execve failed");
    return 1;
}
