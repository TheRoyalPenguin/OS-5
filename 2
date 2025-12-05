#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;

    if (argc < 2) {
        fprintf(stderr, "Использование: %s <имя_файла>\n", argv[0]);
        exit(1);
    }

    if ((fp = fopen(argv[1], "w")) == NULL) {
        perror("Ошибка открытия файла");
        exit(1);
    }

    printf("Введите текст. Для выхода нажмите Ctrl+F затем Enter (или Ctrl+D):\n");

    while ((c = fgetc(stdin)) != EOF) {
        // Проверка на Ctrl+F (ASCII код 6)
        if (c == 6) { 
            break; 
        }
        
        if (fputc(c, fp) == EOF) {
            perror("Ошибка записи в файл");
            break;
        }
    }

    if (fclose(fp) != 0) {
        perror("Ошибка закрытия файла");
        exit(1);
    }

    printf("\nФайл успешно записан.\n");
    return 0;
}
