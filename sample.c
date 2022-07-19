#include <stdio.h>
#include <string.h>
void main()
{
    char a[10] = "geat", b[10] = "";
    int i;

    // a = "get";
    // b = "get";
    i = strcmp(a, "geat");
    printf("%d", i);
}