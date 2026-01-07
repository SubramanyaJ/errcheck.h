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
 * TODO : Check this.
 */

/**
 * Keeping a track of everything here :
 * ERRCHECK_H : 
 *      MACRO
 *      The header guard.
 *
 * ERRCHECK_INT_DECLARE : 
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
 **/

#ifndef ERRCHECK_H
#define ERRCHECK_H

/* I need this for perror() */
#include <stdio.h>

#define ERRCHECK_INT_DECLARE \
        ; \
        int ERRCHECK_INT;

#define ERRCHECK_RET_CATCH \
        ; \
        ERRCHECK_INT = 

void ERRCHECK_HANDLER(int ERRCHECK_INT_PARAM);
void ERRCHECK_HANDLER(int ERRCHECK_INT_PARAM) {
        perror("errcheck");
}

#define ERRCHECK_ERRNO \
        ; \
        ERRCHECK_HANDLER(ERRCHECK_INT);
/**
 * TODO : ERRCHECK_HANDLER is triggered regardless
 * of the return code. Fix this.
 */

/**
 * These were the definitions and declarations.
 * What follows are initializations.
 */

ERRCHECK_INT_DECLARE

#endif
