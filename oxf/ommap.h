//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMMap
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


#ifndef ommap_H
#define ommap_H

//## class OMMap
#include "OMAbstractContainer.h"
//## dependency OMIterator
#include "OMIterator.h"
//## dependency Manager
#include "OXFManager.h"
//## package Design::oxf::Services::Containers::TypeSafe

//## class OMMap
// A binary balanced tree map
template <class Key, class Concept> class OMMap : public OMAbstractContainer<Concept> {
public :

    // A map item (node)
    //## class OMMap::Item
    class Item {
    public :
    
        ////    Friend List    ////
        
        friend  class OMMap<Key, Concept>;
        
        
    
    //#[ ignore
        // override new & delete operators
        OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
        
        
    //#]
    
        ////    Constructors and destructors    ////
        
    public :
    
        // Copy constructor
        // Argument const Item& item :
        // The item to copy
        //## operation Item(const Item&)
        inline Item(const Item& item) : concept(item.concept), key(item.key), larger(item.larger), 
parent(item.parent), rank(item.rank), smaller(item.smaller) {
            //#[ operation Item(const Item&)
            //#]
        }
        
        // Initialize a map item with a key and data
        // Argument Key theKey :
        // The item's key
        // Argument Concept theConcept :
        // The item's data
        //## operation Item(Key,Concept)
        inline Item(Key theKey, Concept theConcept) : concept(theConcept), key(theKey), larger(NULL), parent(NULL), 
rank(1), smaller(NULL) {
            //#[ operation Item(Key,Concept)
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
        
        // Get the item data
        //## operation getConcept()
        inline Concept& getConcept(void) {
            //#[ operation getConcept()
            return concept;
            //#]
        }
        
        // Assignment operator
        // Argument const Item& item :
        // The item to copy
        //## operation operator=(const Item&)
        inline Item& operator=(const Item& item) {
            //#[ operation operator=(const Item&)
            parent = item.parent;
            smaller = item.smaller;
            larger = item.larger;
            concept = item.concept;	// assuming operator = () for Concept
            key = item.key;
            rank = item.rank;
            return (*this);
            //#]
        }
        
    
    private :
    
        // Add an item to this sub tree
        // Argument Item* item :
        // The item to add
        //## operation _add(Item*)
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
        
        // Balance the sub tree
        //## operation _addCheckBalance()
        inline void _addCheckBalance(void) {
            //#[ operation _addCheckBalance()
            if (parent != NULL) {
            	// not balanced
            	Item* grandpa = parent->parent;
            	if ( (grandpa == NULL) || (grandpa->rank == rank+1) ) {
            		// balanced or tree of depth 2 (hence balanced)
            	} else {
            		// "this" is unbalanced
            		// Try to "promote"
            		if ( (grandpa->larger!=NULL && grandpa->smaller!=NULL) &&
            			 (grandpa->larger->rank == grandpa->smaller->rank) ) {
            			// The two red sons case
            			grandpa->rank++;
            			grandpa->_addCheckBalance();
            		} else {
            			// Must do a rotation
            			if (grandpa->smaller==parent) {
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
            					Item* myParent = parent;
            					grandpa->_connectParent(this);
            					// Connect "b" to parent
            					myParent->_connectLarger(smaller);
            					// Connect "c" to grandpa
            					grandpa->_connectSmaller(larger);
            					// connect parent to me
            					_connectSmaller(myParent);
            					_connectLarger(grandpa);
            				}
            			} else { // grandpa->larger==parent
            				// The Left rotation case
            				if (parent->larger == this) {
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
            					Item* myParent = parent;
            					grandpa->_connectParent(this);
            					// Connect "c" to parent
            					myParent->_connectSmaller(larger);
            					// Connect "b" to grandpa
            					grandpa->_connectLarger(smaller);
            					// connect parent to me
            					_connectSmaller(grandpa);
            					_connectLarger(myParent);
            				}
            			}
            		}
            	}
            }
            //#]
        }
        
        // Connect the item to the sub tree
        // Argument Item*& side :
        // The sub tree
        // Argument Item* item :
        // The item to connect
        //## operation _connect(Item*&,Item*)
        inline void _connect(Item*& side, Item* item) {
            //#[ operation _connect(Item*&,Item*)
            side = item;
            if (item != NULL) {
            	item->parent = this;
            }
            //#]
        }
        
        // Connect the item to the right sub tree
        // Argument Item* item :
        // The item to connect
        //## operation _connectLarger(Item*)
        inline void _connectLarger(Item* item) {
            //#[ operation _connectLarger(Item*)
            _connect(larger,item);
            //#]
        }
        
        // Connect the item to the parent sub tree
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
        
        // Connect the item to the left sub tree
        // Argument Item* item :
        // The item to connect
        //## operation _connectSmaller(Item*)
        inline void _connectSmaller(Item* item) {
            //#[ operation _connectSmaller(Item*)
            _connect(smaller,item);
            //#]
        }
        
        // Find the element in the sub tree
        // Argument const Concept & aConcept :
        // The element to find
        //## operation _find(const Concept & ) const
        inline Item* _find(const Concept & aConcept) const {
            //#[ operation _find(const Concept & ) const
            Item* anItem;
            
            if (aConcept == concept) {
            	// Found in me
            	anItem = const_cast<Item*>(this);
            } else {
            	Item* inSmaller = NULL;
            	if (smaller) {
            		// Look in smaller
            		inSmaller = smaller->_find(aConcept);
            	}
            
            	if (inSmaller != NULL) {
            		// Found in smaller
            		anItem = inSmaller;
            	} else {
            		if (larger) {
            			// Look in larger
            			anItem = larger->_find(aConcept);
            		} else {
            			anItem = NULL;
            		}
            	}       
            }
            return anItem;
            //#]
        }
        
        // Find a key in the sub tree - this is an O(log(N)) operation
        // Argument const Key aKey :
        // The key to look for
        //## operation _lookUp(const Key )
        inline Item* _lookUp(const Key aKey) {
            //#[ operation _lookUp(const Key )
            Item* anItem;
            
            if (key == aKey) {
            	anItem = this;
            } else {
            	if (key > aKey) {
            		if (smaller == NULL) {
            			anItem = NULL;
            		} else {
            			anItem = smaller->_lookUp(aKey);
            		}
            	} else {
            		if (larger == NULL) {
            			anItem = NULL;
            		} else {
            			anItem = larger->_lookUp(aKey);
            		}
            	}
            }  
            return anItem;
            //#]
        }
        
        // Cleanup the sub tree
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
        
        // Balance the sub tree after remove
        //## operation _removeCheckBalance()
        inline void _removeCheckBalance(void) {
            //#[ operation _removeCheckBalance()
            // Compute minimal rank of sons
            Rhp_int32_t minRank;
            
            if ( (smaller == NULL) || (larger == NULL) ) {
            	minRank = 0;
            } else {
            	if ( smaller->rank < larger->rank) {
            		minRank = smaller->rank;
            	} else {
            		minRank = larger->rank;
            	}
            }
            
            if (rank < minRank + 2) {
            	// My rank is o.k.
            } else {
            	// "this" is unbalanced
            	if ( (smaller == NULL) || (rank == (smaller->rank + 2)) ) {
            		// Note "larger" cannot be NULL as "smaller" has the minRank
            		if (larger->rank == rank) {
            			// (d) case - make a single right rotation
            			//              this		               theLarger
            			//		  smaller	theLarger   ===>     this      c   
            			//		            b        c      smaller   b      
            			// connect theLarger to rest of tree
            			Item* theLarger = larger;
            			_connectParent(theLarger);
            			// connect "b" to this
            			_connectLarger(theLarger->smaller);
            			// connect this to theLarger
            			theLarger->_connectSmaller(this);
            			// Check again -- should terminate in one iteration
            			_removeCheckBalance();
            		} else {
            			if ( (larger->smaller == NULL) ||
            				 (larger->smaller->rank == rank - 2) ) {
            				if ( (larger->larger == NULL) ||
            					 (larger->larger->rank == rank - 2) ) {
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
            					Item* theLarger = larger;
            					_connectParent(theLarger);
            					// Connect "b" to this
            					_connectLarger(theLarger->smaller);
            					// Connect this to theLarger
            					theLarger->_connectSmaller(this);
            					rank--;
            					theLarger->rank++;
            				}
            			} else {
            				// larger->smaller->rank==rank+1
            				if ( (larger->larger == NULL) ||
            					 (larger->larger->rank==rank - 2) ) {
            					// case c
            					//          this  		              son  
            					//	 smaller   larger     ===>	  this    larger
            					//		      son    d        smaller  b  c     d
            					//	        b    c
            					// connect son to rest of tree
            					Item* son = larger->smaller;
            					_connectParent(son);
            					// Connect "c" to larger
            					larger->_connectSmaller(son->larger);
            					// connect larger to son
            					son->_connectLarger(larger);
            					// Connect "b" to this
            					_connectLarger(son->smaller);
            					// Connect son to this
            					son->_connectSmaller(this);
            					rank--;
            					son->rank++;
            				} else {
            					// case b2
            					//        this  		              larger 
            					//	smaller   larger     ===>	 this     son2
            					//		    son1   son2    smaller  son1  d   e
            					//	       b    c  d   e		   b	c
            					// connect theLarger to rest of tree
            					Item* theLarger = larger;
            					_connectParent(larger);
            					// connect son1 to this
            					_connectLarger(theLarger->smaller);
            					// connect this to theLarger
            					theLarger->_connectSmaller(this);
            					rank--;
            					theLarger->rank++;
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
            			Item* theSmaller = smaller;
            			_connectParent(theSmaller);
            			// connect "c" to this
            			_connectSmaller(theSmaller->larger);
            			// connect this to theSmaller
            			theSmaller->_connectLarger(this);
            			// Check again -- should terminate in one iteration
            			_removeCheckBalance();
            		} else {
            			if ( (smaller->larger == NULL ) ||
            				 (smaller->larger->rank == (rank-2)) ) {
            				if ( (smaller->smaller == NULL ) ||
            					 (smaller->smaller->rank == (rank-2)) ) {
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
            					Item* theSmaller = smaller;
            					_connectParent(theSmaller);
            					// Connect "c" to this
            					_connectSmaller(theSmaller->larger);
            					// Connect this to theSmaller
            					theSmaller->_connectLarger(this);
            					rank--;
            					theSmaller->rank++;
            				}
            			} else {
            				// smaller->larger->rank==rank+1
            				if ( (smaller->smaller == NULL ) ||
            					 (smaller->smaller->rank == (rank-2)) ) {
            					// case c
            					//         this 		          son  
            					//	  smaller  larger ===>	smaller  this  
            					//	 a     son             a      b  c   larger
            					//	      b    c
            					// connect son to rest of tree
            					Item* son = smaller->larger;
            					_connectParent(son);
            					// connect "b" to smaller
            					smaller->_connectLarger(son->smaller);
            					// Connect smaller to son
            						son->_connectSmaller(smaller);
            					// Connect "c" to 
            					_connectSmaller(son->larger);
            					// Connect son to this
            					son->_connectLarger(this);
            					rank--;
            					son->rank++;
            				} else {
            					// case b2
            					//         this 		          smaller
            					//    smaller   larger ===>	  son1      this
            					// son1   son2               a    b  son2   larger
            					//a    b  c   d		                c	 d
            					// connect smaller to rest of tree
            					Item* theSmaller = smaller;
            					_connectParent(theSmaller);
            					// connect son1 to this
            					_connectSmaller(theSmaller->larger);
            					// connect this to theSmaller
            					theSmaller->_connectLarger(this);
            					rank--;
            					theSmaller->rank++;
            				}
            			}
            		}
            	}
            }
            //#]
        }
        
        // Remove this item from the map
        //## operation _removeYourSelf()
        inline void _removeYourSelf(void) {
            //#[ operation _removeYourSelf()
            // make sure I have "smaller==NULL"
            if (smaller != NULL) {
            	if (larger != NULL) {
            		// case    this
            		//		  a    b 
            		// exchange place with my successor in the order
            		Item* item;
            		for (item = larger; item->smaller; item = item->smaller) {
            			// no action
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
        
        // Switch tree position with the specified item
        // Argument Item* other :
        // The item to switch with
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
            Rhp_int32_t IShouldBeSmaller=0;
            Rhp_int32_t HeShouldBeSmaller=0;
            Rhp_int32_t IShouldBeLarger=0;
            Rhp_int32_t HeShouldBeLarger=0;
            
            Rhp_int32_t hisNewRank = rank;
            Rhp_int32_t myNewRank = rank;
            
            if (parent == other) {
            	hisNewParent = this;
            } else {
            	hisNewParent = parent;
            }
            
            if (larger == other) {
            	hisNewLarger = this;
            } else {
            	hisNewLarger = larger;
            }
            
            if (smaller == other) {
            	hisNewSmaller = this;
            } else {
            	hisNewSmaller = smaller;
            }
            
            if (other->parent == this) {
            	myNewParent = other;
            } else {
            	myNewParent = other->parent;
            }
            
            if (other->larger == this) {
            	myNewLarger = other;
            } else {
            	myNewLarger = other->larger;
            }
            
            if (other->smaller == this) {
            	myNewSmaller = other;
            } else {
            	myNewSmaller = other->smaller;
            }
            
            if (parent != NULL) {
            	if (parent->smaller == this) {
            		HeShouldBeSmaller = 1;
            	} else {
            		HeShouldBeLarger = 1;
            	}
            }
            
            if (other->parent != NULL) {
            	if (other->parent->smaller == other) {
            		IShouldBeSmaller = 1;
            	} else {
            		IShouldBeLarger = 1;
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
            if (smaller) {
            	smaller->parent = this;
            }
            if (larger) {
            	larger->parent = this;
            }
            if (other->smaller) {
            	other->smaller->parent = other;
            }
            if (other->larger) {
            	other->larger->parent = other;
            }
            //#]
        }
        
        ////    Additional operations    ////
        
    
    public :
    
        //## auto_generated
        inline void setConcept(Concept p_concept) {
            //#[ auto_generated
            concept = p_concept;
            //#]
        }
        
        //## auto_generated
        inline Key getKey(void) const {
            //#[ auto_generated
            return key;
            //#]
        }
        
        //## auto_generated
        inline void setKey(Key p_key) {
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
        inline void setRank(Rhp_int32_t p_rank) {
            //#[ auto_generated
            rank = p_rank;
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
        Concept concept;		//## attribute concept
        
        // The item key
        Key key;		//## attribute key
        
        // The right sub tree
        Item* larger;		//## attribute larger
        
        // The parent node in the tree
        Item* parent;		//## attribute parent
        
        // The item rank in the balanced tree
        Rhp_int32_t rank;		//## attribute rank
        
        // The left sub tree
        Item* smaller;		//## attribute smaller
        
    };
    
    ////    Constructors and destructors    ////
    
    // Constructor
    //## operation OMMap()
    inline OMMap(void) : count_(0U), root(NULL) {
        //#[ operation OMMap()
        //#]
    }
    
    // copy constructor
    // Argument const OMMap<Key, Concept>& aMap :
    // The map to copy
    //## operation OMMap(const OMMap<Key, Concept>&)
    inline OMMap(const OMMap<Key, Concept>& aMap) : count_(0U), root(NULL) {
        //#[ operation OMMap(const OMMap<Key, Concept>&)
        copy(aMap);
        //#]
    }
    
    // Destructor	
    //## operation ~OMMap()
    inline ~OMMap(void) {
        //#[ operation ~OMMap()
        removeAll();
        //#]
    }
    
    ////    Operations    ////
    
    // Add an element to the map using the provided key.
    // Argument Key aKey :
    // The key
    // Argument Concept aConcept :
    // The data
    //## operation add(Key ,Concept )
    inline void add(Key aKey, Concept aConcept) {
        //#[ operation add(Key ,Concept )
        Item* item = new Item(aKey,aConcept);
        
        if (root==NULL) {
        	root = item;
        } else {
        	root->_add(item);
        	while (root->parent != NULL) {
        		root = root->parent;
        	}
        }
        ++count_;
        //#]
    }
    
    // Find an element in the map
    // Argument Concept aConcept :
    // The element to find
    //## operation find(Concept ) const
    inline Rhp_int32_t find(Concept aConcept) const {
        //#[ operation find(Concept ) const
        Rhp_int32_t status = 0;
        
        if ( root != NULL ) {
        	if ( root->_find(aConcept) ) {
        		status = 1; 
        	}
        }
        return status;
        //#]
    }
    
    // Get an element from the map using an index
    // Argument const Rhp_int32_t anIndex :
    // The index
    //## operation getAt(Rhp_int32_t) const
    inline Concept & getAt(const Rhp_int32_t anIndex) const {
        //#[ operation getAt(Rhp_int32_t) const
        void* item; 
        
        getFirst(item);
        for (Rhp_int32_t j=0; j<anIndex; j++) {
        	if (item != NULL) {
        		getNext(item);
        	} else {
        		break;
        	}
        }
        return getCurrent(item);
        //#]
    }
    
    // Get the element with the specified key
    // Argument const Key& aKey :
    // The key
    //## operation getKey(const Key& ) const
    inline Concept & getKey(const Key& aKey) const {
        //#[ operation getKey(const Key& ) const
        /*LDRA_INSPECTED 7 C  : Can't find a way to have a single return */
        Item* item = lookUp(aKey);
        if (item != NULL) {
          	return item->getConcept();
        } else {
           	return OMNullValue<Concept>::get();
        }
        //#]
    }
    
    // Check if the map is empty
    //## operation isEmpty() const
    inline Rhp_int32_t isEmpty(void) const {
        //#[ operation isEmpty() const
        return (root == NULL);
        //#]
    }
    
    // Find an element in the map based on a key
    // return 1 if found, 0 otherwise
    // Argument const Key & aKey :
    // The key
    // Argument Concept & aConcept :
    // The data found for the specified key (out)
    //## operation lookUp(const Key & ,Concept & ) const
    inline Rhp_int32_t lookUp(const Key & aKey, Concept & aConcept) const {
        //#[ operation lookUp(const Key & ,Concept & ) const
        Rhp_int32_t status = 0;
        Item* item = lookUp(aKey);
        if (item != NULL) {
        	// Place in "aConcept" the concept referenced by "aKey"
        	aConcept = item->getConcept();
        	status = 1;
        }
        return status;
        //#]
    }
    
    // Assignment operator
    // Argument const OMMap<Key,Concept> & aMap :
    // The map to copy
    //## operation operator=(const OMMap<Key,Concept> & )
    inline OMMap<Key,Concept> & operator=(const OMMap<Key,Concept> & aMap) {
        //#[ operation operator=(const OMMap<Key,Concept> & )
        copy(aMap);
        return (*this);
        //#]
    }
    
    // Get the element in the map using a key
    // Argument const Key & aKey :
    // The key
    //## operation operator[](const Key & )
    inline Concept & operator[](const Key & aKey) {
        //#[ operation operator[](const Key & )
        return getKey(aKey);
        //#]
    }
    
    // Remove a key from the map
    // Argument Key aKey :
    // The key
    //## operation remove(Key )
    inline void remove(Key aKey) {
        //#[ operation remove(Key )
        Item* item = lookUp(aKey);
        if (item != NULL) {
        	removeItem(item);
        }
        //#]
    }
    
    // Remove an element from the map
    // Argument Concept aConcept :
    // The element
    //## operation remove(Concept )
    //#[ ignore
    #ifndef OMMAP_PARAMS_OF_SAME_TYPE
    
    //#]
    inline void remove(Concept aConcept) {
        //#[ operation remove(Concept )
        removeByConcept(aConcept);
        //#]
    }
    //#[ ignore
    
    #endif // OMMAP_PARAMS_OF_SAME_TYPE
    //#]
    
    // Cleanup
    //## operation removeAll()
    inline void removeAll(void) {
        //#[ operation removeAll()
        if (root != NULL) {
        	delete root; 
        	root = NULL;
        	count_ = 0U;
        }
        //#]
    }
    
    // Remove an element from the map
    // Argument Concept aConcept :
    // The element
    //## operation removeByConcept(Concept )
    inline void removeByConcept(Concept aConcept) {
        //#[ operation removeByConcept(Concept )
        if (root != NULL) {
        	Item* item = root->_find(aConcept);
        	if (item != NULL) {
        		removeItem(item);
        	}
        }
        //#]
    }
    

protected :

    // Get the element at the given position (called by the iterator)
    // Argument void * pos :
    // The iterator position
    //## operation getCurrent(void *) const
    inline virtual Concept & getCurrent(void * pos) const {
        //#[ operation getCurrent(void *) const
        /*LDRA_INSPECTED 7 C  : Can't find a way to have a single return */
        if (pos != NULL) {
           	return reinterpret_cast<Item*>(pos)->concept;
        } else {
           	return OMNullValue<Concept>::get();
        }
        //#]
    }
    
    // Set the initial position for the iterator
    // Argument void*& pos :
    // The map tree-root address (out)
    //## operation getFirst(void*& ) const
    inline virtual void getFirst(void*& pos) const {
        //#[ operation getFirst(void*& ) const
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
    
    // Update the provided position to the next position in the container
    // Argument void*& pos :
    // The iterator position to advance
    //## operation getNext(void*& ) const
    inline virtual void getNext(void*& pos) const {
        //#[ operation getNext(void*& ) const
        Item* p = reinterpret_cast<Item*>(pos);
        if (p->larger != NULL) { // Can we go down ?
        	p = p->larger;
        	while (p->smaller != NULL) {
        		p = p->smaller;
        	}
        } else { 
        	// Must go up
        	Item* oldP;
        	do {
        		oldP = p;
        		p = p->parent;
        	} while ( (p != NULL) && (p->larger == oldP) );
        }
        pos = p;
        //#]
    }
    

private :

    // Copy a map
    // Argument const OMMap<Key,Concept> & aMap :
    // The map to copy
    //## operation copy(const OMMap<Key,Concept> & )
    inline void copy(const OMMap<Key,Concept> & aMap) {
        //#[ operation copy(const OMMap<Key,Concept> & )
        if (root != aMap.root) {
        	// avoid self copy
        	copy(aMap.root);
        }
        //#]
    }
    
    // Copy a sub tree
    // Argument const Item* anItem :
    // The sub tree to copy
    //## operation copy(const Item*)
    inline void copy(const Item* anItem) {
        //#[ operation copy(const Item*)
        if (anItem != NULL) {
        	if (anItem->smaller != NULL) {
        		// recursive copy of smaller
        		copy(anItem->smaller);
        	}
        	if (anItem->larger != NULL) {
        		// recursive copy of larger
        		copy(anItem->larger);
        	}
        	// actual add to map
        	add(anItem->key, anItem->concept);
        }
        //#]
    }
    
    // Find an item in the map based on a key
    // Argument const Key & aKey :
    // The key
    //## operation lookUp(const Key & ) const
    inline Item* lookUp(const Key & aKey) const {
        //#[ operation lookUp(const Key & ) const
        Item* item = NULL;
        
        if (root != NULL) {
        	item = root->_lookUp(aKey);
        }
        return item;
        //#]
    }
    
    // Remove an item from the map tree
    // Argument Item* anItem :
    // The item to remove
    //## operation removeItem(Item*)
    inline void removeItem(Item* anItem) {
        //#[ operation removeItem(Item*)
        // Make sure we have a "handle to the tree after deletion
        if (anItem == root) {
        	if (root->smaller != NULL) {
        		root = root->smaller;
        	} else {
        		if (root->larger != NULL) {
        			root = root->larger;
        		} else {
        			root = NULL; // Tree will be empty
        		}
        	}
        }
        // Delete the actual element
        if (anItem != NULL) {
        	anItem->_removeYourSelf();
        	delete anItem;
        	--count_;
        }
        // Make sure the handle we have is still the root
        if (root != NULL) {
        	while (root->parent != NULL) {
        		root = root->parent;
        	}
        }
        //#]
    }
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    inline Rhp_int32_t getCount(void) const {
        //#[ auto_generated
        return count_;
        //#]
    }
    
    ////    Attributes    ////
    

private :

    // The number of elements in the map
    Rhp_int32_t count_;		//## attribute count_
    
    // The tree root
    Item* root;		//## attribute root
    
};

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMMap

#endif



