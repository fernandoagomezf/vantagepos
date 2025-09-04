#include <memory.h>
#include <wchar.h>
#include "category.h"

category* category_new() {
    category* cat = malloc(sizeof(category));
    memset(&cat, 0, sizeof(category));
    category_init(cat);

    return cat;
}

category* category_init(category* cat) {
    if (cat!= NULL) {
        uid_init(&cat->id);
        uid_init(&cat->parent_id);
        memset(&cat->name, 0, sizeof(cat->name));
    }
    return cat;
}

void category_delete(category* cat) {
    assert(cat != NULL);
    if (cat != NULL) {
        free(cat);
    }
}