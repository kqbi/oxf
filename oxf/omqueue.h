//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMQueue
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2018. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.


#ifndef omqueue_H
#define omqueue_H

//## class OMQueue
#include "OMAbstractContainer.h"
//## dependency OMIterator
#include "OMIterator.h"
//## dependency OMList
#include "omlist.h"
//## class Collection
#include "omcollec.h"
//## package Design::oxf::Services::Containers::TypeSafe

//## class OMQueue
// A FIFO queue
// Implemented using a cyclic dynamic-array
template <class Concept> class OMQueue : public OMAbstractContainer<Concept> {
public :

    // The dynamic array type
    //## class OMQueue::Collection
    typedef OMCollection<Concept> Collection;
    
    ////    Constructors and destructors    ////
    
    // Initialize the queue with a given size and growth method (dynamic or static size)
    // Argument bool shouldGrow = true :
    // dynamic size flag
    // Argument const Rhp_int32_t initSize = 100 :
    // the initial queue size
    //## operation OMQueue(bool,Rhp_int32_t)
    explicit inline OMQueue(bool shouldGrow = true, const Rhp_int32_t initSize = 100) : m_grow(shouldGrow), m_head(0), 
m_myQueue(initSize), m_tail(0)
      {
        //#[ operation OMQueue(bool,Rhp_int32_t)
        //#]
    }
    
    // copy constructor
    // Argument const OMQueue<Concept>& aQueue :
    // The queue to copy
    //## operation OMQueue(const OMQueue<Concept>&)
    explicit inline OMQueue(const OMQueue<Concept>& aQueue) {
        //#[ operation OMQueue(const OMQueue<Concept>&)
        copy(aQueue);
        //#]
    }
    
    //## auto_generated
    inline virtual ~OMQueue(void) {
        //#[ auto_generated
        //#]
    }
    
    ////    Operations    ////
    
    // Get an element from the queue
    //## operation get()
    inline virtual Concept get(void) {
        //#[ operation get()
        Concept c = OMNullValue<Concept>::get();
        if (!isEmpty()) {
        	c = m_myQueue.getAt(m_head);
        	increaseHead_();
        } 
        return c;
        //#]
    }
    
    // Get the number of elements in the queue
    //## operation getCount() const
    inline Rhp_int32_t getCount(void) const {
        //#[ operation getCount() const
        Rhp_int32_t count;
        
        if (m_tail >= m_head) {
        	count = m_tail - m_head;
        } else {
        	count = (getSize() - m_head) + m_tail;
        }       
        return count;
        //#]
    }
    
    // getQueue() returns the element which is the next to be returned by get() in the tail of the list
    // Argument OMList<Concept> & aList :
    // A list of the elements in the queue (out)
    //## operation getInverseQueue(OMList<Concept> & ) const
    inline virtual void getInverseQueue(OMList<Concept> & aList) const {
        //#[ operation getInverseQueue(OMList<Concept> & ) const
        aList.removeAll();
        if (! isEmpty()) {
        	Rhp_int32_t first = (m_tail > m_head) ? m_head : 0;
        
        	// copy first part
        	Rhp_int32_t j;
        	for (j = m_tail; j > first; j--) {
        		aList.add(m_myQueue.getAt(j - 1));
        	}
        
        	// check if need to continue
        	if (first != m_head) {
        		// copy second part
        		for (j = m_myQueue.getSize(); j > m_head; j--) {
        			aList.add(m_myQueue.getAt(j - 1)); 
        		}
        	}  
        }
        //#]
    }
    
    // getQueue() returns the element which is the next to be returned by get() in the head of the list
    // Argument OMList<Concept> & aList :
    // The list of queue elements (out)
    //## operation getQueue(OMList<Concept> & ) const
    inline virtual void getQueue(OMList<Concept> & aList) const {
        //#[ operation getQueue(OMList<Concept> & ) const
        aList.removeAll();
        if ( !isEmpty() ) {
        	Rhp_int32_t last = (m_tail > m_head) ? m_tail : m_myQueue.getSize();
        	// copy first part
        	Rhp_int32_t j;
        	for (j = m_head; j < last; j++) {
        		aList.add(m_myQueue.getAt(j));
        	}
        
        	// check if need to continue
        	if (last != m_tail) {
        		// copy second part
        		for (j = 0; j < m_tail; j++) {
        			aList.add(m_myQueue.getAt(j));
        		}                    
        	}           
        }
        //#]
    }
    
    // Get the size allocated for the queue
    //## operation getSize() const
    inline Rhp_int32_t getSize(void) const {
        //#[ operation getSize() const
        return ( m_myQueue.getSize() );
        //#]
    }
    
    // Check if the queue is empty
    //## operation isEmpty() const
    inline bool isEmpty(void) const {
        //#[ operation isEmpty() const
        return (m_head == m_tail);
        //#]
    }
    
    // Check if the queue is full.
    //## operation isFull() const
    inline bool isFull(void) const {
        //#[ operation isFull() const
        bool status;
        
        if ( m_grow ) {
        	status = false;
        } else {
        	if (((m_tail + 1) == getSize()) && (m_head == 0)) {
        		status = true; 
        	} else {
        		status = ((m_tail + 1) == m_head);
        	}
        }
        return status;
        //#]
    }
    
    // Assignment operator
    // Argument const OMQueue<Concept>& aQueue :
    // The queue to copy
    //## operation operator=(const OMQueue<Concept>&)
    inline OMQueue<Concept>& operator=(const OMQueue<Concept>& aQueue) {
        //#[ operation operator=(const OMQueue<Concept>&)
        copy(aQueue);
        return (*this);
        //#]
    }
    
    // Add an element to the queue
    // Argument Concept aConcept :
    // The element to add
    //## operation put(Concept )
    inline virtual bool put(Concept aConcept) {
        //#[ operation put(Concept )
        bool status;
        if (isFull()) {
        	status = false;
        } else {
        	m_myQueue.addAt(m_tail, aConcept);
        	increaseTail_();
        	status = true;
        }
        return status;
        //#]
    }
    

protected :

    // Copy a queue
    // Argument const OMQueue<Concept>& aQueue :
    // the queue to copy
    //## operation copy(const OMQueue<Concept>&)
    inline void copy(const OMQueue<Concept>& aQueue) {
        //#[ operation copy(const OMQueue<Concept>&)
        m_head = aQueue.m_head;
        m_tail = aQueue.m_tail;
        m_grow = aQueue.m_grow;
        m_myQueue = aQueue.m_myQueue;
        //#]
    }
    
    // Get the element at the given position (called by the iterator)
    // Argument void * pos :
    // The iterator current position
    //## operation getCurrent(void *) const
    inline virtual Concept& getCurrent(void * pos) const {
        //#[ operation getCurrent(void *) const
        /*LDRA_INSPECTED 7 C  : Can't find a way to have a single return */
        if (isEmpty()) {
        	return OMNullValue<Concept>::get();
        }
        
        if ( (m_head < m_tail) &&
             ((reinterpret_cast<Rhp_uintptr_t>(pos) < static_cast<Rhp_uintptr_t>(m_head)) || 
              (reinterpret_cast<Rhp_uintptr_t>(pos) >= static_cast<Rhp_uintptr_t>(m_tail))) ) {
        	// out of range (before head or after tail)
           	return OMNullValue<Concept>::get();
        } else {
        	if ( (reinterpret_cast<Rhp_uintptr_t>(pos) < static_cast<Rhp_uintptr_t>(m_head)) &&
        	     (reinterpret_cast<Rhp_uintptr_t>(pos) >= static_cast<Rhp_uintptr_t>(m_tail)) ) {
        		// out of range (between head and tail)
               	return OMNullValue<Concept>::get();
            }
        }   
        return m_myQueue.getAt((Rhp_int32_t)(Rhp_uintptr_t)(pos));
        //#]
    }
    
    // Set the initial position for the iterator
    // Argument void*& pos :
    // The queue head position (out)
    //## operation getFirst(void*& ) const
    //#[ ignore
    #ifdef OM_WIN32_COMPILER_DISABLE_WARNING_4312
    #pragma warning ( push )
    #pragma warning ( disable : 4312 )
    #endif // OM_WIN32_COMPILER_DISABLE_WARNING_4312
    //#]
    inline virtual void getFirst(void*& pos) const {
        //#[ operation getFirst(void*& ) const
        pos = reinterpret_cast<void*>(m_head);
        //#]
    }
    //#[ ignore
    #ifdef OM_WIN32_COMPILER_DISABLE_WARNING_4312
    #pragma warning ( pop )
    #endif // OM_WIN32_COMPILER_DISABLE_WARNING_4312
    //#]
    
    // Update the provided position to the next position in the container
    // Argument void*& pos :
    // The iterator position to advance
    //## operation getNext(void*& ) const
    inline virtual void getNext(void*& pos) const {
        //#[ operation getNext(void*& ) const
        size_t i = (size_t)pos;
        
        ++i;
        if (i == (size_t)m_myQueue.getSize()) {
        	i = 0;
        }
        if (i == (size_t)m_head) {
        	i = m_myQueue.getSize();
        }
        
        pos = reinterpret_cast<void*>(i);
        //#]
    }
    
    // Update the queue head position
    //## operation increaseHead_()
    inline void increaseHead_(void) {
        //#[ operation increaseHead_()
        if ( !isEmpty() ) { 
        	++m_head;
        	if ( m_head == m_myQueue.getSize() ) {
        		m_head = 0;
        	}
        }
        //#]
    }
    
    // Advance the queue tail position and grow (if needed).
    //## operation increaseTail_()
    inline void increaseTail_(void) {
        //#[ operation increaseTail_()
        ++m_tail;
        if (m_tail > m_head) {
        	if (m_tail == m_myQueue.getSize()) {
        		if (m_head > 0) {
        			m_tail = 0;
        		} else {
        			if (m_grow) {
        				m_myQueue.reorganize();	// queue if full - grow
        			} else {
        				// queue is full - don't grow
        				--m_tail;	
        			}
        		}
        	}
        } else {
        	if (m_tail == m_head) {
        		if (!m_grow) {	// queue is full - don't grow
        			--m_tail;	
        		} else {
        			// queue if full - grow
        			m_tail = m_myQueue.getSize();
        			m_myQueue.reorganize();
        			for (Rhp_int32_t j = 0; j < m_head; j++) {
        				m_myQueue.addAt(m_tail, m_myQueue.getAt(j));
        				increaseTail_();
        			}
        		}
        	}
        }
        //#]
    }
    
    ////    Attributes    ////
    

private :

    // This flag indicates if the queue size should be dynamic (grow on demand) or static.
    bool m_grow;		//## attribute m_grow
    
    // The queue head (elements are extracted from the head)
    Rhp_int32_t m_head;		//## attribute m_head
    
    // The dynamic array used to implement the queue
    Collection m_myQueue;		//## attribute m_myQueue
    
    // The queue tail (elements are added to the tail)
    Rhp_int32_t m_tail;		//## attribute m_tail
    
};

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMQueue

#endif



