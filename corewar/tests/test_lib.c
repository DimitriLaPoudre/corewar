#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

Test(lib, my_miniprintf)
{
    char *tab[] = {"test1", "test2", NULL};

    my_miniprintf("gay%c%s%d%f%t%% %", 'g', "gay", 2, 4.7, tab);
    my_miniprintf("%y\n");
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
    my_putfloat(3.63);
    my_putfloat(-56.82);
}

Test(lib, getnbr)
{
    my_getnbr("669he");
    my_getnbr("669.e");
    my_getnbr("-426");
    my_getnbr("+12");
}

Test(lib, strcmp)
{
    my_strcmp("gay", "gay");
    my_strcmp("ga", "gay1");
    my_strcmp("gay1", "ga");
    my_strcmp("gay", "gey");
    my_strncmp("gay", "gayn", 2);
    my_strncmp("gay", "gayn", 4);
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
}

Test(lib, strcat)
{
    char gay[] = "hgaayg\0\0\0";

    my_strcat(gay, "gay");
    gay[1] = '\0';
    my_strcat_na(gay, "oue");
}

Test(lib, nbr_to_str)
{
    my_nbr_to_str(-0);
    my_nbr_to_str(3707);
}

Test(lib, str_is_num)
{
    my_str_isnum("539");
    my_str_isnum("5e");
    my_str_isnum("5 ");
    my_str_isnum(NULL);
}

Test(lib, str_to_word_array)
{
    my_str_to_word_array(" test    test  test ", " ");
    my_str_to_word_array("hello     world", " ");
    my_str_to_word_array("     ", " ");
}
