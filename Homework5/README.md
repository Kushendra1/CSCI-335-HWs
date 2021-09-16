Kushendra Ramrup
CSCI 335
Professor Raja
Assignment 5

When working on the first part of the assignment I had trouble actually visualizing in my mind
what the graph was going to look like. If I can't see something like this in my head, then I don't
understand it well enough. Part f the reason it was so difficult was because I had to make
everything from scratch, which is an idea I am still getting used to. Of course I know in the real
word there won't be any given code like what I've dealt with in the 35 courses but it was still an adjustment
for me. After going back through class lectures and slides, I didn't grasp the concept enough, so
I turned to geeksforgeeks: https://www.geeksforgeeks.org/graph-and-its-representations/
and softwaretestinghelp: https://www.softwaretestinghelp.com/graph-implementation-cpp/
These articles right here saved me, because it has a pretty simple and effective take on adjaceny lists
and their graph representations. It also gave me the idea, from their practice code, of how to
implement my connection function based off of their addEdge function- to connect to vertices using
a weighted edge.

Another problem I had was when I was trying to make my vertex structure. It was minor but when I tried to
implement in publicly in my graph class I would get error messages when compiling along the lines of
the struct was not declared or some of its struct members like vertex_ and real_ver_ were not declared.
So because of this, I moved it to the private section of the graph class and the errors were gone. I also
considered just making vertex its own class instead on an inside struct, but I was already too far in for
my tastes so I didn't go through with that.  The compiler also had me compile in c++14 which was new.

The second part of the assignment was where I spent the better part of the week on. Dijkstra's Algorithm
is a concept that also confused me from class, but it was on a higher level than visualizing a graph. I
turned to a couple of friends for help who then directed me to the textbook which had a lengthy bit to
say about it and also some psuedocode in it. But I still didn't fully understand it and again wetnt to
geeksforgeeks: https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/
which had a way longer and more detailed article this time around, with practice code as long if not longer
than what I ended up with. I know that this paricular page from them is really in depth, but I used this along
with the textbook as references to make my own code. They were both amazing helps when combined and cross
referenced.

After I got my Dijkstra Algorithm functions down, the main problem I encountered which then cause me to
near 50 submissions to gradescope - because I thought I was going crazy- was correctly outputting information
and also printing out the "not_possible" statement when there does NOT exist a path to a particular vertex in
the graph. I tried seperate and second isConnected function first, called isConnectedDi - where the only
difference was an additional if statement that checked to see if a vertex points to nullptr and then the print
statements would go from there. That however didn't work for all tests, and I spent a coupe of hours editing the
inputs to take different properties of the vertex struct because since it worked for one of the tests, I thought
only a little editing to inputs would get it to work for all. It didn't and I scraped the function.

Another function I made, was the path function which ultimately had the same goal but went about it differently.
I had to scrap this function also but because I was getting conversion errors pointing to what I was inputing
and also seg faults whenever it compiled. So I believe it could still work, if I had more time to figure it out- so
I kept it. I ended up figuring out how to get this all working when I started o comment my code, because I
wanted to make progress somewhere, and I in the Dijkstra function I came back across how I established that
two vertices weren't connected sing INT_MAX. It was the main problem of my other two funcs, which I thought
were input related but I wasn't correctly laying out how to recognize when two weren't connected. So after rediscovering
this, I didn't need a function and all I had to do was use an if statement with INT_MAX and I was good to go.
