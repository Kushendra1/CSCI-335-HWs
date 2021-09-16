#include <iostream>
#include <string>

using namespace std;

int ordering_driver(int argc, char **argv) {
    //Please place all functionality in here instead of the main.
    //Feel free to make any functions or objects you wish, as long as we only call this function.

}

int main(int argc, char **argv) {
    if (argc != 2) {
		cout << "Usage: " << argv[0] << "<dimensions_file>" << endl;
		return 0;
    }

    ordering_driver(argc, argv);

    return 0;
}
