#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <criterion/criterion.h>
#include "fdf.h"

Test(mat_nul, test_nul)
{
	t_mat4s	nul = mat_nul();
	cr_expect_eq(nul.val[2][1], 0);
}

Test(fl, fl)
{
	printf("%.30lf\n",0.1+0.2-0.3);
	cr_expect_eq(0.1 + 0.2 - 0.3, 0.0);
}
