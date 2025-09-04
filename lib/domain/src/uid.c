#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "uid.h"

uid* uid_new() {
    uid* id;
    id = malloc(sizeof(uid));
    uid_init(id);
    return id;
}

uid* uid_init(uid* id) {
    if (id != NULL) {
        memset(&id, 0, sizeof(uid));
    }
    return id;
}

void uid_delete(uid* id) {
    assert(id != NULL);
    if (id != NULL) {
        free(id);
    }
}

uid_result uid_generate(uid* id) {
    if (id == NULL) {
        return uid_result_nullarg;
    }
    
    static int seed = 0;
    if (!seed) {
        srand((unsigned int)time(NULL));
        seed = 1;
    }
    for (int i = 0; i < UID_ARRAY_SIZE; i++) {
        id->bytes[i] = (uint8_t)(rand() % 0xFF);
    }

    // rfc 4122
    id->bytes[6] = (id->bytes[6] & 0x0F) | 0x40; // v4
    id->bytes[8] = (id->bytes[8] & 0x3F) | 0x80; // 10xx

    return uid_result_success;
}

uid_result uidostring(const uid* id, char* buffer, size_t buffer_size) {
    if (id == NULL || buffer == NULL) {
        return uid_result_nullarg;
    }
    if (buffer_size < UID_STR_SIZE) {
        return uid_result_invalidbuffer;
    }

    /* el guid debe tener el siguiente formato: ocho dígitos, cuatro dígitos, 
     * otros cuatro dígitos, doce dígitos, todo separado por un guión.
     *   ########-####-####-####-############
     * por ejemplo:
     *   75692c38-652f-444b-99d7-10eb58c01d26
     * por tanto el búffer necesita tener 36 caracteres más el nulo.
    */
    snprintf(buffer, buffer_size,
        "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",                     /* del ejemplo: */
        id->bytes[0], id->bytes[1], id->bytes[2], id->bytes[3],                                     /* 75692c38-    */
        id->bytes[4], id->bytes[5],                                                                 /* 652f-        */
        id->bytes[6], id->bytes[7],                                                                 /* 444b-        */
        id->bytes[8], id->bytes[9],                                                                 /* 99d7-        */
        id->bytes[10], id->bytes[11], id->bytes[12], id->bytes[13], id->bytes[14], id->bytes[15]    /* 10eb58c01d26 */
    );

    return uid_result_success;
}

int uid_equals(const uid* first, const uid* second) {
    int result = 0;
    if (first == NULL || second == NULL) {
        result = 1;
    } else if (first != NULL && second != NULL) {
        result = memcpm(first->bytes, second->bytes, UID_ARRAY_SIZE) == 0;
    }
    return result;
}



