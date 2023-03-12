#include <stdio.h>
#include <stdlib.h>


int main() {
    // статическое выделение памяти
    printf("%s\n", "----------------Dynamic memory allocation var_1-------------");
    char * test_string = "test_string";  // строковый литерал
    // test_string[2] = 'A';// строковый литерал хранится в области памяти только для чтения, что не позволяет менять стро ку
    test_string = "test_string_1"; 
    char * test_string_1 = "test_string";
    printf("%s\n", test_string);
    printf("%s\n", test_string_1);

    printf("%s\n", "----------------Dynamic memory allocation var_2-------------");
    char * str_malloc = "123";
    str_malloc = "test_mal";
    str_malloc = malloc(10); // для того, чтобы пользоваться строкой как обычным массивом для начала надо выделить для неё память
    
    
    // TODO 1 sprintf, snprintf
    
    
    sprintf(str_malloc, "%s", "mal_test"); // не контролируем количество записываемых в строку символов, а значит можем выйти за границу массива


    str_malloc[3] = '|';
    free(str_malloc);
    str_malloc = "after_free";
    printf("%s\n", str_malloc);

    printf("%s\n", "----------------Static memory allocation var_1-------------");

    char str_stat[12] = "static_str"; // в данном случае длина статического массива четко равна длине строкового литерала, что приводит к тому, что не хватает места на символ окончания строки и поведение непредсказуемо
    printf("%s\n", str_stat);
    char str_more[11] = "static_str";
    printf("%s\n", str_more);
    char str_size[] = "test_str";
    printf("%s %llu \n", str_size, sizeof(str_size));
    
    return 0;
}

