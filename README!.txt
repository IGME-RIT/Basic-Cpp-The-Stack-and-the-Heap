Documentation Author: Niko Procopi 2019

This tutorial was designed for Visual Studio 2017 / 2019
If the solution does not compile, retarget the solution
to a different version of the Windows SDK. If you do not
have any version of the Windows SDK, it can be installed
from the Visual Studio Installer Tool

Welcome to the Stack and Heap Tutorial!
Prerequesites: Pointers

Stack Memory and Heap Memory are two different sections of RAM
that are used while a program runs. Stack is a small temporary
section of RAM, that is often deleted automatically, while
heap is large memory that can only be erased manually with "free" or "delete"

// This is on the stack
int numbers[10];

// This is on the heap
int* numbers = new int[10];

Each function has its own stack, and the stack is cleared when
the function finishes executing

void func()
{
	int x;
	int y;
	int z;
}

int main()
{
	func();
	cout << "hi" << endl;
}

x, y, and z, are all on the stack memory. As soon as "func" finishes executing,
when the program returns to "main" to print the text "hi", all of the memory on 
the "func" stack will be erased.