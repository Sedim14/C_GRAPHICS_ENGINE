#include"Vector.h"

FVECTOR4D Vector4f()
{
	FVECTOR4D new;
	new.x = 0.0f;
	new.y = 0.0f;
	new.z = 0.0f;
	new.w = 1.0f;
	return new;
}

IVECTOR4D Vector4i()
{
	IVECTOR4D new;
	new.x = 0;
	new.y = 0.;
	new.z = 0;
	new.w = 1;
	return new;
}
