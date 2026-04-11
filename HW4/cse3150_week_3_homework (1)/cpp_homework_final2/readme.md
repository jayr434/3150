The student list is stored in two arrays (one for names, one for gpas), with the capacity CL arg choosing the size. The user can choose to add update print or average. 

The gpas variable is a pointer to an array of doubles on the heap, and equates to a pointer to its first element. `names` is double pointer, i.e. an array of char pointers. 

We use references to refer to original variables, but without having to dereference like with pointers. The addStudent function uses references for size so that it can grow the count and be accessed through main. Using const limits the ways we can edit our variables, and we use it in printStudent to ensure we only read variables. Type casting is used to treat certain variables as different types than the ones they were assigned at definition. We used them to treat the average as a whole number.

The exceptions are how we handle errors cleanly, like throwing a string literal exception when the student array is full, as well as having the gpa array throw when there are no students. Control flow is just the structure and order of our statements, especially through basic conditionals. The menu function is built around the basic do while loop as usual.

