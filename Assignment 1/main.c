#include"list.h"
#include"data.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//main program controls all the action
int main (int argc, char **argv){                     
	struct list *list;
	char *key = malloc(sizeof(*key) * (COLUMNDATA +1));
	assert(key);
	list = create_empty_list();                                                                                          
	
    //open the input csv file
	FILE *fp = fopen(argv[1], "r");
	assert(fp);
	
	//skips header row of input csv file
	while (fgetc(fp) != '\n' && !feof(fp));
	
	//Open the output file if present and else create new file
	FILE *outfile = fopen(argv[2], "w");
	assert(outfile);
	
	//read in and insert data from input file to list  
	list = read_in(fp,list);                                  
    
    //while there is a key entered, write to output file
    while(scanf("%[^\n] ",key) == 1){  
    	output(outfile, list, key);
    }
    
    free(key); 
    
    fclose(fp);   
    fclose(outfile); 
    
    free_list(list);
    
	return 0;     
}
