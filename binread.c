/*
 * binread.c
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_ELEMENTS 1024

unsigned int input_data[MAX_ELEMENTS];
int convert_little(int );
//int check();
int main(int argc, char **argv)
{
  unsigned int size_from_file;
  unsigned int how_many_read;
  FILE *fp;
  unsigned int i;

  if (argc != 2) {
    fprintf(stderr, "syntax for command should be: %s filename\n", argv[0]);
    exit(1);
  }

  /* The mode "rb" means read a binary file.  The "b" is
   * not necessary in Linux systems, but is needed in
   * MS Windows and various other OSes. */
  if ((fp = fopen(argv[1], "rb")) == NULL) {
    fprintf(stderr, "failed to open file %s for input\n", argv[1]);
    exit(1);
  }
 
  printf("\nAttempting to read array stored in %s ...\n", argv[1]);
  
  how_many_read = fread(&size_from_file, sizeof(unsigned int), 1, fp);
 // if(strcmp(argv[1],"ppc_binwrite_out.dat")==0)
 // {
	printf("in side arg");
	int temp = convert_little(size_from_file);
 // }   
        size_from_file = temp;
  if (how_many_read != 1) {
    fprintf(stderr, 
            "Not enough bytes in %s to form an element count.\n",
            argv[1]);
    exit(1);
  }
  printf("Number of elements stated in file: %u\n",size_from_file );

  if (size_from_file > MAX_ELEMENTS) {
    fprintf(stderr, 
            "This program can't handle an array of over %u elements.\n",
            (unsigned int) MAX_ELEMENTS);
    exit(1);
  }

  how_many_read = fread(input_data, sizeof(unsigned int), size_from_file, fp);
  if (how_many_read != size_from_file) {
    fprintf(stderr, 
            "Read error occurred before %u elements could be read from %s.\n",
            size_from_file,
            argv[1]);
    exit(1);
  }
  for (i = 0; i < size_from_file; i++)
  {
//if(strcmp(argv[1],"ppc_binwrite_out.dat")==0)
  {
	input_data[i] = convert_little(input_data[i]);
 // }
    printf("Element %d: %u\n", i, input_data[i]);
  }
  }
return 0;
}
int  convert_little(int a)
{
union Data {
int n;
char a[4];
}data;
data.n = a;
char b[4];
b[0]=data.a[3];
b[1] = data.a[2];
b[2] = data.a[1];
b[3] = data.a[0];
int i=0;
for(i=0;i<4;i++)
  data.a[i] = b[i];
return data.n;
}
/*int check()
{
union Data {
int n;
char a[4];
}data;
data.n = 1;
if(data.a[0]==0)
{
 return 0;
}
else
{
 return 1;
}
}
*/


