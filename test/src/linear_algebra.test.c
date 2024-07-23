#include "fdf.h"
#include "test/test.h"

t_mat4s	r1_mat4s = {{	{1.f,   2.f,  3.f,  4.f},
						{5.f,   6.f,  7.f,  8.f},
						{9.f,  10.f, 11.f, 12.f},
						{13.f, 14.f, 15.f, 16.f}}};

t_mat4s	r2_mat4s = {{	{   1.f,   10.f,  100.f, 1000.f},
						{  10.f,    1.f, 1000.f,  100.f},
						{ 100.f, 1000.f,    1.f,   10.f},
						{1000.f,  100.f,   10.f,    1.f}}};

t_mat4s	r1xr2_mat4s = {{{ 4321.f,  3412.f,  2143.f, 1234.f},
						{ 8765.f,  7856.f,  6587.f, 5678.f},
						{13209.f, 12300.f, 11031.f, 10122.f},
						{17653.f, 16744.f, 15475.f, 14566.f}}};

Test(float, nonsense)
{
	cr_expect_eq(.1f + .2f, .3f);
	cr_expect_neq(.1 + .2, .3);
	cr_expect_float_neq(.1 + .2, .3, 0);
	cr_expect_float_eq(.1 + .2, .3, DBL_EPSILON);
	cr_expect_float_eq(.1f + .2f, .3f, FLT_EPSILON);
	cr_expect_float_eq(1000000001000001.f + 2000000000000000.f, 3000000000000000.f, FLT_EPSILON);
}
