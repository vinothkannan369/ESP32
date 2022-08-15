#include "File_Handling.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * file name =  User file name
 */
int get_file_size(const char* file_name)
{
    FILE *file = fopen(file_name, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}
/*
 * file name =  User file name
 * data =   User data
 */
int write_file(const char* file_name,const char* data)   {

       printf( "Opening file \n");
       FILE* f = fopen(file_name, "w");
       if (f == NULL) {
    	   printf("Failed to open file for writing \n");
    	   return 0;
       }
       fprintf(f,"%s\n",data);
       fclose(f);
       printf("File written \n");
       return 0;
}
/*
 * file name =  User file name
 * data =   User data
 */
int append_file(const char* file_name,const char* data)   {

       printf( "Opening file \n");
       FILE* f = fopen(file_name, "a+");
       if (f == NULL) {
    	   printf("Failed to open file for writing \n");
    	   return 0;
       }
       fprintf(f,"%s\n",data);
       fclose(f);
       printf("File written \n");
       return 0;
}
/*
 * file name =  User file name
 * file_size =   size of the file
 */
int file_line_count(const char* file_name,int file_size )   {


	        FILE *f2;
	    	int count = 0; // Line counter (result)
	    	//char filename2[100]= file_name;
	    	 char c; // To store a character read from file

	    	// Get file name from user. The file should be
	    	// either in current folder or complete path should be provided


	    	// Open the file
	    	f2 = fopen(file_name, "r");

	    	// Check if file exists
	    	if (f2 == NULL)
	    	{
	    		printf("Could not open file %s\n", file_name);
	    		 return 0;
	    	}

	    	// Ehttps://www.onlinegdb.com/#_editor_8046849371xtract characters from file and store in character c
	    	for (int i =0; i <file_size; i++)  {
	    		c = getc(f2);
	    		if (c == '\n')   { // Increment count if this character is newline
	    			count = count + 1;
	    			//printf("counting line %d \n",count);
	    			//break;
	    	     }
	    	}
	    	// Close the file
	    	fclose(f2);
	    	printf("The file %s has %d lines\n", file_name, count);
	    	return count;
}

/*
 * file name =  User file name
 * line_number      =  enter line you want to save , In mode 2 line_number become total line to print all the lines
 * mode 1    = Read Nth line
 * mode 2    = Read all line and print the data
 * save_data =  To store your data  ,In mode 2 save_data  become do not care
 */
int read_nth_line(const char* file_name,int line_number,char *save_data)   {
FILE *f3;
 char data[256];



     int i = 0;
	f3 = fopen(file_name, "r");
	if(f3 == NULL)
	{
	 return 0;
	}
	    while (fgets(data, sizeof(data), f3)) {
	        i++;
	        if(i == line_number )
	        {
	            printf("selected line = %d data = %s\n",i, data);
	            strcpy(save_data,data);
	        }
	    }

	    fclose(f3);

	    return 0;

}

int print_all_line(const char* file_name)   {

FILE *f3;
 char data[256];




       	    	f3 = fopen(file_name, "r");
       	    	if(f3 == NULL){
       	    	        return 0;
       	    	}
       	    	    int i = 0;

       	    	    while (fgets(data, sizeof(data), f3)) {
       	    	        i++;
       	    	         printf("file name = %s line number = %d data = %s\n",file_name, i,data);
       	    	    }

       	    	 fclose(f3);
       	    	 return 0;

}

int delete_line(const char* file_name,int line_number,const char* temp_file_name) {

                         int ctr = 1;
    	    	         char ch;
    	    	         FILE *fptr1, *fptr2;

    	    	         char str[256];
    	    	 		printf("\n\n Delete a specific line from a file :\n");
    	    	 		printf("line number to be deleted is =  %d\n",line_number);
    	    	         fptr1 = fopen(file_name, "r");
    	    	         if (fptr1 == NULL)
    	    	         	    	{
    	    	         	    		printf("Could not open file %s", file_name);
    	    	         	    		 return 0;
    	    	         	    	}
    	    	         fptr2 = fopen(temp_file_name, "w"); // open the temporary file in write mode
    	    	         if (fptr2 == NULL)
							{
								printf("Could not open file %s\n", temp_file_name);
								 return 0;
							}


    	    	 		line_number++;
    	    	         // copy all contents to the temporary file except the specific line
    	    	         while (!feof(fptr1))
    	    	         {
    	    	             strcpy(str, "\0");
    	    	             fgets(str, 256, fptr1);
    	    	             if (!feof(fptr1))
    	    	             {
    	    	                 ctr++;
    	    	                 /* skip the line at given line number */
    	    	                 if (ctr != line_number)
    	    	                 {
    	    	                     fprintf(fptr2, "%s", str);
    	    	                 }
    	    	             }
    	    	         }
    	    	         fclose(fptr1);
    	    	         fclose(fptr2);
    	    	         remove(file_name);  		// remove the original file

    	    	         rename(temp_file_name, file_name); 	// rename the temporary file to original name
    	    	         printf("file deleted and updated\n");
    	    	         return 0;

}
