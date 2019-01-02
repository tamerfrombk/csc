#pragma once

/**
 * @file cbst.h
 * @author Tamer Aly
 * @date 27 Dec 2018
 * @brief This file defines the interface to the #cbst data structure.
 *
 * 
 * #cbst implements a standard binary search tree (BST). In this implementation,
 * attempting to add duplicate or @c NULL keys is not allowed. See #csc_bst_add
 * for more details.
 * 
 * Here is a brief code sample to get you started with using #cbst:
 * 
 * @code
 * // a callback function to call on each element of the tree
 * void print_and_free_elem(void* elem, void* context);
 * 
 * //
 * // somewhere in main
 * //
 * 
 * // create a tree
 * cbst* tree = csc_cbst_create();
 * if (tree == NULL) {
 *     // couldn't create the tree
 * }
 * 
 * // add some elements
 * int elems[] = {5, 3, 7, 2, 4, 6, 8};
 * for (int i = 0; i < sizeof(elems) / sizeof(int); ++i) {
 *      int* x = malloc(sizeof(*x));
 *      if (x == NULL) {
 *          // couldn't allocate memory
 *      }
 *      *x = elems[i];
 *      CSCError e = csc_cbst_add(tree, x, csc_cmp_int);
 *      if (e != E_NOERR) {
 *          // handle the error
 *      }
 * }
 * 
 * // remove an element
 * int* e = (int*) csc_cbst_rm(b, &elems[0], csc_cmp_int);
 * if (e == NULL) {
 *      // the element didn't exist
 * } else {
 *      // e is the element which was removed.
 *      // here is an opportunity to do any resource cleanup or operations on e.
 *      free(e);
 * }
 * 
 * // find an element
 * int* elem = (int*) csc_cbst_find(b, &elems[2], csc_cmp_int);
 * if (elem == NULL) {
 *     // element wasn't found.
 * }
 * 
 * // get the number of elements in the tree
 * size_t n_elems = csc_cbst_size(b);
 * 
 * // iterate over all of the elements in the tree in an in-order traversal
 * csc_cbst_foreach(b, print_elem, NULL);
 * 
 * // clean up
 * csc_cbst_destroy(b);
 * 
 * // implement the callback
 * void print_and_free_elem(void* elem, void* context)
 * {
 *     CSC_UNUSED(context);
 *     int* e = (int*) elem;
 *     printf("%d\n", *e);
 *     free(e);
 * }
 * 
 * @endcode
 * 
 */

#include "csc.h"

/**
 * @brief implementation of a binary search tree.
 * 
 * @see csc_cbst_create
 * 
 */
typedef struct cbst cbst;

/**
 * @brief cbst "constructor" function
 * 
 * This function is used to create a @c cbst. If the function is successful, the function
 * returns a pointer to a @c cbst created on the heap. If unsuccessful, @c NULL is returned.
 * 
 * @return a pointer to a constructed #cbst.
 * 
 * @see csc_cbst_destroy
 * 
 */
cbst* csc_cbst_create();

/**
 * @brief cbst "destructor" function
 * 
 * This function is used to clean up resources used by a @c cbst created via the #csc_cbst_create function.
 * This function must be called whenever a cbst is no longer used.
 * 
 * @see csc_cbst_create
 * 
 */
void csc_cbst_destroy(cbst* b);

/**
 * @brief adds an element into the BST.
 * 
 * This function adds @p elem into the supplied BST. Note that adding the element into the BST does @b not
 * make the BST own the element. The user is still responsible for cleaning up that memory.Moreover, duplicate
 * elements are not allowed.
 * 
 * Both @p elem and @p b are expected to be @b non-null. This means that @c NULL elements are @b not allowed.
 * 
 * <b>Time Complexity:</b> @c O(1) best case, @c O(h) worst case, @c O(log(n)) average case where @c h is the height
 * of the tree and @c n is the number of elements the tree holds.
 * 
 * @param b the BST.
 * @param elem the element to add.
 * 
 * @return On success, @c CSCError#E_NOERR. On memory allocation failure @c CSCError#E_OUTOFMEM. If a duplicate element
 * is attempted to be added, @c CSCError#E_INVALIDOPERATION.
 * 
 */
CSCError csc_cbst_add(cbst* b, void* elem, csc_compare cmp);

/**
 * @brief removes an element from the BST.
 * 
 * This function removes @p elem from the supplied BST if it exists. In order to remove the element,
 * the function must search for the element in the BST using the supplied @p cmp function. The removed element
 * is returned. 
 * 
 * All three parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1) best case, @c O(h) worst case, @c O(log(n)) average case where @c h is the height
 * of the tree and @c n is the number of elements the tree holds.
 * 
 * @param b the BST.
 * @param elem the element to remove.
 * @param cmp the comparison function to use. See #csc_compare for more details.
 * 
 * @return If the element is successfully removed, the element is returned. Otherwise, @c NULL.
 * 
 * @see csc_compare
 * @see csc_cbst_find
 * 
 */ 
void* csc_cbst_rm(cbst* b, const void* elem, csc_compare cmp);

/**
 * @brief finds the element in the specified BST.
 * 
 * This function attempts to find @p elem using comparator @p comp.
 * 
 * All parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1) best case, @c O(h) worst case, @c O(log(n)) average case where @c h is the height
 * of the tree and @c n is the number of elements the tree holds.
 * 
 * @param b the BST.
 * @param elem the element to find.
 * @param cmp the comparison function to use. See #csc_compare for more details.
 * 
 * @return the element or @c NULL if the element couldn't be found.
 */
void* csc_cbst_find(const cbst* b, const void* elem, csc_compare cmp);

/**
 * @brief returns the size of the BST.
 * 
 * All parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1)
 * 
 * @param b the BST.
 *
 * @return the size of the BST.
 */
size_t csc_cbst_size(const cbst* b);

/**
 * @brief checks if the BST is empty.
 * 
 * All parameters are expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1)
 * 
 * @param b the BST.
 * 
 * @return @c true if the BST is empty. In other words, true if @c csc_cbst_size(v) == 0. Otherwise, @c false.
 */
bool csc_cbst_empty(const cbst* b);

/**
 * @brief applies the callback function to each element of the BST in an @b in-order traversal.
 * .
 * The user may pass in additional context using the @p context param or pass in @c NULL if not required.
 * 
 * <b>Time Complexity:</b> @c O(n)
 * 
 * @param b the BST.
 * @param fn the callback function to apply to each element.
 * @param context user-defined data that will be applied to the callback. Can be @c NULL if unused.
 * 
 */
void csc_cbst_foreach(cbst* b, csc_foreach fn, void* context);