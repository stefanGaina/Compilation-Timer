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
 * @file compilation_timer.h                                                                          *
 * @date:      @author:                   Reason for change:                                          *
 * 18.01.2024  Gaina Stefan               Initial version.                                            *
 * @details This file defines the function prototype that determines the compilation time.            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef COMPILATION_TIMER_H_
#define COMPILATION_TIMER_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <glib.h>

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief If mode is "start", stores the current monotonic time in a file and if mode is "end" determines
 * the time difference since start was made.
 * @param argument_count: How many arguments have been passed (not including executable name).
 * @param mode: "start" or "end", otherwise do nothing.
 * @return TRUE - the operation has been successfully.
 * @return FALSE - an error occured.
*/
extern gboolean compilation_timer(gint32 argument_count, const gchar* mode);

#ifdef __cplusplus
}
#endif

#endif /*< COMPILATION_TIMER_H_ */
