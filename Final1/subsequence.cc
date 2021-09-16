/* Kushendra Ramrup
CSCI 335
Professor Raja
Final Exam

Given two sequences A= a1,a2,…am and B= b1,b2,…bN find the length, k, of the longest
subsequence C= c1,c2,…cm such that C is a subsequence (not necessarily contiguous) of both A and B.
Write an algorithm to solve the longest common subsequence problem in O(MN) time.
Your program should take two arguments, word_a and word_b.
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* The function subsequence_length is used for solving the longest common subsequence problem
in o(MN) time. It takes in two words @word_a and @word_b and returns an integer variable
of the subsequence_table which represents the length of the longest common subsequence. It also
prints out the length and the characters themselves. Originally this was just supposed to return
the length of the subsequence and I tried to make a separate function to try and return the the
subsequence itslef (down below), but I had to abandn that idea because I need the subsequence_table
of length values that stored and created in this function to go through and find matching values in
order to ge the letters of the subsequence for the second function. There was no way for me to do that
without making a class of subsequences or somethng, so I ended up just putting it all in
ine function.
*/
int subsequence_length(string word_a, string word_b) {
	int length_a = word_a.length(), length_b = word_b.length();
	vector < vector <int> > subsequence_table (length_a + 1);  //subsequence_table[i][j] stores the length of longest common subsequence of substring

	for (int i = 0; i < length_a + 1; i++) {	//converts vector to two dimensional table
		subsequence_table[i].resize(length_b + 1);
  }
	for (int i = 0; i <= length_a; i++) { //initialize the first column of the subsequence_table to 0
		subsequence_table[i][0] = 0;
  }
	for (int j = 0; j <= length_b; j++) { //initialize the first row of the subsequence_table to 0
	subsequence_table[0][j] = 0;
	}
	for (int i = 1; i <= length_a; i++) { 	//fill up the subsequence_table with lengths by checking if two values are equal
		for (int j = 1; j <= length_b; j++) { //if they are addthe value plus 1, otherwise add the greater of the two
			if (word_a[i - 1] == word_b[j - 1])
				subsequence_table[i][j] = subsequence_table[i - 1][j - 1] + 1;
			else
				subsequence_table[i][j] = max(subsequence_table[i - 1][j], subsequence_table[i][j - 1]);
		}
	}
	cout << subsequence_table[length_a][length_b] << endl; //longest common subsequence length will be last entry in the subsequence_table

	string subsequence;
	while (length_a > 0 && length_b > 0) {  //go through, tracing back the code and look for if the a value with a frequency higher than 1
		if (subsequence_table[length_a][length_b] == 1 + subsequence_table[length_a - 1][length_b - 1] && word_a[length_a - 1] == word_b[length_b - 1]) {
			subsequence = word_a[length_a - 1] + subsequence;  //when this frequency is detected, then add the letter to the subsequence string, building up the
			length_a--;                                        //longest common subsequence. If this doesn't happen, then decrease the row and column numbers
			length_b--;
		}
		else if (subsequence_table[length_a - 1][length_b] > subsequence_table[length_a][length_b - 1]) {
			length_a--;
		}
		else {
			length_b --;
		}
	}
	cout << subsequence << endl;  //the letters that make up the longest common subsequence will now be in the string.
	return subsequence_table[length_a][length_b];
}

/* The function subsequence_word is used to find the longest commone subsequence between two words in
o(MN) time. It takes in two strings @word_a and @word_b and doesnt return anything, but does
print out @subsequence the string tht contains the longest common subsequence between the inputs.
Function was abandoned because of reason described above.
*/
// void subsequence_word(string word_a, string word_b) {
//   int length_a = word_a.length(), length_b = word_b.length();
// 	int sub_length = subsequence_length(word_a, word_b);
//   string subsequence;
//   //subsequence[sub_length] = '\0';
//
//   while (length_a > 0 && length_b > 0) {
//     if (sub_length[length_a][length_b] == 1 + sub_length[length_a -1][length_b -1] && word_a[length_a - 1] == word_b[length_b - 1]) { //check for a match from subsequence_table from above using the string lengths
//       subsequence = word_a[length_a - 1] + subsequence;
//       length_a--;
//       length_b--;
//       //sub_length--;
//     }
//     else if (word_a[length_a - 1] > word_b[length_b - 1]) {
//       length_a--;
//     }
//     else {
//       length_b--;
//     }
//   }
// 	cout << subsequence << endl; //print out the longest common subsequence
// }

int subsequence_driver(int argc, char **argv) {
    //Please place all functionality in here instead of the main.
    //Feel free to make any functions or objects you wish, as long as we only call this function.

    const string word_a(argv[1]);
    const string word_b(argv[2]);

    subsequence_length(word_a, word_b);
    //subsequence_word(word_a, word_b);
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << "<word_a>" << "<word_b>" << endl;

    subsequence_driver(argc, argv);
		return 0;
    }

    subsequence_driver(argc, argv);

    return 0;
}
