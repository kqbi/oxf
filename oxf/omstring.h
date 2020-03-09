//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMString
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.


#ifndef omstring_H
#define omstring_H

//## dependency DllMacros
#include "rp_framework_dll_definition.h"
//## dependency omiotypes
#include "omiotypes.h"
//## dependency SelectiveInclude
//#[ ignore
#ifdef ANIM_USE_IOSTREAM
#ifndef OM_ENABLE_STRING_SERIALIZATION
#define OM_ENABLE_STRING_SERIALIZATION
#endif // OM_ENABLE_STRING_SERIALIZATION
#endif // ANIM_USE_IOSTREAM

#ifdef OM_ENABLE_STRING_SERIALIZATION
#ifndef OM_FORCE_IOSTREAM
#define OM_FORCE_IOSTREAM
#endif // !OM_FORCE_IOSTREAM
#endif // OM_ENABLE_STRING_SERIALIZATION
//#]
#include "OXFSelectiveInclude.h"
//## package Design::oxf::Services::String

//## class OMString
//#[ ignore
// Global string functions that complete the OMString class definition
//#]

// A string class, supports the same API as CString.
class RP_FRAMEWORK_DLL OMString {
    ////    Constructors and destructors    ////
    
public :

    // Initialize a string based on another string
    // Argument const OMString& s1 :
    // The source string
    //## operation OMString(OMString)
    OMString(const OMString& s1);
    
    // Initialize a string based on a single character
    // Argument const char ch :
    // The character
    //## operation OMString(char)
    OMString(const char ch);
    
    // Initialize a string based on another string (C style)
    // Argument const char* st :
    // The C string
    //## operation OMString(char*)
    OMString(const char* st);
    
    // Initialize an empty string
    //## operation OMString()
    OMString(void);
    
    // Cleanup
    //## operation ~OMString()
    ~OMString(void);
    
    ////    Operations    ////
    
    // No case compare
    // Argument const char* const s2 :
    // The string to compare with
    //## operation CompareNoCase(char*) const
    int CompareNoCase(const char* const s2) const;
    
    // No case compare
    // Argument const OMString& s2 :
    // The string to compare with
    //## operation CompareNoCase(OMString) const
    int CompareNoCase(const OMString& s2) const;
    
    // empty the string
    //## operation Empty()
    void Empty(void);
    
    // get a character at a given position
    // Argument int ind :
    // The index
    //## operation GetAt(int)
    char GetAt(int ind);
    
    // get the string buffer
    // Argument int /**/ :
    // dummy
    //## operation GetBuffer(int) const
    char* GetBuffer(int /**/) const;
    
    // get the string buffer, readjusting its size.
    // Argument int newBufferSize :
    // The new buffer minimal size
    //## operation GetBuffer_(int)
    char* GetBuffer(int newBufferSize);
    
    // check if string is empty
    //## operation IsEmpty() const
    bool IsEmpty(void) const;
    
    // Release buffer sets the count value. It must be called before any use of string, if GetBuffer was used for direct change.
    // Argument int nNewLength = -1 :
    // The new string count. It can be called without argument, if buffer string ends with null character.
    //## operation ReleaseBuffer(int)
    void ReleaseBuffer(int nNewLength = -1);
    
    // set a character at a given position
    // Argument int ind :
    // The index
    // Argument char ch :
    // The character
    //## operation SetAt(int,char)
    void SetAt(int ind, char ch);
    
    // cast operator
    //## operation operator const char*()
    operator const char*(void);
    
    // not equal test with a C string
    // Argument const char* c2 :
    // The C string
    //## operation operator!=(char*) const
    bool operator!=(const char* c2) const;
    
    // not equal test with a string
    // Argument const OMString& s2 :
    // The string
    //## operation operator!=(OMString) const
    bool operator!=(const OMString& s2) const;
    
    // Add a C style string to the end of this string
    // Argument const char* st :
    // The string
    //## operation operator+=(char*)
    const OMString& operator+=(const char* st);
    
    // Add a character to the end of this string
    // Argument const char ch :
    // The character
    //## operation operator+=(char)
    const OMString& operator+=(const char ch);
    
    // Add a string to the end of this string
    // Argument const OMString& st :
    // The string
    //## operation operator+=(OMString)
    const OMString& operator+=(const OMString& st);
    
    // Less than test
    // Argument const char* c2 :
    // The context string
    //## operation operator<(char*) const
    bool operator<(const char* c2) const;
    
    // Less than test
    // Argument const OMString& s2 :
    // The context
    //## operation operator<(OMString) const
    bool operator<(const OMString& s2) const;
    
    // Less than or equal to test
    // Argument const char* c2 :
    // The context
    //## operation operator<=(char*) const
    bool operator<=(const char* c2) const;
    
    // Less than or equal to test
    // Argument const OMString& s2 :
    // The context
    //## operation operator<=(OMString) const
    bool operator<=(const OMString& s2) const;
    
    // Assign the specified string as the value of this string
    // Argument const char* st :
    // The context
    //## operation operator=(char*)
    const OMString& operator=(const char* st);
    
    // Assign the specified character as the value of this string
    // Argument const char ch :
    // The context
    //## operation operator=(char)
    const OMString& operator=(const char ch);
    
    // Assign the specified string as the value of this string
    // Argument const OMString& st :
    // The context
    //## operation operator=(OMString)
    const OMString& operator=(const OMString& st);
    
    // Compare this string with the specified string
    // Argument const char* c2 :
    // The context
    //## operation operator==(char*) const
    bool operator==(const char* c2) const;
    
    // Compare this string with the specified string
    // Argument const OMString& s2 :
    // The context
    //## operation operator==(OMString) const
    bool operator==(const OMString& s2) const;
    
    // Greater than test
    // Argument const char* c2 :
    // The context
    //## operation operator>(char*) const
    bool operator>(const char* c2) const;
    
    // Greater than test
    // Argument const OMString& s2 :
    // The context
    //## operation operator>(OMString) const
    bool operator>(const OMString& s2) const;
    
    // Greater than or equal to test
    // Argument const char* c2 :
    // The context
    //## operation operator>=(char*) const
    bool operator>=(const char* c2) const;
    
    // Greater than or equal to test
    // Argument const OMString& s2 :
    // The context
    //## operation operator>=(OMString) const
    bool operator>=(const OMString& s2) const;
    
    // return the character at the given position
    // Argument int ind :
    // The index
    //## operation operator[](int) const
    char operator[](int ind) const;
    
    // give string a new larger size
    // and copy contents to it.
    // Argument int newSize :
    // The new buffer minimal size
    //## operation resetSize(int)
    void resetSize(int newSize);
    

private :

    // No case compare
    // Argument const char* const s1 :
    // The source string
    // Argument const char* const s2 :
    // The string to compare with
    //## operation CompareNoCase_(char*,char*)
    static int CompareNoCase_(const char* const s1, const char* const s2);
    
    // allocate the string buffer
    // Argument int newSize = defaultBlock :
    // The new buffer minimal size
    //## operation setSize(int)
    void setSize(int newSize = defaultBlock);
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    int GetLength(void) const;
    
    //## auto_generated
    static int getDefaultBlock(void);
    
    //## auto_generated
    static void setDefaultBlock(int p_defaultBlock);
    

private :

    //## auto_generated
    int getSize(void) const;
    
    //## auto_generated
    char* getStr(void) const;
    
    ////    Attributes    ////
    
    // How many chars we currently have (without the '\0')
    int count;		//## attribute count
    
    // the string default size
    // need to be declared before used (in this file) to avoid compilation issues in some compilers
    static int defaultBlock;		//## attribute defaultBlock
    
    // The current allocated memory
    int size;		//## attribute size
    
    // Pointer to actual string
    char* str;		//## attribute str
    
};

// Instrumentation support, convert a char* to an OMString
// Argument char* ch :
// The source string
// Argument OMString& /* dummy */ :
// A dummy argument to match a template function and enable specialization
//## operation OMDestructiveString2X(char*,OMString)
//#[ ignore
//lint -save -e818 (parameter could be declared as pointing to const)

//#]
inline OMString OMDestructiveString2X(char* ch, OMString& /* dummy */) {
    //#[ operation OMDestructiveString2X(char*,OMString)
    OMString t1(ch);
    return t1;
    //#]
}
//#[ ignore

//lint -restore
//#]

// ostream << OMString operator
// Argument omostream& oStream :
// the output stream
// Argument const OMString& str :
// The input string
//## operation operator <<(omostream,OMString)
//#[ ignore
#ifdef USE_IOSTREAM
//#]
inline omostream& operator <<(omostream& oStream, const OMString& str) {
    //#[ operation operator <<(omostream,OMString)
    oStream << str.GetBuffer(0);
    return oStream;
    //#]
}
//#[ ignore
#endif // USE_IOSTREAM
//#]

// iostream >> OMString operator
// Argument omistream& iStream :
// The input stream
// Argument OMString& str :
// The output string
//## operation operator >>(omistream,OMString)
//#[ ignore
#ifdef USE_IOSTREAM
//#]
inline omistream& operator >>(omistream& iStream, OMString& str) {
    //#[ operation operator >>(omistream,OMString)
    // ThiStream implementation was struild to mimic the ">>" operation
    // of char *
    str.Empty();
    for ( ; ; )
    {
    	char c;
    	(void)iStream.get(c);
    	if (isspace(c) || iStream.eof())
    	{
    		return iStream;
    	}
    	str += c;
    } 
    //#]
}
//#[ ignore
#endif // USE_IOSTREAM
//#]

// not equal test
// Argument const char* c1 :
// The source
// Argument const OMString& s2 :
// Compared string
//## operation operator!=(char*,OMString)
bool operator!=(const char* c1, const OMString& s2);

// Add stings
// Argument const OMString& s1 :
// A string to add
// Argument const OMString& s2 :
// A string to add
//## operation operator+(OMString,OMString)
OMString operator+(const OMString& s1, const OMString& s2);

// Add stings
// Argument const OMString& s1 :
// A string to add
// Argument const char* s2 :
// A string to add
//## operation operator+(OMString,char*)
OMString operator+(const OMString& s1, const char* s2);

// Add stings
// Argument const char* s1 :
// The C string
// Argument const OMString& s2 :
// The OMString
//## operation operator+(char*,OMString)
OMString operator+(const char* s1, const OMString& s2);

// Add a sting and a character
// Argument const OMString& str :
// A string to add
// Argument const char ch :
// The character
//## operation operator+(OMString,char)
OMString operator+(const OMString& str, const char ch);

// Less than compare C string to an OMString
// Argument const char* c1 :
// The C string source
// Argument const OMString& s2 :
// The string to compare with
//## operation operator<(char*,OMString)
bool operator<(const char* c1, const OMString& s2);

// Less than or equal to compare C string to an OMString
// Argument const char* c1 :
// The C string source
// Argument const OMString& s2 :
// The string to compare with
//## operation operator<=(char*,OMString)
bool operator<=(const char* c1, const OMString& s2);

// Equal to compare C string to an OMString
// Argument const char* c1 :
// The C string source
// Argument const OMString& s2 :
// The string to compare with
//## operation operator==(char*,OMString)
bool operator==(const char* c1, const OMString& s2);

// Greater than compare C string to an OMString
// Argument const char* c1 :
// The C string source
// Argument const OMString& s2 :
// The string to compare with
//## operation operator>(char*,OMString)
bool operator>(const char* c1, const OMString& s2);

// Greater than or equal to compare C string to an OMString
// Argument const char* c1 :
// The C string source
// Argument const OMString& s2 :
// The string to compare with
//## operation operator>=(char*,OMString)
bool operator>=(const char* c1, const OMString& s2);

#endif



