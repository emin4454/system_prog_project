#ifndef RW_OPS_H
#define RW_OPS_H
#include "../libfdr/include/fields.h"
#include "fn_check.h"
struct rw_ops
{
    IS is;
    FILE *os;
    int cursor_loc;
};

extern struct rw_ops *new_rw_ops(struct fn_check *);
extern void start_parsing(struct rw_ops *);
#endif