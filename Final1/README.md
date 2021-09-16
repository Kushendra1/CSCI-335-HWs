Kushendra Ramrup
CSCI 335
Professor Raja
Final Exam

8 All work submitted must be your work only. If you refer to a source other than the text
book, state that in your answer.

First things first, as pointed out by instruction number 8 in the pdf that I copied over
above, for question 1 of th programming section I used geeksforgeeks to help me write the
code for finding the subsequence length. This is the article/page I looked at:
https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
The function I made uses a vector of vector of integers as a subsequence table of lengths instead
of geeksforgeeks' matrix table. At first I tried to make the table in a top to down manner,
breaking the problem into sub problems and then calculating and storing the values. I tried this
at first using a map key for the elements because I had a similar project over winter break for
codefest, however I haven't touched anything for codefest since it took place so I didn't
exactly remember everything. I also considered doing a hash map in the following set up:
empty string. hash longer word, loop through shorter word and use each character as a key.
If a keyed letter shows more than once and the frequency is higher than zero add it to the string
and change value to zero. If there's a key error just push forward. But I ended up using
the vector and subsequence table method, which turned out a lot easier.
Originally the function was just supposed to return the length of the subsequence and I tried
to make a separate function to try and return the the subsequence itslelf (down below), but I had
to abandon that idea because I need the subsequence_table of length values that stored and created
in this function to go through and find matching values in order to ge the letters of the subsequence
for the second function. There was no way for me to do that without making a class of subsequences
or something, so I ended up just putting it all in one function.

The second question was the easier of the two because in the lecture 23 folder,we were provided
with the "Chain Matrix Multiplication Reference" pdf. A very detailed document that talks about
the chain multiplication problem, how to go about solving it, and how to come up with a dynamic
algorithm to solve it. In there, on page 26 is pseudocode that basically answers the question.
Since we were allowed to use the lectures and resources from class, I assumed that this is one
of the resources as it was paired with a lecture, and followed the pseudocode.
After this, I had difficulties with converting the input file of strings into an array of
integers for the matrix_multiplication function to use and solve. So first I made the ifstream
function openFile that opens a ifstream based on the filename given. Then I made the function
make_vector to convert the ifstream into a vector of integers. I don't know how to directly convert
from a txt file to an array so I had the middle man of a vector of ints, which is easier to make
from the file, using the std::stoi function to convert strings to int. Then in the driver
function is where I converted the vector of integers to an array of integers so it can be used in the
matrix_multiplication function. I used the copy function in order to avoid using a loop, and
used the vector size as array size, since they would be the same.
