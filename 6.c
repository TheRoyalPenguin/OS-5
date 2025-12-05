#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

// Вспомогательная функция для вывода содержимого
void print_dir_content(const char *path) {
    DIR *d;
    struct dirent *dir;

    printf("\n--- Каталог: %s ---\n", path);
    
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        if (closedir(d) != 0) {
            perror("Ошибка закрытия каталога");
        }
    } else {
        perror("Ошибка открытия каталога");
    }
}

int main(int argc, char *argv[]) {
    char current_path[PATH_MAX];

    // 1. Текущий каталог
    if (getcwd(current_path, sizeof(current_path)) != NULL) {
        print_dir_content(current_path);
    } else {
        perror("Ошибка получения текущего пути");
    }

    // 2. Заданный каталог (если есть аргумент)
    if (argc > 1) {
        print_dir_content(argv[1]);
    } else {
        printf("\nАргумент с именем каталога не передан.\n");
    }

    return 0;
}
