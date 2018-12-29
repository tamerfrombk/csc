#pragma once

/**
 * @file cvector.h
 * @author Tamer Aly
 * @date 27 Dec 2018
 * @brief contains interface of the cvector structure.
 *
 * 
 * Here is example code to get you started on using the @c cvector:
 * 
 * @code
 * 
 * // for-each callback function signature
 * void print_elem(void* elem, void* context);
 * 
 * //
 * // somewhere in main....
 * //
 * 
 * // create a vector
 * cvector* v = csc_cvector_create();
 * if (v == NULL) {
 *      // couldn't create the vector.
 * }
 * 
 * // add some elements into the vector. Note that they must be on the heap and that the vector "owns" the element.
 * for (int i = 0; i < 10; i++) {
 *      int* x = malloc(sizeof(*x));
 *      if (x == NULL) {
 *          // couldn't allocate memory.
 *      }
 *      CSCError e = csc_cvector_add(v, x);
 *      if (e != E_NOERR) {
 *          // couldn't add the element.
 *      }
 * }
 * 
 * // get the size
 * size_t size = csc_cvector_size(v);
 * 
 * // print the elements "manually"
 * for (size_t i = 0; i < size; i++) {
 *     int* x = (int*) csc_cvector_at(v, i);
 *     printf("%d\n", *x);
 * }
 * 
 * // remove the 2nd element
 * CSCError e = csc_cvector_rm_at(v, 1);
 * if (e != E_NOERR) {
 *     // couldn't remove the element
 * }
 * 
 * // print the elements "functionally"
 * csc_cvector_foreach(v, print_elem, NULL);
 * 
 * // clean up resources
 * csc_cvector_destroy(v);
 * 
 * //
 * // somewhere outside of main...
 * //
 * 
 * // implement the callback
 * void print_elem(void* elem, void* context)
 * {
 *      CSC_UNUSED(context); // no need for context
 *      printf("%d\n", *(int*)elem);
 * }
 * 
 * @endcode
 * 
 */

#include "csc.h"

/**
 * @brief implementation of a generic dynamic array.
 * 
 * cvector implements a dynamic array that mimics @c std::vector from C++.
 * 
 * @see csc_cvector_create
 */
typedef struct cvector cvector;

/**
 * @brief callback function for iterating the elements of a @c cvector.
 * 
 * This callback function defines an operation that will be applied to each element of the @c cvector
 * by the @c csc_cvector_foreach function. 
 * 
 * @param elem the element to process
 * @param context user-defined data that can be passed into the function. Can be @c NULL if unused.
 * 
 * @see csc_cvector_foreach
 */
typedef void (*cvector_foreach)(void* elem, void* context);

/**
 * @brief cvector "constructor" function
 * 
 * This function is used to create a @c cvector. If the function is successful, the function
 * returns a pointer to a @c cvector created on the heap. If unsuccessful, @c NULL is returned.
 * 
 * @return a pointer to a constructed #cvector.
 * 
 * @see csc_cvector_destroy
 */
cvector* csc_cvector_create();

/**
 * @brief cvector "destructor" function
 * 
 * This function is used to clean up resources used by a @c cvector created via the #csc_cvector_create function.
 * This function must be called whenever a cvector is no longer used.
 * 
 * @see csc_cvector_create
 * 
 */
void csc_cvector_destroy(cvector* v);

/**
 * @brief adds an element into the vector.
 * 
 * This function adds @p elem into the supplied vector. Note that @p elem @b MUST point to an element allocated on the heap.
 * 
 * Both @p elem and @p v are expected to be @b non-null. This means that @c NULL elements are @b not allowed.
 * 
 * <b>Time Complexity:</b> @c O(1) best case, @c O(n) worst case, @c O(1) amortized.
 * 
 * @param v the vector.
 * @param elem the element to add.
 * 
 * @return On success, @c CSCError#E_NOERR. On memory allocation failure @c CSCError#E_OUTOFMEM.
 */
CSCError csc_cvector_add(cvector* v, void* elem);

/**
 * @brief removes an element from the vector.
 * 
 * This function removes @p elem from the supplied vector if it exists. In order to remove the element,
 * the function must search for the element in the vector using the supplied @p cmp function. 
 * 
 * All three parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1) best case, @c O(n) average and worst case.
 * 
 * @param v the vector.
 * @param elem the element to remove.
 * @param cmp the comparison function to use. See #csc_compare for more details.
 * 
 * @see csc_compare
 * @see csc_cvector_find
 * 
 */ 
void csc_cvector_rm(cvector* v, const void* elem, csc_compare cmp);

/**
 * @brief removes the element at the specified 0-indexed index from the vector.
 * 
 * This function the element at index @p idx from @p v.
 * 
 * All parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1)
 * 
 * @param v the vector.
 * @param idx the index.
 * 
 * @return @c CSCError#E_NOERR or @c CSCError#E_OUTOFRANGE if the supplied index is out of range.
 */ 
CSCError csc_cvector_rm_at(cvector* v, size_t idx);

/**
 * @brief finds the element in the specified vector.
 * 
 * This function attempts to find @p elem using comparator @p comp.
 * 
 * All parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1) best case, O(n) average and worst case.
 * 
 * @param v the vector.
 * @param elem the element to find.
 * @param cmp the comparison function to use. See #csc_compare for more details.
 * 
 * @return the element or @c NULL if the element couldn't be found.
 */ 
void* csc_cvector_find(const cvector* v, const void* elem, csc_compare cmp);

/**
 * @brief returns the size of the vector.
 * 
 * This function returns the number of elements currently in the vector.
 * 
 * All parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1)
 * 
 * @param v the vector.
 *
 * @return the size of the vector.
 */
size_t csc_cvector_size(const cvector* v);

/**
 * @brief returns the capacity of the vector.
 * 
 * This function returns the number of elements the vector can hold before it needs to be resized.
 * 
 * All parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1)
 * 
 * @param v the vector.
 *
 * @return the capacity of the vector.
 */
size_t csc_cvector_capacity(const cvector* v);

/**
 * @brief applies the callback function to each element of the vector.
 * 
 * This callback function defines an operation that will be applied to each element of the @c cvector.
 * The user may pass in additional context using the @p context param or pass in @c NULL if not required.
 * 
 * <b>Time Complexity:</b> @c O(n)
 * 
 * @param v the vector.
 * @param fn the callback function to apply to each element. See #cvector_foreach.
 * @param context user-defined data that will be applied to the callback. Can be @c NULL if unused.
 * 
 * @see cvector_foreach
 */
void csc_cvector_foreach(cvector* v, cvector_foreach fn, void* context);

/**
 * @brief returns the element at the specified index.
 * 
 * This function performs a range check to ensure that @p idx is less than the size of the vector.
 * 
 * All parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1)
 * 
 * @param v the vector.
 * @param idx the index.
 *
 * @return the element at that index in the vector or @c NULL if the index is out of range.
 */
void* csc_cvector_at(const cvector* v, size_t idx);

/**
 * @brief checks if the vector is empty.
 * 
 * All parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1)
 * 
 * @param v the vector.
 * 
 * @return @c true if the vector is empty. In other words, true if @c csc_cvector_size(v) == 0. Otherwise, @c false.
 */
bool csc_cvector_empty(const cvector* v);

/**
 * @brief reserves memory for the specified number of elements in the vector.
 * 
 * This functions reserves enough memory in the vector such that it is able to hold <i>at least </i>
 * @p num_elems without needing to expand. If the number of elements that will be contained in the vector
 * is known or can be estimated, you @i may be able to improve the performance of your application by allocating
 * the memory for the elements up front using this function. As always with performance, your milage may vary.
 * 
 * Note that memory truncation is @b not allowed. That is, if @p num_elems is < @c csc_cvector_size(v), that is an error.
 * 
 * All parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> OS-specific.
 * 
 * @param v the vector.
 * @param num_elems the number of elements to allocate memory for.
 * 
 * @return On success @c CSCError#E_NOERR. If the requested size is less than the current size, @c CSCError#E_INVALIDOPERATION.
 * If there is a memory error, @c CSCError#E_OUTOFMEM.
 */
CSCError csc_cvector_reserve(cvector* v, size_t num_elems);

/**
 * @brief shrinks the capacity to match the size of the vector.
 * 
 * After a call to this function, the following will be true:
 * 
 * @code
 * csc_cvector_size(v) == csc_cvector_capacity(v);
 * @endcode
 * 
 * This function may be useful in low-memory settings where the vector's capacity greatly exceeds the size and the extra memory
 * won't be required.
 * 
 * All parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> OS-specific.
 * 
 * @param v the vector.
 * 
 * @return On success @c CSCError#E_NOERR. If there is a memory error, @c CSCError#E_OUTOFMEM.
 */
CSCError csc_cvector_shrink_to_fit(cvector* v);

