#include "rw_ops.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

struct rw_ops *new_rw_ops(struct fn_check *fn)
{
    IS is = new_inputstruct(fn->input_fn);
    FILE *os_test = fopen(fn->out_fn, "r");
    if (is == NULL)
    {
        fprintf(stderr, "Giris dosyasi bulunamadi lutfen dosya adini dogru sekilde tekrar giriniz \n");
        return NULL;
    }
    if (os_test == NULL)
    {
        fprintf(stderr, "Cikis dosyasi bulunamadi lutfen dosya adini dogru sekilde tekrar giriniz \n");
        return NULL;
    }
    fclose(os_test);
    FILE *os = fopen(fn->out_fn, "w");
    struct rw_ops *this = (struct rw_ops *)malloc(sizeof(struct rw_ops));
    this->is = is;
    this->os = os;
    this->cursor_loc = 0;
    return this;
}
