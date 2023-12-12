#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stdintail(unsigned int n) {
    char **lines = NULL;
    unsigned int lineCount = 0;
    unsigned int maxLines = n;

    // Read lines from standard input
    char *line = NULL;
    size_t bufferSize = 0;
    ssize_t bytesRead;

    while ((bytesRead = getline(&line, &bufferSize, stdin)) != -1) {
        if (lineCount >= maxLines) {
            free(lines[0]);
            memmove(lines, lines + 1, (maxLines - 1) * sizeof(char *));
            lineCount--;
        }

        lines = realloc(lines, (lineCount + 1) * sizeof(char *));
        lines[lineCount] = malloc((bytesRead + 1) * sizeof(char));
        strncpy(lines[lineCount], line, bytesRead);
        lineCount++;
    }

    free(line);

    for (unsigned int i = 0; i < lineCount; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }

    free(lines);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_lines>\n", argv[0]);
        return 1;
    }

    unsigned int n = atoi(argv[1]);

    stdintail(n);

    return 0;
}
