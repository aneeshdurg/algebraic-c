#include <string.h>
#define newAlgebraic(type, ...)                                                \
  typedef struct type##T {                                                     \
    unsigned int is_ : 1;                                                      \
    __VA_ARGS__                                                                \
  } type##T;

#define NewType(name) unsigned int is##name : 1;
#define __PRINT_GEN(type, val)                                                 \
  if (val.is##type)                                                            \
    printf("%s ", #type);

#define setType(type, name) memset(&name, 0, sizeof(name));name.is##type = 1;

#define $(typea, a, ...)                                                       \
  if ('_' == #typea[0]) {                                                      \
    __VA_ARGS__;                                                               \
  } else {                                                                     \
    if (a.is##typea) {                                                         \
      __VA_ARGS__;                                                             \
    }                                                                          \
  }

#define casefn(typea, a, typeb, b, ...) $(typea, a, $(typeb, b, __VA_ARGS__));
