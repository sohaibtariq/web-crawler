#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <windows.h>
#include <cstdlib>

#include <SFML/Network/Http.hpp>

// URL parser class
class url{
	private:
		std::string address; // Variable to store address of webpage
	public:
		// Default constructor
		url() : address("") {}
		// One argument constructor. Termination character added to string to facilitate class functions
		url(std::string s) : address(s + '\0') {}

		std::string protocol(); // Function to get protocol of URL (http, https, file etc)
		std::string host(); // Function to get hostname of URL (www.xyz.com etc)
		std::string path(); // Function to get path of the URL (/absd/123.htm etc)
		void print() { std::cout << address << std::endl; } // Function to print address

};

// Definition of protocol function
std::string url::protocol(){

	std::size_t location; // Variable that points a location within a string
	
	// We assume that we aren't accessing local files so an http or https specifier is necessary
	// The condition checks to see if the first character is an 'h', which means the url has a protocol
	// If the condition is false, the url has no protocol so we return nothing ("")
	if (this->address[0] == 'h')
		location = 0;
	else
		return "";

	char s[10] = ""; // Character array to store protocol
	int i = 0; // Integer to keep track of characters within array

	// Infinite loop that keeps adding characters to array
	// Breaks once the end of the protocol has been reached
	// This is indicated by a colon (http://....)
	for (;;){

		if (address.at(i) == ':')
			break;

		s[i] = address.at(location);
		i++;
		location++;
	}

	// Last character is set to termination character
	s[i] = '\0';

	std::string ret = s; // C string converted to std::string
	return ret; // Value returned
}

// Definition of host function
std::string url::host(){

	std::size_t location; // Variable that points a location within a string
	
	// We assume that we aren't accessing local files so an http or https specifier is necessary
	// The condition checks to see if the first character is an 'h', which means the url has a protocol
	// If a hostname is provided, the protocol must be there as well
	// So if this condition returns false, we assume neither protocol not host are provided, and we return nothing ("")
	if (this->address[0] == 'h')
		location = this->protocol().length() + 3;
	else
		return "";

	char s1[100] = ""; // Character array to store host
	int i = 0; // Integer to keep track of characters within array

	// Infinite loop that keeps adding characters to array
	// Breaks once the end of the host has been reached
	// This is indicated by a '/' or the last character of the string (if no path has been provided)
	for (;;){

		s1[i] = address.at(location);
		i++;
		location++;

		if ((address.at(location)) == '/' || (address.at(location)) == address.back())
			break;

	}

	// Last character is set to termination character
	s1[i] = '\0';

	std::string s2 = s1; // C string converted to std::string
	return s2; // Value returned
}

// Definition of path function
std::string url::path(){

	std::size_t location; // Variable that points a location within a string

	// Condition checks to see if the length of the protocol is zero
	// If thats the case, then that means the address contains only a path so we start from location 0
	// Otherwise we start from the sum of the lengths of host and protocol and an added 3 bytes (://)
	if (this->protocol().length() != 0)
		location = this->protocol().length() + 3 + this->host().length();
	else
		location = 0;

	char s1[200] = ""; // Character array to store path
	int i = 0; // Integer to keep track of characters within array

	// Loop runs until the end of the address and keeps adding characters to the array
	while (location != address.length()){

		s1[i] = address.at(location);
		i++;
		location++;
	}

	s1[i] = '\0';

	std::string s2(s1);

	// If the path is nothing, we assign "/" to it as it is the minimum request required to access a host webpage
	if (s2.length() == 0){
		s2 = "/";
	}

	// If we get a path that does not start with a '/', we put it as the first character and move everything forward by one place
	if (s2[0] != '/'){
		char temp[200] = "";
		int z = 0;

		temp[0] = '/';

		while (s2[z] != '\0'){
			temp[z + 1] = s2[z];
			z++;
		}

		temp[z] = '\0';
	}

	return s2;
}

// Class for maintaining a web crawling session
class session{
	private:

		// Queue maintains list of webpages to crawl
		std::queue<std::string> list;
		// Counter variable to ensure limited number of webpages are crawled
		static int count;
	public:
		session(std::string s = "") { list.push(s); } // Constructor

		bool check_html(); // Member function to check if current webpage is of html format

		void stringsearch(); // Member function searches for hyperlinks and matchng words

};

// Definition of check_html() function
bool session::check_html(){

	// Opens the source code of current webpage
	// Searched for html tag in the file
	// If found returns true, else false
	std::ifstream source("source.txt");
	std::string s = "";
	do{
		std::getline(source,s);

		if (s.find("<html>") == std::string::npos){
			source.close();
			return true;
		}
	} while (!source.eof());
	source.close();
	return false;
}

// Independent function that takes a url from the list as a string
// Adds it to a file that contains a list of all parsed webpages
void urls_parsed(std::string x){
	std::ofstream urls("urls.txt", std::ios::app|std::ios::out);

	urls << x << std::endl;

	urls.close();
}

// Independent function that takes a url from the list as a string
// Checks if it has already been parsed
// Returns true if found, else false
bool check_urls(std::string x){
	std::ifstream urls("urls.txt", std::ios::in);

	while (!urls.eof()){
		std::string k;

		getline(urls, k);

		if (x == k){
			urls.close();
			return true;
		}
	}
	urls.close();
	return false;
}

// Definition of stringsearch() function
void session::stringsearch(){

	// Whole body is in loop
	// Loop ends if the list is empty or a certain number of urls have been parsed
	do{

		// File that stores source code of URLs
		std::ofstream FILE("source.txt");

		std::ofstream wordfile("index.txt", std::ios::app|std::ios::out);

		// Object of url class created
		url u(list.front());

		// Object of Http class (found in SFML) created
		// Http class only takes host names as input, so host name passed
		sf::Http site(u.host());

		//Generate the request, i.e the path within the webpage
		sf::Http::Request request(u.path());

		// Send the request to generate a response
		sf::Http::Response response = site.sendRequest(request);

		// Check the status code and display the result
		sf::Http::Response::Status status = response.getStatus();
		if (status == sf::Http::Response::Ok){
			FILE << response.getBody() << std::endl;
		}
		else{
			std::cout << "Error " << status << std::endl;
			std::cout << "Skipping webpage. " << std::endl;
			list.pop();
			continue;
		}
		FILE.close();

		std::cout << "Popping URL: " << list.front() << std::endl << std::endl;
		Sleep(1000);

		// Condition check to see if file is of html format
		if (check_html() == false){
			std::cout << "\nWebpage not in html format. Skipping... " << std::endl << std::endl;
			list.pop();
			continue;
		}

		// Condition check to ensure URL hasn't been crawled previously. First URL is skipped
		if (count > 1 && check_urls(list.front()) == true){
			std::cout << "\nWebpage has already been crawled. Skipping...\n\n";
			list.pop();
			continue;
		}

		// Opens file for reading
		std::ifstream file("source.txt");

		std::string s1; // String stores lines from html file
		std::string s2 = "href=\""; // Reference string to locate hyperlinks
		char s3[300]; // C string variable to store hyperlink URLs

		// Condition check to ensure file is open
		if (file.is_open()){

			do{
				// Both string storage variables initialised to null
				s1 = "";

				std::getline(file, s1); // Gets line by line information from the page source
				
				std::size_t location = s1.find(s2); // Variable to point to location in string

				int i = 0;
				// Check to see if location is within string, i.e the desired element has been found
				if (location != std::string::npos){
					std::cout << "Hyperlink found: ";

					// Location set to first element of hyperlink
					// Adding 6 accounts for the 6 tag characters, i.e href"
					std::size_t x = location + 6;

					// Loop adds characters to array until quotation mark is reached
					while (s1.at(x) != '\"'){
						s3[i] = s1.at(x);
						x++;
						i++;
					}

					// Last character set to termination character
					s3[i] = '\0';

					std::string s4 = s3; // Converts C string to std::string

					std::cout << s4 << std::endl;

					// Creates url object that takes s4 as constructor argument
					url u2(s4);

					// Condition check to see if hyperlink has a host
					// If it doesn't, it means it is an extension of the current webpage
					// So current webpage is appended to it
					if (u2.host() == ""){
						s4 = u.protocol() + "://" + u.host() + s4;
					}

					std::cout << "Adding URL to queue..." << std::endl;

					// Hyperlink is added to queue
					list.push(s4);

					std::cout << s4 << std::endl << std::endl;
				}

				if (wordfile.is_open()){
					std::string word = "Boost";

					std::size_t point = s1.find(word);
					
					if (point != std::string::npos){

				//		while ()

						wordfile << list.front() << std::endl;
						wordfile << word << std::endl;
					}
				//	else{
					//	std::cout << "word not found" << std::endl;
						//std::cout << "\n";
				//	}
				}
				else{
					std::cout << "index could not be opened" << std::endl;
				}

			} while (!file.eof());

			// Adds current webpage to list of URLs parsed
			urls_parsed(list.front());
			
			// Removes current webpage from queue
			list.pop();
			file.close();
			wordfile.close();

			std::cout << "\n\nCount: " << count << std::endl;
			count++;

			Sleep(1000);			
		}
		else{
			std::cout << "Error in opening file" << std::endl;
			exit(-1);
		}
		//Sleep(1000);
	} while (count <= 10 && list.empty() == false);
	remove("source.txt");
	remove("urls.txt");

	return;
}

int session::count = 1;

int main()
{
	session sess("http://www.boost.org/");
	sess.stringsearch();
	return 0;
}