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

#ifndef ERRCHECK_H
#define ERRCHECK_H

/* I need these for perror() */
#include <stdio.h>
#include <errno.h>

/**
 * ERRCHECK_INT_RET : 
 *      Catch the value returned from a syscall.
 *
 * ERRCHECK_INT_NOR : 
 *      Hold the value the user supplied, and expects 
 *      syscall to return.
 */
static int ERRCHECK_INT_RET;
static int ERRCHECK_INT_NOR;

/**
 * ERRCHECK_NORVAL_HANDLER :
 *      Assigns the expected return value to ERRCHECK_INT_RET.
 *      If ERRCHECK_PREP_ERRNO is defined, cleans the errno by
 *      setting it to 0.
 *
 * ERRCHECK_ERRNO_HANDLER :
 *      Returns silently if returned value matches expected
 *      value, else calls perror();
 *      If ERRCHECK_RESET_ERRNO is defined, cleans the errno by
 *      setting it to 0.
 */
static inline void ERRCHECK_NORVAL_HANDLER(int);
static inline void ERRCHECK_ERRNO_HANDLER(void);

/**
 * Inspired by Sean Barrett.
 * ERRCHECK_FUNC_NORVAL_HANDLER and ERRCHECK_FUNC_ERRNO_HANDLER
 * need to be defined before including this header to expose the 
 * respective handler function.
 */
#if defined(ERRCHECK_FUNC_NORVAL_HANDLER)
static inline void ERRCHECK_NORVAL_HANDLER(int NORVAL) {
        ERRCHECK_INT_NOR = NORVAL;

#if defined(ERRCHECK_PREP_ERRNO)
        errno = 0;
#endif
}
#endif
/**
 * TODO : Handle range of expected values for NORVAL.
 */

#if defined(ERRCHECK_FUNC_ERRNO_HANDLER)
static inline void ERRCHECK_ERRNO_HANDLER(void) {
        if(ERRCHECK_INT_NOR == ERRCHECK_INT_RET) {
                /* Nothing wrong, return quietly */
                return;
        }
        perror("errcheck");

#if defined(ERRCHECK_RESET_ERRNO)
        errno = 0;
#endif
        /*  Regardless, reset the values. */
        ERRCHECK_INT_NOR = 0;
        ERRCHECK_INT_RET = 0;
}
#endif
/**
 * TODO : Add syscall name to perror output.
 */

/**
 * ERRCHECK_CATCH(NORVAL) :
 *      The macro to be placed right behind a syscall.
 *      Takes the expected return values and passes it
 *      to its handler.
 *      Catches the return value.
 *
 * ERRCHECK_EVAL :
 *      The macro to be placed right after a syscall.
 *      Calls its handler.
 */
#define ERRCHECK_CATCH(NORVAL) \
        ERRCHECK_NORVAL_HANDLER(NORVAL); \
        ERRCHECK_INT_RET = 

#define ERRCHECK_EVAL ERRCHECK_ERRNO_HANDLER();

/**
 * TODO : 
 *      Test in multithreaded code
 *      Test cross-file errors
 */
 
#endif
