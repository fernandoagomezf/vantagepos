
#ifndef _ID_H_
#define _ID_H_

#include <stdint.h>

#define UID_ARRAY_SIZE  16
#define UID_STR_SIZE    37

typedef struct {
    uint8_t bytes[UID_ARRAY_SIZE];
} uid;

typedef enum {
    uid_result_success = 0, 
    uid_result_nullarg, 
    uid_result_invalidbuffer, 
    uid_result_formaterror
} uid_result;

uid* uid_new();
uid_result uid_generate(uid* id);
uid_result uid_tostring(const uid* id, char* buffer, size_t buffer_size);
int uid_equals(const uid* first, const uid* second);
void uid_delete(uid* id);

#endif
