#ifndef CROSSOVER_H
#define CROSSOVER_H

void singlePoint_crsvr(int c_lgth, int *ch, const int *p1, const int *p2, int cp);

void twoPoint_crsvr(int c_lgth, int *ch, const int *p1, const int *p2, int cp1, int cp2);

void uniform_crsvr(int c_lgth, int *ch, const int *p1, const int *p2, const int *cp);

void accentuated_crsvr(int c_lgth, int *ch, int *cp, const int *p1, const int *p2, const int *cp1, const int *cp2);

#endif