#ifndef   FLT_H
#define   FLT_H
#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus

struct flt_obj {
	struct flt_obj *prv, *nxt;
	u64 len;
	bool use;
};

struct flt {
	struct flt_obj *fst, *lst;
};

#define flt_obj_bin(x) ((void *)(((i8 *)(x)) + sizeof(struct flt_obj)))
#define flt_bin_obj(x) ((struct flt_obj *)(((i8 *)(x)) - sizeof(struct flt_obj)))
#define CMP(l, r) ((l) == (r) ? cmp_equal : ((l) < (r) ? cmp_greater : cmp_lesser))

struct flt flt_ini(void *buf, u64 len);
struct flt_obj *flt_get(struct flt *flt, u64 len);
void flt_del(struct flt *flt, struct flt_obj *obj);
void flt_ext(struct flt *flt, u64 len);

#ifdef    __cplusplus
}
#endif // __cplusplus
#endif // FLT_H
