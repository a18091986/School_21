#include <stdio.h>
#include <string.h>

typedef long unsigned s21_size_t;
#define s21_NULL ((void *) 0)

void *s21_memchr(const void *str, int c, s21_size_t n) {
    char *str1 = (char*)str;
    char ch = (char)c;
    char *p = s21_NULL;
    while (n--) {
        if (*str1 == ch) {
            p = (void*)str1;
            break;
        }
        str1++;
    }
    return p;
}

int main()
{
    printf("A: %d\n", 'A');
    char s[] = "Aticleworld";
    char *ptr = memchr(s,'c',sizeof(s));
    char * ptr1 = s21_memchr(s, 'c', sizeof(s));
    
    if (ptr != NULL)
    {
        printf ("'c' found at position %lld.\n", ptr-s+1);
        printf ("search character found:  %s\n", ptr);
    }
    else
    {
        printf ("search character not found\n");
    }

    if (ptr1 != NULL)
    {
        printf ("'c' found at position %lld.\n", ptr1-s+1);
        printf ("search character found:  %s\n", ptr1);
    }
    else
    {
        printf ("search character not found\n");
    }
    return 0;
}