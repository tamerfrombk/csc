/**
 * @file cbst.c
 * @author Tamer Aly
 * @date 27 Dec 2018
 * @brief This file defines the implements the #cbst data structure and interface functions.
 * 
 */

#include "cbst.h"
#include <assert.h>

typedef struct _node {
    void* data;
    struct _node* left;
    struct _node* right;
} _node;

struct cbst {
    _node* root;
    size_t size;
};

static _node* _create_node(void* data)
{
    _node* n = calloc(1, sizeof(*n));
    if (n != NULL) {
        n->data = data;
    }
    return n;
}

// TODO: turn into iterative traversal
static void _inorder_traversal(_node* n, csc_foreach fn, void* context)
{
    if (n != NULL) {
        _inorder_traversal(n->left, fn, context);
        fn(n->data, context);
        _inorder_traversal(n->right, fn, context);
    }
}

// TODO: turn into iterative traversal
static void _free_cbst(_node* n)
{
    if (n != NULL) {
        _free_cbst(n->left);
        _free_cbst(n->right);
        free(n);
    }
}

static CSCError _add_cbst(_node** n, void* elem, csc_compare cmp, size_t* size)
{
    if (*n == NULL) {
        *n = _create_node(elem);
        if (*n == NULL) {
            return E_OUTOFMEM;
        }
        ++*size;
        return E_NOERR;
    }

    _node* w = *n;
    while (true) {
        const int result = cmp(elem, w->data);
        if (result < 0) {
            return _add_cbst(&(w->left), elem, cmp, size);
        } else if (result > 0) {
            return _add_cbst(&(w->right), elem, cmp, size);
        } else {
            return E_INVALIDOPERATION;
        }
    }
    return E_NOERR;
}

static _node* _find_cbst(const cbst* b, const void* elem, csc_compare cmp)
{
    assert(b != NULL);
    if (elem == NULL) {
        return NULL;
    }

    _node* n = b->root;
    while (n != NULL) {
        const int result = cmp(elem, n->data);
        if (result < 0) {
            n = n->left;
        } else if (result > 0) {
            n = n->right;
        } else {
            return n;
        }
    }
    return NULL;
}

static _node* _leftmost(_node* n)
{
    while (n != NULL && n->left != NULL) {
        n = n->left;
    }
    return n;
}

cbst* csc_cbst_create()
{
    return calloc(1, sizeof(cbst));
}

void csc_cbst_destroy(cbst* b)
{
    assert(b != NULL);
    _free_cbst(b->root);
    free(b);
}

CSCError csc_cbst_add(cbst* b, void* elem, csc_compare cmp)
{
    assert(b != NULL);
    if (elem == NULL) {
        return E_INVALIDOPERATION;
    }
    return _add_cbst(&(b->root), elem, cmp, &(b->size));
}

void* csc_cbst_rm(cbst* b, const void* elem, csc_compare cmp)
{
    assert(b != NULL);
    _node* n = _find_cbst(b, elem, cmp);
    if (n == NULL) {
        return NULL;
    }
    
   if (n->left == NULL && n->right == NULL) { // no children
        void* data = n->data;
        free(n); // TODO: does parent of n know it is now NULL?
        --b->size;
        return data;
    } else if (n->right == NULL && n->left != NULL) { // only left child
        void* data = n->data;
        csc_swap(&(n->data), &(n->left->data));
        free(n->left);
        --b->size;
        n->left = NULL;
        return data;
    } else if (n->left == NULL && n->right != NULL) { // only right child
        void* data = n->data;
        csc_swap(&(n->data), &(n->right->data));
        free(n->right);
        --b->size;
        n->right = NULL;
        return data;
    } else { // both children
        void* data = n->data;
        _node* left = _leftmost(n->right);
        csc_swap(&(left->data), &(n->data));
        --b->size;
        free(left); // TODO: does parent of left know it is now NULL?
        return data;
    }
}

void* csc_cbst_find(const cbst* b, const void* elem, csc_compare cmp)
{
    assert(b != NULL);
    _node* n = _find_cbst(b, elem, cmp);
    if (n == NULL) {
        return NULL;
    }
    return n->data;
}

size_t csc_cbst_size(const cbst* b)
{
    assert(b != NULL);
    return b->size;
}

bool csc_cbst_empty(const cbst* b)
{
    assert(b != NULL);
    return b->size == 0;
}

void csc_cbst_foreach(cbst* b, csc_foreach fn, void* context)
{
    assert(b != NULL);
    _inorder_traversal(b->root, fn, context);
}