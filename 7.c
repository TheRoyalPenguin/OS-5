#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

// Функция обработки одного каталога (рекурсивная)
void process_directory(const char *path, FILE *out_fp) {
    DIR *d;
    struct dirent *dir;
    struct stat st;
    char full_path[PATH_MAX];
    
    // Переменные для статистики
    long long total_size = 0;
    int file_count = 0;
    long long max_size = -1;
    char max_filename[256] = "(нет файлов)";

    // --- ПРОХОД 1: Сбор статистики по файлам в текущей папке ---
    d = opendir(path);
    if (!d) {
        perror("Не удалось открыть каталог"); // Не фатально, просто пропускаем
        return;
    }

    while ((dir = readdir(d)) != NULL) {
        // Пропускаем . и ..
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;

        // Собираем полный путь: path + "/" + name
        snprintf(full_path, sizeof(full_path), "%s/%s", path, dir->d_name);

        if (stat(full_path, &st) == 0) {
            // Если это обычный файл
            if (S_ISREG(st.st_mode)) {
                file_count++;
                total_size += st.st_size;
                if (st.st_size > max_size) {
                    max_size = st.st_size;
                    strncpy(max_filename, dir->d_name, sizeof(max_filename));
                }
            }
        }
    }
    closedir(d);

    // Вывод результатов для текущей папки
    char buffer[2048];
    sprintf(buffer, "Каталог: %s\n\tФайлов: %d\n\tОбщий размер: %lld байт\n\tСамый большой файл: %s\n\n",
            path, file_count, total_size, max_filename);
    
    printf("%s", buffer); // На экран
    fprintf(out_fp, "%s", buffer); // В файл

    // --- ПРОХОД 2: Поиск подкаталогов для рекурсии ---
    // Нам нужно снова открыть каталог, чтобы пройтись по папкам
    d = opendir(path);
    if (!d) return;

    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", path, dir->d_name);

        if (stat(full_path, &st) == 0) {
            // Если это каталог, запускаем функцию рекурсивно
            if (S_ISDIR(st.st_mode)) {
                process_directory(full_path, out_fp);
            }
        }
    }
    closedir(d);
}

int main(int argc, char *argv[]) {
    FILE *outfile;

    if (argc < 3) {
        fprintf(stderr, "Использование: %s <путь_к_каталогу> <файл_отчета>\n", argv[0]);
        exit(1);
    }

    outfile = fopen(argv[2], "w");
    if (!outfile) {
        perror("Ошибка создания файла отчета");
        exit(1);
    }

    printf("Начинаем анализ каталога: %s\n\n", argv[1]);
    
    // Запуск рекурсии
    process_directory(argv[1], outfile);

    printf("Анализ завершен. Результаты записаны в %s\n", argv[2]);
    fclose(outfile);

    return 0;
}
