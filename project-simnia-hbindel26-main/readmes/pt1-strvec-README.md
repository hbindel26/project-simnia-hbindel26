# Memory Management, "Classes", and Error Handling (44-550: Operating Systems)

## Building your Shell, part 1

## 50 points

This project serves two purposes:

1. Refresh your C programming skills, including memory management, structs, strings in C, and very basic error handling
2. Get ready to read command strings for our simple shell we will be writing throughout the first portion of this class

You will be implementing a specialized string `vector` "class" (you may know the `vector` as the `ArrayList`) with certain functionality.
We will be wrapping this functionality in a `struct` to make our code significantly simpler as we continue building our shell.

This string vector has one particularly interesting feature: if the vector contains `n` strings, then the value at index `n` must be `NULL`.
You will need to trigger a "resize" of the vector earlier than you may be used to from your Data Structures class.

### Milestones

| Milestone | Tests Passed |
| --- | --- |
|Create the `strvec.h` and `strvec.c` with enough to compile and run (and fail) all of the tests.| (none) |
|Implement `strvec_init`, `strvec_size`, `strvec_capacity`, and `strvec_free`. | `init` |
|Implement `strvec_get`. | `get_bad`|
|Implement `strvec_push`. | `add` |

---

### Milestone and Function Descriptions

#### File Creation and Function Stubbing

You must create the `strvec.h` and `strvec.c` files that will contain your `strvec` struct.
In the `.h` file you must create the `strvec` struct:

```c
typedef struct _strvec {
	// put your member "variables" here
} strvec;
```

Your struct must contain at least the following three pieces of information:
* The pointer to the array of strings (`char**`)
* The current number of elements (`int`)
* The current capacity of the array (`int`)

You may add other information in your struct if you desire.

Additionally you must define all function prototypes:

* `void strvec_init(strvec * svec);`
* `void strvec_free(strvec * svec);`
* `void strvec_push(strvec * svec, const char* str);`
* `char* strvec_get(const strvec svec, int idx);`
* `int strvec_size(const strvec svec);`
* `int strvec_capacity(const strvec svec);`

In your `.c` file you must `#include` your header file and write stub definitions of the functions.  
For now, have any `void` function have an empty body, any function that returns an `int` return -1, and any function that returns a pointer `return NULL`.
This is a common development practice called "stubbing", where you are building in space to write your functions later.
You can verify that your code compiles by running `make test` (on really any system but Windows), or manually compiling all `.c` files together and running.
Most tests should fail (though not necessarily all, we may have a false positive in our stubs).

You may name the parameters whatever you want, but you should maintain the types (pay special attention to which functions take pointers to our struct and which just take an object of the struct).

#### Global Precondition

Since you are passing pointers, you should always have a precondition that the pointer not be null (unless it is allowed to be for some reason).

#### Function: `strvec_init`

This function should initialize a `strvec` with the following:
* The array should be allocated enough space to hold 4 pointers to characters
* The capacity of the `strvec` should be 4
* The size of the `strvec` should be 0

We will not try to make this function robust (i.e. weird things will happen if some jerk programmer calls the function multiple times).
As such, it should have the following preconditions:
* the strvec shall not yet have been initialized (or have been freed)

#### Function: `strvec_free`

This function should go through and free each string in the vector individually, then free the actual array of strings.
The array member should be set to `NULL`, and the size and capacity should be set to 0.
You should only try to free the individual strings in the array if the array pointer is not `NULL`

#### Function: `strvec_push`

If the size of the array is greater than or equal to the capacity of the array minus 1, you should resize the array and double the capacity.
There are several ways to go about doing this (`realloc`, allocating a new array and copying the data, etc).  
When you do this, the new capacity should be twice the old capacity.

Once there is space, you should allocate memory that is the length of the string plus 1 at the last available index in the array, then copy the string into the newly allocated space.
You should then increment the size, and set the new last index's value to be `NULL`.  NOTE: THIS IS IMPORTANT! 
It cannot be tested for, but may break your shell later if you do not set the new end of the array to the `NULL` pointer.

#### Function: `strvec_get`

If the specified index is less than zero or greater than (or equal to) the size of the array, you should return `NULL`.
Otherwise, return the pointer at the specified index.

#### Function: `strvec_size`

Return the size (number of elements) of the vector

#### Function: `strvec_capacity`

Return the capacity (maximum number of elements) of the vector

---

### Rubric

| Criteria | Points Per Unit | Total Points |
| --- | --- | --- |
| At least one unique commit for each milestone |1/milestone| 4 |
| Commit messages describe what the commit is doing | 1/milestone | 4 |
| Passes tests | 6/test | 18 |
| Tests run without memory leaks | 3/test | 9 |
| `strvec.h` and `strvec.c` have appropriate comment header | 3/file | 6 |
| Functions have appropriate function documentation |1/function | 6 |
| Files are formatted well and follow consistent coding standards (naming, spacing, etc) | | 3 |
| ***Total*** | | ***50*** |
