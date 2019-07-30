
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<math.h>

// --------------------------------------------------------
// STRUCT prob_dist_item
// --------------------------------------------------------
typedef struct prob_dist_item
{
    int value;
    int frequency;
    double probability;
    double normal_probability;
    double normal_frequency;
} prob_dist_item;

// --------------------------------------------------------
// STRUCT prob_dist
// --------------------------------------------------------
typedef struct prob_dist
{
    prob_dist_item* items;
    int count;

    double total_probability;
    double total_normal_probability;
    double total_frequency;
    double total_normal_frequency;
} prob_dist;

// --------------------------------------------------------
// FUNCTION PROTOTYPES
// --------------------------------------------------------
prob_dist* normal_distribution_create();
void normal_distribution_calculate(int* data, int size, prob_dist* pd);
void normal_distribution_print(prob_dist* pd);
void normal_distribution_free(prob_dist* pd);
