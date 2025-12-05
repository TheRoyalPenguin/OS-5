#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;
    int n_lines = 0;
    int line_count = 0;

    if (argc < 3) {
        fprintf(stderr, "Использование: %s <имя_файла> <N строк (0 для всех)>\n", argv[0]);
        exit(1);
    }

    n_lines = atoi(argv[2]);

    if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("Ошибка открытия файла");
        exit(1);
    }

    while ((c = fgetc(fp)) != EOF) {
        fputc(c, stdout);

        if (c == '\n') {
            line_count++;
            
            // Если N > 0 и достигли лимита строк
            if (n_lines > 0 && line_count % n_lines == 0) {
                printf("\n--- Нажмите любую клавишу для продолжения ---\n");
                
                // Открываем терминал напрямую для ожидания нажатия
                FILE *tty = fopen("/dev/tty", "r");
                if (tty) {
                    fgetc(tty); // Ждем ввода
                    fclose(tty);
                }
            }
        }
    }

    if (fclose(fp) != 0) {
        perror("Ошибка закрытия файла");
        exit(1);
    }

    printf("\n");
    return 0;
}
