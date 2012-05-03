#include <iostream>
#include <stdio.h>
#include "passingargs.h"

void integerTest(int i)
{
    i++;
};

void integerRefTest(int& i)
{
    i++;
}

void integerPointerTest(int* i)
{
    // if you don't add the paranthesis you increment the
    // pointer not the value!
    (*i)++;
}

void passingArgsTest()
{
    // i stays 0 because i is copied.
    int i = 0;
    integerTest(i);
    printf("int test: %u\n", i);
    
    // i2 becomes 1 because i2 is passed by reference
    int i2 = 0;
    integerRefTest(i2);
    printf("int ref test: %u\n", i2);
    
    // i3 becomes 1 because i3 is a pointer to the value 0
    int* i3 = new int(0);
    integerPointerTest(i3);
    printf("int pointer test: %u\n", *i3);
}