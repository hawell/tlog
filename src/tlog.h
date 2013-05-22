/*
 * tlog.h
 *
 *  Created on: May 22, 2013
 *      Author: arash
 *
 *  This file is part of tlog
 *
 *  tlog is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  tlog is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with tlog.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TLOG_H_
#define TLOG_H_

#include <stdarg.h>

#define TLOG_MODE_STDERR		0
#define TLOG_MODE_STDOUT		1
#define TLOG_MODE_SYSLOG		2
#define TLOG_MODE_FILE			3

#define	TLOG_ERR		3
#define	TLOG_WARNING	4
#define	TLOG_INFO		6
#define	TLOG_DEBUG		7

#define DEBUG(...) tlog(TLOG_DEBUG, __VA_ARGS__)
#define INFO(...) tlog(TLOG_INFO, __VA_ARGS__)
#define WARNING(...) tlog(TLOG_WARNING, __VA_ARGS__)
#define ERROR(...) tlog(TLOG_ERR, __VA_ARGS__)

int tlog_init(int mode, int level, void* param);

void tlog(int level, const char* format, ...);

void log_hex(int level, const char* str, void* d, int l);

#endif /* TLOG_H_ */
