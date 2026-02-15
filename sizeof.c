#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

/* -----------------------------------------------------------------------------
 * sizeof - for when stat is too big
 * there's no point in licensing less 20 lines of code. use it how you want.
 *
 *						~authentic zawadzki 2026
 * -----------------------------------------------------------------------------
 */

int main(int argc, char *argv[]) {
    if (argc == 0)
	return 1;

    int i;
    for (i = 1; i < argc; i++) {
	char *filename = argv[i];

	int descriptor = open(filename, O_RDONLY);
	if (descriptor == -1)
	    return errno;
	
	struct stat filestat;
	int s = stat(filename, &filestat);
	if (s == -1)
	    return errno;

	printf("Size of %s: %ld bytes\n", filename, filestat.st_size);

	close(descriptor);
    }

    return 0;
}
