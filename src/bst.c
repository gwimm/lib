#include "bst.h"
#include "mem.h"

struct bst_obj {
	struct bst_obj *lft, *rit;
	void *val, *key;
};

struct bst {
	struct bst_obj *root;
	cmp_fun_t cmp;
};

struct bst_obj *bst_obj_alc(void *key, void *val) {
	struct bst_obj *obj = mem_alc(sizeof(struct bst_obj));
	obj->lft = NULL;
	obj->rit = NULL;
	obj->key = key;
	obj->val = val;
	return obj;
}

struct bst *bst_alc(cmp_fun_t cmp) {
	struct bst *bst = mem_alc(sizeof(struct bst));
	bst->cmp = cmp;
	bst->root= NULL;
	return bst;
}

void bst_ins(struct bst *bst, void *key, void *val) {
	struct bst_obj **obj = &bst->root;
	while (*obj) switch (bst->cmp((*obj)->key, key)) {
	case cmp_lss: obj = &(*obj)->lft; break;
	case cmp_grt: obj = &(*obj)->rit; break;
	case cmp_eql: (*obj)->val = val; return;
	}
	*obj = bst_obj_alc(key, val);
}

void bst_del(struct bst *bst, void *key) {
	struct bst_obj **obj = &bst->root;
	while (*obj) switch (bst->cmp((*obj)->key, key)) {
	case cmp_lss: obj = &(*obj)->lft; break;
	case cmp_grt: obj = &(*obj)->rit; break;
	case cmp_eql: {
		// TODO
		// you IDIOT!
		// write node deletion algorithm
		// implementation.
		// and then finish the stupid avl tree.
		// thank you.
	} break;
	}
	
}

typedef int (*bst_blk_fun_t)(void *, void *, void *);

void bst_obj_for(struct bst_obj *obj, register bst_blk_fun_t blk, void *arg) {
	if (obj) {
		bst_obj_for(obj->lft, blk, arg);
		blk(obj->val, obj->key, arg);
		bst_obj_for(obj->rit, blk, arg);
	}
}

void bst_for(struct bst *bst, register bst_blk_fun_t blk, void *arg) {
	bst_obj_for(bst->root, blk, arg);
}

void bst_obj_dlc(struct bst_obj *obj) {
	if (obj) {
		bst_obj_dlc(obj->lft);
		bst_obj_dlc(obj->rit);
		mem_dlc(&obj);
	}
}

void bst_dlc(struct bst **bst) {
	bst_obj_dlc((*bst)->root);
	mem_dlc(bst);
}
