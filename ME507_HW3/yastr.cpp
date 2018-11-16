//*************************************************************************************
/** @file yastr.cpp
 *    This is a simple example of how C++ classes are used. It is part of an ME507
 *    course assignment. The name 'yastr' is short for 'yet another string.' This is
 *    NOT a string class which should be used for any practical purpose; it is only a
 *    demonstration of C++ classes to be used for educational purposes.
 *
 *  @b Revisions:
 *    01-17-2013 JRR Original file
 *    01-18-2013 JRR Added a couple of checks for NULL pointer that should be there
 *    11-04-2018 JRR Changed to suit the new ME507 course
 *
 *  @b Usage:
 *    This file is intended to be compiled and run on some sort of desktop or laptop
 *    computer using the GCC compiler on Windows Vista/7/8/10(tm) or better (such as
 *    Linux, Unix, or Mac).
 *
 *    A simple Makefile is provided. You first need to run 'make', then run the
 *    compiled program by typing './yastr' in the terminal -- and that's it.
 *
 *  @b License:
 *    This file is copyright 2018 by JR Ridgely and released under the Lesser GNU
 *    Public License, version 3. It intended for educational use only, but its use
 *    is not limited thereto, except by the fact that it's not really useful for
 *    anything else, so nobody in his right (or left) mind would try to use it.
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUEN-
 *    TIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
//*************************************************************************************

#include <stdlib.h>                         // These are standard C/C++ libraries
#include <string.h>
#include <stdint.h>
#include <iostream>

// This namespace is needed to use I/O streams on a PC but not on a microcontroller
using namespace std;

#include "yastr.h"                          // Include header file for this project


//-------------------------------------------------------------------------------------
/** @brief   Create an empty yet-another-string object.
 *  @details This constructor creates an empty string. The string's emptiness is
 *           indicated by the fact that the character buffer isn't there and the
 *           pointer to the character buffer has the value NULL, which means it
 *           doesn't point to anything.
 */

yastr::yastr (void)
{
    p_buffer = NULL;                        // Set the buffer pointer to NULL
}


//-------------------------------------------------------------------------------------
/** @brief   Create a string and fill it with text from the given string.
 *  @details This constructor creates a string whose contents are set to the contents
 *           of the character array given in its parameter. The @c new operator is used
 *           each time a string is created; this is good practice on a PC with its
 *           fancy-schmancy memory manager, but usually lousy practice on an embedded
 *           microcontroller with its very small RAM and real-time constraints that
 *           should not interact with memory managers. The @c const in front of
 *           @c char* means that the parameter @c newstr cannot be used to alter the
 *           contents of the string to which it points (you might try to do this,
 *           changing one of the characters in the string given by @c newstr, and
 *           seeing what happens).
 *  @param   newstr An array containing the characters to go into the string
 */

yastr::yastr (const char* newstr)
{
    // Check that the length of the string isn't outside the range of reasonable values
    if (strlen (newstr) > MAX_YASTR_LENGTH)
    {
        cout << "Phooey! String too long for yet another string to hold" << endl;
        return;
    }

    // First allocate memory to hold this object's copy of the characters in the string
    p_buffer = new char[strlen (newstr)];

    // Make sure that the memory allocation was successful; if not, complain
    if (p_buffer == NULL)
    {
        cout << "Oh Noes! Can't allocate memory for yet another string" << endl;
    }
    else
    {
        strcpy (p_buffer, newstr);          // Oh good, things are OK if we get here
    }
}


//-------------------------------------------------------------------------------------
/** @brief   Convert all letters in a string to uppercase.
 *  @details This method converts all the letters in the string which are lowercase to
 *           uppercase. If not dealing with lowercase ASCII letters, this method leaves
 *           them as they have been. Funny thing: 'A' - 'a' is actually a negative
 *           number, but everything works anyway.
 */

void yastr::CAPITALIZE (void)
{
	for (uint16_t index = 0; index < strlen (p_buffer); index++)
	{
		if (p_buffer[index] >= 'a' && p_buffer[index] <= 'z')
		{
			p_buffer[index] += 'A' - 'a';
		}
	}
}


//-------------------------------------------------------------------------------------
/** @brief   Convert the first letters in words in this string to uppercase.
 *  @details This method converts only the letters in the string which are at the
 *           beginnings of words from lowercase to uppercase, if those letters are in
 *           lowercase to begin with.
 */

void yastr::Capitalize (void)
{
	// Seems as if we need to handle the first letter in the string specially
	if (p_buffer[0] >= 'a' && p_buffer[0] <= 'z')
	{
		p_buffer[0] += 'A' - 'a';
	}

	char prev_ch = p_buffer[0];             // Previous character found in the string

	// Now go through the rest of the string, looking for lowercase letters at the
	// beginnings of words which can be converted to uppercase. The beginning of a
	// word is defined as a character which follows a space, tab, or return character.
	// If the string is only one printable character long, nothing in this loop runs
	for (uint16_t index = 1; index < strlen (p_buffer); index++)
	{
		if (p_buffer[index] >= 'a' && p_buffer[index] <= 'z' && p_buffer
		   && (prev_ch == ' ' || prev_ch == '\t' || prev_ch == '\r' || prev_ch == '\n')
		)
		{
			p_buffer[index] += 'A' - 'a';
		}

		prev_ch = p_buffer[index];          // This will be previous char. next time
	}
}

//-------------------------------------------------------------------------------------
/** @brief Reverses the string in object
 * @details To come
 * @param *to come
 * @return void
 */

 void yastr::reverse (void)
 {
   uint8_t length = strlen(p_buffer);
   uint8_t c, i , j;
   for(i=0, j=length - 1;i<j;i++,j--)
   {
     c = p_buffer[i];
     p_buffer[i]=p_buffer[j];
     p_buffer[j]=c;
   }
 }
cryptostr::cryptostr(void) //child class no string constructor
    : yastr()
    {

    }

cryptostr::cryptostr(const char* p_buffer) //child class string constructor
    : yastr(p_buffer)
    {

    }

void cryptostr::rot13(void)
{
    for(uint16_t index =0; index < strlen(p_buffer);index++)
    {
        if(p_buffer[index] >= 'A' && p_buffer[index] <= 'Z') //check if letter is capital
        {
            if((p_buffer[index] + 13) > 'Z') //check if adding 13 caused *p_buffer to be greater than Z
            {
                p_buffer[index] = p_buffer[index] + 13 - 26; // if so, subtract 26 to make it a valid capital letter
            }
            else
            {
            p_buffer[index] = p_buffer[index] + 13; // if not too large, just add 13
            }

        }
    }
}

void cryptostr::table(ostream& stream = cout)
{
    for(uint16_t index = 65; index <= 90;index++) // create table of capital letters
    {
        uint8_t count = 0;
        for(uint16_t index2=0; index2 < strlen(p_buffer) ;index2++)
        {
            //stream << index2 << " " << p_buffer[index2] << endl;
            if(p_buffer[index2] == char(index))
            {
                count++;
            }
        }
        //stream << char(index) << " " << count << endl;
        stream << "    " << char(index) << " "<< int(count) << endl;
    }
    for(uint16_t index = 97; index <= 122;index++) // create table of lowercase letters
    {
        uint8_t count = 0;
        for(uint16_t index2=0; index2 < strlen(p_buffer) ;index2++)
        {
            //stream << index2 << " " << p_buffer[index2] << endl;
            if(p_buffer[index2] == char(index))
            {
                count++;
            }
        }
        //stream << char(index) << " " << count << endl;
        stream << "    " << char(index) << " "<< int(count) << endl;
    }
}
//-------------------------------------------------------------------------------------
/** @brief   Shift operator which prints a @c yastr to a stream.
 *  @details This overloaded shifty operator prints a @c yastr string to an output
 *           stream such as the commonly used @c cout on regular PC type computers.
 *  @param   strm The stream to which the string is to be printed
 *  @param   yazzy The yet-another-string which will be printed to the stream
 *  @return  A reference to the stream on which the string was printed; this reference
 *           is used if something else is printed on the same line with another "<<"
 */

ostream& operator << (ostream& strm, yastr& yazzy)
{
	if (yazzy.get_buffer () != NULL)
	{
		strm << yazzy.get_buffer ();
	}

	return (strm);
}


//-------------------------------------------------------------------------------------
/** @brief   Test a @c yastr string.
 *  @details This function (just a regular C-style function, not a method belonging to
 *           any class) tests the functions belonging to class yastr or one of its
 *           descendants by calling the tested methods and printing out the results.
 *  @param   p_str A pointer to a @c yastr string object; this pointer can also contain
 *           the address of a descendent of class @c yastr, which works just as well.
 */

void yastr_test (yastr* p_str)
{
	cout << "Tests of yastr" << endl;
	cout << "  Original string:  " << *p_str << endl;
	p_str->Capitalize ();
	cout << "  Capitalized:      " << *p_str << endl;
	p_str->reverse ();
	cout << "  Reversed...?:     " << *p_str << endl;
	cout << "  Done." << endl << endl;
}

void cryptostr_test (cryptostr* p_str)
{
    cout << "Tests of cryptostr" << endl;
    cout << " OG String: " << *p_str << endl;
    p_str->rot13();
    cout << " Rot13ed " << *p_str << endl;
    p_str->rot13();
    cout << " Double rot13ed " << *p_str << endl;
    cout << " Done with rot13" << endl;
    cout << " making da tabley table" << endl;
    p_str->table();
    cout << " Now we really done yo!" << endl;
}

//-------------------------------------------------------------------------------------
/** This is the entry point of the program, where the user's code begins running.
 */

#ifndef NOT_MAIN // Compiling of this main() can be turned off for testing

int main ()
{
	// Create a string object, returning the result as a simple reference to the string
	// which has been created
	yastr empty;

	// Create another string object, returning a pointer to the string just created.
	// The pointer can be passed to functions or classes that do something with the
	// string to which the pointer points
	yastr* p_name = new yastr ("terrence trianglepants 0123");

	// Print the pointer (i.e. the memory address), then the string at that address
	cout << "[" << p_name << "]:   " << *p_name << endl;

	// For a little fun (and I do mean a little), run a series of functions and tests
	yastr_test (p_name);

    // test cryptostr class
    cryptostr* p_names = new cryptostr ("UpPeR CaSeZ");
    cout << "[" << p_names << "]:   " << *p_names << endl;
    cryptostr_test (p_names);
    //cryptostr* p_names->table(cout);
}

#endif // NOT_MAIN
