#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   char ch, file_name[25];
   FILE *fp;
   printf("Enter name of a file you wish to see\n");
   fgets(file_name, sizeof(file_name), stdin);
   file_name[strlen(file_name) - 1] = '\0';
   fp = fopen(file_name, "r"); 
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
   printf("The contents of %s file are:\n", file_name);
   while((ch = fgetc(fp)) != EOF)
      printf("%c", ch);
   fclose(fp);
   return 0;
}
