#include <NinjaDev.h>

void njLightSystemInit()
{
	int i;

	_nj_light_control_.ltptr = 0;

	_nj_light_material_.diffuse.a = 1;
	_nj_light_material_.diffuse.r = 0.5f;
	_nj_light_material_.diffuse.g = 0.5f;
	_nj_light_material_.diffuse.b = 0.5f;
	_nj_light_material_.specular.a = 1;
	_nj_light_material_.specular.r = 0.5f;
	_nj_light_material_.specular.g = 0.5f;
	_nj_light_material_.specular.b = 0.5f;
	_nj_light_material_.ambient.a = 1;
	_nj_light_material_.ambient.r = 0;
	_nj_light_material_.ambient.g = 0;
	_nj_light_material_.ambient.b = 0;
	_nj_light_material_.exponent = 6.0f;

	
	_nj_light_queue_.num = 0;
	i = 0;
	do
	{
		_nj_light_queue_.ltptr[i] = 0;
		i++;
	}while(i < 32);
	
}