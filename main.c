/*
 * Copyright (c) 2020 Richard Bradshaw
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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define _XOPEN_SOURCE
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SECONDSINDAY	86400

static void usage(void);
static int date_to_time_t(const char *, time_t *);

static void
usage()
{
	fprintf(stderr, "Usage: daysbetween -e <end date> -s <start date>\n");
	fprintf(stderr, "The start date is optional, where this is not "
			"provided, the value will be the current date.\n");
	exit(EXIT_FAILURE);
}

static int
date_to_time_t(const char *date_rep, time_t *tval)
{
	static const char format[] = "%d-%m-%Y";
	struct tm convert;

	memset(&convert, 0, sizeof(struct tm));

	if (date_rep == NULL || tval == NULL)
		return -1;

	if (strptime(date_rep, format, &convert) == NULL)
		return -1;
	*tval = mktime(&convert);
	if (*tval == ((time_t) -1))
		return -1;

	return 0;
}

int
main(int argc, char **argv)
{
	char *date_start;
	char *date_end;
	time_t start;
	time_t end;
	int c;

	date_start = date_end = NULL;
	start = end = 0;

	while ((c = getopt(argc, argv, "e:s:")) != -1) {
		switch (c) {
		case 'e':
			date_end = optarg;
			break;
		case 's':
			date_start = optarg;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (date_end == NULL)
		usage();
	c = date_to_time_t(date_end, &end);
	if (c == -1)
		exit(EXIT_FAILURE);
	if (date_start == NULL) {
		start = time(NULL);
		if (start == ((time_t) -1))
			exit(EXIT_FAILURE);
	} else {
		c = date_to_time_t(date_start, &start);
		if (c == -1)
			exit (EXIT_FAILURE);
	}
	const double diff = difftime(end, start);
	printf("%ld\n", (long)ceil(diff/SECONDSINDAY));

	return 0;
}
