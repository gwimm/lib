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

struct flt flt_ini(void *buf, u64 len) {
	struct flt_obj *obj = 0;
	if (sizeof(struct flt_obj) <= len) {
		obj = buf;
		*obj = (struct flt_obj) {
			.prv = 0,
			.nxt = 0,
			.len = len - sizeof(struct flt_obj),
			.use = false,
		};
	}
	return (struct flt) { .fst = obj, .lst = obj };
}

struct flt_obj *flt_get(struct flt *flt, u64 len) {
	struct flt_obj *obj = flt->fst;
	do {
		if ((!obj->use) && obj->len >= len) {
			if ((obj->len - len) > sizeof(struct flt_obj)) {
				struct flt_obj *nxt = (struct flt_obj *)((i8 *)obj) + len;
				*nxt = (struct flt_obj) {
					.prv = obj,
					.nxt = obj->nxt,
					.len = obj->len - len - sizeof(struct flt_obj),
				};
				if (flt->lst == obj) {
					flt->lst = nxt;
				}
				*obj = (struct flt_obj) {
					.nxt = obj + len,
					.len = len,
				};
			}
			return obj;
		}
	} while ((obj = obj->nxt));
	return 0;
}

void flt_del(struct flt *flt, struct flt_obj *obj) {
	obj->use = false;
	struct flt_obj *objv[] = { obj, obj->prv };
	for (u64 i = 0; i < 2 && objv[i] && objv[i]->use && objv[i]->nxt && objv[i]->nxt->use; i++) {
		obj = objv[i];
		obj->len += obj->nxt->len + sizeof(struct flt_obj);
		if (obj->nxt == flt->lst) {
			flt->lst = obj;
		}
		if ((obj->nxt = obj->nxt->nxt)) {
			obj->nxt->prv = obj;
		}
	}
}

void flt_ext(struct flt *flt, u64 len) {
	if (flt->fst) {
		struct flt_obj *obj = flt_ini(flt_obj_bin((i8 *)flt->lst + flt->lst->len), len).fst;
		if (obj) {
			obj->prv = flt->lst;
			flt->lst->nxt = obj;
		}
	}
}
