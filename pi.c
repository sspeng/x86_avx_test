/*************************************************************************
	> File Name: pi.c
	> Author: ShiShupeng
	> Mail: shishupeng@mail.nsccwx.cn 
	> Created Time: 2017年10月19日 星期四 08时46分45秒
 ************************************************************************/

#include <stdio.h>
#include "timer.h"

double computer_pi_native(size_t dt)
{
	double pi = 0.0;
	double delta = 1.0/dt;
	size_t i;

	for(i = 0; i < dt; i++)
	{
		double x = (double) i/ dt;
		pi += delta / (1.0 + x * x);
	}
	return pi * 4.0;
}
 
int main()
{
	double t1, t2;
	size_t dt = 1000000000;
	double pi;
	get_time(t1);
	pi = computer_pi_native(dt);
	get_time(t2);
	printf("pi = %lf\n", pi);
	printf("time = %lfs\n", t2 - t1);
	return 0;
}
