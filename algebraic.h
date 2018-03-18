#include <string.h>
#define newAlgebraic(type, body)                                               \
  typedef struct type##T {                                                     \
    unsigned int is_ : 1;                                                      \
    body                                                                       \
  } type##T;

#define NewType(name) unsigned int is##name : 1;
#define __PRINT_GEN(type, val)                                                 \
  if (val.is##type)                                                            \
    printf("%s ", #type);

#define setType(type, name) memset(&name, 0, sizeof(name));name.is##type = 1;

#define $(typea, a, expr)                                                      \
  if ('_' == #typea[0]) {                                                      \
    expr;                                                                      \
  } else {                                                                     \
    if (a.is##typea) {                                                         \
      expr;                                                                    \
    }                                                                          \
  }

#define casefn(typea, a, typeb, b, expr) $(typea, a, $(typeb, b, expr));
