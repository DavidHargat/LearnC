
# Pointer Example
Struggling to understand how pointers work in C?
Maybe this example will help!
Compile it and see the magic of pointers.

# Explanation of pointers.

A POINTER is an address to some memory.

In C, the symbol '*' DEREFERENCES a pointer
this means it gets whatever memory is stored at that pointer,
therefore '*(x)' means "memory at the address x".

In C, we also have the symbol '&'
it's much like the opposite of '*' because
instead of getting some memory we're getting
an ADDRESS to some memory, therefore
'&(x)' means the address of 'x'.
	
# Line by line explanation of main.c
## (also included in the comments)

Create a constant int 'a' and set it to 12
'int a = 12;'

Create a POINTER 'ptr'
set it to the ADDRESS of 'a' (where we have '12' stored in memory)
'int *ptr = &a;'

Print out our variables.
'printf( "a    == %d \n", a);
'printf( "ptr  == %p \n", ptr);'

Print out whats stored at 'ptr'
'printf( "*ptr == %d \n", *ptr);'

Print out the address of 'a'.
'printf( "&a   == %p \n", &a);'

The memory at the address 'ptr' is the same as 'a'!
'printf( "*ptr == a \n\n");'

## The above example shows how 'ptr' is equivalent to the address of 'a'.
### (redundant 'printf' statements are ommitted from here)

The index 'i' of 'ptr' is the memory at 'ptr+i'
In other words:
'ptr[i] == *(ptr+i)' 

For example:
'ptr[0] == *(ptr+0)' 
'ptr[0] == *ptr'

Since 'ptr[i]' is just a notation for '*(i+ptr)'
We can say: 'i' of 'ptr' is the same as the memory at 'i+ptr'.
'i[ptr] == *(i+ptr)'

For example:
'0[ptr] == *(0+ptr)'
'0[ptr] == *ptr'

Since '*' and '&' are essentially opposites you can use them together to cancel eachother out
For example:
'*&a == a'