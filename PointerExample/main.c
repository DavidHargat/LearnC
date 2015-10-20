
#include<stdio.h>
#include<stdlib.h>

/*
* @Author David Hargat
* @Email DavidHargat@Yahoo.com
*/

int main(int argc , char **argv)
{

	/* 
	*	A POINTER is an address to some memory.
	*	In C, the symbol '*' DEREFERENCES a pointer
	*	this means it gets whatever memory is stored at that pointer,
	*	therefore *(x) means "whatever memory is at the address x".
	*
	*
	*	In C, we also have the symbol '&'
	*	it's much like the opposite of '*', because
	*	instead of getting some memory, we're getting
	*	an ADDRESS to some memory, therefore
	*	&(x) means "the address of whatever memory x".
	*/

	// Create a constant int 'a' and set it to 12
	int a = 12;

	// Create a POINTER 'ptr'
	// set it to the ADDRESS of 'a' (where we have '12' stored in memory)
	int *ptr = &a;

	printf( "\nPointer Example\n\n");

	printf( "a    == %d \n", a); // print constant 'a'
	printf( "ptr  == %p \n", ptr); // prints pointer 'ptr' (in hex form)
	printf( "*ptr == %d \n", *ptr); // the memory at 'ptr' is 12
	printf( "&a   == %p \n", &a); // prints the address of 'a' (in hex form)

	// The memory at the address 'ptr' is the same as the memory at the address of 'a'
	printf( "*ptr == &a \n\n"); 

	// The index 'i' of 'ptr' is the memory at ('ptr'+i).
	// In other words:
	printf( "ptr[i] == *(ptr+i) \n"); 

	// For example:
	printf( "ptr[0] == *(ptr+0) \n"); 
	printf( "ptr[0] == *ptr \n");
	printf( "ptr[0] == %d \n\n", ptr[0]);

	// Since ptr[i] is just a notation for *(i+ptr)
	// We can say: the memory at 'i' of 'ptr' is the same as the memory at 'i'+'ptr'.
	printf( "i[ptr] == *(i+ptr) \n");

	// For example:
	printf( "0[ptr] == *(0+ptr) \n");
	printf( "0[ptr] == *ptr \n");
	printf( "0[ptr] == %d \n\n", 0[ptr]);

	// Since '*' and '&' you can use them together to cancel eachother out
	// For example:
	printf( "*&a    == %d \n",*&a);
	printf( "*&a    == a \n\n");

	return 0;
}