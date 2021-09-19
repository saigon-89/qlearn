#include "qlearn.h"

/**
 * \fn 
 * \brief Процедура обучения
 * \param[in] table Q-таблица
 * \param[in] s номер состояния
 * \return Номер лучшего действия
 */
static size_t action(qtable_t* table, size_t s)
{
    srand(time(NULL));
    if(((double)rand() / (double)(RAND_MAX)) < qparam.eps)
        return rand() % table->n;
    else
    return best_action(table, s);
}

/**
 * \fn 
 * \brief Процедура обучения
 * \param[in] table начальная Q-таблица
 * \param[in] s0 начальное состояние
 * \param[in] sfin конечное состояние
 * \param[in] epmax число обучающих эпизодов
 */
errno_t qlearn(qtable_t* table, size_t s0, size_t sfin, size_t epmax)
{
    size_t s = s0, snext, a;
    for(size_t ep = 0; ep < epmax; ep++)
    {
        printf("Current episode: %d", ep);
        while(s != sfin)
        {   
            a = qfunc.action(table, s);
            qfunc.observe(&r, &snext);
            qfunc.update(table, s, snext, a);
            s = snext;
        }
    }
    return 0;
}

/**
 * \fn 
 * \brief Функция выбора лучшего действия
 * \param[in] ptr Q-таблица
 * \param[in] s номер состояния
 * \return Номер лучшего действия
 */
static size_t best_action(qtable_t* ptr, size_t s)
{
    double* row = ptr->arr[s];
    size_t index = 0;
    double val = row[index]; 
    for(size_t i = 1; i < s; i++)
        if(val < row[i]) 
        {
            val = row[i];
            index = i;
        }
    return index;
}

/**
 * \fn 
 * \brief Функция инициализации Q-таблицы
 * \param[in] m число строк таблицы
 * \param[in] n число столбцов таблицы
 * \return Указатель на Q-таблицу
 */
qtable_t* qtable_init(size_t m, size_t n)
{
    if(m < 1 || n < 1) 
    {
        printf("Board error!\n");
        return NULL;
    }
    qtable_t* ptr;
    ptr->m = m;
    ptr->n = n;
    //ptr->clear = qtable_del;
    ptr->arr = (double**)calloc(m, sizeof(double*));
    for(size_t i = 0; i < n; i++)
        ptr->arr[i] = (double*)calloc(n, sizeof(double));
    return ptr;
}

/**
 * \fn 
 * \brief Функция удаления Q-таблицы
 * \param[in] table Q-таблица
 * \return Код ошибки
 */
errno_t qtable_del(qtable_t* table)
{
    for(size_t i = 0; i < table->n; i++)
        free(table->arr[i]);
    free(table);
    return 0;
}

/**
 * \fn 
 * \brief Функция обновления Q-таблицы
 * \param[in] table Q-таблица
 * \param[in] s номер состояния
 * \param[in] a номер действия
 * \return Код ошибки
 */
static errno_t qtable_update(qtable_t* table, size_t s, size_t snext, size_t a)
{
    table->arr[s][a] += qparam.alpha*(r + qparam.gamma*best_action(table, snext) - table->arr[s][a]);
    return 0;
}

/**
 * \fn 
 * \brief Функция печати Q-таблицы
 * \param[in] table Q-таблица
 * \return Код ошибки
 */
errno_t qtable_print(qtable_t* table)
{
    for(size_t i = 0; i < table->m; i++)
    {
        for(size_t j = 0; j < table->n; j++)
            printf("%lf\t", table->arr[i][j]);
        printf('\n');
    }
    return 0;
}

int main()
{
    return 0;
}