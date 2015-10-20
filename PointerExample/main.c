
#include<stdio.h>
#include<stdlib.h>

int main(int argc , char **argv)
{
	int a = 12;

	int *ptr = &a;

	printf( "\nPointer Example\n\n");

	printf( "a    == %d \n", a);
	printf( "ptr  == %p \n", ptr);
	printf( "*ptr == %d \n", *ptr);
	printf( "&a   == %p \n", &a);

	printf( "*ptr == a \n\n"); 

	printf( "ptr[i] == *(ptr+i) \n"); 

	printf( "ptr[0] == *(ptr+0) \n"); 
	printf( "ptr[0] == *ptr \n");
	printf( "ptr[0] == %d \n\n", ptr[0]);

	printf( "i[ptr] == *(i+ptr) \n");

	printf( "0[ptr] == *(0+ptr) \n");
	printf( "0[ptr] == *ptr \n");
	printf( "0[ptr] == %d \n\n", 0[ptr]);

	printf( "*&a    == %d \n",*&a);
	printf( "*&a    == a \n\n");

	return 0;
}