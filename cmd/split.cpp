#include <iostream>

std::string* split(char sep, std::string& str){
	int size = str.size();
	int nb = 0;
	int i, j;

	for (i = 0; i < size; i++){
		while (i < size && str[i] == sep)
			i++;
		if (i < size && str[i] != sep)
			nb++;
		while (i < size && str[i] != sep)
			i++;	
	}
	if (!nb)
		return NULL;
	std::string* tab;
	tab = new std::string[nb + 1];
	nb = 0;
	for (i = 0; i < size; i++){
		j = 0;
		while (i < size && str[i] == sep)
			i++;
		while (i + j < size && str[i + j] != sep)
			j++;
		if (j){
			tab[nb] = str.substr(i, j);
			if (tab[nb++].empty()){
				delete[] tab;
				return NULL;
			}
		}
		i += j;
	}
	return tab;
}

// int main(){
// 	std::string a = " u   er g  he we w w w yw55yw5 ywyw5y  yw54y w54y y	 ";
// 	std::string* b = split(' ', a);
// 	if (!b)
// 		return 1;
// 	for (int i = 0; !b[i].empty(); i++)
// 		std::cout << b[i] << std::endl;
// 	delete[] b;
// 	return 0;
// }

