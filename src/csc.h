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

/**
 * @brief macro that silences compiler warnings about unused function parameters.
 * 
 * This macro is used to silence compiler warnings about unused function parameters.
 * Mostly, this is for unused context parameters in generic callback functions used
 * internally by the library.
 */
#define CSC_UNUSED(x) (void)x

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
 *     // handle the error condition.
 * }
 * @endcode
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
 *      a return value < 1 means @p a is less than @p b.
 *      a return value of > 1 means @p a is greater than @p b.
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

CSC_DECLARE_BUILTIN_CMP(int);