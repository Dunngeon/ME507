//*************************************************************************************
/** @file F18hw2.cpp
 *  @mainpage
 *    This is the starting code for an ME507 programming homework assignment. 
 *
 *  @b Usage
 *    This file is intended to be compiled on some sort of desktop or laptop computer
 *    using the GCC compiler. GCC is installed on the Windows(tm) computers in the lab,
 *    and it can be installed on Windows Vista Service Pack 7, 8, or 10 (see
 *    @c http://www.cygwin.com/ and note that Cygwin is a large set of programs).
 *    GCC is native on Linux, though you may have to run "sudo apt-get build-essential"
 *    to make sure you have all the right tools on your computer. On Mac OSX computers,
 *    you can use Homebrew; see @c https://discussions.apple.com/thread/8336714 for 
 *    some help. 
 * 
 *    This code should be compiled and run from a command line such as a regular
 *    terminal in Linux or a Cygwin console in Windows(tm). Type the following command
 *    to compile the program:
 *    @code{.bash}
 *    g++ F18hw2.cpp -Wall -Wextra -o run_this
 *    @endcode
 *    When the code has been compiled, typing "./run_this" will run it. Note that when 
 *    you have successfully completed the assignment, the compiler warnings will have 
 *    gone away. 
 *
 *  @b License
 *    This file is copyright 2018 by JR Ridgely and released under the Lesser GNU 
 *    Public License, version 3. It intended for educational use only, but its use
 *    is not limited thereto. Although, what else would one ever do with it? 
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

#include <iostream>


// We don't need these namespace things with most microcontrollers, but with PC 
// programs we often do. This is the standard input/output namespace, which gives us 
// 'cout.' The ME405 serial device library (based on class emstream) imitates 'cout' 
// and similar stuff, and you get to name the output stream.
using namespace std;


//-------------------------------------------------------------------------------------
/** @brief   Dump a readable view of an array to an output stream.
 *  @details This method displays a semi-human-readable printout showing the contents
 *           of an array of unsigned 16-bit integers to the given stream. 
 *  @param   size The number of elements (not bytes) in the array.
 *  @param   p_array A pointer to the array.
 *  @param   stream A reference to the stream object on which text will be "printed."
 *           If this parameter is not supplied, it defaults to @c cout, which is the
 *           standard output console such as the terminal in which a program is run.
 */

void array_dump (uint16_t size, uint16_t* p_array, ostream& stream = cout)
{
    // ---------------------------MY CODE---------------------------------------
	stream << "Array of 25 uint16_t at address " << &p_array << endl;
	// print column header of table
	
	stream.width(7);
	stream << " ";
	for(int y=0;y<10;y++)
	{
		stream.width(7);
		stream << y << ":";
	}
	stream << endl;
	
	// print column line seperator
	stream.width(7);
	stream << " ";	//prints blank space offset
	for(int y=0;y<10;y++)
	{
		stream.width(8);
		stream << "---";
	}
	stream << endl;
	
	// Print horizontal headers and data, 10 entries per line
	uint16_t ite_count = 0; // declared in function scope to avoid reset in for loop
	for(uint16_t y=0; y< ((size / 10)+1);y++)
	{	
		stream.width(6);
		stream << y*10 << ":"; // prints row header
		for(uint16_t y1=0;y1<10 ;y1++,ite_count++,p_array++)
		{
			if( ite_count>=size)
			{
				break; //stops loop when iteration count reaches the size of the array
			}
			stream.width(8);
			stream << *p_array; //prints the data p_array is pointing at
		}
		stream << endl;
	}
}



//-------------------------------------------------------------------------------------
/** @brief   Dump a readable view of an array to an output stream.
 *  @details This method displays a semi-human-readable printout showing the contents
 *           of an array of signed 16-bit integers to the given stream. 
 *  @param   size The number of elements (not bytes) in the array.
 *  @param   p_array A pointer to the array.
 *  @param   stream A reference to the stream object on which text will be "printed."
 *           If this parameter is not supplied, it defaults to @c cout, which is the
 *           standard output console such as the terminal in which a program is run.
 */

void array_dump (uint16_t size, int16_t* p_array, ostream& stream = cout)
{
	stream << "Array of 25 int16_t at address " << &p_array << endl;
	// print column header of table
	
	stream.width(7);
	stream << " ";
	for(int y=0;y<10;y++)
	{
		stream.width(7);
		stream << y << ":";
	}
	stream << endl;
	
	// print column line seperator
	stream.width(7);
	stream << " ";	//prints blank space offset
	for(int y=0;y<10;y++)
	{
		stream.width(8);
		stream << "---";
	}
	stream << endl;
	
	// Print horizontal headers and data, 10 entries per line
	uint16_t ite_count = 0; // declared in function scope to avoid reset in for loop
	for(uint16_t y=0; y< ((size / 10)+1);y++)
	{	
		stream.width(6);
		stream << y*10 << ":"; // prints row header
		for(uint16_t y1=0;y1<10 ;y1++,ite_count++,p_array++)
		{
			if( ite_count>=size)
			{
				break; //stops loop when iteration count reaches the size of the array
			}
			stream.width(8);
			stream << *p_array; //prints the data p_array is pointing at
		}
		stream << endl;
	}
}



//=====================================================================================
// To compile functions above without the test code in main(), put -DNOT_MAIN in the
// g++ command line. This is similar to the "if __name__ == '__main__':" in Python
#ifndef NOT_MAIN

/** @brief   This is the main routine which runs when the program is started.
 *  @details As the main routine, it sets things up and then calls your functions. 
 *           This particular @c main() tests code in the rest of the program. 
 */

int main ()
{
    const uint16_t ARRAY_SIZE = 75;
    cout << "Creating arrays of size " << ARRAY_SIZE << endl;
	
    uint16_t unsigned_array[ARRAY_SIZE];
    int16_t signed_array[ARRAY_SIZE];

    for (uint16_t index = 0; index < ARRAY_SIZE; index++)
    {
        unsigned_array[index] = index * index;
        signed_array[index] = -index * index;
    }

    array_dump (ARRAY_SIZE, unsigned_array);
    cout << endl;
    array_dump (ARRAY_SIZE, signed_array);
}

#endif // NOT_MAIN
