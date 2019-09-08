struct flt_obj {
	struct flt_obj *prv, *nxt;
	wrd_t len;
	bool use;
};

struct flt {
	struct flt_obj *fst, *lst;
};

#define flt_obj_bin(x) ((void *)(((char *)(x)) + sizeof(struct flt_obj)))
#define flt_bin_obj(x) ((struct flt_obj *)(((char *)(x)) - sizeof(struct flt_obj)))
#define CMP(l, r) ((l) == (r) ? cmp_eql : ((l) < (r) ? cmp_grt : cmp_lss))

struct flt flt_ini(void *buf, wrd_t len) {
	struct flt_obj *obj = NULL;
	if (sizeof(struct flt_obj) <= len) {
		obj = buf;
		*obj = (struct flt_obj) {
			.prv = NULL,
			.nxt = NULL,
			.len = len - sizeof(struct flt_obj),
			.use = false,
		};
	}
	return (struct flt) { .fst = obj, .lst = obj };
}

struct flt_obj *flt_get(struct flt *flt, wrd_t len) {
	struct flt_obj *obj = flt->fst;
	do {
		if ((!obj->use) && obj->len >= len) {
			if ((obj->len - len) > sizeof(struct flt_obj)) {
				struct flt_obj *nxt = (struct flt_obj *)((char *)obj) + len;
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
	return NULL;
}

void flt_del(struct flt *flt, struct flt_obj *obj) {
	obj->use = false;
	struct flt_obj *objv[] = { obj, obj->prv };
	for (wrd_t i = 0; i < 2 && objv[i] && objv[i]->use && objv[i]->nxt && objv[i]->nxt->use; i++) {
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

void flt_ext(struct flt *flt, wrd_t len) {
	struct flt_obj *obj = flt_ini(flt_obj_bin((char *)flt->lst + flt->lst->len), len).fst;
	if (obj) {
		obj->prv = flt->lst;
		flt->lst->nxt = obj;
	}
}
