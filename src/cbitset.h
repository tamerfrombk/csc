#pragma once

/**
 * @file cbitset.h
 * @author Tamer Aly
 * @date 27 Dec 2018
 * @brief defines the interface to the #cbitset data structure.
 * 
 * Here is some code to get you started with basic usage of a #cbitset:
 * 
 * @code
 * // create a bitset capable of holding 10 bits
 * cbitset* b = csc_cbitset_create(10);
 * 
 * // set bit 2nd bit
 * CSCError e = csc_cbitset_set(b, 1);
 * if (e != E_NOERR) {
 *      // handle the error
 * }
 * 
 * // check if the 3rd bit is set
 * if (csc_cbitset_at(b, 2, &e)) {
 *      // the bit is set
 * } else {
 *      // the bit isn't set
 * }
 * 
 * // flip the 4th bit
 * e = csc_cbitset_flip(b, 3);
 * if (e != E_NOERR) {
 *      // handle the error
 * }
 * 
 * // access the 11th bit (an error)
 * if (csc_cbitset_at(b, 10, &e)) {
 *      // can't happen
 * } else {
 *      if (e != E_NOERR) {
 *          // out of range
 *      } else {
 *          // can't happen
 *      }
 * }
 * 
 * 
 * // clean up
 * csc_cbitset_destroy(b);
 * 
 * @endcode
 * 
 * @see cbitset.c
 * 
 */

#include "csc.h"

/**
 * @brief the cbitset data structure.
 * 
 * A bitset is a data structure that allows a user to manipulate state that can be represented in a single bit.
 * Normally, this is used to store the state of several boolean conditions in a space efficient manner.
 * You can think of a bitset as a space-optimized version of a vector of @c bool types.
 * 
 */
typedef struct cbitset cbitset;

/**
 * @brief creates a #cbitset.
 * 
 * This function creates a #cbitset capable of holding @p nbits of data. Note that @p nbits must be greater than 0.
 * The bitset is initialized with all of the bits cleared.
 * 
 * @param nbits the number of bits the bitset should manage.
 * 
 * @return a pointer to a #cbitset if successful. On failure or if @p nbits is 0, @c NULL is returned.
 * 
 * @see csc_cbitset_destroy
 * 
 */
cbitset* csc_cbitset_create(size_t nbits);

/**
 * @brief destroys a #cbitset.
 * 
 * This function destroys a #cbitset by cleaning up any resources it holds. After a call to this function @p b should
 * no longer be used.
 * 
 * @p b is expected to be @b non-null.
 * 
 * @param b the bitset.
 * 
 * @see csc_cbitset_create
 *  
 */
void csc_cbitset_destroy(cbitset* b);

/**
 * @brief return the number of bits the bitset is capable of holding.
 * 
 * @p b is expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1)
 * 
 * @param b the bitset.
 * 
 * @return the number of bits the bitset is capable of holding.
 * 
 */
size_t csc_cbitset_size(const cbitset* b);

/**
 * @brief sets the 0-indexed bit supplied in the bitset.
 * 
 * @p b is expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1)
 * 
 * @param b the bitset.
 * @param bit the 0-indexed bit to set.
 * 
 * @return On success, @c CSCError#E_NOERR. If @p bit is out of range, @c CSCError#E_OUTOFRANGE.
 * 
 */
CSCError csc_cbitset_set(cbitset* b, size_t bit);

/**
 * @brief clears the 0-indexed bit supplied in the bitset.
 * 
 * @p b is expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1)
 * 
 * @param b the bitset.
 * @param bit the 0-indexed bit to clear.
 * 
 * @return On success, @c CSCError#E_NOERR. If @p bit is out of range, @c CSCError#E_OUTOFRANGE.
 * 
 */
CSCError csc_cbitset_clear(cbitset* b, size_t bit);

/**
 * @brief flips the 0-indexed bit supplied in the bitset.
 * 
 * @p b is expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1)
 * 
 * @param b the bitset.
 * @param bit the 0-indexed bit to flip.
 * 
 * @return On success, @c CSCError#E_NOERR. If @p bit is out of range, @c CSCError#E_OUTOFRANGE.
 * 
 */
CSCError csc_cbitset_flip(cbitset* b, size_t bit);

/**
 * @brief retrieves the state of the bit at the specified 0-indexed position.
 * 
 * @p b is expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(1)
 * 
 * @param b the bitset.
 * @param bit the 0-indexed bit to check.
 * @param e @b optional parameter to retrieve any errors. Can be @c NULL.
 * 
 * @return On success, @p e is @c CSCError#E_NOERR. If @p bit is out of range, @p e is @c CSCError#E_OUTOFRANGE.
 * If the bit is set, @c true is returned and @c false otherwise.
 * 
 */
bool csc_cbitset_at(const cbitset* b, size_t bit, CSCError* e);

/**
 * @brief sets all the bits in the bitset.
 * 
 * @p b is expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(n)
 * 
 * @param b the bitset.
 * 
 */
void csc_cbitset_set_all(cbitset* b);

/**
 * @brief clears all the bits in the bitset.
 * 
 * @p b is expected to be @b non-null.
 * 
 * <b>Time Complexity:</b> @c O(n)
 * 
 * @param b the bitset.
 * 
 */
void csc_cbitset_clear_all(cbitset* b);