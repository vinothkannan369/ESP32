


int get_file_size(const char* file_name);
int write_file(const char* file_name,const char* data);
int append_file(const char* file_name,const char* data);
int file_line_count(const char* file_name,int file_size );
int read_nth_line(const char* file_name,int linenumber,char *save_data);
int print_all_line(const char* file_name);
int delete_line(const char* file_name,int line_number,const char* temp_file_name) ;
