#ifndef VECTOR_H
#define VECTOR_H


typedef struct
{
	float x;
	float y;
	float z;
	float w;
}FVECTOR4D;

typedef struct
{
	int x;
	int y;
	int z;
	int w;
}IVECTOR4D;

FVECTOR4D Vector4f();
IVECTOR4D Vector4i();
#endif

