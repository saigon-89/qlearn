#ifndef QLEARN_H
#define QLEARN_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

typedef int errno_t;

extern volatile double r = 0; /** Награда агента */

/**
 * \typedef 
 * \brief Тип, содержащий Q-таблицу и её параметры
 */
typedef struct {
    size_t m, n;
    double** arr;
    //errno_t (*clear)(qtable_t*);
} qtable_t;

/**
 * \typedef 
 * \brief Тип, содержащий параметры Q-обучения
 */
typedef struct {
    float alpha, gamma, eps;
} qparam_t;

extern volatile qparam_t qparam = { 
    .alpha = .01, 
    .gamma = .95, 
    .eps = .1 
};

/**
 * \typedef
 * \brief Тип, содержащий указатели на базовые функции обучения
 */
typedef struct {
    errno_t (*update)(qtable_t*, size_t, size_t, size_t);
    errno_t (*observe)(double* r, size_t* snext);
    size_t (*action)(qtable_t*, size_t);
    void (*feedback)(qtable_t);
} qfunc_t;

static errno_t qtable_update(qtable_t* table, size_t s, size_t snext, size_t a);
static size_t action(qtable_t* table, size_t s);

extern volatile qfunc_t qfunc = { 
    .action = action, 
    .update = qtable_update,
    .feedback = NULL, 
    .observe = NULL 
};

static size_t best_action(qtable_t* ptr, size_t s);
errno_t qlearn(qtable_t* table, size_t s0, size_t sfin, size_t epmax);
errno_t qtable_del(qtable_t* table);
qtable_t* qtable_init(size_t m, size_t n);
errno_t qtable_print(qtable_t* table);

#endif