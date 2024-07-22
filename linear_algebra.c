#include "fdf.h"

/*
*	so... hmap gives us 3d vectors 
*	rotate it around x +45deg
*	rotate it around y +35.264
*	first 2 coord are screen x y
*
*
*
*
*
*
*
*
*/

t_mat4s	mat_rot(int axis, double angle)
{
	t_mat4s	res;
	int i;
	int j;

	while (
