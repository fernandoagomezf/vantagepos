
#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include "uid.h"

#define PRODUCT_STR_SKU     16
#define PRODUCT_STR_NAME    100
#define PRODUCT_STR_DESC    500

typedef enum {
    product_result_success = 0
} product_result;

typedef struct {
    uid id;
    uid category_id;
    char sku[PRODUCT_STR_SKU];
    char name[PRODUCT_STR_NAME];
    char description[PRODUCT_STR_DESC];
    float price;
} product;

#endif
