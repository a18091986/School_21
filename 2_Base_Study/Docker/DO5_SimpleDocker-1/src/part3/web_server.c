#include <stdlib.h>
#include "fcgi_stdio.h"

int main (void) {
    // fcgi_accept - принимает http запросы
    while (FCGI_Accept() >= 0) {
        printf("Connect-type: text/html\r\nStatus: 200 OK\r\n\r\n"
        "Hello World!");
    }
    return 0;
}
