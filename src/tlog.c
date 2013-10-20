/*
 * tlog.c
 *
 *  Created on: May 22, 2013
 *      Author: arash
 *
 *  rcpplus is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  rcpplus is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with rcpplus.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <syslog.h>

#include "tlog.h"

static int log_mode = TLOG_MODE_STDERR;
static int min_level = TLOG_WARNING;
static FILE* log_file;
static char log_str[2048];
static const char log_prestr[] = "tlog";
static const char level_str[][10] = {"[EMERG]", "[ALERT]", "[CRIT]", "[ERR]", "[WARN]", "[NOTICE]", "[INFO]", "[DEBUG]"};

int tlog_init(int mode, int level, void* param)
{
	log_mode = mode;
	min_level = level;

	switch (mode)
	{
		case TLOG_MODE_FILE:
		{
			log_file = fopen((const char*)param, "w");
		}
		break;

		case TLOG_MODE_SYSLOG:
		{
			setlogmask(LOG_UPTO(level));

			openlog(log_prestr, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
		}
		break;

		case TLOG_MODE_STDOUT:
			log_file = stdout;
		break;

		case TLOG_MODE_STDERR:
			log_file = stderr;
		break;
	}

	return 0;
}

void tlog(int level, const char* format, ...)
{
	if (level > min_level)
		return;

	va_list args;

	va_start(args, format);
	vsprintf(log_str, format, args);

	if (log_mode == TLOG_MODE_SYSLOG)
		syslog(level, "%s %s", level_str[level], log_str);
	else
	{
		fprintf(log_file, "%s ", level_str[level]);
		fputs(log_str, log_file);
		fputs("\n", log_file);
	}

	va_end(args);
}

void tlog_hex(int level, const char* str, void* d, int l)
{
	if (level > min_level)
		return;

	unsigned char* p = (unsigned char*)d;
	int pos = sprintf(log_str, "%s: (%d) ", str, l);

	for (int i=0; i<l; i++)
		pos += sprintf(log_str+pos, "%02hhx:", p[i]);

	if (log_mode == TLOG_MODE_SYSLOG)
		syslog(level, "%s %s",level_str[level], log_str);
	else
	{
		fprintf(log_file, "%s ", level_str[level]);
		fputs(log_str, log_file);
		fputs("\n", log_file);
	}
}
