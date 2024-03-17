#pragma once

#include <list>

template<typename T>
class ObjectPooler
{
	 private:
	    // All the Objects in the Pool
	    std::list<T> objs;
	    // Objects free for use
	    std::list<T*> free;
	    // Objects already in use
	    std::list<T*> used;

	 public:

	    ObjectPooler() : free(), used() {}
		
	    // Get and object from the pool
	    T* get() 
	    {
	        if (free.empty())
	        {  
	            // Create a new object if the list is empty
	            objs.push_back(T());
	            used.push_back(&objs.back());
	        } 
	        else
	        {  
	            // Gets the last free object into the used list
	            used.push_back(free.back());
	            free.pop_back();
	        }
			// returns the last object in the used list
	        return used.back();
	    }

	    // Saves the object back for reuse it again
	    inline void put(T* obj) 
	    {
	        // Removes the object from the used list
	        used.remove(obj);
	        // Sets the object free to use
	        free.push_back(obj);
	    }

		// Get the used list where the Pooled Objects are
	    std::list<T*> getPooledObjects() const { return used; }
};