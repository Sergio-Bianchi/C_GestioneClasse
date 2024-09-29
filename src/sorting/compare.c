//
// Created by jag on 9/29/24.
//

#include "sorting.h"
#include "../header.h"

int cmpNameDescending(const void *a, const void *b) {
    student *aa = (student *) a;
    student *bb = (student *) b;
    return strcasecmp(aa->name, bb->name);

}

int cmpSurnameDescending(const void *a, const void *b) {
    student *aa = (student *) a;
    student *bb = (student *) b;
    return strcasecmp(aa->surname, bb->surname);

}


int cmpNameAscending(const void *a, const void *b) {
    student *aa = (student *) a;
    student *bb = (student *) b;
    return strcasecmp(bb->name, aa->name);

}

int cmpSurnameAscending(const void *a, const void *b) {
    student *aa = (student *) a;
    student *bb = (student *) b;
    return strcasecmp(bb->surname, aa->surname);

}


int cmpHeightDescending(const void *a, const void *b) {
    student *aa = (student *) a;
    student *bb = (student *) b;
    return (bb->height - aa->height);

}


int cmpHeightAscending(const void *a, const void *b) {
    student *aa = (student *) a;
    student *bb = (student *) b;
    return (aa->height - bb->height);
}