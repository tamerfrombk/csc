# csc
**C** **S**tandard **C**ontainers

## Introduction
`csc` is a C99 compliant library that implements many standard container types in a generic and reusable way. `csc`'s primary goals are efficiency, ease of use and integration, and API consistency.

## Primary Features
As previously stated, `csc` aims to be an efficient, generic,
easy to use library that implements many of the most important
data structures in a C99 compliant way. This library is _not_ meant to be the be-all-end-all solution to generic containers. Instead, it is meant as a small and efficient library for C developers who need access to a generic data structure. Without further ado, here are the reasons why `csc` is successful:

* Consistent API:
    * All containers are named with a `c` prefix, use lower case, and snake style naming. For example, a `vector` is called `cvector`.
    * All container interfaces are named like this: `csc_<container>_<operation>`. For example, a find operation for a vector is `csc_cvector_find`; a find operation in a BST is `csc_cbst_find`.
    * Callbacks and other library functions all have the `csc` prefix.
    * Containers are created and destroyed uniformly: `csc_<container>_create()` and `csc_<container>_destroy()`
* (Almost) macro free generic containers.
    * A common way of implementing generic containers in C is to define a set of macros that implement a type specific container. However, a common sentiment in software engineering is that macros are evil and with good reason: macros are hard to write and debug. `csc` prefers to go the `void*` way of implementing generic containers.  
* Slim and trim functionality
    * `csc` does not claim to be the last and greatest container library for C. It contains enough functionality to make the containers user-friendly, bug free, and performant without all the setup bells and whistles many other libraries come with.
* Documentation 
    * `csc` comes with documentation bundled right into the repository upon each version update. See the `/doc` subdirectory for the library's documentation.
* Hassle-free licensing
    * The library is licensed using the MIT license which is very non-restrictive and allows for full use of the source code without warranty. However, I would greatly appreciate a mention if you happen to use `csc` in your projects :)

## Code Sample
> Talk is cheap. Let's see the code. - Linus Torvalds

Here is some code that creates and uses a vector data structure:

```c
#include "cvector.h"
#include <stdio.h>

// define and implement a callback function with this signature
static inline void _print_and_free_elem(void* elem, void* context)
{
    CSC_UNUSED(context); // unused context
    printf("%d\n", *(int*)elem);
    free(elem);
}

int main()
{
    // create a cvector
    cvector* v = csc_cvector_create();
    if (v == NULL) {
        // couldn't create the vector.
    }

    // add some elements to the vector
    int elems[] = {1, 2, 3};
    for (int i = 0; i < sizeof(elems) / sizeof(elems[0]); ++i) {
        int* x = malloc(sizeof(*x));
        if (x == NULL) {
            // no memory
        }
        *x = i;
        CSCError e = csc_cvector_add(v, x);
        if (e != E_NOERR) {
            // print diagnostic message
            char buf[CSC_MAX_ERROR_MSG_LEN] = {0};
            csc_error_str(e, buf, CSC_MAX_ERROR_MSG_LEN);
            puts(buf);
        }
    }

    // print the elements "manually"
    size_t size = csc_cvector_size(v);
    for (size_t i = 0; i < size; i++) {
        int* x = (int*) csc_cvector_at(v, i);
        printf("%d\n", *x);
    }
  
    // remove the 2nd element
    CSCError e = csc_cvector_rm_at(v, 1);
    if (e != E_NOERR) {
        // couldn't remove the element
    }

    // print and clean up resources
    csc_cvector_foreach(v, _print_and_free_elem, NULL);
    csc_cvector_destroy(v);
}
```

## Data Structures
Below is a list of the supported data structures. See the documentation for more info:

* vector
* binary search tree
* bitset

## Building
The library is built as a static library using CMake. To run the build, simply execute the following:

```
mkdir build
cd build
cmake ..
```

This will generate a release version of the library that can be linked into your project. Once the library is built, you can add the `/src` directory to your compiler's include path and the built library to the linked library's path. To generate the debug version of the library that comes with debug symbols, simply define `CMAKE_BUILD_TYPE=debug`:

```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=debug
```

### Building the documentation
It is also possible to build the documentation yourself although this should not be necessary since the documentation is always updated along with the library.

To build the documentation, it is necessary to have `doxygen` installed on your system and in your PATH. Once doxygen is installed, you need to define the `CSC_GENERATE_DOCS` cmake flag in your build. This can be done like so:

```
mkdir build
cd build
cmake .. -DCSC_GENERATE_DOCS=true
```

This command will build the library along with the documentation PDF and put the PDF into the `/doc` directory.

NOTE: this is only supported on Unix-flavor OS's at the moment. Windows support will be added in the future.

## Testing
`csc` comes with a full suite of unit tests to ensure proper behavior functionality and regression testing. The tests are built as an executable called `csc-tests` when cmake is run. Simply run the executable to see the results of your tests. All of the tests are included in the `/test` subdirectory. 

## Contributing
Want to help develop `csc`? Create a branch and raise a PR! :)

## Credits
* [CuTest C Unit Testing](https://github.com/ennorehling/cutest)
* [CMake](https://www.cmake.com)
