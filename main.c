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

// ---- Batch import from CSV ----
// Very simple parsing: fields must not contain commas.
void loadCSV(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Could not open file: %s\n", filename);
        return;
    }

    char line[300];

    // Skip header line
    if (fgets(line, sizeof(line), fp) == NULL) {
        fclose(fp);
        printf("Empty file.\n");
        return;
    }

    while (fgets(line, sizeof(line), fp) && count < MAX_MEDIA) {
        Media m;
        if (sscanf(line, "%d,%99[^,],%99[^,],%49[^,],%d",
                   &m.id, m.title, m.artist, m.genre, &m.year) == 5) {
            library[count++] = m;
        }
    }

    fclose(fp);
    printf("Loaded %d items from CSV.\n", count);
}

// ---- Display all media ----
void displayMedia() {
    if (count == 0) {
        printf("No media in library.\n");
        return;
    }

    printf("\n--- Media Library ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Title: %s | Artist: %s | Genre: %s | Year: %d\n",
               library[i].id,
               library[i].title,
               library[i].artist,
               library[i].genre,
               library[i].year);
    }
}



// ---- Main menu ----
int main() {
    int choice;

    while (1) {
        printf("\nMedia Library Menu\n");
        printf("1. Load from CSV (batch import)\n");
        printf("2. Add media\n");
        printf("3. Edit media\n");
        printf("4. Delete media\n");
        printf("5. Display all media\n");
        printf("6. Search by title (exact / substring)\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                loadCSV("media.csv");
                break;
            case 2:
                addMedia();
                break;
            case 3:
                editMedia();
                break;
            case 4:
                deleteMedia();
                break;
            case 5:
                displayMedia();
                break;
            case 6:
                searchTitle();
                break;
            case 7:
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }
}