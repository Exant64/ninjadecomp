#include <NinjaDev.h>

void njDeleteAllLight()
{
    int i = 0;
    int ltptr = _nj_light_control_.ltptr;

    _nj_light_control_.ltptr = 0;
    _nj_light_queue_.num = 0;

    if(_nj_light_control_.ltptr)
    {
        do
        {
            _nj_light_queue_.ltptr[i] = 0;
        } while (i++ < ltptr);
        
    }
}