#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

Test(lib, my_miniprintf)
{
    my_miniprintf("gay%c%s%d%% %", 'g', "gay", 2);
    my_miniprintf("%y");
}

Test(lib, power)
{
    my_power(2, 0);
    my_power(2, -1);
    my_power(2, 2);
    my_power_float(2, 0);
    my_power_float(2, -1);
    my_power_float(2, 2);
}

Test(lib, puterror)
{
    my_puterror("gay");
}

Test(lib, putnbr)
{
    my_putnbr(-2);
    my_putnbr(30);
    my_putnbr_base(20, "01");
}

Test(lib, getnbr)
{
    my_getnbr("669he");
    my_getnbr("669.e");
}

Test(lib, strcmp)
{
    my_strcmp("gay", "gay");
    my_strcmp("ga", "gay1");
    my_strcmp("gay1", "ga");
    my_strcmp("gay", "gey");
}

Test(lib, stralloc)
{
    char *gay = NULL;
    gay = my_stradd(&gay, 'c');
    my_strdup(NULL);
    gay = my_strdup("gay");
    gay = my_stradd(&gay, 'c');
    my_stradd(NULL, 'c');
    my_stradd(&gay, 0);
}

Test(lib, strcpy)
{
    char gay[] = "hgaayg";

    my_strcpy(gay, "pd");
    my_strcpy(gay, "biobepdpepj");
}


Test(lib, strcat)
{
    char gay[] = "hgaayg\0\0\0";

    my_strcat(gay, "gay");
}
