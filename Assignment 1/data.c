#include "data.h"
#include "list.h"
#include <stdlib.h>
#include <assert.h>

#include <stdio.h>
#include <string.h>


//Reads in the input file and inserts data from it into the list
struct list *read_in(FILE *fp, struct list *list){
    size_t size = COLUMNDATA + 1;
    int i;
    int num_quote;
    int continuation = 1, quoted = 0;
    char *lineptr;
    lineptr = malloc(sizeof(*lineptr) * (COLUMNDATA + 1));
    assert(lineptr);
    
    char *index = lineptr;
    
    int data_index = 0;
    int char_index = 0;
    char token[NUMCOLUMS][COLUMNDATA + 1];
    
    
    //read till EOF, getting each data.
   while (getdelim(&lineptr, &size, ',', fp) != -1) {
   	   index = lineptr;
   	   while(*index){
   	   	   //If the character is a quote
		   if(*index == '"'){
		   	   //if its the beginning of a new data that is quoted
			   if(!quoted){
			   	   quoted = 1;
				   index++;
			  }
			   num_quote = count_quotes(index); 
			   index += num_quote;
			   
			   //If there is odd number of quotes, end of data
			   if (num_quote % 2 == 1){
			   	   index++;
			   	   continuation = 0;
			   }
			   //Add intermediate quotes
			   for(i = 0; i < (num_quote/2) ; i++){
				   token[data_index][char_index] = '"';
				   char_index ++;
			   }
		   }
		   //if data is not quoted and a comma is read in
		   else if(*index == ',' && !quoted){ 
		   	   continuation = 0;
		   	   index ++;
		   }
		   else{
		   		token[data_index][char_index] = *index;
		   		char_index++;
		   		index++;
			   }
		   //insert the data
		   if(!continuation){
		   	   token[data_index][char_index] = '\0';
		   	   //if all the data fields for the business are filled in
		   	   if(data_index == NUMCOLUMS-1){
		   	   	   list = insert_node(list);
		   	   	   list = insert_data(list, token);  
		   	   	   data_index = 0;
		   	   }
		   	   //move to next data field
		   	   else{
		   	   	   data_index ++;
		   	   }
		   	   char_index = 0;	
		   	   quoted = 0;
		   	   continuation = 1;
		   } 	
	   }
   }
   
   free(lineptr);
   return list;
}

//count the number of quotes read in consecutively
int count_quotes(char *index){
	int num_quote = 0;
	while(*index == '"'){
		num_quote +=1;
		index++;
	}
	return num_quote;
}

//insert the data read in into the node of the linked list
struct list *insert_data(struct list *list, char token[NUMCOLUMS][COLUMNDATA + 1]){
   struct data * new_data;
	new_data = malloc (sizeof(*new_data) * NUMCOLUMS);
    assert(new_data);
   
    new_data -> census_Year = strdup(token[CENSUS_YEAR]);
	new_data -> block_ID = strdup(token[BLOCK_ID]);
	new_data -> property_ID = strdup(token[PROPERTY_ID]);
	new_data -> base_property_ID = strdup(token[BASE_PROPERTY_ID]);
	new_data -> small_area = strdup(token[SMALL_AREA]);
	new_data -> trading_name = strdup(token[TRADING_NAME]);
	new_data -> industry_code = strdup(token[INDUSTRY_CODE]);
	new_data -> industry_description = strdup(token[INDUSTRY_DESCRIPTION]);
	new_data -> x_coord = strdup(token[X_COORD]);
	new_data -> y_coord = strdup(token[Y_COORD]);
	new_data -> location = strdup(token[LOCATION]);
	
	list -> foot -> dataptr = new_data;
	
	return list;	
}
               
//output the results from the key read in onto the output file
void output(FILE *outfile, struct list *list, char *key){
	int key_found = 0;
	struct business * ptr = list -> head;
	while(ptr){
		//if key entered is found
		if(!strcmp(ptr -> dataptr -> trading_name, key)){
			key_found = 1;
			fprintf(outfile, "%s -->", key);
			fprintf(outfile, " Census year: %s || ", ptr -> dataptr -> census_Year);
			fprintf(outfile, "Block ID: %s || ", ptr -> dataptr -> block_ID);
			fprintf(outfile, "Property ID: %s || ", ptr -> dataptr -> property_ID);
			fprintf(outfile, "Base property ID: %s || ", ptr -> dataptr -> base_property_ID);
			fprintf(outfile, "CLUE small area: %s || ", ptr -> dataptr -> small_area);
			fprintf(outfile, "Industry (ANZSIC4) code: %s || ", ptr -> dataptr -> industry_code);
			fprintf(outfile, "Industry (ANZSIC4) description: %s || ", ptr -> dataptr -> industry_description);
			fprintf(outfile, "x coordinate: %s || ", ptr -> dataptr -> x_coord);
			fprintf(outfile, "y coordinate: %s || ", ptr -> dataptr -> y_coord);     
			fprintf(outfile, "Location: %s || ", ptr -> dataptr -> location);
			fprintf(outfile, "\n");
			
		}                        
		ptr = ptr->next;                       
	}
	//if key is not found
	if(!key_found){
		fprintf(outfile, "%s --> NOTFOUND", key);
	}
}

//free the data stored in the node of the linked list
void free_data(struct business *business){
	free(business -> dataptr -> census_Year);
	free(business -> dataptr -> block_ID);
	free(business -> dataptr -> property_ID);
	free(business -> dataptr -> base_property_ID);
	free(business -> dataptr -> small_area);
	free(business -> dataptr -> trading_name);
	free(business -> dataptr -> industry_code);
	free(business -> dataptr -> industry_description);
	free(business -> dataptr -> x_coord);
	free(business -> dataptr -> y_coord);
	free(business -> dataptr -> location);

	free(business -> dataptr);
	
}

