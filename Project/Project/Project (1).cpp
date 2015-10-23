//#include <iostream>
//#include <fstream>
//#include <string>
//#include <queue>
////#include <cstdio>
//#include <cstdlib>
//
//#include <SFML/Network/Http.hpp>
//
//class url{
//private:
//	std::string address;
//public:
//	url() : address("") {}
//	url(std::string s) : address(s) {}
//
//	std::string protocol();
//	std::string host();
//	std::string path();
//	void print() { std::cout << address << std::endl; }
//
//};
//
//std::string url::protocol(){
//
//	std::size_t location;
//	if (isalpha(this->address[0]))
//		location = 0;
//	else
//		return "";
//
//	char s[10] = "";
//	int i = 0;
//
//	while (address.at(location) != ':'){
//		s[i] = address.at(location);
//		i++;
//		location++;
//	}
//
//	s[i] = '\0';
//
//	std::string ret = s;
//	return ret;
//}
//
//std::string url::host(){
//
//	std::size_t location;
//	if (isalpha(this->address[0]))
//		location = this->protocol().length() + 3;
//	else
//		return "";
//
//	char s1[100] = "";
//	int i = 0;
//
//	while (address.at(location) != '/'){
//
//		if (isspace(address.at(location + 1)))
//			break;
//
//		s1[i] = address.at(location);
//		i++;
//		location++;
//	}
//
//	s1[i] = '\0';
//
//	std::string s2(s1);
//	return s2;
//
//}
//
//std::string url::path(){
//
//	std::size_t location;
//	if (this->protocol().length() != 0)
//		location = this->protocol().length() + 3 + this->host().length();
//	else
//		location = 0;
//
//	char s1[200] = "";
//	int i = 0;
//
//	while (location != address.length()){
//
//		s1[i] = address.at(location);
//		i++;
//		location++;
//	}
//
//	s1[i] = '\0';
//
//	std::string s2(s1);
//
//	if (s2.length() == 0){
//		s2 = "/";
//	}
//
//	return s2;
//}
//
//
//class session{
//private:
//	// Queue maintains list of webpages to crawl
//	std::queue<std::string> list;
//	// Counter variable to ensure limited number of webpages are crawled
//	static int count;
//public:
//	session(std::string s) { list.push(s); } // Constructor
//	void stringsearch(); // Member function searches for hyperlinks
//
//};
//
//void session::stringsearch(){
//
//	std::ofstream FILE("source.txt");
//
//	sf::Http site(list.front());
//
//	//Generate the request
//	sf::Http::Request request;
//
//	// Send the request
//	sf::Http::Response response = site.sendRequest(request);
//
//	// Check the status code and display the result
//	sf::Http::Response::Status status = response.getStatus();
//	if (status == sf::Http::Response::Ok)
//	{
//		FILE << response.getBody() << std::endl;
//	}
//	else
//	{
//		std::cout << "Error " << status << std::endl;
//	}
//	FILE.close();
//
//	std::cout << "Popping URL: " << list.front() << std::endl << std::endl;
//	list.pop();
//
//	// Opens file for reading
//	std::ifstream file("source.txt");
//	std::ofstream wordfile("wordindex.txt");
//	std::string s1; // String stores lines from html file
//	std::string s2 = "href=\""; // Reference string to locate hyperlinks
//	char s3[300]; // C string variable to store hyperlink URLs
//
//	if (file.is_open()){
//
//		do{
//			// Both string storage variables initialised to null
//			s1 = "";
//
//			std::getline(file, s1); // Gets line by line information from the page source
//
//			std::size_t location = s1.find(s2); // Variable to point to location in string
//
//			int i = 0;
//			// Check to see if location is within string, i.e the desired element has been found
//			if (location != std::string::npos){
//				std::cout << "Hyperlink found: ";
//
//				std::size_t x = location + 6;
//
//				while (s1.at(x) != '\"'){
//					s3[i] = s1.at(x);
//					x++;
//					i++;
//				}
//
//				s3[i] = '\0';
//
//				std::string s4 = s3;
//
//				std::cout << s4 << std::endl;
//				std::cout << "Adding URL to queue..." << std::endl;
//
//				list.push(s4);
//
//				std::cout << s4 << std::endl << std::endl;
//
//			}
//			if (wordfile.is_open()){
//				std::string word = "boost";
//				std::size_t point = s1.find(word);
//				if (point != std::string::npos){
//					std::cout << "found word: ";
//					std::cout << word << std::endl;
//					std::cout << list.front() << std::endl;
//					wordfile << "found word: ";
//					wordfile << word << std::endl;
//					wordfile << list.front() << std::endl;
//				}
//				else{
//					std::cout << "word not found" << std::endl;
//					std::cout << "\n";
//				}
//			}
//			else{
//				std::cout << "index could not be opened" << std::endl;
//			}
//			// WORD SEARCH CODE COMES HERE///////////////////
//			/*std::ofstream wordfile("wordindex.txt");
//			if (wordfile.is_open()){
//			std::string word = "boost";
//			char wordkill[100];
//			do{
//
//			std::size_t point = s1.find(word);
//			int j = 0;
//			if (point != std::string::npos){
//			wordfile << "word found: ";
//			std::size_t k = point;
//			while (s1.at(point) != ' '){
//			wordkill[j] = s1.at(point);
//			k++;
//			j++;
//			}
//			wordkill[j] = '\0';
//			std::string hword = wordkill;
//
//			wordfile << "word: " << hword << std::endl;
//			wordfile << "URL: " << list.front() << std::endl;
//
//			}
//			else{
//			wordfile << "word not found" << std::endl;
//			std::cout << "word not found" << std::endl;
//			}
//			wordfile.close();
//			} while (!file.eof());
//
//			}
//			else{
//			std::cout << "file could not open" << std::endl;
//			}*/
//			//////////////////////////////////////////////
//
//		} while (s1 != "</html>");
//
//		wordfile.close();
//		file.close();
//	}
//	else{
//		std::cout << "Error in opening file" << std::endl;
//		exit(-1);;
//	}
//
//	file.close();
//}
//
//int session::count = 1;
//
//int main()
//{
//	session sess("www.boost.org");
//	sess.stringsearch();
//	return 0;
//}