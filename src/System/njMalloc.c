#include <NinjaDev.h>

void *njMalloc(unsigned int nbytes)
{
    return syMalloc(nbytes);
}

void njFree(void *ap)
{
    syFree(ap);
}