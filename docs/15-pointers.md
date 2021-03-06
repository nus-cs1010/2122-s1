# Unit 15: Pointers

## Learning Objectives

After this unit, students should:

- understand what the address-of operator, `&`, represents and what is its type
- be able to use the `&` operator to access the address of a variable
- understand what the dereference operator, `*`, represents
- be aware that there is a pointer type associated with each type in C and that when `*` is used in the variable declaration it has a different meaning to the dereference operator
- be able to define pointer type variables and use the `*` operator, including:
    - declaration of a pointer type variable
    - assigning an address (of the appropriate type) to a pointer type variable
    - accessing/assigning the value that a pointer variable points at
    - assigning a new value by dereferencing a pointer variable
- understand why we cannot only change the address referenced by a variable
- understand the units being stored by a pointer and thus, how arithmetic operations would affect pointers
- be aware of pointers to pointers (and more), and the possibility of multiple levels of dereferencing
- be aware of the `NULL` pointer, understand what it represents, and be able to use it


## Memory Address

You have learned that each variable must have three things: (i) a name, (ii) a type, and (iii) a value.  A variable must be stored somewhere in the memory.  Every location in the memory has an address.  So, there is a fourth thing that every variable must have: a memory address.

Unlike many higher-level languages, such as Java, Python, and JavaScript, C allows us direct access to memory addresses.  This empowers programmers to do wonderful things that cannot be done in other languages.  But, it is also dangerous at the same time -- using it improperly can lead to bugs that are hard to track down and debug.

## The Address-of Operator

Given a variable, we can get its memory address with the "address-of" operator, denoted by `&`.

Let say that we have a variable
```C
long c;
```

We can refer to the memory address of `c` with the expression `&c`. The expression `&c` has the type "address of a `long`" and evaluates to a number that corresponds to the memory address of `c`.  Note that "address of a `long`" and `long` are two different types to C.  In general, the expression `&x` has the type "address of $T$" where $T$ is the type of variable `x`.

You have also seen in [Unit 14](14-array.md) that a variable that stores a memory address is called a pointer.  So we also interchangeably refer to the type of `&c` as "pointer to a `long`".

Suppose we want to print out the address of `c`.  We cannot use `cs1010_println_long(&c)`, since the type does not match.  The CS1010 library has a function to print a pointer variable, which prints out the address in decimal format.

```C
#include "cs1010.h"

void add(long sum, long a, long b) {
  sum = a + b;
  cs1010_println_pointer(&sum);
}

int main()
{
  long x = 1;
  long sum = 0;
  add(sum, x, 10);
  cs1010_println_pointer(&sum);
}
```

Running the program above prints something like this:
```
140723025685528
140723025685552
```

Your results will most likely be different since the OS allocates different regions of the memory to this program every time it is run.

![pointers](figures/pointers/pointers.001.png)

## The Dereference Operator

The dereference operator is the reversed of address-of and is denoted by `*`.  Think of this as the "location-of" operator.  We use this operator in two places:

- to declare a pointer variable, and
- to reference the location of an address.

You have seen how we can declare a pointer variable in [Unit 14](14-array.md).  For example,

```C
double *addr;
```

declares a variable `addr` that is an address to a variable of type `double`.  The way to read this is that `*addr` (or the memory location of `addr`) stores a variable of type `double`, so `addr` is an address of a memory location containing a `double`.

## Changing the Value via Pointer

Suppose we declare a pointer to a `double` variable (or, for short, a `double` pointer):
```C
double *addr;
```

We can use `*addr` just like a normal `double` variable:
```C
*addr = 1.0;
```

The line above means that, _we take the address stored in addr, go to the location at that address, and store the value 1.0 in the location._

This is where things can get dangerous.  You could be changing the value in a memory location that you do not mean to.  If you are lucky, your program crashes with a `segmentation fault` error[^2]. We say that your program has segfault.  If you are unlucky, your program runs normally but produces incorrect output occasionally.

![pointers](figures/pointers/pointers.002.png)

So, _always make sure that your pointer is pointing to the right location before dereferencing and writing to the location._

[^2]: I leave it to the later OS classes CG2271 / CS2106 to explain the term "segmentation" and "fault".  Interested students can always google and [read on Wikipedia](https://en.wikipedia.org/wiki/Segmentation_fault).

In the code above, if we write:
```C
double *addr;
*addr = 1.0;
```

back-to-back, the program will almost certainly segfault, because the pointer variable `addr` is not initialized, so it is pointing to the location of whatever address happens to be in the memory at that time.

We should point `addr` to a valid location first, like this:
```C
double c;
double *addr;
addr = &c;
*addr = 1.0;
```

![pointers](figures/pointers/pointers.003.png)

Of course, the above could be simply written as:
```C
double c = 1.0;
```

I am just doing it the complicated way (which you should avoid unless you have good reasons to do so) to demonstrate the concept of pointers.

Note that the two lines:
```C
double *addr;
addr = &c;
```

can be shorten to:
```C
double *addr = &c;
```

## Basic Rules About Using Pointers

1. When we use pointers, it must point to the variable of the same type as that declared by the pointer.  For instance,

	```C
	double pi = 3.1415926;
	long radius = 5;
	double *addr;
	addr = &pi; // ok
	addr = &radius; // not ok
	```

	Line 5 above would lead to a compilation error since we try to point a `double` pointer to a `long`.  

	One exception to this rule is the type `void *`.  A pointer to `void` has a special place in C and it can be used to point to any other type without type errors.  The function `cs1010_println_pointer`, for instance, takes in a parameter of type `void *`, hence we can pass a pointer of any type to this function as an argument.

2. We cannot change the address of a variable.  For instance

	```C
	long x = 1;
	long y = 2;
	&x = &y;
	```

	We try to set the address of `x` to be the address of `y`.  This is not allowed since the allocation of variables in the memory is determined by the OS, a process we have no control over.

3. We can perform arithmetic operations on pointers, but not in the way you expect.

	Suppose we have a pointer:
	```C
	long x;
	long *ptr;
	x = 1;
	ptr = &x;
	ptr += 1;
	```

	Suppose that `x` is stored in memory address 1000, after Line 4, `ptr` would have the value of 1000.
	After the line `ptr += 1`, using normal arithmetic operation, we would think that `ptr` will have a value of 1001.  However, the semantic for arithmetic operations differ for pointers.  The `+` operation for `ptr` causes the `ptr` variable to move forward by the size of the variable pointed to by the pointer.  In this example, `ptr` points to `long`, assuming that `long` is 8 bytes, after `ptr += 1`, `ptr` will have the value of 1008.

	We can only do addition and subtraction for pointers.

	Note that the array notation `a[i]` is synonym with `*(a + i)`.  

## Pointer of Pointer (of Pointer..)

A pointer variable is also stored in the memory, so it has an address too.

```C
long x;
long *ptr;
ptr = &x;
```

For instance, in the above, `ptr` would have a memory location allocated on the stack too, and so it has an address, and we can have a variable `ptrptr` referring to the address of `ptr`.  What would the type of this variable be?  Since `ptr` is an address of `long`, `ptrptr` is an address of an address of `long`, and can be written as:

```C
long x;
long *ptr;
long **ptrptr;
ptr = &x;
ptrptr = &ptr;
```

This dereference can go on since `ptrptr` is also a variable and has been allocated in some memory location on the stack.  We rarely need to dereference more than twice in practice, but if the situation arises, such multiple layers of dereferencing are possible.

## The `NULL` Pointer

`NULL` is a special value that is used to indicate that a pointer is pointing to nothing.  In C, `NULL` is actually 0 (i.e., pointing to memory location 0).

We use `NULL` to indicate that the pointer is invalid, typically to mean that we have not initialized the pointer or to flag an error condition.

!!! note "Billion Dollar Mistakes"
    Sir Tony Hoare (the same one whom we met when we talked about [Assertion](10-assert.md)) also invented the null pointer.  He called it his billion-dollar mistake.  Quoting from him: "I couldn't resist the temptation to put in a null reference, simply because it was so easy to implement. This has led to innumerable errors, vulnerabilities, and system crashes, which have probably caused a billion dollars of pain and damage in the last forty years."  As you start to use pointers in CS1010, you will see why it is a pain.

## Problem Set 15
### Problem 15.1

Sketch the content of the memory while tracing through the following code.  What would be printed?

```C
long *ptr1;
long *ptr2;
long x;
long y;

ptr1 = &x;
ptr2 = &y;

*ptr1 = 123;
*ptr2 = -1;

cs1010_println_long(x);
cs1010_println_long(y);
cs1010_println_long(*ptr1);
cs1010_println_long(*ptr2);

ptr1 = ptr2;
*ptr1 = 1946;

cs1010_println_long(x);
cs1010_println_long(y);
cs1010_println_long(*ptr1);
cs1010_println_long(*ptr2);

y = 10;

cs1010_println_long(x);
cs1010_println_long(y);
cs1010_println_long(*ptr1);
cs1010_println_long(*ptr2);
```

### Problem 15.2

What is wrong with both programs below?

```C
double *addr_of(double x)
{
  return &x;
}

int main()
{
  double c = 0.0;
  double *ptr;

  ptr = addr_of(c);
  *ptr = 10;
}
```


```C
double *triple_of(double x)
{
  double triple = 3 * x;
  return &triple;
}

int main()
{
  double *ptr;

  ptr = triple_of(10);
  cs1010_println_double(*ptr);
}
```
