//
// Created by chad on 5/24/17.
//

#ifndef ACA_PROJECT_SET_H
#define ACA_PROJECT_SET_H


typedef struct SetTag{
    int (*close)(void *self);
    //contain blocks
    //maybe store how many blocks
} Set;
#endif //ACA_PROJECT_SET_H
