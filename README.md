# errcheck.h

A library for error handling in C.

Get `errcheck.h` : 
```
wget https://raw.githubusercontent.com/SubramanyaJ/errcheck.h/refs/heads/master/errcheck.h
# OR
curl https://raw.githubusercontent.com/SubramanyaJ/errcheck.h/refs/heads/master/errcheck.h > errcheck.h
```

## Usage

The header file contains the documentation required to 
use the library.

However, a quick guide is given below.
Include `"errcheck.h"` after defining these macros :
```
ERRCHECK_FUNC_NORVAL_HANDLER
ERRCHECK_FUNC_ERRNO_HANDLER
ERRCHECK_PREP_ERRNO
ERRCHECK_RESET_ERRNO
```

Simply use the ERRCHECK_CATCH(NORVAL) and ERRCHECK_EVAL macros
before and after a call that may modify errno.

Pass the expected return value as the parameter NORVAL in ERRCHECK_CATCH.

```
/**
 * e -> Equals
 * n -> Not equals
 * g -> Greater than
 * l -> Less than
 */
...
ERRCHECK_CATCH('e', 0) somecall();
ERRCHECK_EVAL
...
```
