/*
	set.h

	Set manipulation.

	Copyright (C) 2012 Bill Currie <bill@taniwha.org>

	Author: Bill Currie <bill@taniwha.org>
	Date: 2012/8/4

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to:

		Free Software Foundation, Inc.
		59 Temple Place - Suite 330
		Boston, MA  02111-1307, USA

*/

#ifndef __QF_set_h
#define __QF_set_h

/**	\defgroup set Set handling
	\ingroup utils
*/
//@{

#define DEFMAP_SIZE ((32 - sizeof (struct set_s *) \
					  - sizeof (unsigned *) \
					  - sizeof (int) - sizeof (unsigned))\
					 / sizeof (unsigned))

/** Represent a set using a bitmap.

	When \a inverted is zero, ones in the bitmap represent members, but when
	\a inverted is non-zero, zeros in the bitmap represent members. However,
	this really is all private implementation details and it is best to treat
	set_t as a black box.
*/
typedef struct set_s {
	struct set_s *next;				///< private. for ALLOC
	unsigned   *map;				///< bitmap of set members
	int         inverted;			///< if true, 0 indicates membership
	unsigned    size;				///< number of representable members
	unsigned	defmap[DEFMAP_SIZE];///< backing store for small sets
} set_t;

/** Represent the state of a scan through a set.

	Very useful in for-loops:
	\code
		set_t      *set;
		set_iter_t *iter;

		create_and_populate (set);
		for (iter = set_first (set); iter; iter = set_next (iter))
			do_something (iter->element);
	\endcode
*/
typedef struct set_iter_s {
	struct set_iter_s *next;	///< private. for ALLOC
	const set_t *set;			///< the set to which this iterator belongs
	/** The result of set_first() or set_next(). set_next() will start at the
		following element.

		\note	For inverted sets, indicates a non-member.
	*/
	unsigned    element;
} set_iter_t;

/** Delete a set iterator that is no longer needed.

	\param set_iter	The set iterator to be deleted.
*/
void set_del_iter (set_iter_t *set_iter);

/** Create a new set.

	The set is initialized to be the empty set.

	\return			The newly created, empty set.
*/
set_t *set_new (void);

/** Delete a set that is no longer needed.

	\param set		The set to be deleted.
*/
void set_delete (set_t *set);

/** Add an element to a set.

	It is not an error to add an element that is already a member of the set.

	\note \a set is modified.

	\param set		The set to which the element will be added.
	\param x		The element to be added.
	\return			The modified set.
*/
set_t *set_add (set_t *set, unsigned x);

/** Remove an element from a set.

	It is not an error to remove an element that is not a member of the set.

	\note \a set is modified.

	\param set		The set from which the element will be removed.
	\param x		The element to be removed.
	\return			The modified set.
*/
set_t *set_remove (set_t *set, unsigned x);

/** Compute the inverse of a set.

	The computation is done as \a set = ~\a set.

	\note \a set is modified.

	\param set		The set to be inverted.
	\return			The set modified to be ~\a src.
*/
set_t *set_invert (set_t *set);

/** Compute the union of two sets.

	The computation is done as \a dst = \a dst | \a src.

	\note \a dst is modified.

	\param dst		The destination set to be modified.
	\param src		The source set.
	\return			The destination set modified to be \a dst | \a src.
*/
set_t *set_union (set_t *dst, const set_t *src);

/** Compute the intersection of two sets.

	The computation is done as \a dst = \a dst & \a src.

	\note \a dst is modified.

	\param dst		The destination set to be modified.
	\param src		The source set.
	\return			The destination set modified to be \a dst & \a src.
*/
set_t *set_intersection (set_t *dst, const set_t *src);

/** Compute the diffedrence of two sets.

	The computation is done as \a dst = \a dst - \a src.

	\note \a dst is modified.

	\param dst		The destination set to be modified.
	\param src		The source set.
	\return			The destination set modified to be \a dst - \a src.
*/
set_t *set_difference (set_t *dst, const set_t *src);

/** Compute the diffedrence of two sets.

	The computation is done as \a dst = \a src - \a dst.

	\note \a dst is modified.

	\param dst		The destination set to be modified.
	\param src		The source set.
	\return			The destination set modified to be \a src - \a dst.
*/
set_t *set_reverse_difference (set_t *dst, const set_t *src);

/** Make a set equivalent to another.

	\note \a dst is modified.

	\param dst		The destination set to make equivalent.
	\param src		The source set to assign to \a dst.
	\return			The modified destination set.
*/
set_t *set_assign (set_t *dst, const set_t *src);

/** Make a set the empty set.

	\note \a set is modified.

	\param set		The set to make the empty set.
	\return			\a set.
*/
set_t *set_empty (set_t *set);

/** Make a set the set of everything.

	\note \a set is modified.

	\param set		The set to make the set of everything.
	\return			\a set.
*/
set_t *set_everything (set_t *set);

/** Test if a set is the set of everything.

	\param set		The set to test.
	\return			1 if \a set is empty (non-inverted).
*/
int set_is_empty (const set_t *set);

/** Test if a set is the set of everything.

	\param set		The set to test.
	\return			1 if \a set is the set of everything (empty inverted set).
*/
int set_is_everything (const set_t *set);

/** Test if two sets are disjoint.

	\param s1		The first set to test.
	\param s2		The second set to test.
	\return			1 if \a s2 is disjoint from \a s1, 0 if not.

	\note	The emtpy set is disjoint with itself.
*/
int set_is_disjoint (const set_t *s1, const set_t *s2);

/** Test if two sets intersect.

	\param s1		The first set to test.
	\param s2		The second set to test.
	\return			1 if \a s2 intersects \a s1, 0 if not.

	\note	Equivalent non-empty sets are treated as intersecting.
*/
int set_is_intersecting (const set_t *s1, const set_t *s2);

/** Test if two sets are equivalent.

	\param s1		The first set to test.
	\param s2		The second set to test.
	\return			1 if \a s2 is equivalent to \a s1, 0 if not.
*/
int set_is_equivalent (const set_t *s1, const set_t *s2);

/** Test if a set is a subset of another set.

	An equivalent set is considered to be a subset.

	\param set		The potential super-set.
	\param sub		The potential subset.
	\return			1 if \a sub is a subset of \a set, or if the sets are
					equivalent.
*/
int set_is_subset (const set_t *set, const set_t *sub);

/** Test an element for membership in a set.

	\param set		The set to test.
	\param x		The element to test.
	\return			1 if the element is a member of the set, otherwise 0.
*/
int set_is_member (const set_t *set, unsigned x);

/** Obtain the number of members (or non-members) of a set.

	Normal sets return the number of members, inverted sets return the number
	of non-members.

	\param set		The set from which the number of (non-)members will be
					obtained.
	\return			The number of (non-)members. Both empty sets and sets of
					evertything will return 0.
*/
unsigned set_size (const set_t *set);

/** Find the first "member" of the set.

	\warning	For normal sets, the set iterator represents a member of the
				set, but for inverted sets, the set iterator represetns a
				<em>non</em>-member of the set.

	\param set		The set to scan.
	\return			A pointer to a set iterator indicating the first
					(non-)member of the set, or null if the set is empty or
					of everything.
*/
set_iter_t *set_first (const set_t *set);

/** Find the next "member" of the set.

	\warning	For normal sets, the set iterator represents a member of the
				set, but for inverted sets, the set iterator represetns a
				<em>non</em>-member of the set.

	\param set_iter	The set iterator representing the state of the current
					scan.
	\return			A pointer to a set iterator indicating the next
					(non-)member of the set, or null if no mor (non-)members
					are available.

	\note	The set iterator is automatically deleted when the end of the set
			is reached.
*/
set_iter_t *set_next (set_iter_t *set_iter);

/** Return a human-readable string representing the set.

	Empty sets will be represented by the string "[empty]". Sets of everything
	will be represented by the string "[everything]". Inverted sets will have
	the first implicit member followed by "..." (eg, "256 ...").

	\param set		The set to be converted to a string.
	\return			The human readable representation of the string.

	\warning	The string is kept in a static variable, so subsequent calls
				will overwrite the results of preceeding calls.
*/
const char *set_as_string (const set_t *set);

//@}
#endif//__QF_set_h
