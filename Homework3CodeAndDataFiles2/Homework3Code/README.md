Kushendra Ramrup
4/7/2020
Professor Raja
CSCI 335

As I am writing this, my great uncle, a person who was like a grandfather to me has just
passed away at his home. I am not sure if it was from COVID 19 as he was confirmed with it
2 weeks ago or from a heart attack, which is what my parents are telling me happened. He
was recovering until tonight so comes to me as a shock. My cousin and his wife also have
contracted the virus, from caring for him, and are currently in the hospital also. I apologize
if my comments or README are not up to par as I definitely chose a bad time to write them, but
my mind isn't exactly clear right now.

The main issues I encountered when doing part 1 was counting the collisions that occurred during probing.
I first tried to have a counter in the private of the hashtable class, increment it where probing took place,
and then have an accessor return it. It then dawned on me that this was impossible and so I had to use the pass by
reference method. Creating the linear file was easy as all that had to be done was erasing the offset incrementing.

In part two for double hashing, I used prime numbers smaller than the table size. Since the table is huge, I just
used the first primes numbers that come up when counting: 3,5,7,11,13 and others. At first I was
thoroughly confused about how to even do double hashing so I had to go back to the online slides.
After the refresher I was still confused because I didn't know how to implement the double hashing function.
In the end I figured it had to be similar way the first hashing function was made and so I did that.
I also had trouble with figuring out the R values and passing it, but had help from some classmates and
figured it out.

The first thing I did in part 3 was make the helper function to simplify the words- taking out non
letter characters and keeping it in one case- because I tried to do the problem without simple words
and it was near impossible.  Then I went to make the other three helper functions for each case
of the spell checker. The most difficult one to make was the first- adding one character to any possible position.
So I made the functions for case 2 and 3 first instead and then by working through those I was able
to figure out case 1. They all use vectors to make up the candidate for replacing the misspelled words.
