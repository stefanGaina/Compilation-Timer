/******************************************************************************************************
 * Compilation-Timer Copyright (C) 2024                                                               *
 *                                                                                                    *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the   *
 * authors be held liable for any damages arising from the use of this software.                      *
 *                                                                                                    *
 * Permission is granted to anyone to use this software for any purpose, including commercial         *
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:   *
 *                                                                                                    *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the   *
 *    original software. If you use this software in a product, an acknowledgment in the product      *
 *    documentation would be appreciated but is not required.                                         *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being *
 *    the original software.                                                                          *
 * 3. This notice may not be removed or altered from any source distribution.                         *
******************************************************************************************************/

/******************************************************************************************************
 * @file compilation_timer.c                                                                          *
 * @date:      @author:                   Reason for change:                                          *
 * 18.01.2024  Gaina Stefan               Initial version.                                            *
 * @details This file implements the interface defined in compilation_timer.h.                        *
 * @todo If the compilation takes more than 60 minutes the output will not be formatted as            *
 * 01:00:00.000, but instead as 60:00.000.                                                            *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <time.h>
#include <glib/gprintf.h>

#include "compilation_timer.h"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief The name of the file in which the start time will be written and read.
*/
#define TIME_FILE_NAME "time"

/******************************************************************************************************
 * LOCAL FUNCTIONS                                                                                    *
 *****************************************************************************************************/

/**
 * @brief Prints to the terminal the usage of the application.
 * @param void
 * @return void
*/
static void print_usage(void);

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

gboolean compilation_timer(const gint32 argument_count, const gchar* const mode)
{
	FILE*           file       = NULL;
	gchar           buffer[64] = "";
	struct timespec start_time = {};
	struct timespec end_time   = {};
	gint64*         time_ref   = NULL;
	gchar*          end        = NULL;

	if (0 >= argument_count)
	{
		(void)g_fprintf(stdout, "Not enough parameters!\n");
		print_usage();

		return FALSE;
	}

	if (0 == strcmp("start", mode))
	{
		if (1 < argument_count)
		{
			(void)g_fprintf(stdout, "Extra parameters will be ignored!\n");
			print_usage();
		}

		file = fopen(TIME_FILE_NAME, "w");
		if (NULL == file)
		{
			(void)g_fprintf(stdout, "Failed to open \"" TIME_FILE_NAME "\" in write mode!\n");
			return FALSE;
		}

		if (0 != clock_gettime(CLOCK_MONOTONIC, &start_time))
		{
			(void)g_fprintf(stdout, "Failed to get the monotonic time! (error message: %s)", strerror(errno));
			(void)fclose(file);
			file = NULL;

			return FALSE;
		}

		(void)g_fprintf(file, "%" G_GUINT64_FORMAT "\n%" G_GUINT64_FORMAT "\n", start_time.tv_sec, start_time.tv_nsec);
		(void)fclose(file);
		file = NULL;

		return TRUE;
	}

	if (0 == strcmp("end", mode))
	{
		if (1 < argument_count)
		{
			(void)g_fprintf(stdout, "Extra parameters will be ignored!\n");
			print_usage();
		}

		if (2 < argument_count)
		{
			(void)g_fprintf(stdout, "Extra parameters will be ignored!\n");
			print_usage();
		}

		file = fopen(TIME_FILE_NAME, "r");
		if (NULL == file)
		{
			(void)g_fprintf(stdout, "Failed to open \"" TIME_FILE_NAME "\" in read mode!\n");
			return FALSE;
		}

		if (0 != clock_gettime(CLOCK_MONOTONIC, &end_time))
		{
			(void)g_fprintf(stdout, "Failed to get the monotonic time! (error message: %s)", strerror(errno));
			(void)fclose(file);
			file = NULL;

			return FALSE;
		}

		for (time_ref = &start_time.tv_sec; &start_time.tv_nsec != time_ref; time_ref = &start_time.tv_nsec)
		{
			if (NULL == fgets(buffer, sizeof(buffer), file))
			{
				(void)g_fprintf(stdout, "Failed to get the start time!\n");
				(void)fclose(file);
				file = NULL;

				return FALSE;
			}

			errno     = 0;
			*time_ref = g_ascii_strtoll(buffer, &end, 0U);
			if ('\n' != *end || 0 != errno)
			{
				(void)g_fprintf(stdout, "Start time is invalid! (error message: %s)\n", strerror(errno));
				(void)fclose(file);
				file = NULL;

				return FALSE;
			}
		}

		end_time.tv_sec  -= start_time.tv_sec;
		end_time.tv_nsec -= start_time.tv_nsec;
		if (0 > end_time.tv_nsec)
		{
			end_time.tv_nsec += 1000000000L;
			--end_time.tv_sec;
		}

		(void)g_fprintf(stdout, "Time spent: %02" G_GUINT64_FORMAT ":%02" G_GUINT64_FORMAT ".%03" G_GUINT64_FORMAT "\n",
			end_time.tv_sec / 60L, end_time.tv_sec % 60L, end_time.tv_nsec / 1000000L);
		(void)fclose(file);
		file = NULL;

		return TRUE;
	}

	print_usage();
	return FALSE;
}

static void print_usage(void)
{
	(void)g_fprintf(stdout, "Usage: <start/end>\n");
}
