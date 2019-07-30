
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include"normaldistribution.h"

#ifndef M_PI
#define M_PI 3.14159
#endif

#ifndef M_E
#define M_E 2.71828
#endif

// --------------------------------------------------------
// FUNCTION PROTOTYPES
// --------------------------------------------------------
static int indexof(int value, prob_dist* pd);
static int compare_prob_dist_item(const void* a, const void* b);

// --------------------------------------------------------
// FUNCTION normal_distribution_create
// --------------------------------------------------------
prob_dist* normal_distribution_create()
{
    prob_dist* pd = malloc(sizeof(prob_dist));

    pd->count = 0;
    pd->items = NULL;

    pd->total_probability = 0;
    pd->total_normal_probability = 0;
    pd->total_normal_frequency = 0;

    return pd;
}

// --------------------------------------------------------
// FUNCTION normal_distribution_calculate
// --------------------------------------------------------
void normal_distribution_calculate(int* data, int size, prob_dist* pd)
{
    int index;
    double total = 0;
    double sumofsquares = 0;
    double mean;
    double variance;
    double stddev;

    pd->total_frequency = size;

    // CALCULATE FREQUENCIES
    // iterate data
    // add new values to pd
    // or
    // increment frequency of existing values
    for(int i = 0; i < size; i++)
    {
        index = indexof(data[i], pd);

        // already exists
        if(index >= 0)
        {
            pd->items[index].frequency++;
        }
        // does not exist
        else
        {
            pd->count++;

            // first item
            if(pd->items == NULL)
            {
                pd->items = malloc(sizeof(prob_dist_item));
            }
            else
            {
                pd->items = realloc(pd->items, sizeof(prob_dist_item) * pd->count);
            }

            pd->items[pd->count - 1].value = data[i];
            pd->items[pd->count - 1].frequency = 1;
        }

        total += data[i];
        sumofsquares += pow(data[i], 2);
    }

    // SORT ITEMS
    qsort(pd->items, pd->count, sizeof(prob_dist_item), compare_prob_dist_item);

    // CALCULATE MEAN, VARIANCE AND STANDARD DEVIATION
    mean = total / size;
    variance = (sumofsquares - ((pow(total, 2)) / size)) / size;
    stddev = sqrt(variance);

    // CALCULATE PROBABILITIES OF EACH UNIQUE VALUE
    for(int c = 0; c < pd->count; c++)
    {
        pd->items[c].probability = (double)pd->items[c].frequency / (double)size;

	    pd->items[c].normal_probability = ((1.0 / (stddev * sqrt(2.0 * M_PI))) * (pow(M_E, -1.0 * ((pow((pd->items[c].value - mean), 2.0)) / ( variance * 2.0)))));

	    pd->items[c].normal_frequency = pd->items[c].normal_probability * size;

        pd->total_probability += pd->items[c].probability;

        pd->total_normal_probability += pd->items[c].normal_probability;

        pd->total_normal_frequency += pd->items[c].normal_frequency;
    }
}

// --------------------------------------------------------
// FUNCTION normal_distribution_print
// --------------------------------------------------------
void normal_distribution_print(prob_dist* pd)
{
    printf("Value | Probability | Normal Prob | Freq | Normal Freq\n------------------------------------------------------\n");

    for(int i = 0; i < pd->count; i++)
    {
        printf("%5d |%12.6lf |%12.4lf |%5d |%12.4lf\n", pd->items[i].value, pd->items[i].probability, pd->items[i].normal_probability, pd->items[i].frequency, pd->items[i].normal_frequency);
    }

    printf("------------------------------------------------------\n");

    printf("      |%12.4lf |%12.6lf |%5.0lf |%12.4lf\n", pd->total_probability, pd->total_normal_probability, pd->total_frequency, pd->total_normal_frequency);

    printf("------------------------------------------------------\n");
}

// --------------------------------------------------------
// FUNCTION normal_distribution_free
// --------------------------------------------------------
void normal_distribution_free(prob_dist* pd)
{
    free(pd->items);

    free(pd);
}

// --------------------------------------------------------
// FUNCTION indexof
// --------------------------------------------------------
static int indexof(int value, prob_dist* pd)
{
    for(int i = 0; i < pd->count; i++)
    {
        if(pd->items[i].value == value)
        {
            return i;
        }
    }

    return -1;
}

//--------------------------------------------------------
// STATIC FUNCTION compare_prob_dist_item
//--------------------------------------------------------
static int compare_prob_dist_item(const void* a, const void* b)
{
    if(((prob_dist_item*)a)->value < ((prob_dist_item*)b)->value)
        return -1;
    else if(((prob_dist_item*)a)->value > ((prob_dist_item*)b)->value)
        return 1;
    else
        return 0;
}
