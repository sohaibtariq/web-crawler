//#include <iostream>
//#include <string>
//using namespace std;
//
//class url{
//private:
//	std::string address;
//public:
//	url() : address("") {}
//	url(std::string s) : address(s + '\0') {}
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
//	if (this->address[0] == 'h')
//		location = 0;
//	else
//		return "";
//
//	char s[10] = "";
//	int i = 0;
//
//	for(;;){
//
//		if (address.at(i) == ':')
//			break;
//
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
//	if (this->address[0] == 'h')
//		location = this->protocol().length() + 3;
//	else
//		return "";
//
//	char s1[100] = "";
//	int i = 0;
//
//	for (;;){
//
//		s1[i] = address.at(location);
//		i++;
//		location++;
//
//		if ((address.at(location)) == '/' || (address.at(location)) == address.back())
//			break;
//
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
//	if (s2[0] != '/'){
//		char temp[200] = "";
//		int z = 0;
//
//		temp[0] = '/';
//
//		while (s2[z] != '\0'){
//			temp[z + 1] = s2[z];
//			z++;
//		}
//		
//		temp[z] = '\0';
//	}
//
//	return s2;
//}
//
//int main()
//{
//	url u("http://www.boost.org/");
//	cout << "Protocol: " << u.protocol() << endl << "Host: " << u.host() << endl << "Path: " << u.path() << endl;
//	return 0;
//}