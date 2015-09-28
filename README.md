# List_T
A parametric list in C with support for LINQ-style functions and lambda expressions

#####Generate object files with:

    gcc -O2 -c Library\list_t.c Library\Introsort\introsort.c
    
#####Then get the static library using:

    ar rcs list_t.a list_t.o introsort.o
    
######Now just add the .a file in your project folder and compile with "list_t.a"
