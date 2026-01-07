/*
    Copyright (C) 2026 Subramanya J
    This file provides macros for error handling. 

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * I am assuming that ERRCHECK_H is not a commonly 
 * used header guard name.
 * For now, I assume this is safe.
 * TODO : Check this.
 */

/**
 * Keeping a track of everything here :
 * ERRCHECK_H : 
 *      MACRO
 *      The header guard.
 *
 * ERRCHECK_INT_DECLARE_RET : 
 *      MACRO
 *      Used to declare an integer that catches return values.
 *
 * ERRCHECK_INT:
 *      INT
 *      The integer that catches return values.
 *
 * ERRCHECK_RET_CATCH:
 *      MACRO
 *      To be placed right before a function that
 *      may return a value that signals an error.
 *
 * ERRCHECK_ERRNO:
 *      MACRO
 *      To be placed right after a function that
 *      might have set errno.
 *
 * ERRCHECK_HANDLER:
 *      void(int retval);
 *      The function that handles an errno that was set.
 *
 * ERRCHECK_RESET_ERRNO:
 *      Set this to reset errno to 0 after every check.
 *
 * ERRCHECK_ERRCHECK_HANDLER:
 *      Set this to bring the handler into scope.
 **/

#ifndef ERRCHECK_H
#define ERRCHECK_H

/* I need these for perror() */
#include <stdio.h>
#include <errno.h>

#define ERRCHECK_INT_DECLARE_RET static int ERRCHECK_INT_RET;
#define ERRCHECK_INT_DECLARE_NOR static int ERRCHECK_INT_NOR;

ERRCHECK_INT_DECLARE_RET
ERRCHECK_INT_DECLARE_NOR

#define ERRCHECK_RET_CATCH(NORVAL) \
        ERRCHECK_INT_NOR = NORVAL; \
        ERRCHECK_INT_RET = 

static void ERRCHECK_HANDLER(void);

/* Inspired by Sean Barrett */
#if defined(ERRCHECK_ERRCHECK_HANDLER)

static void ERRCHECK_HANDLER(void) {
        if(ERRCHECK_INT_NOR == ERRCHECK_INT_RET) {
                /** Nothing went wrong
                 * Return quietly
                 */
                return;
        }
        perror("errcheck");
#if defined(ERRCHECK_RESET_ERRNO)
        errno = 0;
#endif
}

#endif

#define ERRCHECK_ERRNO ERRCHECK_HANDLER();
/**
 * TODO : ERRCHECK_HANDLER is triggered regardless
 * of the return code. Fix this.
 */


#endif
