#include"..\Metro's line\Metro's line.h"
#include "stdio.h"

using namespace Prog4;

int main()
{
	std::string s;
	int n, q;

	std::cout << "Enter name of line:" << std::endl;
	std::cin >> s;
	Line first(s);
	std::cout <<"Name of line: " << first.nameofline()<<std::endl;

	int fl1 = 1;
	while (fl1) {
		std::cout << std::endl;
		std::cout << "Enter operation:" << std::endl; 
		std::cout << "1. Enter new Ustation" << std::endl;
		std::cout << "2. Enter new Transition" << std::endl;
		std::cout << "3. Enter new Node" << std::endl;
		std::cout << "4. Find station" << std::endl;
		std::cout << "5. Change type" << std::endl;
		std::cout << "6. Show Line" << std::endl;
		std::cout << "7. Change station name" << std::endl;
		std::cout << "or press ctrl + Z to quit " << std::endl;
		std::cin >> q;
		if (std::cin.good()) {
			if (q == 1) {
				std::cout << "Enter name of station: " << std::endl;
				std::cin >> s;
				UStation* x = new UStation(s);
				Item temp;
				temp.ptr = x;
				if (first.empty()) {
					temp.tonext = 0;
					temp.toprev = 0;
				}
				else
				{
					std::cout << "Enter distance to next station: ";
					std::cin >> q;
					temp.tonext = q;
					std::cout << "Enter distance to prev station: ";
					std::cin >> q;
					temp.toprev = q;
				}
				try {
					first.newstation(temp);
				}
				catch (const std::exception &msg)
				{
					std::cout << msg.what() << std::endl;
				}
				std::cout << std::endl << temp << std::endl;
			}
			else if (q == 2) {
				std::cout << "Enter name of station: ";
				std::cin >> s;
				std::cout << std::endl;
				std::cout << "Enter number of lines(3 max): ";
				std::cin >> n;
				std::cout << std::endl;
				std::string* a = new std::string[n];
				for (int i = 0; i < n; i++) {
					std::cout << "Enter line #" << i + 1 << ": ";
					std::cin >> a[i];
				}
				Transition* x = new Transition(s);
				x->setlinename(a, n);
				Item temp;
				temp.ptr = x;
				if (first.empty()) {
					temp.tonext = 0;
					temp.toprev = 0;
				}
				else
				{
					std::cout << "Enter distance to next station: ";
					std::cin >> q;
					temp.tonext = q;
					std::cout << "Enter distance to prev station: ";
					std::cin >> q;
					temp.toprev = q;
				}
				try {
					first.newstation(temp);
				}
				catch (const std::exception &msg)
				{
					std::cout << msg.what() << std::endl;
				}
				std::cout << std::endl << temp << std::endl;
			}
			else if (q == 3) {
				std::cout << "Enter name of station: " << std::endl;
				std::cin >> s;
				std::cout << std::endl;
				std::cout << "Enter number of lines(3 max): ";
				std::cin >> n;
				std::cout << std::endl;
				std::string* a = new std::string[n];
				std::string* b = new std::string[n];
				for (int i = 0; i < n; i++) {
					std::cout << "Enter line #" << i + 1 << ": ";
					std::cin >> a[i];
					std::cout << "Enter station of line #" << i + 1 << ": ";
					std::cin >> b[i];
				}
				Node* x = new Node(s);
				x->setlinename(a, b, n);
				Item temp;
				temp.ptr = x;
				if (first.empty()) {
					temp.tonext = 0;
					temp.toprev = 0;
				}
				else
				{
					std::cout << "Enter distance to next station: ";
					std::cin >> q;
					temp.tonext = q;
					std::cout << "Enter distance to prev station: ";
					std::cin >> q;
					temp.toprev = q;
				}
				try {
					first.newstation(temp);
				}
				catch (const std::exception &msg)
				{
					std::cout << msg.what() << std::endl;
				}
				std::cout << std::endl << temp << std::endl;
			}
			else if (q == 4) {
				std::string str;
				std::cout << "Enter name of searching station: ";
				std::cin >> str;
				std::cout << std::endl;
				try
				{
					list<Item>::iterator cur = first.find(str);
					std::cout << *cur << std::endl;
				}
				catch (const std::exception &msg)
				{
					std::cout << msg.what() << std::endl;
				}
			}
			else if (q == 7) {
				std::string str;
				std::cout << "Enter name of searching station: ";
				std::cin >> str;
				std::cout << std::endl;
				list<Item>::iterator cur;
				try
				{
					cur = first.find(str);
				}
				catch (const std::exception &msg)
				{
					std::cout << msg.what() << std::endl;
				}
				std::cout << "Enter new name of station: ";
				std::cin >> str; 
				std::cout << std::endl;
				cur->ptr->changename(str);
			}
			else if (q == 5) {
				std::string str;
				int k;
				list<Item>::iterator cur;
				std::cout << "Enter name of searching station: ";
				std::cin >> str;
				std::cout << std::endl;
				try
				{
					cur = first.find(str);
				}
				catch (const std::exception &msg)
				{
					std::cout << msg.what() << std::endl;
				}
				std::string type = cur->ptr->typeofstation();
				if (type == "Ustation") {
					do {
						std::cout << "What type to change? 0 for Transition, 1 for Node: ";
						std::cin >> k;
					} while ((k != 0) && (k != 1));
					if (k == 0) {
						std::cout << "Enter number of lines(3 max): ";
						std::cin >> n;
						std::cout << std::endl;
						std::string* a = new std::string[n];
						for (int i = 0; i < n; i++) {
							std::cout << "Enter line #" << i + 1 << ": ";
							std::cin >> a[i];
						}
						cur->ptr = cur->ptr->changetype(a, n);
					}
					else if (k == 1) {
						std::cout << "Enter number of lines(3 max): ";
						std::cin >> n;
						std::cout << std::endl;
						std::string* a = new std::string[n];
						std::string* b = new std::string[n];
						for (int i = 0; i < n; i++) {
							std::cout << "Enter line #" << i + 1 << ": ";
							std::cin >> a[i];
							std::cout << "Enter station of line #" << i + 1 << ": ";
							std::cin >> b[i];
						}
						cur->ptr = cur->ptr->changetype(a, b, n);
					}
				}
				if (type == "Transition") {
					do {
						std::cout << "What type to change? 0 for Ustation, 1 for Node: ";
						std::cin >> k;
					} while ((k != 0) && (k != 1));
					if (k == 0) {
						cur->ptr = cur->ptr->changetype();
					}
					else if (k == 1) {
						std::cout << "Enter number of lines(3 max): ";
						std::cin >> n;
						std::cout << std::endl;
						std::string* a = new std::string[n];
						std::string* b = new std::string[n];
						for (int i = 0; i < n; i++) {
							std::cout << "Enter line #" << i + 1 << ": ";
							std::cin >> a[i];
							std::cout << "Enter station of line #" << i + 1 << ": ";
							std::cin >> b[i];
						}
						cur->ptr = cur->ptr->changetype(a, b, n);
					}

				}
				if (type == "Node") {
					do {
						std::cout << "What type to change? 0 for Ustation, 1 for Transition: ";
						std::cin >> k;
					} while ((k != 0) && (k != 1));
					if (k == 0) {
						if (k == 0) {
							cur->ptr = cur->ptr->changetype();
						}
					}
					else if (k == 1) {
						std::cout << "Enter number of lines(3 max): ";
						std::cin >> n;
						std::cout << std::endl;
						std::string* a = new std::string[n];
						std::string* b = new std::string[n];
						for (int i = 0; i < n; i++) {
							std::cout << "Enter line #" << i + 1 << ": ";
							std::cin >> a[i];
						}
						cur->ptr = cur->ptr->changetype(a, n);
					}
				}

			}
			else if (q == 6) {
				try
				{
					std::cout << first;
				}
				catch (const std::exception &msg)
				{
					std::cout << msg.what() << std::endl;
				}
			}
			else
				std::cout << "Repeat pls" << std::endl;
		}
		else
			fl1 = 0;

	}



	return 0;
}