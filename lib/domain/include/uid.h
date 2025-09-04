
#ifndef _ID_H_
#define _ID_H_

#include <stdint.h>

const size_t ID_BUFFER_SIZE = 16;
const size_t ID_STRING_BUFFER_SIZE = 37;

struct uid {
    uint8_t bytes[16];
};

enum uid_result {
    uid_result_success = 0, 
    uid_result_nullarg, 
    uid_result_invalidarg
};

struct uid* uid_new();
enum uid_result uid_generate(struct uid* id);
enum uid_result uid_tostring(struct uid* id, char* buffer);
void uid_delete(struct uid* id);

#endif
