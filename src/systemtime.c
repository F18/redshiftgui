/* systemtime.c -- Portable system time source
   This file is part of Redshift.

   Redshift is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Redshift is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Redshift.  If not, see <http://www.gnu.org/licenses/>.

   Copyright (c) 2010  Jon Lund Steffensen <jonlst@gmail.com>
*/

#include "common.h"
#include "systemtime.h"

int systemtime_get_time(double *t){
#ifndef _WIN32
	struct timespec now;
	/*@i@*/int r = clock_gettime(CLOCK_REALTIME, &now);
	if (r < 0) {
		*t=0.0;
		perror("clock_gettime");
		return RET_FUN_FAILED;
	}

	/*@i@*/*t = now.tv_sec + (now.tv_nsec / 1000000000.0);
#else /* _WIN32 */
	FILETIME now;
	ULARGE_INTEGER i;
	GetSystemTimeAsFileTime(&now);
	/*@i@*/i.LowPart = now.dwLowDateTime;
	/*@i@*/i.HighPart = now.dwHighDateTime;

	/* FILETIME is tenths of microseconds since 1601-01-01 UTC */
	/*@i@*/*t = (i.QuadPart / 10000000.0) - 11644473600.0;
#endif /* _WIN32 */

	return RET_FUN_SUCCESS;
}
