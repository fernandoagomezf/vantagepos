#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uid.h"

struct uid* uid_new() {
    struct uid* id;
    id = malloc(sizeof(struct uid));
    memset(&id, 0, sizeof(struct uid));
    return id;
}

enum uid_result uid_generate(struct uid* id) {
    if (id == NULL) {
        return uid_result_nullarg;
    }
    
    for (int i = 0; i < ID_BUFFER_SIZE; i++) {
        int random = rand();
        id->bytes[i] = random & 0xFF;
    }
    id->bytes[6] = (id->bytes[6] & 0x0F) | 0x40; // versión 4
    id->bytes[8] = (id->bytes[8] & 0x3F) | 0x80; // rfc 4122

    return uid_result_success;
}

enum uid_result uid_tostring(struct uid* id, char* buffer) {
    if (id == NULL || buffer == NULL) {
        return uid_result_nullarg;
    }

    /* el guid debe tener el siguiente formato: ocho dígitos, cuatro dígitos, 
     * otros cuatro dígitos, doce dígitos, todo separado por un guión.
     *   ########-####-####-####-############
     * por ejemplo:
     *   75692c38-652f-444b-99d7-10eb58c01d26
     * por tanto el búffer necesita tener 36 caracteres más el nulo.
    */
    sprintf(buffer,
        "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",                     /* del ejemplo: */
        id->bytes[0], id->bytes[1], id->bytes[2], id->bytes[3],                                     /* 75692c38-    */
        id->bytes[4], id->bytes[5],                                                                 /* 652f-        */
        id->bytes[6], id->bytes[7],                                                                 /* 444b-        */
        id->bytes[8], id->bytes[9],                                                                 /* 99d7-        */
        id->bytes[10], id->bytes[11], id->bytes[12], id->bytes[13], id->bytes[14], id->bytes[15]    /* 10eb58c01d26 */
    );

    return uid_result_success;
}

void uid_delete(struct uid* id) {
    assert(id != NULL);
    if (id != NULL) {
        free(id);
    }
}

