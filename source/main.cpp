/*
New and Delete
(c) 2016
Author: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Include iostream for output during the program.
#include <iostream>
#include "../header/gun.h"

using namespace std;

int main() 
{
    {
        // Before we talk about new and delete, it's important to understand how pointers work.
        // If you haven't read the pointers tutorial, you should look at that first and then come back.


        // Just like pointers to basic data types, you can also create pointers to objects.

        Magazine mag = Magazine(4, 4);
        Magazine* magptr = &mag;        // Get pointer to magazine.

        cout << "\nChangin number of bullets:" << endl; // Options:

        /*1*/
        mag.bullets = 1;            // First way of doing this: just change the object we already have.
        cout << "Bullets: " << mag.bullets << endl;

        /*2*/
        (*magptr).bullets = 2;      // Second way of doing this: dereference the pointer and change it.
        cout << "Bullets: " << mag.bullets << endl;

        /*3*/
        magptr->bullets = 3;           // T-> is a shortcut (member access operator) that does the same thing as the second way.
        cout << "Bullets: " << mag.bullets << endl;

        cin.get();  // Wait...
    }
    cin.get();      // Wait...



    // The NEW keyword is a special way of creating pointers to objects that uses the constructor.
    // Here's a basic example of this explained step by step:
    {
        Magazine* magptr = new Magazine(8, 8);      // Create a NEW magazine using the constuctor.
                                                    // Notice how we store it as a pointer, because "new constructor()" returns a pointer instead of the object.

        Gun* gunptr = new Gun(magptr);              // Create a NEW gun the same way.
                                                    // This gun constructor takes a pointer to a mag instead of a mag itself.

        cout << "Press enter to fire." << endl;

        while (gunptr->IsLoaded())                  // Use -> on the pointer to access members variables and functions.
        {
            cin.get();      // Wait for user to press enter.
            gunptr->Fire(); // Fire gun.
        }

        cout << "First gun empty..." << endl;
        cin.get();      // Wait for user to press enter.




        // Are we done yet? Not quite.
        // Objects created with the new keyword don't work the same way as objects you create normally.

        // Normally, if an object goes out of scope, its destructor is called, and the program frees up the memory to be reused.

        // When an object is created with new, we only get a pointer to it.
        // That pointer will be in scope, and it will stop existing, but the actual isn't, and it won't be cleaned up.

        // If that happens, and we don't have any pointers to the object, there's no way to access it.
        // This is called a memory leak, because the memory is being leaked from the program.


        // In order to avoid memory leaks, we use the delete keyword to clean up the memory.
        cout << "Deleting objects created with new:" << endl;
        delete magptr;  // This calls the destructor, and cleans up any memory for the object.
        delete gunptr;

        // Avoiding memory leaks is one of the most difficult parts of programming in C++.
        // That's why there are so many strategies for it.

    }   // At this point, if we haven't deleted our pointers, there is a memory leak.
    cin.get();  // Wait for user to press enter.


    // delete doesn't work on objects that weren't created with new.
    {
        Magazine mag = Magazine(1, 2);
        Magazine* magptr = &mag;

        // This won't work:
        // delete magptr;
        // Why?
    }
    cin.get();



    {
        // So what's the difference between this:

        Magazine magazine1 = Magazine(6, 6);

        // and this:

        Magazine* magazine2 = new Magazine(6, 6);
    
        // is where they are allocated.

        // Objects like magazine1 are allocated on the STACK
        // Objects created with new are allocated on the HEAP


        /*

        ==== THE STACK ====  


        The stack works very similarly to your web browser.
        You navigate to a page, and then click a link, and then another, and another, and
        then eventually you're watching He-Man sing "What's Up" by 4 Non Blondes on repeat for 10 hours.

        The important thing is, you can always continue where you left off on the previous page with the back button.
        You can keep doing this too, all the way back to your home page.

        Stack memory works the same way:

        +--------------+    When your program starts, we start at the bottom of the stack.
        |     main     |    This is all of the memory used by your main function.
        +--------------+    Each of these blocks is referred to as a 'Stack Frame'.
               \/
        +--------------+    If in main, you call function foo, it's memory is added on top of the stack.
        |     foo      |    This is very fast for small objects with they way that computers work.
        +--------------+
        |     main     |    All of the memory from main still exists on the bottom of the stack.
        +--------------+
               \/
        +--------------+    Then the foo function calls the bar function. bar is added to the stack.
        |     bar      |
        +--------------+    If this pattern continues, the stack can actually run out of memory.
        |     foo      |    This is called a stack overflow.
        +--------------+    It used to be a big problem on older computers, but with modern computers not so much.
        |     main     |    Today, stack overflows won't happen unless you make a serious mistake.
        +--------------+
               \/
        +--------------+    Assuming that the pattern doesn't continue, eventually we reach the end of function bar.
        |     foo      |    Function bar is then removed from the stack, and we return to the previous stack frame.
        +--------------+    It's important to note that each stack frame will not only keep track of it's allocated memory.
        |     main     |    It also tracks where in the code it is, and what object the function is being called on (for member functions)
        +--------------+
               \/
        +--------------+    During the program, stack frames will get 'pushed' onto and 'popped' from the stack, constantly shifting up and down.
        |     main     |    As long as the program does not loop forever, we will eventually reach the end of our main function.
        +--------------+    At that point the function ends and all of the memory is cleaned up.
               \/
         End of Program


        */




        /*
        
        ==== THE HEAP ====
        
        The heap is usually a much larger block of memory that works very differently from the stack.
        Imagine the heap as a giant parking garage. Not just big though, enormous, about the size of the moon.

        Now imagine trying to find a space for your car.
        If the garage is empty, no big deal, but what if it's half full?
        What if some of the cars take up 2 spots. 10 spots? 500 spots? It's starting to feel like tetris in here.

        Now imagine that you parked your car, and then you come back later to get it...
        and you've completely forgetten where you parked it... uh oh.
        Even if you know what model it is you probably won't find it.
        At this point, you're probably better of buying a new one.

        This is essentially how the heap works.
        You can think of a pointer as the location of your parked car or your "keys"

        ==== BUT WHY THE HEAP? ====

        You might be wondering: "Why would I ever use the heap for anything if it's so bad?"
        There are many situations in which the heap is much better than the stack:

        1) You want an object or variable to exist after the stack frame where it was allocated.
        This is particularly imporant when writing functions that create objects and then return them (similar to a constructor)
        Every other case is somewhat an extension of this one.

        2) You want to transfer ownership of an object from one place to another.
        Copying a pointer is much much much much faster than copying an entire object, especially when objects start getting really big.


        ==== THE PARKING LOT PROBLEM ====

        Now that we have a basic idea of what the heap is, let's talk about how it actually works.
        Traditionally, there are two strategies to deal with this problem.

        ==== DO IT YOURSELF ( C, C++ ) ====

        This is the aproach that C++ takes (with a little bit of help)
        The new and delete keys work like a valet in this giant parking lot.
        Internally, C++ has a strategy for keeping tracking of which spots are taken and which aren't, but that doesn't matter too much.

        What does matter, is that when you use the new keyword, you're essentially asking the valet to park your spaceship.
        After your car has been parked, you get it's location, and you can request to get your car at any time.
        You can also share the location of the car with other people, and they can access your car too!

        There are two things you have to watch out for in this situation:

        1) Someone you shared your car with asks the valet to remove the car from the garage.
        If you then try to access the car yourself, you can run into some really ugly problems.
        Trying to get data at a pointer than has been deleted is the same thing as trying to use memory at some random address.

        Depending on the compiler/debugger, this can give you an access violation error.
        Alternatively, it might not notice and act like everything is fine, giving you complete garbage data, or worse:
        If you write to that memory location, you could overwrite extremely important data in another part of your program, or another program!
        This is called heap corruption, and it can be very difficult to track down and fix.


        2) You forget where you parked your car, and nobody knows where it is.
        The valet assumes that you want your car to stay there, which can be ok.

        This is a memory leak, and if it keeps happening, and your program runs long enough, you can crash by running out of memory!

        ==== GARBAGE COLLECTION ( Java, C# )====
        
        If you've programmed in C# before you may have learned something about garbage collection.
        This is a strategy where the owner of the car, the programmer, doesn't have to remember where they parked the car.

        In this situation, no single person can ask the valet to remove any given car.
        Instead the valet just keeps track of how many people know about each car;
        If that number is ever zero, then the car is towed.

        This convenience is one of the main reasons many programmers choose C# or Java over C++.
        On the other hand, many C++ programmers prefer having more control over their program.


        */

        // Before we forget, we should probably delete this pointer so that we don't leak memory ;)
        delete magazine2;
    }
    cin.get();





    return 0;   // End Program.
}