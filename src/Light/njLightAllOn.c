#include <NinjaDev.h>

void njLightAllOn()
{
	int ltptr = _nj_light_control_.ltptr;
	int i = 0;
	
	_nj_light_queue_.num = 0;
	
	if(ltptr > 0) //it matches from here on onwards, i cant get the first part to match, probably compiler diff
	{
		do
		{
			_nj_light_control_.lt[i]->stat = 1;
		}while(++i < ltptr);
	}
}