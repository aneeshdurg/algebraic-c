#include <string.h>

%{
for i in range(100):
  if i == 0:
    #define FOR_EACH0(...)
  else:
    #define FOR_EACH%{i}%(t, a, ...) t(a) FOR_EACH%{i-1}%(t, __VA_ARGS__)

for i in range(2, 100):
  if i == 2:
    #define FOR_EACH_2_0(...)
    #define P1_FOR_EACH_2_0(...)
  elif i == 3:
    #define FOR_EACH_2_3(t, a, b, ...) t(a, b)
    #define P1_FOR_EACH_2_3(t, a, b, c, ...) t(a, b, c) 
  else:
    #define FOR_EACH_2_%{i}%(t, a, b, ...) t(a, b) FOR_EACH_2_%{i-1}%(t, __VA_ARGS__)
    #define P1_FOR_EACH_2_%{i}%(t, a, b, c, ...) t(a, b, c) P1_FOR_EACH_2_%{i-1}%(t, a, __VA_ARGS__)

for i in range(100):
  if i == 0:
    #define P1_FOR_EACH0(...)
  else:
    #define P1_FOR_EACH%{i}%(t, a, b, ...) t(a, b) P1_FOR_EACH%{i-1}%(t, a, __VA_ARGS__)

#define NUM_ARGS_H1(x, %{','.join(['x'+str(100-i-1) for i in range(100)])}%, ...) x0 
#define NUM_ARGS(...) NUM_ARGS_H1(dummy, ##__VA_ARGS__, %{','.join([str(100-i-1) for i in range(100)])}%)
}%

#define APPLY_ALL_H3(t, n, ...) FOR_EACH##n(t, __VA_ARGS__)
#define APPLY_ALL_H2(t, n, ...) APPLY_ALL_H3(t, n, __VA_ARGS__)
#define APPLY_ALL(t, ...) APPLY_ALL_H2(t, NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

#define APPLY_ALL_2_H3(t, n, ...) FOR_EACH_2_##n(t, __VA_ARGS__)
#define APPLY_ALL_2_H2(t, n, ...) APPLY_ALL_2_H3(t, n, __VA_ARGS__)
#define APPLY_ALL_2(t, ...) APPLY_ALL_2_H2(t, NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

#define P1_APPLY_ALL_H3(t, a, n, ...) P1_FOR_EACH##n(t, a, __VA_ARGS__)
#define P1_APPLY_ALL_H2(t, a, n, ...) P1_APPLY_ALL_H3(t, a, n, __VA_ARGS__)
#define P1_APPLY_ALL(t, a, ...) P1_APPLY_ALL_H2(t, a, NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

#define P1_APPLY_ALL_2_H3(t, a, n, ...) P1_FOR_EACH_2_##n(t, a, __VA_ARGS__)
#define P1_APPLY_ALL_2_H2(t, a, n, ...) P1_APPLY_ALL_2_H3(t, a, n, __VA_ARGS__)
#define P1_APPLY_ALL_2(t, a, ...) P1_APPLY_ALL_2_H2(t, a, NUM_ARGS(__VA_ARGS__), __VA_ARGS__)

#define newAlgebraic(type, ...)                                                \
  typedef struct type##T {                                                     \
    unsigned int is_ : 1;                                                      \
    __VA_ARGS__                                                                \
  } type##T;

#define NewTypeD(name, ...)                                                    \
  unsigned int is##name : 1;                                                   \
  struct name##_data {__VA_ARGS__};

#define NewType(name)                                                          \
  NewTypeD(name)

#define DeclareData(type, ...)                                                 \
  union type##Data{                                                            \
    __VA_ARGS__                                                                \
  } data;

#define DeclareData_(x)                                                        \
  struct x##_data x; 
#define DeclareData__(x, y)                                                    \
  DeclareData_(x)

#define DeclareGetters(type, x)                                                \
  static inline struct x##_data get##x(type##T e){ return e.data.x; }
#define DeclareGetters_(type, x, y)                                            \
  DeclareGetters(type, x)

#define NewAlgebraic(type, ...)                                                \
  newAlgebraic(type, APPLY_ALL(NewType, __VA_ARGS__)                           \
      DeclareData(type, APPLY_ALL(DeclareData_, __VA_ARGS__)));                \
      P1_APPLY_ALL(DeclareGetters, type, __VA_ARGS__); 

#define NewAlgebraic2(type, ...)                                               \
  newAlgebraic(type, APPLY_ALL_2(NewTypeD, __VA_ARGS__)                        \
    DeclareData(type, APPLY_ALL_2(DeclareData__, __VA_ARGS__)));               \
  P1_APPLY_ALL_2(DeclareGetters_, type, __VA_ARGS__); 

#define __PRINT_GEN(type, val)                                                 \
  if (val.is##type)                                                            \
    printf("%s ", #type);

#define setType(type, name)                                                    \
  memset(&name, 1, sizeof(name));                                              \
  name.is##type = 1;

#define $(typea, a, ...)                                                       \
  if ('_' == #typea[0]) {                                                      \
    __VA_ARGS__;                                                               \
  } else {                                                                     \
    if (a.is##typea) {                                                         \
      __VA_ARGS__;                                                             \
    }                                                                          \
  }

#define casefn(typea, a, typeb, b, ...) $(typea, a, $(typeb, b, __VA_ARGS__));
