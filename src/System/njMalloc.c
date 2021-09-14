#include <NinjaDev.h>

void *njMalloc(unsigned int nbytes)
{
    return (void*)syMalloc(nbytes);
}

void njFree(void *ap)
{
    syFree(ap);
}