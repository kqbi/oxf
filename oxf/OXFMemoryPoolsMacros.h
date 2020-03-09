//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: MemoryPoolsMacros
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


#ifndef OXFMemoryPoolsMacros_H
#define OXFMemoryPoolsMacros_H

//## package Design::oxf::Services::Macros::MemoryPoolsMacros


//#[ ignore
// Memory pools declaration/implementation macros
//#]

// The framework memory pool static initializer definition
//#[ type DECLARE_STATIC_MEMORY_INITIALIZATION
#ifdef OM_USE_STATIC_MEMORY_POOL_INITIALIZATION
#define DECLARE_STATIC_MEMORY_INITIALIZATION(CLASSNAME,INITNUM) \
		static OMSelfLinkedMemoryAllocator<CLASSNAME,INITNUM>* allocatorRef;
#else
#define DECLARE_STATIC_MEMORY_INITIALIZATION(CLASSNAME,INITNUM)	
#endif  // OM_USE_STATIC_MEMORY_POOL_INITIALIZATION

//#]

// The memory pool is initialized when the  myOMMemoryAllocator() function is called.
// If user wants to use static initialization of memory pool, the OM_USE_STATIC_MEMORY_POOL_INITIALIZATION 
// macro should be defined in omosconfig.h file and framework should be rebuilt.
// This initialization may be needed if there is a racing between two tasks, 
// which both send the same event for the first time or create an instance of the same class for the first time.
//#[ type IMPLEMENT_STATIC_MEMORY_INITIALIZATION
#ifdef OM_USE_STATIC_MEMORY_POOL_INITIALIZATION
#define IMPLEMENT_STATIC_MEMORY_INITIALIZATION(CLASSNAME,INITNUM)\
		OMSelfLinkedMemoryAllocator<CLASSNAME,INITNUM>* CLASSNAME::allocatorRef(myOMMemoryAllocator());
#define MY_MEMORY_ALLOCATOR allocatorRef
#else
#define IMPLEMENT_STATIC_MEMORY_INITIALIZATION(CLASSNAME,INITNUM)
#define MY_MEMORY_ALLOCATOR myOMMemoryAllocator()
#endif
//#]

// nothrow new/delete operator declaraton
//#[ type OM_DECLARE_NOTHROW_ALLOCATION_OPERATORS
#ifdef OM_NO_NOTHROW_NEW_SUPPORT
#define OM_DECLARE_NOTHROW_ALLOCATION_OPERATORS
#else
#define OM_DECLARE_NOTHROW_ALLOCATION_OPERATORS \
	static void operator delete(void* deadObject, const struct std::nothrow_t&) throw(); \
	static void* operator new(size_t size, const struct std::nothrow_t&) throw();
#endif

//#]

// nothrow new/delete operator implementation
//#[ type OM_IMPLEMENT_NOTHROW_ALLOCATION_OPERATORS
#ifdef OM_NO_NOTHROW_NEW_SUPPORT
#define OM_IMPLEMENT_NOTHROW_ALLOCATION_OPERATORS(CLASSNAME)
#else
#define OM_IMPLEMENT_NOTHROW_ALLOCATION_OPERATORS(CLASSNAME) \
	void CLASSNAME::operator delete(void *deadObject, const struct std::nothrow_t&) throw() \
	{																			\
		MY_MEMORY_ALLOCATOR->returnMemory(deadObject,0);						\
	}																			\
	void * CLASSNAME::operator new(size_t size, const struct std::nothrow_t&) throw() \
	{																			\
		void * mem = MY_MEMORY_ALLOCATOR->getMemory(size);						\
		if (mem == NULL) {														\
			MEMORY_ALLOCATION_FAIL_MSG(CLASSNAME,mem)							\
		}																		\
		return mem;																\
	}
#endif

//#]

// The framework memory pool new/delete operators declaration.
//#[ type DECLARE_ALLOCATION_OPERATORS
#define DECLARE_ALLOCATION_OPERATORS														\
	static void operator delete(void* deadObject  DELETE_DUMMY_PARAM_IMP);		\
	static void* operator new(size_t size NEW_DUMMY_PARAM) OM_NO_THROW; \
	OM_DECLARE_NOTHROW_ALLOCATION_OPERATORS
//#]

// The framework memory pool operations that are added to the controlled classes.
//#[ type DECLARE_MEMORY_ALLOCATOR
#ifdef OM_NO_TEMPLATES_USAGE
	#define DECLARE_MEMORY_ALLOCATOR(CLASSNAME,INITNUM)
#else
	#define DECLARE_MEMORY_ALLOCATOR(CLASSNAME,INITNUM)									\
		public:																	\
			CLASSNAME* OMMemoryPoolNextChunk;									\
			DECLARE_ALLOCATION_OPERATORS										\
			static void OMMemoryPoolIsEmpty();									\
			static void OMMemoryPoolSetIncrement(Rhp_int32_t value);				\
			static void OMCallMemoryPoolIsEmpty(bool flagValue);				\
			static void OMSetMemoryAllocator(CLASSNAME*(*newAllocator)(Rhp_int32_t));	\
			static Rhp_int32_t OMNumberOfEmptyElements(); 						\
			DECLARE_STATIC_MEMORY_INITIALIZATION(CLASSNAME,INITNUM)	\
			static OMSelfLinkedMemoryAllocator<CLASSNAME,INITNUM>* myOMMemoryAllocator();
#endif // OM_NO_TEMPLATES_USAGE
//#]

// The framework memory pool new/delete operators implementation.
//#[ type IMPLEMENT_ALLOCATION_OPERATORS
#define IMPLEMENT_ALLOCATION_OPERATORS(CLASSNAME)															\
	void CLASSNAME::operator delete(void *deadObject DELETE_DUMMY_PARAM_IMP)	\
	{																			\
		MY_MEMORY_ALLOCATOR->returnMemory(deadObject,SIZE_PARAM_NAME);			\
	}																			\
	void * CLASSNAME::operator new(size_t size NEW_DUMMY_PARAM_IMP) OM_NO_THROW	\
	{																			\
		void * mem = MY_MEMORY_ALLOCATOR->getMemory(size);						\
		if (mem == NULL) {														\
			MEMORY_ALLOCATION_FAIL_MSG(CLASSNAME,mem)							\
		}																		\
		return mem;																\
	} \
	OM_IMPLEMENT_NOTHROW_ALLOCATION_OPERATORS(CLASSNAME)
//#]

// The framework memory pool operations that are added to the controlled classes.
//#[ type IMPLEMENT_MEMORY_ALLOCATOR
#ifdef OM_NO_TEMPLATES_USAGE
	#define IMPLEMENT_MEMORY_ALLOCATOR(CLASSNAME,INITNUM,INCREMENTNUM,ISPROTECTED)
#else
	#define IMPLEMENT_MEMORY_ALLOCATOR(CLASSNAME,INITNUM,INCREMENTNUM,ISPROTECTED)						\
		OMSelfLinkedMemoryAllocator<CLASSNAME,INITNUM>* CLASSNAME::myOMMemoryAllocator() 				\
		{																								\
			static OMSelfLinkedMemoryAllocator<CLASSNAME,INITNUM> allocator(INCREMENTNUM,ISPROTECTED);	\
			return &allocator;																			\
		}																								\
		IMPLEMENT_STATIC_MEMORY_INITIALIZATION(CLASSNAME,INITNUM)						\
		IMPLEMENT_ALLOCATION_OPERATORS(CLASSNAME)											\
		void CLASSNAME::OMMemoryPoolSetIncrement(Rhp_int32_t value)							\
		{																					\
			MY_MEMORY_ALLOCATOR->setIncrementNum(value);											\
		}																					\
		void CLASSNAME::OMMemoryPoolIsEmpty()															\
		{																								\
			POOL_REALLOCATION_MSG(CLASSNAME,INCREMENTNUM)												\
		}																								\
		void CLASSNAME::OMCallMemoryPoolIsEmpty(bool flagValue)											\
		{																								\
			MY_MEMORY_ALLOCATOR->callMemoryPoolIsEmpty(flagValue);										\
		}																								\
		void CLASSNAME::OMSetMemoryAllocator(CLASSNAME*(*newAllocator)(Rhp_int32_t))						\
		{																								\
			MY_MEMORY_ALLOCATOR->setAllocator(newAllocator);											\
		}																								\
		Rhp_int32_t CLASSNAME::OMNumberOfEmptyElements()														\
		{																								\
			return MY_MEMORY_ALLOCATOR->numberOfEmptyElements();										\
		}		
#endif // OM_NO_TEMPLATES_USAGE
//#]

// The framework memory pool fail message
//#[ type MEMORY_ALLOCATION_FAIL_MSG
#ifdef _OMINSTRUMENT
	#define	MEMORY_ALLOCATION_FAIL_MSG(CLASSNAME,MEM)				\
		OMString s((Rhp_char_pt)#CLASSNAME);								\
		s += (Rhp_char_pt)": Memory allocation for new instances failed.\n";	\
		OM_NOTIFY_TO_ERROR(s.GetBuffer(0));										
#else
	#define	MEMORY_ALLOCATION_FAIL_MSG(CLASSNAME,MEM)
#endif // _OMINSTRUMENT
//#]

// The initial pool size for dynamic initialization
//#[ type OM_DYNAMIC_POOL_INITIALIZATION_SIZE
#define OM_DYNAMIC_POOL_INITIALIZATION_SIZE 0
//#]

// The framework memory pool additional allocation message
//#[ type POOL_REALLOCATION_MSG
#ifdef _OMINSTRUMENT
	#define POOL_REALLOCATION_MSG(CLASSNAME,INCREMENTSIZE)						\
		OMString s((Rhp_char_pt)#CLASSNAME);												\
		s += (Rhp_char_pt)": Memory pool is empty, allocating memory pool for additional ";	\
		s += (Rhp_char_pt)#INCREMENTSIZE ;													\
		s += (Rhp_char_pt)" instances.\n";													\
		OM_NOTIFY_TO_OUTPUT(s.GetBuffer(0));
#else
	#define POOL_REALLOCATION_MSG(CLASSNAME,INCREMENTSIZE)
#endif // _OMINSTRUMENT
//#]

// Reset the memory pool
//#[ type RESET_MEMORY_ALLOCATOR
#ifdef OM_NO_TEMPLATES_USAGE
	#define RESET_MEMORY_ALLOCATOR(CLASSNAME)
#else
	#define RESET_MEMORY_ALLOCATOR(CLASSNAME) \
		OMMemoryPoolNextChunk = reinterpret_cast<CLASSNAME*>(NULL); 
#endif // OM_NO_TEMPLATES_USAGE
//#]

// The framework memory pool operations that are added to the controlled classes.
//#[ type DECLARE_MEMORY_ALLOCATOR_T
#ifdef OM_NO_TEMPLATES_USAGE
	#define DECLARE_MEMORY_ALLOCATOR_T(CLASSNAME,INITNUM,INCREMENTNUM,ISPROTECTED)
#else
	#define DECLARE_MEMORY_ALLOCATOR_T(CLASSNAME,INITNUM,INCREMENTNUM,ISPROTECTED)	\
	public:	\
		CLASSNAME* OMMemoryPoolNextChunk;\
	static void operator delete(void *deadObject DELETE_DUMMY_PARAM_IMP) {\
		myOMMemoryAllocator().returnMemory(deadObject,SIZE_PARAM_NAME);\
	}\
	static void * operator new(size_t size) OM_NO_THROW	{\
		void * mem = myOMMemoryAllocator().getMemory(size);						\
		if (mem == NULL) {														\
			MEMORY_ALLOCATION_FAIL_MSG(CLASSNAME,mem)							\
		}																		\
		return mem;																\
	}\
	static void OMMemoryPoolIsEmpty(void) {\
		POOL_REALLOCATION_MSG(CLASSNAME,INCREMENTNUM)	\
	}\
	static void OMMemoryPoolSetIncrement(Rhp_int32_t value)	{\
		myOMMemoryAllocator().setIncrementNum(value);												\
	}\
	static void OMCallMemoryPoolIsEmpty(bool flagValue)	{\
		myOMMemoryAllocator().callMemoryPoolIsEmpty(flagValue);										\
	}\
	static void OMSetMemoryAllocator(CLASSNAME*(*newAllocator)(Rhp_int32_t)) {\
		myOMMemoryAllocator().setAllocator(newAllocator);											\
	}\
	static Rhp_int32_t OMNumberOfEmptyElements(void) {\
		return myOMMemoryAllocator().numberOfEmptyElements();										\
	}\
	static OMSelfLinkedMemoryAllocator<CLASSNAME,INITNUM>& myOMMemoryAllocator(void) {\
		static OMSelfLinkedMemoryAllocator<CLASSNAME,INITNUM> allocator(INCREMENTNUM,ISPROTECTED);	\
		return allocator;																			\
	}																								
#endif // OM_NO_TEMPLATES_USAGE

//#]

#endif



