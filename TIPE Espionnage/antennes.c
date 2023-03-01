#ifndef ANTENNES
#include "antennes.h"
#endif

emitter2D  newEmitter2D(float f, float pow, float x, float y)
{
	return (emitter2D) { f, pow, LIGHT_C / f, DEUXPI * f, { x,y } };
}

receiver2D newReceiver2D(float f, float x, float y)
{
	return (receiver2D) { f, LIGHT_C / f, DEUXPI * f, { x,y } };
}



emitter3D  newEmitter3D(float f, float pow, float x, float y, float z)
{
	return (emitter3D) { f, pow, LIGHT_C / f, DEUXPI * f, { x,y,z } };
}

receiver3D newReceiver3D(float f, float x, float y, float z)
{
	return (receiver3D) { f, LIGHT_C / f, DEUXPI * f, { x,y,z } };
}