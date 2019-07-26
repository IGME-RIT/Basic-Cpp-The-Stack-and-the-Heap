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

// Includes
#include "gun.h"
#include <iostream>

// This is the constructor definition for the magazine type.
Magazine::Magazine(int bulletsinitial, int bulletsCapacity) :
    bullets(bulletsinitial),    // :memberName(parameterName) initializes the members of the magazine using the values
    capacity(bulletsCapacity)   // passed in as parameters. This is called an initializer list.
{
    bullets = bulletsinitial;   // It's also possible to initialize members like this.
    capacity = bulletsCapacity; // Using both styles is redundant.
}

// The destructor definition for magazine.
Magazine::~Magazine()
{
    // Any code that you want to happen before an object is erased from memory will happen here.
    std::cout << "Magazine destructor." << std::endl;
}

// This is the constructor definition for the gun class.
Gun::Gun(Magazine* m) : mag(m)
{
    // If you remove the : mag(m), the compiler will error, saying that Magazine doesn't have a default constructor.

    // By default all classes and structs have a constructor that just creates an empty object with no parameters.
    // That constructor is secretly called whenever you declare an object of that type.
    // When a constructor is defined, the compiler can't create the object without the correct parameters.

    // Even if you try to initialize it in the body of the constructor instead, it won't work.
    // That's because anything not in the initializer list automatically has it's default constructor called first.
    std::cout << "Gun Created: " << mag->bullets << "/" << mag->capacity << std::endl;
}

// Definition for the gun destructor.
Gun::~Gun()
{
    // Similarly to the constructor, the gun destructor will do things without telling you.
    // Since the gun contains a magazine object, it will also call the magazines destructor as part of it's own destructor.
    std::cout << "Gun destructor" << std::endl;
}

// Function defintion for firing the gun:
void Gun::Fire()
{
    if (IsLoaded())
    {
        // If there are bullets, fire the gun.
        std::cout << "BANG!" << std::endl;
        mag->bullets--;
    }
    else
    {
        // If there are no bullets, click instead.
        std::cout << "click" << std::endl;
    }
}

// Reloads the magazine.
void Gun::Reload()
{
    std::cout << "Reload" << std::endl;
    mag->bullets = mag->capacity;
}


// Returns true if the magazine has more than 0 bullets.
bool Gun::IsLoaded()
{
    return mag->bullets > 0;
}

