#include <bst.h>
#include <mem.h>
#include <alloc.h>

struct bst_obj {
        struct bst_obj *left, *right;
        void *val;
};

static struct bst_obj *bst_obj_alc(void *);
static void bst_obj_for(struct bst_obj *, register bst_blk_fun_t, void *);
static void bst_obj_dlc(struct bst_obj *);

struct bst *bst_alc(cmp_fun_t cmp) {
	struct bst *bst = mem_alc(sizeof(struct bst));
	bst->cmp = cmp;
	bst->root = 0;
	return bst;
}

static struct bst_obj *bst_obj_alc(void *val) {
	struct bst_obj *obj = mem_alc(sizeof(struct bst_obj));
	obj->left = 0;
	obj->right = 0;
	obj->val = val;
	return obj;
}

void bst_ins(struct bst *bst, void *val) {
	struct bst_obj **obj = &bst->root;
	while (*obj) switch (bst->cmp((*obj)->val, val)) {
	case cmp_lesser: obj = &(*obj)->left; break;
	case cmp_greater: obj = &(*obj)->right; break;
	case cmp_equal: (*obj)->val = val; return;
	}
	*obj = bst_obj_alc(val);
}

void bst_del(struct bst *bst, void *val) {
	struct bst_obj **obj = &bst->root;
	while (*obj) switch (bst->cmp((*obj)->val, val)) {
	case cmp_lesser: obj = &(*obj)->left; break;
	case cmp_greater: obj = &(*obj)->right; break;
	case cmp_equal: {
		*obj = (*obj)->right;
	} break;
	}
	
}

void bst_for(struct bst *bst, register bst_blk_fun_t blk, void *arg) {
	bst_obj_for(bst->root, blk, arg);
}

static void bst_obj_for(struct bst_obj *obj, register bst_blk_fun_t blk, void *arg) {
	if (obj) {
		bst_obj_for(obj->left, blk, arg);
		blk(obj->val, arg);
		bst_obj_for(obj->right, blk, arg);
	}
}

void bst_dlc(struct bst **bst) {
	bst_obj_dlc((*bst)->root);
	mem_dlc(bst);
}

static void bst_obj_dlc(struct bst_obj *obj) {
	if (obj) {
		bst_obj_dlc(obj->left);
		bst_obj_dlc(obj->right);
		mem_dlc(&obj);
	}
}
