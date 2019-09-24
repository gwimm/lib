#ifndef   PRC_H
#define   PRC_H

#define PRC_NUM(a,b,c,d,e,f,g,h,i,j,k,...) k
#define PRC_NUM_ARG(...) PRC_NUM(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define PRC_CAT(a, b) a ## b

#endif // PRC_H
