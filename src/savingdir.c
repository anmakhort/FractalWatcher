#include "../include/graphics.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void prepare_saving_dir_and_path(char *buff, const char *base_dir) {
	if (!buff) return;

	size_t n = strlen(base_dir);
	memcpy(buff, base_dir, n);
	buff[n] = '\0';

	struct stat st = {0};
	if (stat(buff, &st) == -1) mkdir(buff, 0700);

	time_t t = time(NULL);
	struct tm local = *localtime(&t);
	sprintf(buff, "%s%d-%d-%d_%d:%d:%d/", buff, \
		local.tm_year+1900, local.tm_mon+1, local.tm_mday, \
		local.tm_hour, local.tm_min, local.tm_sec);

	if (stat(buff, &st) == -1) mkdir(buff, 0700);
}