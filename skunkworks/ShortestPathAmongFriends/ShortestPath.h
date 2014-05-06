/*
 * ShortestPath.h
 *
 *  Created on: 05-May-2014
 *      Author: neerajnandakumar
 */

#ifndef SHORTESTPATH_H_
#define SHORTESTPATH_H_

namespace convo
{

class ShortestPath
{
public:
    ShortestPath ();
    ~ShortestPath ();

   List<Profile> getFriends(Profile A);  //Given



   list<Profile> findShortestPath(Profile A, Profile B)  //returns the shortest path between A & B through their mutual friends (if any)
   {
       // queue to track immediate nodes
       vector<Profile> queue;

       // list to track immediate nodes
       unordered_set<Profile> visited;

       //list to track the result set
       list<Profile> resultset;

       // Add the first element . Here its A.
       queue.push_back (A);

       while (queue.size () != 0) // check for queue not empty
       {
           Profile t = queue.pop_front (); // get the front item

           resultset.push_back (t); // add visited to the current node

           // assuming == is implemented
           // if t is B  we have our result
           // track the list of nodes/profile path here
           // return path
           if (t == B)
           {
               return resultset;
           }

           List<Profile> friends = getFriends (t); // check for each friend, so get the friendlist

           // check for each friend.
           for (auto& friendi : friends)
           {
                // if visited ignore
                // track visited here
               if (visited.find (friendi) == visited.end ())
               {
                   continue;
               }
               else
               {
                   // now consider it visited.
                   visited.insert (friendi);
                   queue.push_back (friendi);
               }
           }
       }
   }
};

} /* namespace convo */

#endif /* SHORTESTPATH_H_ */
