/***********************************************************************
 * Header:
 *    PRIORITY QUEUE
 * Summary:
 *    Our custom implementation of std::priority_queue
 *      __      __     _______        __
 *     /  |    /  |   |  _____|   _  / /
 *     `| |    `| |   | |____    (_)/ /
 *      | |     | |   '_.____''.   / / _
 *     _| |_   _| |_  | \____) |  / / (_)
 *    |_____| |_____|  \______.' /_/
 *
 *
 *    This will contain the class definition of:
 *        priority_queue          : A class that represents a Priority Queue
 * Author
 *    Daniel Carr, Jarom Anderson, Arlo Jolly
 ************************************************************************/

#pragma once

#include <cassert>
#include "vector.h" // for default underlying container

class TestPQueue;    // forward declaration for unit test class

namespace custom
{

/*************************************************
 * P QUEUE
 * Create a priority queue.
 *************************************************/
template<class T, class Container = custom::vector<T>, class Compare = std::less<T>>
class priority_queue
{
   friend class ::TestPQueue; // give the unit test class access to the privates
   template <class TT, class CContainer, class CCompare>
   friend void swap(priority_queue<TT, CContainer, CCompare>& lhs, priority_queue<TT, CContainer, CCompare>& rhs);

public:

   //
   // construct
   //
   priority_queue(const Compare& c = Compare()) : compare(c) { }
   priority_queue(const priority_queue& rhs, const Compare& c = Compare()) : compare(c) { container = rhs.container; }
   priority_queue(priority_queue&& rhs, const Compare& c = Compare()) : compare(c) { container = std::move(rhs.container); }
   template <class Iterator>
   priority_queue(Iterator first, Iterator last, const Compare& c = Compare()) : compare(c)
   {
      container.reserve(last - first);
      for (auto it = first; it != last; ++it)
         push(*it);
   }
   explicit priority_queue(const Compare& c, Container&& rhs) : compare(c), container(std::move(rhs)) {
      heapify();
   }
   explicit priority_queue(const Compare& c, Container& rhs) : compare(c), container(rhs) {
      heapify();
   }
   ~priority_queue() { }

   //
   // Access
   //
   const T & top() const;

   //
   // Insert
   //
   void  push(const T& t);
   void  push(T&& t);

   //
   // Remove
   //
   void  pop();

   //
   // Status
   //
   size_t size()  const { return container.size(); }

   bool empty() const { return size() == size_t(0);}

private:

   void heapify();                            // convert the container in to a heap
   bool percolateDown(size_t indexHeap);      // fix heap from index down. This is a heap index!

   Container container;       // underlying container (probably a vector)
   Compare   compare;         // comparision operator

};

/************************************************
 * P QUEUE :: TOP
 * Get the maximum item from the heap: the top item.
 ***********************************************/
template <class T, class Container, class Compare>
const T & priority_queue <T, Container, Compare> :: top() const
{
   if (!container.empty()) // test to see if exeption needs thrown
      return container.front();
   else
      throw std::out_of_range("std:out_of_range");

}

/**********************************************
 * P QUEUE :: POP
 * Delete the top item from the heap.
 **********************************************/
template <class T, class Container, class Compare>
void priority_queue <T, Container, Compare> :: pop()
{
   // stubbed out the best I could does not compile
   /* T* temp = container[0];
   container[0] = container[size() - 1];
   container[size() - 1] = temp;
   container.pop_back();
   percolateDown(); */
}

/*****************************************
 * P QUEUE :: PUSH
 * Add a new element to the heap, reallocating as necessary
 ****************************************/
template <class T, class Container, class Compare>
void priority_queue <T, Container, Compare> :: push(const T & t)
{
   // stubbed out the best I could does not compile
   //container.push_back(t);
   size_t i = size() / 2;
   while (i && percolateDown(i))
      i /= 2;
}
template <class T, class Container, class Compare>
void priority_queue <T, Container, Compare> :: push(T && t)
{
   // stubbed out the best I could does not compile
   //container->push_back(t);
   size_t i = size() / 2;
   while (i && percolateDown(i))
      i /= 2;
}

/************************************************
 * P QUEUE :: PERCOLATE DOWN
 * The item at the passed index may be out of heap
 * order. Take care of that little detail!
 * Return TRUE if anything changed.
 ************************************************/
template <class T, class Container, class Compare>
bool priority_queue <T, Container, Compare> :: percolateDown(size_t indexHeap)
{

   // Find the left child and the right child of index indexLeft <- index x 2
   size_t indexLeft = indexHeap * 2;
   size_t indexRight = indexLeft + 1;
   size_t indexBigger = indexHeap;

   using std::swap;
   // Check to see if indexRight and indexLeft exist
   if (indexRight <= container.size() && indexLeft <= container.size())
   {

      // Find which child is bigger, the left child or the right child?
      if (indexRight <= container.size() && container[indexLeft - 1] < container[indexRight - 1])
         indexBigger = indexRight;
      else
         indexBigger = indexLeft;

      // If the bigger child is greater than the parent, then swap it
      if (container[indexHeap - 1] < container[indexBigger - 1])
      {
         swap(container[indexHeap - 1], container[indexBigger - 1]);
         percolateDown(indexBigger);
         return true;
      }

   }
   return false;
}

/************************************************
 * P QUEUE :: HEAPIFY
 * Turn the container into a heap.
 ************************************************/
template <class T, class Container, class Compare>
void priority_queue <T, Container, Compare> ::heapify()
{
   for (int i = container.size() / 2; i >= 0; i--)
      percolateDown(i);
}

/************************************************
 * SWAP
 * Swap the contents of two priority queues
 ************************************************/
template <class T, class Container, class Compare>
inline void swap(custom::priority_queue <T, Container, Compare> & lhs,
                 custom::priority_queue <T, Container, Compare> & rhs)
{
   using std::swap;
   swap(lhs.container, rhs.container);
   swap(lhs.compare, rhs.compare);
}

};
