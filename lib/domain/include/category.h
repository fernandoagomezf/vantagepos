#ifndef _CATEGORY_H_
#define _CATEGORY_H_

#include "uid.h"

#define CATEGORY_STR_NAME   100

typedef struct {
    uid id;
    uid parent_id;
    char name[CATEGORY_STR_NAME];
} category;

typedef enum {
    category_result_success = 0
} category_result;

category* category_new();
category* category_init(category* category);
void category_delete(category* category);

#endif
