//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_SET_H
#define ACA_PROJECT_SET_H
#include "uthash/include/uthash.h"

typedef struct SetTag {
    //Used in HashMap
    int size; /* use this field as the key */
    UT_hash_handle hh; /* make this structure hashable*/
    //Used in HashMap

    int (*close)(void *self);
    int index;//refers to the Set
    //contain blocks
    //maybe store how many blocks
} Set;
#endif //ACA_PROJECT_SET_H
