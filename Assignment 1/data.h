#ifndef DATA_H
#define DATA_H

#define CENSUS_YEAR 0
#define BLOCK_ID 1
#define PROPERTY_ID 2
#define BASE_PROPERTY_ID 3
#define SMALL_AREA 4
#define TRADING_NAME 5
#define INDUSTRY_CODE 6
#define INDUSTRY_DESCRIPTION 7
#define X_COORD 8
#define Y_COORD 9
#define LOCATION 10

#define NUMCOLUMS 11
#define ONELINE 512
#define COLUMNDATA 128

#include <stdio.h>


struct data{
	char *census_Year;
	char *block_ID;
	char *property_ID;
	char *base_property_ID;
	char *small_area;
	char *trading_name;                  
	char *industry_code;
	char *industry_description;
	char *x_coord;
	char *y_coord;
	char *location;
};

struct business{
	struct data * dataptr;
	struct business *next;
};


struct list *read_in(FILE *fp, struct list *list);
int count_quotes(char *index);
struct list *insert_data(struct list *list, char token[NUMCOLUMS][COLUMNDATA + 1]);
void output(FILE *outfile, struct list *list, char *key);
void free_data(struct business *business);

#endif