#include<iostream>
#include"shared_ptr.h"

/**
*		   .---------------.											   .---------------.   .---------------.								
*		   |integer pointer|											   |integer pointer|   |    nullptr    |			
*		   .---------------.											   .---------------.   .---------------.
*		 /			|	   \  											    /			|	        	|
*		/			|		\											   /			|		    	|
* .________.	.________.	.________.        shared3.reset()		 .________.	    .________.	    .________.			
* |shared 1|	|shared 2|	|shared 3|    	================>		 |shared 1|	    |shared 2|	    |shared 3|	      
* `--------`	`--------`	`--------`							     `--------`	    `--------`	    `--------`	
*		  \         |        /											     \         |		 	   |
*		   \        |       /											      \        |		 	   |
*			\       |	   /												   \       |		 	   |
*			.______________.												.______________.    .______________.
*			| refcount = 3 |												| refcount = 2 |    | refcount = 1 |
*			`--------------`												`--------------`    `--------------`
*		(this is shared resource)
*/
void shared_demo() {
	shared_ptr ptr(new int(3));

	// Copy constructor incrementing refcount
	shared_ptr second(ptr);

	// Empty shared ptr pointing to nullptr with refcount 1
	shared_ptr third;

	third = ptr;

	assert(third.use_count() == 3);

	third.reset();

	assert(third.use_count() == 1 && ptr.use_count() == 2);

	*ptr = 10;
	assert(*second == 10);

	third = ptr;
	assert(ptr.use_count() == 3);
}

int main() {
	// while (true) {	// <--- check for memory leaks
		shared_demo();
	// }
}