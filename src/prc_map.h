#ifndef PRC_MAP_H
#define PRC_MAP_H

#define PRC_MAP(f, ...) \
	PRC_MAP_EVAL(PRC_MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define PRC_MAP0(f, x, peek, ...) \
	f(x) PRC_MAP_NEXT(peek, PRC_MAP1)(f, peek, __VA_ARGS__)
#define PRC_MAP1(f, x, peek, ...) \
	f(x) PRC_MAP_NEXT(peek, PRC_MAP0)(f, peek, __VA_ARGS__)

#define PRC_MAP_NEXT0(test, next, ...) next PRC_MAP_OUT
#define PRC_MAP_NEXT1(test, next) PRC_MAP_NEXT0(test, next, 0)
#define PRC_MAP_NEXT(test, next)  PRC_MAP_NEXT1(PRC_MAP_GET_END test, next)

#define PRC_MAP_LIST(f, ...) \
	PRC_MAP_EVAL(PRC_MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define PRC_MAP_LIST0(f, x, peek, ...) \
	f(x) PRC_MAP_LIST_NEXT(peek, PRC_MAP_LIST1)(f, peek, __VA_ARGS__)
#define PRC_MAP_LIST1(f, x, peek, ...) \
	f(x) PRC_MAP_LIST_NEXT(peek, PRC_MAP_LIST0)(f, peek, __VA_ARGS__)

#define PRC_MAP_LIST_NEXT1(test, next) \
	PRC_MAP_NEXT0(test, PRC_MAP_COMMA next, 0)
#define PRC_MAP_LIST_NEXT(test, next) \
	PRC_MAP_LIST_NEXT1(PRC_MAP_GET_END test, next)

#define PRC_MAP_GET_END2() 0, PRC_MAP_END
#define PRC_MAP_GET_END1(...) PRC_MAP_GET_END2
#define PRC_MAP_GET_END(...) PRC_MAP_GET_END1

#define PRC_MAP_END(...)
#define PRC_MAP_OUT
#define PRC_MAP_COMMA ,

#define PRC_MAP_EVAL0(...) __VA_ARGS__
#define PRC_MAP_EVAL1(...) PRC_MAP_EVAL0(PRC_MAP_EVAL0(PRC_MAP_EVAL0(__VA_ARGS__)))
#define PRC_MAP_EVAL2(...) PRC_MAP_EVAL1(PRC_MAP_EVAL1(PRC_MAP_EVAL1(__VA_ARGS__)))
#define PRC_MAP_EVAL3(...) PRC_MAP_EVAL2(PRC_MAP_EVAL2(PRC_MAP_EVAL2(__VA_ARGS__)))
#define PRC_MAP_EVAL4(...) PRC_MAP_EVAL3(PRC_MAP_EVAL3(PRC_MAP_EVAL3(__VA_ARGS__)))
#define PRC_MAP_EVAL(...)  PRC_MAP_EVAL4(PRC_MAP_EVAL4(PRC_MAP_EVAL4(__VA_ARGS__)))

#endif // PRC_MAP_H
