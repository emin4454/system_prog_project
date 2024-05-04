#include "../libfdr/include/fields.h"
#include "../include/fn_check.h"
#include "../include/rw_ops.h"

void print_ft_err();
int main(int argc, char **argv)
{

    struct fn_check *fn = new_fn_check_args(argc, argv);
    struct rw_ops *rw;
    int fn_success = 0; // file name success

    if (fn == NULL)
    {
        fn_success = 0;
        print_ft_err();
    }
    else
    {
        rw = new_rw_ops(fn);
        if (rw == NULL)
        {
            fn_success = 0;
            print_ft_err();
        }
        else
        {
            fn_success = 1;
        }
    }
    while (1)
    {
        if (fn_success == 0)
        {
            char in[100];
            fgets(in, sizeof(in), stdin);
            fn = new_fn_check_in(in);
            if (fn == NULL)
            {
                print_ft_err();
                continue;
            }
            else
            {
                rw = new_rw_ops(fn);
                if (rw == NULL)
                {
                    fn_success = 0;
                    print_ft_err();
                }
                else
                {
                    fn_success = 1;
                }
            }
        }
        else
        {
            start_parsing(rw);
            break;
        }
    }
    delete_fn_check(fn);
    delete_rw_ops(rw);
}

void print_ft_err()
{
    printf("Arada bosluk olacak sekilde sirasiyla 'dosya1.dat dosya2.dat' giriniz \n");
}