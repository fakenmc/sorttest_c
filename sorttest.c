/*
 * Copyright (c) 2016 Nuno Fachada
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * */

 /**
 * @file
 * Self-contained ANSI C program for benchmarking sorting algorithms.
 *
 * @author Nuno Fachada
 * @date 2016
 * @copyright Distributed under the [MIT License](http://opensource.org/licenses/MIT)
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/**
 * Generic sort ascending function.
 *
 * @param[in,out] vec Vector to sort.
 * @param[in] n Number of elements to sort.
 * */
typedef void (*sort_generic)(int vec[], int n);

/**
 * Naive bubble sort.
 *
 * @see sort_generic()
 * */
void sort_bubble(int vec[], int n) {

	/* Required variables. */
	int x, y, aux;

	/* Sort cycle. */
	for (x = 0; x < n; x++) {

		for (y = 0; y < n - 1; y++) {

			if (vec[y] > vec[y + 1]) {

				aux = vec[y + 1];
				vec[y + 1] = vec[y];
				vec[y] = aux;

			}

		}

	}
}

/**
 * Selection sort.
 *
 * @see sort_generic()
 * */
void sort_selection(int vec[], int n) {

	/* Required variables. */
	int x, y, min_idx, aux;

	/* Sort cycle. */
	for (x = 0; x < n; x++) {

		min_idx = x;

		for (y = x; y < n; y++) {

			if (vec[min_idx] > vec[y]) {
				min_idx = y;
			}

		}

		aux = vec[x];
		vec[x] = vec[min_idx];
		vec[min_idx] = aux;

	}
}

/**
 * Merge sort.
 *
 * @see sort_generic()
 * */
void sort_merge(int *vec, int n) {

	/* Required variables. */
	int m, i, j, k, *l, *r;

	/* Do not do anything if the array has less than two elements. */
	if (n < 2) {
		return;
	}

	/* Middle index of the array. */
	m = n / 2;

	/* Create temporary left sub-array. */
	l = (int*) malloc(m * sizeof(int));

	for(i = 0; i < m; i++) {
		l[i] = vec[i];
	}

	/* Create temporary right sub-array. */
	r = (int*) malloc((n - m) * sizeof(int));

	for(i = m; i < n; i++) {
		r[i - m] = vec[i];
	}

	/* Recursively sort left sub-array. */
	sort_merge(l, m);

	/* Recursively sort right sub-array. */
	sort_merge(r, n - m);

	/* Merge left and right sub-arrays into vec. */
	i = 0; j = 0; k = 0;

	while ((i < m) && (j < n - m)) {

		if (l[i] < r[j]) {
			vec[k++] = l[i++];
		} else {
			vec[k++] = r[j++];
		}
	}

	while (i < m) {
		vec[k++] = l[i++];
	}

	while (j < n - m) {
		vec[k++] = r[j++];
	}

	/* Free temporary sub-arrays. */
	free(l);
	free(r);
}

/**
 * Quick sort.
 *
 * @see sort_generic()
 * */
void sort_quick(int *vec, int n) {

	/* Required variables. */
	int i, j, p, aux;

	/* Do not do anything if the array has less than two elements. */
	if (n < 2) {
		return;
	}

	/* Get the middle element. */
	p = vec[n / 2];

	/* Partitioning. */
	for (i = 0, j = n - 1; ; i++, j--) {

		while (vec[i] < p) {
			i++;
		}
		while (p < vec[j]) {
			j--;
		}
		if (i >= j) {
			break;
		}

		aux = vec[i];
		vec[i] = vec[j];
		vec[j] = aux;

	}

	/* Recursive calls with partitioned sub-arrays. */
	sort_quick(vec, i);
	sort_quick(vec + i, n - i);
}


/**
 * Main function.
 *
 * @param[in] argc Number of command-line arguments.
 * @param[in] argv Vector of command-line arguments.
 * */
int main(int argc, char* argv[]) {

	/* Required variables. */
	sort_generic sort_func;
	int numel;
	int rng_state;
	int* vec;
	int i;

	/* Require three or four parameters */
	if ((argc < 4) || (argc > 5)) {
		fprintf(stderr, "Usage: %s SORTALG NUM SEED [CHECK]\n", argv[0]);
		fprintf(stderr, "\tSORTALG - Sorting algorithm: bubble, selection, "
			"merge, quick\n");
		fprintf(stderr, "\t    NUM - Number of elements to sort\n");
		fprintf(stderr, "\t   SEED - Seed for random number generator\n");
		fprintf(stderr, "\t  CHECK - Check if sorting is correct\n");
		exit(-1);
	}

	/* Sorting algorithm */
	if (strcmp("bubble", argv[1]) == 0) {
		sort_func = sort_bubble;
	} else if (strcmp("selection", argv[1]) == 0) {
		sort_func = sort_selection;
	} else if (strcmp("merge", argv[1]) == 0) {
		sort_func = sort_merge;
	} else if (strcmp("quick", argv[1]) == 0) {
		sort_func = sort_quick;
	} else {
		fprintf(stderr, "Unknown sorting algorithm: '%s'\n", argv[1]);
		exit(-2);
	}

	/* Number of elements to sort */
	numel = atoi(argv[2]);
	if (numel < 2) {
		fprintf(stderr, "Number of elements to sort must be greater than 1.\n");
		exit(-2);
	}

	/* RNG seed. */
	rng_state = atoi(argv[3]);
	if (rng_state == 0) {
		fprintf(stderr, "Seed for random number generator cannot be 0.\n");
		exit(-3);
	}

	/* Create random vector. */
	vec = (int*) malloc(sizeof(int) * numel);
	for (i = 0; i < numel; i++) {

		/* Use the very basic Park-Miller PRNG. */
		rng_state = (int) ((((long) rng_state) * 16807) % INT_MAX);
		vec[i] = rng_state;

	}

	/* Perform sorting. */
	sort_func(vec, numel);

	/* Check sorting? */
	if (argc == 5) {

		for (i = 0; i < numel - 1; i++) {
			if (vec[i] > vec[i + 1]) {
				fprintf(stderr, "Sorting did not work!\n");
				break;
			}
		}
		if (i == numel - 1) {
			printf("Sorting Ok!\n");
		}
	}

	/* Release random vector. */
	free(vec);

	/* Bye. */
	return 0;

}
