/*

  Problem: Given a singly linked list with a loop or no loop, find where we encounter the start of the loop.

  This is an example of a list with a loop:

                         ()<--\ 
                        /      \
                       /      /
                        ↘   /
  ()----> () ----> () --->()

                           ^ 
                           |-- this is the start of the loop

  This is an example of a list without a loop:

  ()----> () ----> ()

  Algorithm:
  Place a slow pointer (one that moves one step per iteration) at the head of the node list.
  Place a fast pointer (one that moves two steps per iteration) at the head's next element. 

  Let both pointers move until they are either: on the same node, or one has found the end of the list (a nullptr).
  If one has found the end of the list, return nullptr to signify that there is no loop.
  If the pointers are on the same node, then place a slow pointer at that node and also at the beginning of the list. 
  Check that the pointers are not on the same node, then move both pointers forward one step, and so on, until they both are on the same node. 
  Return the node both pointers end up both landing on. This is the beginning of the list. 

  Proof:

  The linked list is made of two components: a segment leading into the loop, and the loop.
  In the example of a list with a loop above, there is a segment of 3 nodes leading into the loop,
  and a loop of 2 nodes. 

  Let's call the length of the segment leading into the loop LEADING, and the length of the loop LOOP. 
  
  Assume that our linked list has LEADING >= 0 and LOOP >= 1.

  The number of nodes it takes for the slow pointer to get to the first node of the loop is LEADING + 1.
  After our slow pointer moves LEADING + 1 nodes, our fast pointer will have moved 2*LEADING + 2 nodes.
  
  They are now both in the loop. They are possibly on the same node or one is ahead/behind the other. 
  If we impose a modular number system on the loop, with 0 starting at the loop's beginning, and 1 at the 
  second element of the loop, 2 at the next element ... we can infer that the slow pointer is at node ( (LEADING + 1) mod LOOP), 
  and the fast pointer is at node ( (2*LEADING+2) mod LOOP).

  If the fast pointer is one node behind the slow pointer, the next time both pointers move, they will be on the same node. 
  If the fast pointer is two nodes behind the slow pointer, after both pointers move two times, they will be on the same node. 
  If the fast pointer is K nodes behind the slow pointer, after both pointers move K times, they will be on the same node. 
  We can calculate how many nodes the fast pointer is behind the slow pointer by subtracting the fast pointer's location from the slow pointer's location. 

  Thus, to find how many nodes the fast pointer is behind the slow pointer when the slow pointer is at the beginning of the loop,
  we can perform the calculation ( (LEADING + 1) mod LOOP) - ( (2*LEADING+2) mod LOOP). By the rules of modular arithmetic, we know this is equal to 
  ( -(LEADING + 1)  mod LOOP). This means both pointers collide at node # (-(LEADING + 1)  mod LOOP).

  This means that if let both pointers collide, then place a slow pointer at that node and place a slow pointer at the start, and then let both 
  slow pointers move until they are on the same node X, then X will be where the loop starts. 

  This is because moving the slow pointer placed at the start (LEADING+1) steps and the slow pointer placed at the "collision" point in the loop (LEADING+1) steps
  insures that both land on the 0th node of the loop, because after moving (LEADING+1) nodes from the start, you are at the loop's beginning, and moving (LEADING+1) steps from
  ( ( -(LEADING + 1)  mod LOOP) ) gets you to (0 mod LOOP), which is the loop's beginning. 

*/


struct Node {
  Node* ptr = nullptr;
};

Node* detectCycle(Node* start) {
  if(start == nullptr) return nullptr;
  
  Node* slowPointer = start;
  Node* fastPointer = start->ptr;

  //If there is a loop, let both pointers collide. If there is no loop, return nullptr
  while(slowPointer != fastPointer) {
    slowPointer = slowPointer->ptr;
    if(fastPointer) fastPointer = fastPointer->ptr;
    else return nullptr;
    if(fastPointer) fastPointer = fastPointer->ptr;
    else return nullptr;
  }

  Node* startingSlowPointer = start;
  Node* collisionSlowPointer = fastPointer;
  while(startingSlowPointer != collisionSlowPointer) {
    startingSlowPointer = startingSlowPointer->ptr;
    collisionSlowPointer = collisionSlowPointer->ptr;
  }

  return collisionSlowPointer;

}