#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "sds.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    if (size < 1)
        return 0;

    char *input = malloc(size + 1);
    if (!input)
        return 0;
    memcpy(input, data, size);
    input[size] = '\0';

    sds mystring = sdsnew(input);

        size_t len = sdslen(mystring);

    sds another_string = sdsnew("_fuzz");
    mystring = sdscat(mystring, another_string);
    sdsfree(another_string);

    if (sdscmp(mystring, input) == 0) {
    }

    sdsrange(mystring, 1, -2);

    sdstrim(mystring, "fu");

    sdsfree(mystring);

    if (mystring)
    {
        mystring[size + 10] = 'X';

        sds largeString = sdsnewlen("A", 1000000);
        sdscat(mystring, largeString);

        sdsfree(largeString);
    }

    sdsfree(mystring);
    sdsfree(mystring);

    free(input);
    return 0;
}