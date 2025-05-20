#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../slstatus.h"
#include "../util.h"

const char *
mic(const char *unused)
{
	FILE *fp;
	char line[128];
	int mic_muted = 0;

	fp = popen("wpctl get-volume @DEFAULT_SOURCE@", "r");
	if (!fp)
		return NULL;

	if (fgets(line, sizeof(line), fp)) {
		if (strstr(line, "[MUTED]"))
			mic_muted = 1;
	}
	pclose(fp);

	bprintf("%s", mic_muted ? "[MUTED]" : "");
	return buf;
}
