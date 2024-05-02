#include "fn_check.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
int check_fns(char *, char *);
void err_argn();
struct fn_check *new_fn_check_args(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Sadece 2 arguman giriniz");
        return NULL;
    }
    if (check_fns(argv[1], argv[2]) == 0)
    {
        return NULL;
    }
    else
    {
        struct fn_check *this = (struct fn_check *)malloc(sizeof(struct fn_check));
        this->input_fn = argv[1];
        this->out_fn = argv[2];
        return this;
    }
}

struct fn_check *new_fn_check_in(char *input)
{
    char *found;
    char *filenames[2];
    int i = 0;
    while ((found = strsep(&input, " ")) != NULL)
    {
        if (i == 2)
        {
            err_argn();
            return NULL;
        }
        filenames[i] = found;
        i++;
    }
    if (i != 2)
    {
        err_argn();
        return NULL;
    }
    else if (check_fns(filenames[0], filenames[1]) == 0)
    {
        return NULL;
    }
    else
    {
        struct fn_check *this = (struct fn_check *)malloc(sizeof(struct fn_check));
        this->input_fn = filenames[0];
        this->out_fn = filenames[1];
        return this;
    }
}

int check_fns(char *in_fn, char *out_fn)
{
    char *fl_format;
    fl_format = strrchr(in_fn, '.');
    if (fl_format == NULL || strncmp(fl_format, ".dat", 4) != 0)
    {
        fprintf(stderr, "Ilk argumanin dosya tipi dogru degil (sadece .dat dosyalari uyumludur) \n");
        return 0;
    }
    fl_format = strrchr(out_fn, '.');
    if (fl_format == NULL || strncmp(fl_format, ".dat", 4) != 0)
    {
        fprintf(stderr, "Ikinci argumanin dosya tipi dogru degil (sadece .dat dosyalari uyumludur) \n");
        return 0;
    }
    return 1;
}

void err_argn()
{
    fprintf(stderr, "Sadece 2 arguman giriniz");
}