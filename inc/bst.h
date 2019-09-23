#ifndef   BST_H
#define   BST_H
#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus

typedef int (*bst_blk_fun_t)(void *, void *);

struct bst {
        struct bst_obj *root;
        cmp_fun_t cmp;
};

struct bst *bst_alc(cmp_fun_t);
void bst_dlc(struct bst **);

void bst_ins(struct bst *, void *);
void bst_del(struct bst *, void *);
void bst_for(struct bst *, register bst_blk_fun_t, void *);

#ifdef    __cplusplus
}
#endif // __cplusplus
#endif // BST_H
