#include <iostream>
#include <string>

using namespace std;

int subsequence_length(string word_a, string word_b) {
	int length_a = word_a.length(), length_b = word_b.length();

	int subsequence_table[length_a + 1][length_b + 1];  //subsequence_table[i][j] stores the length of longest common subsequence of substring
	for (int i = 0; i <= length_a; i++) {	//initialize the first column of the subsequence_table to 0
		subsequence_table[i][0] = 0;
  }
	for (int j = 0; j <= length_b; j++) { //initialize the first row of the subsequence_table to 0
		subsequence_table[0][j] = 0;
  }
	for (int i = 1; i <= length_a; i++) { 	//fill up the subsequence_table with lengths
		for (int j = 1; j <= length_b; j++) {
			if (word_a[i - 1] == word_b[j - 1])
				subsequence_table[i][j] = subsequence_table[i - 1][j - 1] + 1;
			else
				subsequence_table[i][j] = max(subsequence_table[i - 1][j], subsequence_table[i][j - 1]);
		}
	}
	return subsequence_table[length_a][length_b]; //longest common subsequence length will be last entry in the subsequence_table
}

void subsequence_word(string word_a, string word_b) {
  int length_a = word_a.length(), length_b = word_b.length();
	int sub_length = subsequence_length(word_a, word_b);
  char subsequence[sub_length + 1];
  subsequence[sub_length] = '\0';

  while (length_a > 0 && length_b > 0) {
    if (word_a[length_a - 1] == word_b[length_b - 1]) {
      subsequence[sub_length - 1] = word_a[length_a - 1];
      length_a--;
      length_b--;
      sub_length--;
    }
    else if (word_a[length_a - 1] > word_b[length_b - 1]) {
      length_a--;
    }
    else {
      length_b--;
    }
  }
	cout << subsequence << endl; //print out the longest common subsequence
}

int subsequence_driver(int argc, char **argv) {
    //Please place all functionality in here instead of the main.
    //Feel free to make any functions or objects you wish, as long as we only call this function.

    const string word_a(argv[1]);
    const string word_b(argv[2]);

    cout << subsequence_length(word_a, word_b) << endl;
    subsequence_word(word_a, word_b);
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
