#include "../libfdr/include/fields.h"
#include "../include/fn_check.h"

void print_ft_err();
int main(int argc, char **argv)
{

    struct fn_check *file_names = new_fn_check_args(argc, argv);
    int success = 0;
    if (file_names == NULL)
    {
        print_ft_err();
    }
    else
        success = 1;

    while (1)
    {
        if (success == 0)
        {
            char in[100];
            fgets(in, sizeof(in), stdin);
            file_names = new_fn_check_in(in);
            if (file_names == NULL)
            {
                print_ft_err();
                continue;
            }
            else
            {
                success = 1;
            }
        }
        printf("aaaa");
    }

    printf("\n %s %s", file_names->input_fn, file_names->out_fn);
}

void print_ft_err()
{
    printf("arada bosluk olacak sekilde sirasiyla 'dosya1.dat dosya2.dat' giriniz \n");
}