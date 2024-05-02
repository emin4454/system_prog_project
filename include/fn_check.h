#ifndef FN_CHECK_H
#define FN_CHECK_H

struct fn_check
{
    char *input_fn;
    char *out_fn;
};

extern struct fn_check *new_fn_check_args(int, char **);
extern struct fn_check *new_fn_check_in(char *);
#endif