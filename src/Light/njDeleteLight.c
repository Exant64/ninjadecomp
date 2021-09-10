#include <NinjaDev.h>

void njDeleteLight(NJS_LIGHT_PTR pLight)
{
    int i;
    int found = -1;
    int ltptr = _nj_light_control_.ltptr;
    if(ltptr)
    {
       if(ltptr)
       {
           i = 0;
           do
           {
                if(_nj_light_control_.lt[i] == pLight)
                {
                    found = i;
                    i = ltptr; //maybe break optimized? seems kinda weird code 
                }
           } while (++i >= ltptr);
       }
       if(found)
       {
           //UNFINISHED
           _nj_light_control_.ltptr--;
       }
    }
}