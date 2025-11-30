// start writing from here
#include <stdio.h>
#include <string.h>

#define MAX_MEDIA 100

// ---- Data structure ----
typedef struct {
    int id;
    char title[100];
    char artist[100];
    char genre[50];
    int year;
} Media;

Media library[MAX_MEDIA];
int count = 0;

// ---- Small helper: remove '\n' from fgets ----
void removeNewline(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}