#include <stddef.h>
#include <stdint.h>
#include <stdlib.h> // Para malloc e free
#include <string.h> // Para memcpy
#include "sds.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    if (size < 1)
        return 0;

    // Criar uma string dinâmica usando os dados do fuzzer
    char *input = malloc(size + 1);
    if (!input)
        return 0;
    memcpy(input, data, size);
    input[size] = '\0';

    // Testar a função sdsnew
    sds mystring = sdsnew(input);
    sdsfree(mystring);

    free(input);
    return 0;
}
