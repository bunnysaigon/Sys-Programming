/**
* Extreme Edge Cases Lab
* CS 241 - Fall 2018
*/

#include <stdio.h>
#include <stdlib.h>

#include "camelCaser.h"
#include "camelCaser_tests.h"

int main() {
    if (test_camelCaser(&camel_caser, &destroy)) {
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
    }
}