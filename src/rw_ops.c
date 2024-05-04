#include "rw_ops.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
void ops_to_file(struct rw_ops *, char type);
int print_xtimesy_toloc(int, char *, struct rw_ops *);
int remove_xtimesy_toloc(int, char *, struct rw_ops *);
int addc_tostr(char *, char, int);
int delc_fromstr(char *, char, int);
struct rw_ops *new_rw_ops(struct fn_check *fn)
{
    IS is = new_inputstruct(fn->input_fn);
    if (is == NULL)
    {
        fprintf(stderr, "Giris dosyasi bulunamadi lutfen dosya adini dogru sekilde tekrar giriniz \n");
        return NULL;
    }
    FILE *os = fopen(fn->out_fn, "w");
    struct rw_ops *this = (struct rw_ops *)malloc(sizeof(struct rw_ops));
    this->is = is;
    this->os = os;
    this->buffer = malloc(sizeof(char) * 1000);
    return this;
}

void start_parsing(struct rw_ops *rw)
{
    while (get_line(rw->is) >= 0)
    {
        if (rw->is->NF < 1)
        {
            fprintf(stderr, "Eksik komut girildi satir gorulmezden gelinecek \n");
            continue;
        }
        if (strcmp(rw->is->fields[0], "yaz:") == 0)
            ops_to_file(rw, 'p');
        else if (strcmp(rw->is->fields[0], "sil:") == 0)
            ops_to_file(rw, 'r');
        else if (strcmp(rw->is->fields[0], "sonagit:") == 0)
            rw->cursor_loc = strlen(rw->buffer);
        else if (strcmp(rw->is->fields[0], "dur:") == 0)
            break;
        else
        {
            fprintf(stderr, "Beklenmedik komut girildi satir gorulmezden gelinecek \n");
            continue;
        }
    }
    fprintf(rw->os, "%s", rw->buffer);
}

void ops_to_file(struct rw_ops *rw, char type)
{
    if (rw->is->NF % 2 == 0 || rw->is->NF <= 1)
    {
        fprintf(stderr, "Yaz komutunda eksik veri girildi satir gorulmezden gelinecek \n");
        return;
    }
    for (int i = 1; i < rw->is->NF; i = i + 2)
    {
        int num = atoi(rw->is->fields[i]);
        if (num == 0)
        {
            fprintf(stderr, "Adet sayisina 0 veya harf girilemez satir gorunmezden geliniyor \n");
            return;
        }
        int result;
        if (type == 'p')
        {
            result = print_xtimesy_toloc(num, rw->is->fields[i + 1], rw);
        }
        else if (type == 'r')
            result = remove_xtimesy_toloc(num, rw->is->fields[i + 1], rw);
        if (result == 0)
        {
            break;
        }
    }
}

int print_xtimesy_toloc(int x, char *y, struct rw_ops *rw)
{
    if (strlen(y) == 2)
    {
        if ((int)y[0] == 92 && y[1] == 'n')
        {
            y[0] = '\n';
            y[1] = '\0';
        }
        else if ((int)y[0] == 92 && y[1] == 'b')
        {
            y[0] = ' ';
            y[1] = '\0';
        }
    }
    if (strlen(y) >= 2)
    {
        fprintf(stderr, "Gecersiz komut , komut gormezden geliniyor, Satirin devami okunmayacak \n");
        return 0;
    }
    for (int i = 0; i < x; i++)
    {
        rw->cursor_loc = addc_tostr(rw->buffer, y[0], rw->cursor_loc);
    }
    return 1;
}
int addc_tostr(char *buffer, char c, int loc)
{
    if (strlen(buffer) == loc)
    {
        buffer[loc] = c;
        buffer[loc + 1] = '\0';
        return loc + 1;
    }
    else
    {
        for (int i = strlen(buffer); i >= loc; i--)
        {
            buffer[i + 1] = buffer[i];
        }
        buffer[loc] = c;
        return loc + 1;
    }
}
int remove_xtimesy_toloc(int x, char *y, struct rw_ops *rw)
{
    if (strlen(y) == 2)
    {
        if ((int)y[0] == 92 && y[1] == 'n')
        {
            y[0] = '\n';
            y[1] = '\0';
        }
        else if ((int)y[0] == 92 && y[1] == 'b')
        {
            y[0] = ' ';
            y[1] = '\0';
        }
    }
    if (strlen(y) >= 2)
    {
        fprintf(stderr, "Gecersiz komut , komut gormezden geliniyor, Satirin devami okunmayacak \n");
        return 0;
    }
    while (x > 0)
    {
        if (rw->cursor_loc == 0)
        {
            return 0; // if cursor loc is 0 you cant delete another char while executing same line
        }
        rw->cursor_loc--;
        x = x - delc_fromstr(rw->buffer, y[0], rw->cursor_loc);
    }
    return 1;
}

int delc_fromstr(char *buffer, char y, int loc)
{
    if (buffer[loc] != y)
    {
        return 0;
    }
    else
    {
        int bufferlen = strlen(buffer);
        for (int i = loc; i < bufferlen; i++)
        {
            buffer[i] = buffer[i + 1];
        }
        return 1;
    }
}

void delete_rw_ops(struct rw_ops *rw)
{
    free(rw->buffer);
    fclose(rw->os);
    jettison_inputstruct(rw->is);
    free(rw);
}
