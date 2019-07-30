
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"data.h"
#include"normaldistribution.h"

//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
int main(void)
{
    puts("-----------------------");
    puts("| codedrome.com       |");
    puts("| Normal Distribution |");
    puts("-----------------------\n");

    int data[138];

    populatedata(data);

    prob_dist* pd = normal_distribution_create();

    normal_distribution_calculate(data, 138, pd);

    normal_distribution_print(pd);

    normal_distribution_free(pd);

    return EXIT_SUCCESS;
}
