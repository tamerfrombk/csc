#pragma once

/**
 * @file csc.h
 * @author Tamer Aly
 * @date 27 Dec 2018
 * @brief the main include file for the csc library.
 *
 * This is the main include file that must be included alongside any other
 * source and header combination for a particular data structure in the library.
 * This file defines several helper functions that are used throughout the library.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

/**
 * @brief macro that silences compiler warnings about unused function parameters.
 * 
 * This macro is used to silence compiler warnings about unused function parameters.
 * Mostly, this is for unused context parameters in generic callback functions used
 * internally by the library.
 */
#define CSC_UNUSED(x) (void)x

// Windows sometimes doesn't define __WORDSIZE so we use the windows standard instead
#if _WIN32 || _WIN64
    #if _WIN64
        #define CSC_64
    #else
        #define CSC_32
    #endif
#elif defined(__WORDSIZE)
    #if (__WORDSIZE == 64)
        #define CSC_64
    #else
        #define CSC_32
    #endif
#else
    #error "Architecture or environment not currently supported."
#endif

// This macro block will only be defined during a Doxygen run.
// The extra indirection is necessary because Doxygen will only generate documentation for define'd macros.
// This method allows us to define the macros only during a Doxygen run and leave them undef'd during a normal
// build.
#ifdef __CSC_DOXYGEN__

    /**
     * @brief This macro is only defined if compiling on a 64 bit architecture.
     * 
     */
    #define CSC_64

    /**
     * @brief This macro is only defined if compiling on a 32 bit architecture.
     * 
     */
    #define CSC_32
#endif

/**
 * @brief the list of errors that can be returned by the library.
 * 
 * This enumeration defines all of the errors that can be returned by certain library calls.
 * These errors can provide more diagnostic information than a simple true/false return.
 * Whenever this error type is returned, a type of @c CSCError#E_NOERR indicates a successful operation.
 * Any other error, with the exception of @c CSCError#E_ERR_N, indicates an error condition.
 * 
 * It is recommended that you check for this error code whenever possible:
 * @code
 * CSCError e = csc_function(args...);
 * if (e != E_NOERR) {
 *      // handle the error by printing a simple diagnostic message.
 *      char buf[CSC_MAX_ERROR_MSG_LEN] = {0};
 *      csc_error_str(e, buf, CSC_MAX_ERROR_MSG_LEN);
 *      puts(buf);
 * }
 * @endcode
 * 
 * @see csc_error_str
 */
typedef enum CSCError {
    E_NOERR = 0, /**< This indicates no errors occurred in the operation. */
    E_OUTOFMEM, /**< This error indicates the operation failed since memory could not be allocated. */
    E_OUTOFRANGE, /**< This error indicates that the operation failed due to accessing an out of range element. i.e. array index of -1. */
    E_INVALIDOPERATION, /**< This error indicates that the operation failed because an invalid operation was attempted. */
    E_ERR_N /**< This is never returned by any function calls and can be ignored. */
} CSCError;

/**
 * @brief generic swap function to swap two @c void*
 * 
 * This is a generic swap function to swap the provided elements.
 * 
 * @param a A is the first elem.
 * @param b B is the second elem. 
 */
void csc_swap(void** a, void** b);

/**
 * @brief comparison function callback for comparing two elements
 * 
 * This is a comparison function callback for comparing two elements that is used for routine functions like
 * sorting or searching a generic container. When creating a custom comparison function for your type,
 * the following protocol @b must be adhered to:
 *      a return value < 0 means @p a is less than @p b.
 *      a return value of > 0 means @p a is greater than @p b.
 *      a return value of 0 means @p a is equal to @p b.
 * 
 * As a convenience, the library provides comparison functions for all the C built in types.
 * 
 * @param a the first element
 * @param b the second element
 * 
 * @see CSC_DECLARE_BUILTIN_CMP
 */
typedef int (*csc_compare)(const void* a, const void* b);

/**
 * @brief callback function for iterating the elements of a container.
 * 
 * This callback function defines an operation that will be applied to each element of a container.
 * 
 * @param elem the element to process
 * @param context user-defined data that can be passed into the function. Can be @c NULL if unused.
 * 
 */
typedef void (*csc_foreach)(void* elem, void* context);

/**
 * @brief convenience macro defining comparison functions for built in types.
 * 
 * This macro defines a comparison function for built-in C types.
 * 
 * For example, defining CSC_DECLARE_BUILTIN_CMP(int) would create the signature:
 * 
 * @code
 * int csc_cmp_int(const void* a, const void* b);
 * @endcode
 * 
 * Note that this macro only creates the signature of the function. See @c csc.c for 
 * how to implement the signature.
 * 
 * @see csc.c
 */
#define CSC_DECLARE_BUILTIN_CMP(type) int csc_cmp_##type(const void* a, const void* b)

/**
 * @brief the maximum message length a #CSCError is guaranteed to generate.
 * 
 * @see csc_error_str
 * 
 */ 
#define CSC_MAX_ERROR_MSG_LEN 128

/**
 * @brief returns a library-defined error string depending on the error.
 * 
 * This is a convenience function that populates @p buf of length @p len with a 
 * library-defined error message that depends on the value of @p e. It is recommended that @p len 
 * is <i>at least</i> #CSC_MAX_ERROR_MSG_LEN.
 * 
 * This function should ideally be used after a library call returning a #CSCError for a simple diagnostic
 * error handling mechanism. For example:
 * 
 * @code
 * CSCError e = csc_some_func(args...);
 * if (e != E_NOERR) { // uh oh. An error.
 *      char buf[CSC_MAX_ERROR_MSG_LEN] = {0};
 *      csc_error_str(e, buf, CSC_MAX_ERROR_MSG_LEN);
 *      puts(buf);
 * }
 * @endcode
 * 
 * @param e the error.
 * @param buf the buffer to fill. Must be @b non-null.
 * @param len the length of the buffer. Recommended to be >= #CSC_MAX_ERROR_MSG_LEN.
 * 
 * @see CSC_MAX_ERROR_MSG_LEN
 * 
 */
void csc_error_str(CSCError e, char* buf, size_t len);

/*
 * Declare all built-in type comparison functions.
 */

CSC_DECLARE_BUILTIN_CMP(int);