#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../slstatus.h"
#include "../util.h"

const char *
fortivpn(const char *unused)
{
	FILE *fp;
	char line[256];
	int connected = 0;

	fp = popen("forticlient vpn status", "r");
	if (!fp)
		return NULL;

	while (fgets(line, sizeof(line), fp)) {
		if (strcasestr(line, "connected")) {
			connected = 1;
			break;
		}
	}
	pclose(fp);

    bprintf("%s", connected ? "VPN " : "");
	return buf;
}
