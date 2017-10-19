/*************************************************************************
	> File Name: pi.c
	> Author: ShiShupeng
	> Mail: shishupeng@mail.nsccwx.cn 
	> Created Time: 2017年10月19日 星期四 08时46分45秒
 ************************************************************************/

#include <stdio.h>
#include "timer.h"
#include <immintrin.h>

double compute_pi_native(size_t dt)
{
	double pi = 0.0;
	double delta = 1.0/dt;
	size_t i;

	for(i = 0; i < dt; i++)
	{
		double x = (double) i / dt;
		pi += delta / (1.0 + x * x);
	}
	return pi * 4.0;
}
 
double compute_pi_omp_avx(size_t dt)
{
	int i;
	double pi = 0.0;
	double delta = 1.0/ dt;

	__m256d ymm0, ymm1, ymm2, ymm3, ymm4;
	ymm0 = _mm256_set1_pd(1.0);
	ymm1 = _mm256_set1_pd(delta);
	ymm2 = _mm256_set_pd(delta * 3, delta * 2, delta, 0.0);
	ymm4 = _mm256_setzero_pd();

	for(i = 0; i <= dt - 4; i +=4)
	{
		ymm3 = _mm256_set1_pd(i * delta);
		ymm3 = _mm256_add_pd(ymm3, ymm2);
		ymm3 = _mm256_mul_pd(ymm3, ymm3);
		ymm3 = _mm256_add_pd(ymm0, ymm3);
		ymm3 = _mm256_div_pd(ymm1, ymm3);
		ymm4 = _mm256_add_pd(ymm4, ymm3);
	}
	double tmp[4] __attribute__((aligned(32)));
	_mm256_store_pd(tmp, ymm4);
	pi += tmp[0] + tmp[1] + tmp[2] + tmp[3];

	return pi * 4.0;
}
 
double compute_pi_omp_avx_v2(size_t dt)
{
	int i;
	double pi = 0.0;
	double delta = 1.0/ dt;

	__m256d ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6;
	ymm0 = _mm256_set1_pd(1.0);
	ymm1 = _mm256_set1_pd(delta);
	ymm2 = _mm256_set_pd(delta * 3, delta * 2, delta, 0.0);
	ymm4 = _mm256_setzero_pd();
	ymm5 = _mm256_setzero_pd();

	for(i = 0; i <= dt - 8; i += 8)
	{
		ymm3 = _mm256_set1_pd(i * delta);
		ymm3 = _mm256_add_pd(ymm3, ymm2);
		ymm3 = _mm256_mul_pd(ymm3, ymm3);
		ymm3 = _mm256_add_pd(ymm0, ymm3);
		ymm3 = _mm256_div_pd(ymm1, ymm3);
		ymm4 = _mm256_add_pd(ymm4, ymm3);

		ymm6 = _mm256_set1_pd((i + 4) * delta);
		ymm6 = _mm256_add_pd(ymm6, ymm2);
		ymm6 = _mm256_mul_pd(ymm6, ymm6);
		ymm6 = _mm256_add_pd(ymm0, ymm6);
		ymm6 = _mm256_div_pd(ymm1, ymm6);
		ymm5 = _mm256_add_pd(ymm5, ymm6);
	}
	ymm4 = _mm256_add_pd(ymm4, ymm5);
	double tmp[4] __attribute__((aligned(32)));
	_mm256_store_pd(tmp, ymm4);
	pi += tmp[0] + tmp[1] + tmp[2] + tmp[3];

	return pi * 4.0;
}

int main()
{
	double t1, t2;
	size_t dt = 128000000;
	double pi;
	printf("**********base line**********\n");
	get_time(t1);
	pi = compute_pi_native(dt);
	get_time(t2);
	printf("pi = %lf\n", pi);
	printf("time = %lfs\n", t2 - t1);
	printf("**********end**********\n\n");

	printf("**********avx**********\n");
	get_time(t1);
	pi = compute_pi_omp_avx(dt);
	get_time(t2);
	printf("pi = %lf\n", pi);
	printf("time = %lfs\n", t2 - t1);
	printf("**********end**********\n\n");

	printf("**********avx v2*******\n");
	get_time(t1);
	pi = compute_pi_omp_avx_v2(dt);
	get_time(t2);
	printf("pi = %lf\n", pi);
	printf("time = %lfs\n", t2 - t1);
	printf("**********end**********\n");

	return 0;
}
