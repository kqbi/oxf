//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMUMap
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


#ifndef omumap_H
#define omumap_H

//## dependency MemoryManagerMacros
#include "OXFMemoryManagerMacros.h"
//## class OMUMap
#include "OMUAbstractContainer.h"
//## dependency OMUIterator
#include "OMUIterator.h"
//## dependency Manager
#include "OXFManager.h"
//## class OMUMap
class OMUMap;

//## package Design::oxf::Services::Containers::Typeless

//## class OMUMap
// A type less map - implemented as a balanced tree (log(N) search)
class RP_FRAMEWORK_DLL OMUMap : public OMUAbstractContainer {
public :

    // A map item
    //## class OMUMap::Item
    class RP_FRAMEWORK_DLL Item {
    //#[ ignore
        // override new & delete operators
        OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
        
        
    //#]
    
        ////    Friends    ////
        
    public :
    
        friend class OMUMap;
        
        ////    Constructors and destructors    ////
        
        // Copy constructor
        // Argument const Item& item :
        // The item to copy
        //## operation Item(const Item&)
        explicit inline Item(const Item& item) : element(item.element), key(item.key), larger(item.larger), 
parent(item.parent), rank(item.rank), smaller(item.smaller)
          {
            //#[ operation Item(const Item&)
            //#]
        }
        
        // Constructor
        // Argument void * theKey :
        // The item key
        // Argument void * theElement :
        // The item data
        //## operation Item(void *,void *)
        //#[ ignore
        /*LDRA_INSPECTED 62 D : Can't make argument const */  
        
        //#]
        inline Item(void * theKey, void * theElement) : element(theElement), key(theKey), larger(NULL), parent(NULL), 
rank(1), smaller(NULL) {
            //#[ operation Item(void *,void *)
            //#]
        }
        
        // Cleanup
        //## operation ~Item()
        inline virtual ~Item(void) {
            //#[ operation ~Item()
            _removeAll();
            //#]
        }
        
        ////    Operations    ////
        
        // Assignment operator
        // Argument const Item& item :
        // The item to copy
        //## operation operator=(const Item&)
        inline Item& operator=(const Item& item) {
            //#[ operation operator=(const Item&)
            parent = item.parent;
            smaller = item.smaller;
            larger = item.larger;
            element = item.element;
            key = item.key;
            rank = item.rank;
            return (*this);
            //#]
        }
        
    
    private :
    
        // add a new map item to sub tree, and balance the sub tree
        // Argument Item* item :
        // The item to add to my sub tree
        //## operation _add(Item*)
        //#[ ignore
        /*LDRA_INSPECTED 6 D : Can't make non recursive */  
        
        //#]
        inline void _add(Item* item) {
            //#[ operation _add(Item*)
            if (item->key <= key) {
            	if (smaller == NULL) {
            		_connectSmaller(item);
            		item->_addCheckBalance();
            	} else {
            		smaller->_add(item);
            	}
            } else {
            	if (larger == NULL) {
            		_connectLarger(item);
            		item->_addCheckBalance();
            	} else {
            		larger->_add(item);
            	}
            }
            //#]
        }
        
        // balance the tree
        //## operation _addCheckBalance()
        //#[ ignore
        /*LDRA_INSPECTED 6 D : Can't make non recursive */  
        
        //#]
        inline void _addCheckBalance(void) {
            //#[ operation _addCheckBalance()
            if (parent != NULL) {
            	Item* grandpa = parent->parent;
            	if ( (grandpa == NULL) || (grandpa->rank == (rank + 1)) ) {
            		// balanced or tree of depth 2 (hence balanced)
            	} else {
            		// "this" is unbalanced
            		// Try to "promote"
            		if ( (grandpa->larger != NULL) && 
            			 (grandpa->smaller != NULL) &&
            			 (grandpa->larger->rank == grandpa->smaller->rank) ) {
            			// The two red sons case
            			grandpa->rank++;
            			grandpa->_addCheckBalance();
            		} else {                               
            			// Must do a rotation
            			if (grandpa->smaller == parent) {
            				// The Right rotation case
            				if (parent->smaller == this) {
            					// LL case - make a single right rotation
            					//            grandpa		        parent
            					//		    parent	 d   ===>	this    grandpa
            					//		this	 c             a    b   c      d
            					//	   a	b
            					// connect parent to rest of tree
            					grandpa->_connectParent(parent);
            					// connect "c" to grandpa
            					grandpa->_connectSmaller(parent->larger);
            					// connect grandpa to parent
            					parent->_connectLarger(grandpa);
            				} else {
            					// LR case - make a double right rotation
            					//            grandpa		        this  
            					//		    parent	 d   ===>	parent  grandpa
            					//		  a     this           a     b  c      d
            					//	           b    c
            					// connect this to rest of tree
            					Item* myParent1 = parent;
            					grandpa->_connectParent(this);
            					// Connect "b" to parent
            					myParent1->_connectLarger(smaller);
            					// Connect "c" to grandpa
            					grandpa->_connectSmaller(larger);
            					// connect parent to me
            					_connectSmaller(myParent1);
            					_connectLarger(grandpa);
            				}
            			} else {
            				// grandpa->larger==parent
            				// The Left rotation case
            				if (parent->larger==this) {
            					// RR case - make a single left rotation
            					//    grandpa		                parent
            					//	a 	    parent	     ===>	grandpa   this
            					//		   b     this           a    b   c    d
            					//              c	 d
            					// connect parent to rest of tree
            					grandpa->_connectParent(parent);
            					// connect "b" to grandpa
            					grandpa->_connectLarger(parent->smaller);
            					// connect grandpa to parent
            					parent->_connectSmaller(grandpa);
            				} else {
            					// RL case - make a double left rotation
            					//      grandpa		                this  
            					//		a     parent	===>   grandpa  parent
            					//		    this    d          a     b  c      d
            					//	       b    c
            					// connect this to rest of tree
            					Item* myParent2 = parent;
            					grandpa->_connectParent(this);
            					// Connect "c" to parent
            					myParent2->_connectSmaller(larger);
            					// Connect "b" to grandpa
            					grandpa->_connectLarger(smaller);
            					// connect parent to me
            					_connectSmaller(grandpa);
            					_connectLarger(myParent2);
            				}
            			}
            		}
            	}
            }
            //#]
        }
        
        // connect sub trees
        // Argument Item*& side :
        // The new sub tree
        // Argument Item* item :
        // The item to connect
        //## operation _connect(Item*&,Item*)
        //#[ ignore
        /*LDRA_INSPECTED 62 D : Can't make argument const */  
        
        //#]
        inline void _connect(Item*& side, Item* item) {
            //#[ operation _connect(Item*&,Item*)
            side = item;
            if (item != NULL) {
            	item->parent = this;
            }
            //#]
        }
        
        // connect to the right sub tree
        // Argument Item* item :
        // The item to connect
        //## operation _connectLarger(Item*)
        inline void _connectLarger(Item* item) {
            //#[ operation _connectLarger(Item*)
            _connect(larger,item);
            //#]
        }
        
        // connect to parent sub tree
        // Argument Item* newN :
        // The item to connect
        //## operation _connectParent(Item*)
        inline void _connectParent(Item* newN) {
            //#[ operation _connectParent(Item*)
            if (parent != NULL) {
            	if (this == parent->smaller) {
            		parent->_connectSmaller(newN);
            	} else {
            		parent->_connectLarger(newN);
            	}
            } else {
            	if (newN != NULL) {
            		newN->parent = NULL;
            	}
            }
            //#]
        }
        
        // connect to the left sub tree
        // Argument Item* item :
        // The item to connect
        //## operation _connectSmaller(Item*)
        inline void _connectSmaller(Item* item) {
            //#[ operation _connectSmaller(Item*)
            _connect(smaller,item);
            //#]
        }
        
        // find an element in the map item sub tree
        // Argument const void * anItem :
        // The element to find
        //## operation _find(void *) const
        //#[ ignore
        /*LDRA_INSPECTED 6 D : Can't make non recursive */  
        
        //#]
        inline const Item* _find(const void * anItem) const {
            //#[ operation _find(void *) const
            const Item* item;
            
            if (anItem == element) {
            	item = this;
            } else {
            	const Item* inSmaller = NULL;
            	if (smaller != NULL) {
            		inSmaller = smaller->_find(anItem);
            	}
            	if (inSmaller != NULL) {
            		item = inSmaller;
            	} else {
            		if (larger == NULL) {
            			item = NULL;
            		} else {
            			item = larger->_find(anItem);  
            		}
            	}
            }
            return item;
            //#]
        }
        
        // get the number of elements in the map item sub tree
        //## operation _getCount() const
        //#[ ignore
        /*LDRA_INSPECTED 6 D : Can't make non recursive */  
        
        //#]
        inline Rhp_int32_t _getCount(void) const {
            //#[ operation _getCount() const
            Rhp_int32_t count = 1;
            
            if (smaller != NULL) {
            	count += smaller->_getCount();
            }
            
            if (larger != NULL) {
            	count += larger->_getCount();
            }
            return count;
            //#]
        }
        
        // find a map item in this map item sub tree
        // Argument const void * theKey :
        // The key to find
        //## operation _lookUp(void *)
        //#[ ignore
        /*LDRA_INSPECTED 6 D : Can't make non recursive */  
        
        //#]
        inline Item* _lookUp(const void * theKey) {
            //#[ operation _lookUp(void *)
            Item* item;
            
            if (key == theKey) {
            	item = this;
            } else if (key > theKey) {
            	if (smaller == NULL) {
            		item = NULL;
            	} else {
            		item = smaller->_lookUp(theKey);
            	}
            } else  {
            	if (larger == NULL) {
            		item = NULL;
            	} else {
            		item = larger->_lookUp(theKey);
            	}
            }
            return item; 
            //#]
        }
        
        // remove all the elements in the map item sub tree
        //## operation _removeAll()
        inline void _removeAll(void) {
            //#[ operation _removeAll()
            if (smaller != NULL) {
            	delete smaller;
            	smaller = NULL;
            }
            
            if (larger != NULL) {
            	delete larger;
            	larger = NULL;
            }
            //#]
        }
        
        // balance tree
        //## operation _removeCheckBalance()
        //#[ ignore
        /*LDRA_INSPECTED 6 D : Can't make non recursive */  
        
        //#]
        inline void _removeCheckBalance(void) {
            //#[ operation _removeCheckBalance()
            // Compute minimal rank of sons
            Rhp_int32_t minRank;
                        
            if ( (smaller == NULL) || (larger == NULL) ) {
            	minRank = 0;
            } else {
            	if (smaller->rank < larger->rank) {
            		minRank = smaller->rank;
            	} else {
            		minRank = larger->rank;
            	}
            }
                        
            if (rank < (minRank + 2)) {
            	// My rank is o.k.
            } else {
            	// "this" is unbalanced
               	if ( (smaller == NULL) || (rank == (smaller->rank + 2))) {
            		// Note "larger" cannot be NULL as "smaller" has the minRank
            		if (larger->rank == rank) {
            			// (d) case - make a single right rotation
            			//              this		               theLarger
            			//		  smaller	theLarger   ===>     this      c   
            			//		            b        c      smaller   b      
            			// connect theLarger to rest of tree
            			Item* theLarger1 = larger;
            			_connectParent(theLarger1);
            			// connect "b" to this
            			_connectLarger(theLarger1->smaller);
            			// connect this to theLarger
            			theLarger1->_connectSmaller(this);
            			// Check again -- should terminate in one iteration
            			_removeCheckBalance();
            		} else {
            			if ( (larger->smaller == NULL) ||
                        	 (larger->smaller->rank == (rank - 2)) ) {
                    		if ( (larger->larger == NULL) ||
            					 (larger->larger->rank == (rank - 2)) )	{
            					// Case a - Demotion
            					rank--;
            					if (parent != NULL) {
            						parent->_removeCheckBalance();
            					}
            				} else { 
            					// case b1. Single right rotation
            					//        this  		            theLarger
            					//	  smaller theLarger  ===>	 this       son
            					//		       b     son     smaller  b    c   d
            					//	                c    d
            					// connect theLarger to rest of tree
            					Item* theLarger2 = larger;
            					_connectParent(theLarger2);
            					// Connect "b" to this
            					_connectLarger(theLarger2->smaller);
            					// Connect this to theLarger
            					theLarger2->_connectSmaller(this);
            					rank--;
            					theLarger2->rank++;
            				}
                        } else { 
            				// larger->smaller->rank==rank+1
            				if ( (larger->larger == NULL) ||
            					 (larger->larger->rank == (rank - 2)) ) {
            					// case c
            					//          this  		              son  
            					//	 smaller   larger     ===>	  this    larger
            					//		      son    d        smaller  b  c     d
            					//	        b    c
            					// connect son to rest of tree
            					Item* son1 = larger->smaller;
            					_connectParent(son1);
            					// Connect "c" to larger
            					larger->_connectSmaller(son1->larger);
            					// connect larger to son1
            					son1->_connectLarger(larger);
            					// Connect "b" to this
            					_connectLarger(son1->smaller);
            					// Connect son to this
            					son1->_connectSmaller(this);
            					rank--;
            					son1->rank++;
            				} else {
            					// case b2
            					//        this  		              larger 
            					//	smaller   larger     ===>	 this     son2
            					//		    son1   son2    smaller  son1  d   e
            					//	       b    c  d   e		   b	c
            					// connect theLarger to rest of tree
            					Item* theLarger3 = larger;
            					_connectParent(larger);
            					// connect son1 to this
            					_connectLarger(theLarger3->smaller);
            					// connect this to theLarger
            					theLarger3->_connectSmaller(this);
            					rank--;
            					theLarger3->rank++;
            				}
            			}
            		}  
            	} else {
            		// The Left rotation case
            		// note smaller cannot be null as larger is the minRank
            		if (smaller->rank == rank) {
            			// (d) case - make a single left rotation
            			//            this		          smaller
            			//		smaller   larger ===>    b     this
            			//	   b     c                        c   larger
            			// connect theSmaller to rest of tree
            			Item* theSmaller1 = smaller;
            			_connectParent(theSmaller1);
            			// connect "c" to this
            			_connectSmaller(theSmaller1->larger);
            			// connect this to theSmaller1
            			theSmaller1->_connectLarger(this);
            			// Check again -- should terminate in one iteration
            			_removeCheckBalance();
            		} else {
            			if ( (smaller->larger == NULL) ||
            				 (smaller->larger->rank == (rank - 2)) ) {
            				if ( (smaller->smaller == NULL) ||
                       			 (smaller->smaller->rank == (rank - 2)) ) {
                       			// Case a - Demotion
                       			rank--;
                       			if (parent != NULL) {
                       				parent->_removeCheckBalance();
                       			}
                       		} else { 
                       			// case b1. Single Left rotation
                       			//         this		           smaller
                       			//	  smaller  larger ===>	son     this  
                       			//	 son   c               a   b   c   larger
                       			//	a   b
                       			// connect theSmaller to rest of tree
                       			Item* theSmaller2 = smaller;
                       			_connectParent(theSmaller2);
                       			// Connect "c" to this
                       			_connectSmaller(theSmaller2->larger);
                       			// Connect this to theSmaller
                       			theSmaller2->_connectLarger(this);
                       			rank--;
                       			theSmaller2->rank++;
                       		}
                       	} else { 
                       		// smaller->larger->rank==rank+1
                       		if ( (smaller->smaller == NULL) ||
                       			 (smaller->smaller->rank == (rank - 2)) ) {
                       			// case c
                       			//         this 		          son  
                       			//	  smaller  larger ===>	smaller  this  
                       			//	 a     son             a      b  c   larger
                       			//	      b    c
                       			// connect son to rest of tree
                       			Item* son2 = smaller->larger;
                       			_connectParent(son2);
                       			// connect "b" to smaller
                       			smaller->_connectLarger(son2->smaller);
                       			// Connect smaller to son
                       			son2->_connectSmaller(smaller);
                       			// Connect "c" to 
                       			_connectSmaller(son2->larger);
                       			// Connect son to this
                       			son2->_connectLarger(this);
                       			rank--;
                       			son2->rank++;
                       		} else {
                       			// case b2
                       			//         this 		          smaller
                       			//    smaller   larger ===>	  son1      this
                       			// son1   son2               a    b  son2   larger
                       			//a    b  c   d		                c	 d
                       			// connect smaller to rest of tree
                       			Item* theSmaller3 = smaller;
                       			_connectParent(theSmaller3);
                       			// connect son1 to this
                       			_connectSmaller(theSmaller3->larger);
                       			// connect this to theSmaller
                       			theSmaller3->_connectLarger(this);
                       			rank--;
                       			theSmaller3->rank++;
                        	}
                        }
                    }	
            	}
            }
            //#]
        }
        
        // remove this map item
        //## operation _removeYourSelf()
        //#[ ignore
        /*LDRA_INSPECTED 6 D : Can't make non recursive */  
        
        //#]
        inline void _removeYourSelf(void) {
            //#[ operation _removeYourSelf()
            // make sure I have "smaller==NULL"
            Item* item;
            if (smaller != NULL) {
            	if (larger != NULL) {
            		// case    this
            		//		  a    b 
            		// exchange place with my successor in the order
            		for (item = larger; item->smaller; item = item->smaller) {
            		}
            		_switchNode(item);
            	} else {
            		// case    this
            		//		  a   NULL
            		// exchange place with 'a' (which must be a leaf)
            		_switchNode(smaller);
            	}
            }
            // Remove "this" from tree
            _connectParent(larger);
            // Update the rank of parent if necessary
            if (parent != NULL) {
            	parent->_removeCheckBalance();
            }
            parent = NULL;
            smaller = NULL;
            larger = NULL;
            //#]
        }
        
        // replace positions with the other map item
        // Argument Item* other :
        // The node to switch with
        //## operation _switchNode(Item*)
        inline void _switchNode(Item* other) {
            //#[ operation _switchNode(Item*)
            // Switch my position in the tree with that of other
            Item* myNewParent;
            Item* hisNewParent;
            Item* myNewSmaller;
            Item* hisNewSmaller;
            Item* myNewLarger;
            Item* hisNewLarger;
            bool IShouldBeSmaller=false;
            bool HeShouldBeSmaller=false;
            bool IShouldBeLarger=false;
            bool HeShouldBeLarger=false;
            
            Rhp_int32_t hisNewRank = rank;
            Rhp_int32_t myNewRank = rank;
            
            if (parent==other) {
            	hisNewParent = this;
            } else {
            	hisNewParent = parent;
            }
            if (larger==other) {
            	hisNewLarger = this;
            } else {
            	hisNewLarger = larger;
            }
            if (smaller==other) {
            	hisNewSmaller = this;
            } else {
            	hisNewSmaller = smaller;
            }
            
            if (other->parent==this) {
            	myNewParent = other;
            } else {
            	myNewParent = other->parent;
            }
            if (other->larger==this) {
            	myNewLarger = other;
            } else {
            	myNewLarger = other->larger;
            }
            if (other->smaller==this) {
            	myNewSmaller = other;
            } else {
            	myNewSmaller = other->smaller;
            }
            if (parent != NULL) {
            	if (parent->smaller == this) {
            		HeShouldBeSmaller = true;
            	} else {
            		HeShouldBeLarger = true;        
            	}
            }
            
            if (other->parent != NULL) {
            	if (other->parent->smaller == other) {
            		IShouldBeSmaller = true;
            	} else {
            		IShouldBeLarger = true;                 
            	}
            }
            // Exchange ranks
            rank = myNewRank;
            other->rank = hisNewRank;
            
            // Make the "out" links
            parent = myNewParent;
            larger = myNewLarger;
            smaller = myNewSmaller;
            other->parent = hisNewParent;
            other->larger = hisNewLarger;
            other->smaller = hisNewSmaller;
            // Make the "in" links
            if (HeShouldBeSmaller) {
            	other->parent->smaller = other;
            }
            if (HeShouldBeLarger) {
            	other->parent->larger = other;
            }
            
            if (IShouldBeSmaller) {
            	parent->smaller = this;
            }
            if (IShouldBeLarger) {
            	parent->larger = this;
            }
            
            if (smaller != NULL) {
            	smaller->parent = this;
            }
            if (larger != NULL) {
            	larger->parent = this;
            }
            if (other->smaller != NULL) {
            	other->smaller->parent = other;
            }
            if (other->larger != NULL) {
            	other->larger->parent = other;
            }
            //#]
        }
        
        ////    Additional operations    ////
        
    
    public :
    
        //## auto_generated
        inline void * getElement(void) const {
            //#[ auto_generated
            return element;
            //#]
        }
        
        //## auto_generated
        inline void setElement(void * const p_element) {
            //#[ auto_generated
            element = p_element;
            //#]
        }
        
        //## auto_generated
        inline void * getKey(void) const {
            //#[ auto_generated
            return key;
            //#]
        }
        
        //## auto_generated
        inline void setKey(void * const p_key) {
            //#[ auto_generated
            key = p_key;
            //#]
        }
        
        //## auto_generated
        inline Item* getLarger(void) const {
            //#[ auto_generated
            return larger;
            //#]
        }
        
        //## auto_generated
        inline void setLarger(Item* const p_larger) {
            //#[ auto_generated
            larger = p_larger;
            //#]
        }
        
        //## auto_generated
        inline Item* getParent(void) const {
            //#[ auto_generated
            return parent;
            //#]
        }
        
        //## auto_generated
        inline void setParent(Item* const p_parent) {
            //#[ auto_generated
            parent = p_parent;
            //#]
        }
        
        //## auto_generated
        inline Rhp_int32_t getRank(void) const {
            //#[ auto_generated
            return rank;
            //#]
        }
        
        //## auto_generated
        inline Item* getSmaller(void) const {
            //#[ auto_generated
            return smaller;
            //#]
        }
        
        //## auto_generated
        inline void setSmaller(Item* const p_smaller) {
            //#[ auto_generated
            smaller = p_smaller;
            //#]
        }
        
        ////    Attributes    ////
        
    
    private :
    
        // The item data
        void * element;		//## attribute element
        
        // The key
        void * key;		//## attribute key
        
        // The right sub tree
        Item* larger;		//## attribute larger
        
        // The parent node
        Item* parent;		//## attribute parent
        
        // This node rank in the balanced tree
        Rhp_int32_t rank;		//## attribute rank
        
        // The left sub tree
        Item* smaller;		//## attribute smaller
        
    };
    
    ////    Constructors and destructors    ////
    
    // copy constructor and assignment operator
    // Argument const OMUMap& aMap :
    // The map to copy
    //## operation OMUMap(OMUMap)
    explicit inline OMUMap(const OMUMap& aMap) : OMUAbstractContainer(), root(NULL) {
        //#[ operation OMUMap(OMUMap)
        copy(aMap);
        //#]
    }
    
    // Constructor
    //## operation OMUMap()
    inline OMUMap(void) : OMUAbstractContainer(), root(NULL) {
        //#[ operation OMUMap()
        //#]
    }
    
    // Destructor	
    //## operation ~OMUMap()
    inline ~OMUMap(void) {
        //#[ operation ~OMUMap()
        removeAll();
        root = NULL;
        //#]
    }
    
    ////    Operations    ////
    
    // add a new element to the given key
    // Argument void * theKey :
    // The key
    // Argument void * anElement :
    // The element
    //## operation add(void *,void *)
    inline void add(void * theKey, void * anElement) {
        //#[ operation add(void *,void *)
        Item* item = new Item(theKey,anElement);
        if (root == NULL) {
        	root = item;
        } else {
        	root->_add(item);
        	while (root->parent != NULL) {
        		// get the current root
        		root = root->parent;
        	}
        }
        //#]
    }
    
    // find an element in the map
    // Argument const void * anElement :
    // The element to find in the map
    //## operation find(void *) const
    //#[ ignore
    /*LDRA_INSPECTED 62 D : Can't make argument const */  
    
    //#]
    inline bool find(const void * anElement) const {
        //#[ operation find(void *) const
        bool status = false;
        
        if (root != NULL) {
        	if (root->_find(anElement) != NULL) {
        		status = true;
        	}
        }
        return status;
        //#]
    }
    
    // get the element for a given key
    // Argument const void * theKey :
    // The key to look for
    //## operation getAt(void *) const
    inline void * getAt(const void * theKey) const {
        //#[ operation getAt(void *) const
        return getKey(theKey);
        //#]
    }
    
    // get the number of elements in the map
    //## operation getCount() const
    inline Rhp_int32_t getCount(void) const {
        //#[ operation getCount() const
        Rhp_int32_t count;
        
        if (root == NULL) {
        	count = 0;
        } else {
        	count = root->_getCount();
        }
        return count;
        //#]
    }
    
    // get the element for a given key
    // Argument const void * theKey :
    // The key to look for
    //## operation getKey(void *) const
    inline void * getKey(const void * theKey) const {
        //#[ operation getKey(void *) const
        void* element;
        Item* item = lookUp(theKey);
        if (item != NULL) {
        	element = item->getElement();
        } else {
        	element = NULL;
        }
        return element;
        //#]
    }
    
    // check for empty map
    //## operation isEmpty() const
    inline bool isEmpty(void) const {
        //#[ operation isEmpty() const
        return (root == NULL);
        //#]
    }
    
    // find an element by its key
    // Place in "element" the element referenced by "theKey".
    // return true if found false otherwise
    // Argument const void * theKey :
    // The key to look for
    // Argument void *& element :
    // The element found
    //## operation lookUp(void *,void *) const
    //#[ ignore
    /*LDRA_INSPECTED 6 D : Can't make non recursive */  
    
    //#]
    inline bool lookUp(const void * theKey, void *& element) const {
        //#[ operation lookUp(void *,void *) const
        bool status = false;
        Item* item = lookUp(theKey);
        if (item != NULL) {
        	element = item->getElement();
        	status = true;
        }
        return status;
        //#]
    }
    
    // Assignment operator
    // Argument const OMUMap& aMap :
    // The map to copy
    //## operation operator=(OMUMap)
    inline OMUMap& operator=(const OMUMap& aMap) {
        //#[ operation operator=(OMUMap)
        copy(aMap);
        return (*this);
        //#]
    }
    
    // get the element for a given key
    // Argument const void * theKey :
    // The key to look for
    //## operation operator[](void *) const
    inline void * operator[](const void * theKey) const {
        //#[ operation operator[](void *) const
        return getKey(theKey);
        //#]
    }
    
    // remove an element from the map
    // Argument const void * anElement :
    // The element to remove
    //## operation remove(void *)
    //#[ ignore
    /*LDRA_INSPECTED 6 D : Can't make non recursive */  
    
    //#]
    inline void remove(const void * anElement) {
        //#[ operation remove(void *)
        if (root != NULL) {
        	Item* item = const_cast<Item*>(root->_find(anElement));
        	if (item != NULL) {
        		remove(item);   
        	}
        }
        //#]
    }
    
    // remove all elements in the map
    //## operation removeAll()
    inline void removeAll(void) {
        //#[ operation removeAll()
        if (root != NULL) {
        	delete root; 
        	root = NULL;
        }
        //#]
    }
    
    // remove an element from the map by its key
    // Argument const void * theKey :
    // The key to remove
    //## operation removeKey(void *)
    //#[ ignore
    /*LDRA_INSPECTED 6 D : Can't make non recursive */  
    
    //#]
    inline void removeKey(const void * theKey) {
        //#[ operation removeKey(void *)
        Item* item = lookUp(theKey);
        if (item != NULL) {
        	remove(item);
        }
        //#]
    }
    

protected :

    // Get the item in the provided position (supplied by the iterator)
    // Argument void * pos :
    // the current position (of the iterator)
    //## operation getCurrent(void *) const
    inline virtual void * getCurrent(void * pos) const {
        //#[ operation getCurrent(void *) const
        void* element = NULL;
        
        if (pos != NULL) {
        	element = static_cast<Item*>(pos)->getElement();
        }
        return element;
        //#]
    }
    
    // iteration interface - get the initial position
    // Argument void *& pos :
    // The position to set
    //## operation getFirst(void *) const
    inline virtual void getFirst(void *& pos) const {
        //#[ operation getFirst(void *) const
        if (root == NULL) {
        	pos = NULL;
        } else {
        	// Go to smallest item
        	Item* p = root;
        	while (p->smaller != NULL) {
        		p = p->smaller;
        	}
        	pos = p;
        }
        //#]
    }
    
    // Get the next position for the iterator
    // Argument void *& pos :
    // The current position
    //## operation getNext(void *) const
    inline virtual void getNext(void *& pos) const {
        //#[ operation getNext(void *) const
        Item* p = static_cast<Item*>(pos);
        
        if (p->larger != NULL) {
        	// Can we go down ?
        	p = p->larger;
        	while (p->smaller != NULL) {
        		p = p->smaller;
        	}
        } else {
        	// Must go up
        	Item* oldP = NULL;
        	do {
        		oldP = p;
        		p = p->parent;
        	} while ((p != NULL) && (p->larger == oldP));
        }
        pos = p;
        //#]
    }
    

private :

    // copy a map
    // Argument const OMUMap& aMap :
    // The map to copy
    //## operation copy(OMUMap)
    //#[ ignore
    /*LDRA_INSPECTED 6 D : Can't make non recursive */  
    
    //#]
    inline void copy(const OMUMap& aMap) {
        //#[ operation copy(OMUMap)
        if (root != aMap.root) {
        	// avoid self copy
        	copy(aMap.root);
        }
        //#]
    }
    
    // copy an item into the map
    // Argument const Item* item :
    // The item to copy
    //## operation copy(Item)
    inline void copy(const Item* item) {
        //#[ operation copy(Item)
        if (item != NULL) {
        	if (item->smaller != NULL) {
        		// recursive copy of smaller
        		copy(item->smaller);
        	}
        	if (item->larger != NULL) {
        		// recursive copy of larger
        		copy(item->larger);
        	}
        	// actual add to map
        	add(item->key, item->element);
        }
        //#]
    }
    
    // return a map item for a given key
    // Argument const void * theKey :
    // The key to look for
    //## operation lookUp(void *) const
    inline Item* lookUp(const void * theKey) const {
        //#[ operation lookUp(void *) const
        Item* item;
        
        if (root != NULL) {
        	item = root->_lookUp(theKey);
        } else {
        	item = NULL;
        }
        return item;
        //#]
    }
    
    // remove a map item
    // Argument Item* item :
    // The item to remove
    //## operation remove(Item)
    inline void remove(Item* item) {
        //#[ operation remove(Item)
        // Make sure we have a "handle" to the tree after deletion
        if (item == root) {
        	if (root->smaller != NULL) {
        		root = root->smaller;
        	} else {
        		if (root->larger != NULL) {
        			root = root->larger;
        		} else {
        			// Tree will be empty
        			root = NULL;
        		}
        	}
        }
        // Delete the actual element
        if (item != NULL) {
        	item->_removeYourSelf();
        }
        delete item;
        
        // Make sure the handle we have is still the root
        if (root != NULL) {
        	while (root->parent != NULL) {
        		root = root->parent;
        	}
        }
        //#]
    }
    
    ////    Relations and components    ////
    
    Item* root;		//## link root
    
};

#endif



