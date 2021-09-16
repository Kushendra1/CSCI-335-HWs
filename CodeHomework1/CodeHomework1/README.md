Kushendra Ramrup
2/5/2020
CSCI 335 Assignment 1
For Part 2

It is not very clear what exactly I have to do for this part of the assignment.
The instructions on the pdf are vague and at points contradictory, for example at one point it says we need to add some code to the file and in the nest line it says that has already been done. It also does not clearly state what exactly the points2 class does nor gives an apt description of it.

I am currently working on implementing the BIG 5 for the points2 class. This is very new waters for me so I am sure that I am going to make many mistakes. I am following along the Lecture 2 notes which is about Big Five implementation of another class, IntCell. This example is extremely helpful and I am trying to implement the functions in This
class in a similar way, taking note of the fact that I am dealing with arrays and not just values by themselves. In fact once I figure out the correct syntax pertaining to arrays I think Big 5 Implementation will be complete.

Today was filed completely with debugging the code as I kept getting weird seg fault messages.
Things like "free memory" or "mallock" which I had no idea what they meant. I ended up changing like half of my code before finding the problem. In Line 48 I were missing this line here. you deleted the sequence and starting making changes to memory I didn't own anymore, I forgot to allocate new memory after deleting.
