int clear_display(); //just clears the display :)

int display(int highlight, int *numbers, int num); // display numbers, right-justified
						  // highlight shows index of a number to highligh
						 // num is the total number of elements in the array

int delay(int msec); // really just pauses until user hits enter

int myRnd(int *numbers, int num); // fill an array with consecutive integers, then shuffle it

int done(); // wait for ^D
