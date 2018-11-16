//*************************************************************************************
/*  File:  yastr.h
 *    This is a simple example of how C++ classes are used. It is part of an ME507
 *    course assignment. The name 'yastr' is short for 'yet another string.' This is
 *    NOT a string class which should be used for any practical purpose; it is only a
 *    demonstration of C++ classes to be used for educational purposes.
 *
 *  Revisions:
 *    01-17-2013 JRR Original file
 *    01-18-2013 JRR Added a couple of checks for NULL pointer that should be there
 *    11-04-2018 JRR Changed to suit the new ME507 course
 *
 *  Usage:
 *    This file is intended to be compiled and run on some sort of desktop or laptop
 *    computer using the GCC compiler on Windows Vista/7/8/10(tm) or better (such as
 *    Linux, Unix, or Mac).
 *
 *    A simple Makefile is provided. You first need to run 'make', then run the
 *    compiled program by typing './yastr' in the terminal -- and that's it.
 *
 *  License:
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


/** The maximum length for a yet-another-string object, defined so that nobody can
 *  create a string holding War and Peace. It's legal, the copyright having expired
 *  long ago, but an awfully silly thing to do. */
const uint16_t MAX_YASTR_LENGTH = 1000;


//-------------------------------------------------------------------------------------
/** @brief   A basic parent class for yet-another-strings.
 *  @details This parent class encapsulates basic functionality of yet another string
 *           including the ability to mess with capitalization and print itself out.
 */

class yastr
{
protected:
	char* p_buffer;                         // Pointer to character storage buffer

public:
	yastr (void);                           // Default constructor creates empty string
	yastr (const char*);                    // Constructor initializes string contents

	/** @brief   Get the address of the buffer which holds the string.
     *  @details This method is declared @e inline, Java(tm) style. It returns the
     *           address of the buffer that holds the characters in the string. Because
     *           of the word @c const, the pointer which is returned cannot (without
     *           special tricks) be used to write anything to the buffer; it can only
     *           be used by the calling function to read characters in the string.
	 *           As this method is implemented here, it need not be in the C_++ file.
     *  @return  A pointer to the buffer which holds the yet-another-string's contents
	 */
	const char* get_buffer (void)
	{
		return (p_buffer);
	}
	void CAPITALIZE (void);                 // Change string to ALL UPPERCASE
	void Capitalize (void);                 // Change string to Leading Uppercase Only
	virtual void reverse (void);       // Reverse letters in a string...if written
};
/** @brief   Print a yet-another-string on a stream.
 *  @details This overloaded shift-happens operator prints out a @c yastr object to an
 *           ostream. @c ostream is the type of class which @c emstream partly imitates
 *           on microcontrollers.
 */
ostream& operator << (ostream&, yastr&);

class cryptostr: public yastr
{
public:
	cryptostr(void);					// constructor
	cryptostr(const char*);
	//need a constructor that works
	void rot13(void);
	void table(ostream&);
};
