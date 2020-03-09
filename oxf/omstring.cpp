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



//## auto_generated
#include "omstring.h"
//## dependency Manager
#include "OXFManager.h"
//## dependency Unicode
#include "omunicode.h"
//## package Design::oxf::Services::String

//## class OMString
int OMString::defaultBlock = 256;

OMString::OMString(const OMString& s1) : count(0), size(0), str(0) {
    //#[ operation OMString(OMString)
    //lint -save -e668 -e613 (lint fail to identify the memory allocation by setSize())
    count = s1.count;
    setSize(count + 1);
    if (count > 0) { 
    	memcpy(str, s1.str,(unsigned int)count + 1);
    } 
    else { 
    	str[count] = '\0'; 
    }
    // lint -restore
    //#]
}

OMString::OMString(const char ch) : count(0), size(0), str(0) {
    //#[ operation OMString(char)
    count = 1;
    setSize(count + 1);
    //lint -save -e613 (lint fail to identify the memory allocation by setSize())
    str[0] = ch;
    str[count] = '\0';
    //lint -restore
    //#]
}

OMString::OMString(const char* st) : count(0), size(0), str(0) {
    //#[ operation OMString(char*)
    //lint -save  -e668 -e613 (lint fails to identify the memory allocation by setSize())
    if (st != 0) {
    	count = static_cast<int>(strlen(st));
    	setSize(count + 1);
    	if (count > 0) { 
    		memcpy(str, st, strlen(st) + 1);
    	} 
    	else { 
    		str[count] = '\0'; 
    	} 
    }
    else{
    	setSize(count + 1);
    	str[count]='\0';
    }
    //lint -restore
    //#]
}

OMString::OMString(void) : count(0), size(0), str(0) {
    //#[ operation OMString()
    setSize(1);
    //lint -save -e613 (lint fail to identify the memory allocation by setSize())
    str[0] = '\0';
    // lint -restore
    //#]
}

OMString::~OMString(void) {
    //#[ operation ~OMString()
    if (size > 0) {
    	OMDELETE(str, size);
    }
    str = NULL;
    size = 0;
    count = 0;
    //#]
}

int OMString::CompareNoCase(const char* const s2) const {
    //#[ operation CompareNoCase(char*) const
    return CompareNoCase_(str,s2);
    //#]
}

int OMString::CompareNoCase(const OMString& s2) const {
    //#[ operation CompareNoCase(OMString) const
    return CompareNoCase_(str, s2.str);
    //#]
}

void OMString::Empty(void) {
    //#[ operation Empty()
    if (count > 0)
    {
    	count = 0;
    	// lint fails to identify the correlation between count and str
    	str[count]='\0';  //lint !e613
    }
    //#]
}

char OMString::GetAt(int ind) {
    //#[ operation GetAt(int)
    char retVal = '\0';
    if (ind > -1 && ind < count)
    {
    	retVal = str[ind];
    }           
    return retVal;
    //#]
}

char* OMString::GetBuffer(int /**/) const {
    //#[ operation GetBuffer(int) const
    return str;
    //#]
}

char* OMString::GetBuffer(int newBufferSize) {
    //#[ operation GetBuffer_(int)
    resetSize(newBufferSize);
    return str;
    //#]
}

bool OMString::IsEmpty(void) const {
    //#[ operation IsEmpty() const
    return count == 0; 
    //#]
}

void OMString::ReleaseBuffer(int nNewLength) {
    //#[ operation ReleaseBuffer(int)
    if (nNewLength == -1)
    {
    	count = static_cast<int>(strlen(str));
    }
    else
    {
    	if (nNewLength <= size)
    	{
    		count = nNewLength;
    		if (count < size)
    		{
    			str[count] = '\0';
    		}
    	}
    }
    //#]
}

void OMString::SetAt(int ind, char ch) {
    //#[ operation SetAt(int,char)
    if (ind < count)
    {
    	// lint fails to identify the correlation between count and str
    	str[ind] = ch;	//lint !e613
    }
    //#]
}

//#[ ignore
// the operation is not const to comply with MFC CString
//lint -save -e1762
//#]
OMString::operator const char*(void) {
    //#[ operation operator const char*()
    return str;
    //#]
}
//#[ ignore


//lint -restore
//#]

bool OMString::operator!=(const char* c2) const {
    //#[ operation operator!=(char*) const
    return (strcmp(str, c2) != 0);  //lint !e668 (OMString::str is never NULL)
    //#]
}

bool OMString::operator!=(const OMString& s2) const {
    //#[ operation operator!=(OMString) const
    return (strcmp(str, s2.str) != 0); //lint !e668 (OMString::str is never NULL)
    //#]
}

const OMString& OMString::operator+=(const char* st) {
    //#[ operation operator+=(char*)
    if(st){
    	int newCount = count + static_cast<int>(strlen(st));
    	resetSize(newCount + 1);
    	if(str){
    		memcpy(str + count, st, strlen(st) + 1);
    		count = newCount;
    	}
    }
    return *this;
    //#]
}

const OMString& OMString::operator+=(const char ch) {
    //#[ operation operator+=(char)
    ++count;
    resetSize(count + 1);
    if(str) {
    	str[count-1] = ch;
    	str[count] = '\0';
    }
    return *this;
    //#]
}

const OMString& OMString::operator+=(const OMString& st) {
    //#[ operation operator+=(OMString)
    int newCount = count + st.count;
    resetSize(newCount + 1);
    if (str) {
    	memcpy(str + count, st.str, (unsigned int) st.count + 1);
    	count = newCount;
    }
    return *this;
    //#]
}

bool OMString::operator<(const char* c2) const {
    //#[ operation operator<(char*) const
    bool smaller = false;
    if (c2 != 0) {
    	smaller = (strcmp(str,c2) < 0); //lint !e668 (str is never NULL)
    }
    return smaller;
    //#]
}

bool OMString::operator<(const OMString& s2) const {
    //#[ operation operator<(OMString) const
    return (strcmp(str, s2.str) < 0); //lint !e668 (OMString::str is never NULL)
    //#]
}

bool OMString::operator<=(const char* c2) const {
    //#[ operation operator<=(char*) const
    bool res = false;
    if (c2 != 0) {
    	res = (strcmp(str, c2) <= 0); //lint !e668 (str is never NULL)
    }
    return res;
    //#]
}

bool OMString::operator<=(const OMString& s2) const {
    //#[ operation operator<=(OMString) const
    return (strcmp(str, s2.str) <= 0);	//lint !e668 (OMString::str is never NULL)
    //#]
}

const OMString& OMString::operator=(const char* st) {
    //#[ operation operator=(char*)
    if (st) {
    	count = static_cast<int>(strlen(st));
    	resetSize(count + 1);
    	if (str) {
    		memcpy(str, st, strlen(st) + 1);
    	}
    }
    return *this;
    //#]
}

//#[ ignore
//lint -save -e1539 (the size doesn't change only the data)

//#]
const OMString& OMString::operator=(const char ch) {
    //#[ operation operator=(char)
    count = 1;
    if (str) {
    	str[0] = ch;
    	str[count] = '\0';
    }
    return *this;
    //#]
}
//#[ ignore


//lint -restore
//#]

const OMString& OMString::operator=(const OMString& st) {
    //#[ operation operator=(OMString)
    if(str != st.str) {
    	count = st.count;
    	resetSize(count + 1);
    	if (str) {
    		memcpy(str, st.str, static_cast<unsigned int>(count) + 1);
    	}
    }
    return *this;
    //#]
}

bool OMString::operator==(const char* c2) const {
    //#[ operation operator==(char*) const
    bool res = false;
    if (c2 != 0) {
    	res = (strcmp(str, c2) == 0); //lint !e668 (str is never NULL)
    }
    return res;
    //#]
}

bool OMString::operator==(const OMString& s2) const {
    //#[ operation operator==(OMString) const
    return (strcmp(str, s2.str) == 0); //lint !e668 (str is never NULL)
    //#]
}

bool OMString::operator>(const char* c2) const {
    //#[ operation operator>(char*) const
    bool res = true;
    if (c2 != 0) {
    	res = (strcmp(str, c2) > 0); //lint !e668 (str is never NULL)
    }
    return res;
    //#]
}

bool OMString::operator>(const OMString& s2) const {
    //#[ operation operator>(OMString) const
    return (strcmp(str, s2.str) > 0);	//lint !e668 (str is never NULL)
    //#]
}

bool OMString::operator>=(const char* c2) const {
    //#[ operation operator>=(char*) const
    bool res = true;
    if (c2 != 0) {
    	res = (strcmp(str, c2) >= 0);	//lint !e668 (str is never NULL)
    }
    return res;
    //#]
}

bool OMString::operator>=(const OMString& s2) const {
    //#[ operation operator>=(OMString) const
    return (strcmp(str, s2.str) >= 0);	//lint !e668 (str is never NULL)
    //#]
}

char OMString::operator[](int ind) const {
    //#[ operation operator[](int) const
    return str[ind];
    //#]
}

void OMString::resetSize(int newSize) {
    //#[ operation resetSize(int)
    // Do we need to allocate new memory
    if (size < newSize) {
    	// retain a pointer to the actual data
    	char* oldStr = str;
    	// allocate the new memory
    	int oldSize = size;
    	setSize(newSize);
    	// copy the actual data to the new location
    	if (str && oldStr) {
    		memcpy(str,oldStr, (unsigned int)oldSize);
    	}
    	// free memory used by the old location
    	OMDELETE(oldStr, oldSize);
    }
    //#]
}

int OMString::CompareNoCase_(const char* const s1, const char* const s2) {
    //#[ operation CompareNoCase_(char*,char*)
    // res = 3 - unknown
    int res = 3;
    if ((s1 != 0) && (s2 != 0)) {
    	for (int i = 0; res == 3; i++) {
    #ifndef _OM_UNICODE_ONLY
    		char d1 = (char)toupper(s1[i]);
    		char d2 = (char)toupper(s2[i]);
    #else
    		char d1 = (char)OMtoupper(s1[i]);
    		char d2 = (char)OMtoupper(s2[i]);
    #endif // _OM_UNICODE_ONLY
    		if (d1 < d2) {
    			res = -1;
    		}
    		else if (d1 > d2) {
    			res = 1;
    		}
    		else if (d1 == '\0') {
    			res = 0;
    		}
    	}
    }
    return res;
    //#]
}

void OMString::setSize(int newSize) {
    //#[ operation setSize(int)
    
    // Round size up to the nearest stringBlock
    size = (newSize / defaultBlock) * defaultBlock;
    if (newSize > size) {
    	size += defaultBlock;
    }
    // Actually allocate the memory
    //lint -save -e119 (lint fail to find the replacement operator new[] )
    str = OMNEW(char, size);
    //lint -restore
    //#]
}

int OMString::GetLength(void) const {
    return count;
}

int OMString::getDefaultBlock(void) {
    return defaultBlock;
}

void OMString::setDefaultBlock(int p_defaultBlock) {
    defaultBlock = p_defaultBlock;
}

int OMString::getSize(void) const {
    return size;
}

char* OMString::getStr(void) const {
    return str;
}

//## operation operator!=(char*,OMString)
bool operator!=(const char* c1, const OMString& s2) {
    //#[ operation operator!=(char*,OMString)
    return (strcmp(c1, s2.GetBuffer(0)) != 0);
    //#]
}

//## operation operator+(OMString,OMString)
OMString operator+(const OMString& s1, const OMString& s2) {
    //#[ operation operator+(OMString,OMString)
    OMString res(s1);
    res += s2;
    return res; 
    //#]
}

//## operation operator+(OMString,char*)
OMString operator+(const OMString& s1, const char* s2) {
    //#[ operation operator+(OMString,char*)
    OMString res(s1);
    res += s2;
    return res; 
    //#]
}

//## operation operator+(char*,OMString)
OMString operator+(const char* s1, const OMString& s2) {
    //#[ operation operator+(char*,OMString)
    OMString res(s1);
    res += s2;
    return res;
    //#]
}

//## operation operator+(OMString,char)
OMString operator+(const OMString& str, const char ch) {
    //#[ operation operator+(OMString,char)
    OMString res(str);
    res += ch;
    return res;
    //#]
}

//## operation operator<(char*,OMString)
bool operator<(const char* c1, const OMString& s2) {
    //#[ operation operator<(char*,OMString)
    return (strcmp(c1,s2.GetBuffer(0)) < 0);
    //#]
}

//## operation operator<=(char*,OMString)
bool operator<=(const char* c1, const OMString& s2) {
    //#[ operation operator<=(char*,OMString)
    return (strcmp(c1,s2.GetBuffer(0)) <= 0);
    //#]
}

//## operation operator==(char*,OMString)
bool operator==(const char* c1, const OMString& s2) {
    //#[ operation operator==(char*,OMString)
    return (strcmp(c1,s2.GetBuffer(0)) == 0);
    //#]
}

//## operation operator>(char*,OMString)
bool operator>(const char* c1, const OMString& s2) {
    //#[ operation operator>(char*,OMString)
    return (strcmp(c1,s2.GetBuffer(0)) > 0);
    //#]
}

//## operation operator>=(char*,OMString)
bool operator>=(const char* c1, const OMString& s2) {
    //#[ operation operator>=(char*,OMString)
    return (strcmp(c1,s2.GetBuffer(0)) >= 0);
    //#]
}




