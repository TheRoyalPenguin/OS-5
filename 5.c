#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    FILE *src, *dst;
    int c;
    struct stat st;

    if (argc < 3) {
        fprintf(stderr, "Использование: %s <источник> <назначение>\n", argv[0]);
        exit(1);
    }

    // 1. Получаем права доступа исходного файла
    if (stat(argv[1], &st) == -1) {
        perror("Ошибка получения информации о файле (stat)");
        exit(1);
    }

    // 2. Открываем файлы
    if ((src = fopen(argv[1], "r")) == NULL) {
        perror("Ошибка открытия источника");
        exit(1);
    }
    if ((dst = fopen(argv[2], "w")) == NULL) {
        perror("Ошибка открытия назначения");
        fclose(src);
        exit(1);
    }

    // 3. Копируем
    while ((c = fgetc(src)) != EOF) {
        if (fputc(c, dst) == EOF) {
            perror("Ошибка записи");
            break;
        }
    }

    fclose(src);
    fclose(dst);

    // 4. Применяем права доступа (st.st_mode) к новому файлу
    if (chmod(argv[2], st.st_mode) == -1) {
        perror("Ошибка переноса прав доступа (chmod)");
        exit(1);
    }

    printf("Файл скопирован, права доступа перенесены.\n");
    return 0;
}
