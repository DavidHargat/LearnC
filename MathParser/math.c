#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

/*************
* STRUCTURES *
**************/

struct Token{
	char *symbol;
	int value;
};

/****************************************************************************************/
/* MATH */

// integer POW (has size restrictions)
int gpow(int base, int exponent)
{
	int sum = base;
	int i;
	
	for(i=0;i<exponent-1;i++){
		sum = sum * base;
	}
	
	if(exponent==0){
		sum = 1;
	}
	
	return sum;
}

/****************************************************************************************/
/* STRING CHECKS & MANIPULATION */

// Returns length of a string.
int slen(char *str){
	int i=0;
	while(str[i] != '\0'){
		i++;
	}
	return i;
}

// Convert a numerical string to an int.
int string_to_number( char *word )
{
	int size = slen(word);
	int sum = 0;
	
	int i;
	for( i=0; i<size; i++ ){
		int num = word[i] - '0';
		int p = (int)gpow(10,(size-i-1));
		int inc = num * p;
		sum = sum + inc;
	}	
	
	return sum;
}

// "test",0,3 -> "tes"
char *ssub( char *word, int first, int last )
{
	int length = last-first;
	
	char *output = malloc (sizeof (char) * length); // allocate sizeof(char) bytes for each char in word
	
	int i; 
	for( i=first; i<last; i++ ){
		output[i-first] = word[i]; // copy selected chars to output
	}
	output[length] = '\0'; // terminator

	return output;
}

char *char_to_string(char c){
	char *ptr = malloc(sizeof(char) * 2);
	ptr[0] = c;
	ptr[1] = '\0';
	return ptr;
}

bool on_whitelist(char *whitelist, char c){
	int length = slen(whitelist);
	
	int i;
	for(i=0; i<length; i++){
		if( whitelist[i] == c)return true;
	}
	
	return false;
}

bool is_operator(char c){
	return on_whitelist("+-*/",c);
}

int count_operators(char *expression){
	int length = slen(expression);
	int operators = 0;
	
	int i;
	for(i=0; i<length; i++){
		if(is_operator(expression[i]))
			operators++;
	}
	
	return operators;
}

/****************************************************************************************/
/* OUTPUT */

void error(char *msg)
{
	printf("[ERROR] %s\n",msg);
}

void print_token_array( struct Token *tokens, int length ){
	int i;
	for(i=0; i<length; i++){
		if(tokens[i].symbol == "value"){
			printf("'%d' ",tokens[i].value);
		}else if(tokens[i].symbol == "null"){
			printf("'%s' ","n");	
		}else{
			printf("'%s' ",tokens[i].symbol);			
		}
	}
	printf("\n");
}
/****************************************************************************************/
/****************************************************************************************/
/* MAIN ALGORITHM */

int solve_operation(struct Token a, struct Token b, struct Token op){
	int num_a,num_b;
	
	if(a.symbol == "value"){
		num_a = a.value;
	}else{
		num_a = string_to_number(a.symbol);
	}
	
	if(b.symbol == "value"){
		num_b = b.value;
	}else{
		num_b = string_to_number(b.symbol);
	}

	//printf("%d %s %d \n",num_a,op.symbol,num_b);
	
	if(op.symbol[0] == '+')
		return num_a + num_b;
	
	if(op.symbol[0] == '-')
		return num_a - num_b;
	
	if(op.symbol[0] == '*')
		return num_a * num_b;
	
	if(op.symbol[0] == '/'){
		if(num_b == 0){
			error("Cannot divide by 0.");
		}else{
			return num_a / num_b;
		}
	}
	
	return 0;
}

// The token array, the index of the operator you want to solve, and the size of the token array
void reduce_token(struct Token *tokens, int op_ptr, int size){
	struct Token a,b,op;
	
	// Grab selected tokens
	op = tokens[op_ptr];
	a = tokens[op_ptr-1];
	b = tokens[op_ptr+1];
	
	// Calculate
	int result = solve_operation(a,b,op);
	
	// Put the result in a token
	struct Token result_token;
	result_token.symbol = "value";
	result_token.value = result;
	// Parse the expression starting at the left-most token
	int start = op_ptr-1;
	int i;
	for(i=start; i<size-2; i++){
		if(i==start){
			// Replace the left-most token with the result
			tokens[i] = result_token;
		}else{
			// then shift the remaining tokens 2 to the left
			tokens[i] = tokens[i+2];
		}
	}
	
	// Replace the last 2 tokens with 'null tokens'
	struct Token null_token;
	null_token.symbol = "null";
	tokens[size-2] = null_token;
	tokens[size-1] = null_token;
}

// Return array of tokens
struct Token* expression_to_tokens(char *expression){

	int length = slen(expression);
	
	struct Token *tokens;
	tokens = malloc( sizeof(struct Token) * length );
	
	int token_i = 0; // pointer to keep track of how many tokens
	int last = 0; // pointer to keep track of the 'last' operator in *expression
	
	int i;
	for(i=0; i<length; i++){
		char c = expression[i]; // Grab the current char
		if( is_operator(c) ){ // If the current char is an operator
			char *before_operator = ssub(expression,last,i); // Grab the preceding chars as a string.
			
			// Insert a new token for the integer preceding the operator
			// as in '11' of '11+3'
			struct Token t1;
			t1.symbol = before_operator;
			tokens[token_i] = t1;
			token_i++;
			
			// Insert a new token for the operator. (current char)
			struct Token t2;
			t2.symbol = char_to_string(c);
			tokens[token_i] = t2;
			token_i++;
			
			// Okay, I hope that wasn't too obfuscated....
			
			last = i+1; // indicate the last position of an operator in *expression
		}else{
			if( i==length-1 ){
				char *before_last = ssub(expression,last,i+1); // Grab the preceding chars as a string.
				// Insert a new token for the integer preceding the operator
				// as in '11' of '11+3'
				struct Token t1;
				t1.symbol = before_last;
				tokens[token_i] = t1;
				token_i++;
			}
		}
	}	
	
	return tokens;
}

void solve_all(struct Token *tokens, int size, char op){
	int i;
	for(i=0; i<size; i++){
		if( tokens[i].symbol[0] == op ){
			reduce_token(tokens,i,size);
			i = 0;
		}
	}
}

void solve_pemdas(struct Token *tokens, int size){	
	// PEMDAS
	solve_all(tokens,size,'*');
	solve_all(tokens,size,'/');
	solve_all(tokens,size,'+');
	solve_all(tokens,size,'-');
}

int main( int argc, char *argv[] )
{
	// Initial String
	//char *exp = "111+222+3+4+32-213*4";
	char *exp = argv[1];
	//printf("%s\n",exp);
	
	// Catch invalid expressions...
	
	if(!exp){
		error("No Expression");
		return 0;
	}
	
	if(slen(exp)<3){
		error("Invalid Expression");
		return 0;
	}
	
	
	// Count the number of 'operators' '+' '-' etc.
	int num_of_operators = count_operators(exp);
	int num_of_tokens = (num_of_operators*2)+1; // calculate the total number of tokens
	
	struct Token *tokens; // Array of tokens
	tokens = expression_to_tokens(exp); // Converts expression to an array of tokens
	
	solve_pemdas(tokens,num_of_tokens);
	
	printf("%d",tokens[0].value);
	
    return 0;
}