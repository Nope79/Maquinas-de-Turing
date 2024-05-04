#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

using namespace std;

enum class Estado {q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, WA};

Estado analisis(vector <char>& v, ofstream& salida);

int main(){
	
	vector <char> v;
	
	
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	
	string s = "hola";
	
	for(auto c : s){
		
		v.push_back(c);
	}
	
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	
	for(auto c : v){
		
		cout << c << " ";
	}
	
	
	
	return 0;
}

Estado analisis(vector <char>& v, ofstream& salida){
	
	Estado actual = Estado::q0;
	int pos = 0;
	bool ban = true;
	
	// TODOs
	// Añadir cinta
	
	while(ban){
		
		char c = v[pos];
		
		switch(actual){
			
			case Estado::q0:
				
				if(isdigit(c) || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
				
					actual = Estado::q0;
				}
			
				else if(c == '='){
				
					actual = Estado::q1;
				}else{
				
					ban = false;
				}
			
			break;
			
			case Estado::q1:
				
				if(isdigit(c) || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
				
					actual = Estado::q1;
				}
			
				else if(c == 1){
				
					actual = Estado::q2;
				}else{
				
					ban = false;
				}
				
			break;
			
			case Estado::q2:
				
				if(isdigit(c)){
				
					actual = Estado::q2;
				}
			
				else if(c == 'a' || c == 'e' || c == 'i' || c || 'o' || c == 'u'){
				
					actual = Estado::q3;
				}
				
				else if(c == '='){
					
					actual = Estado::q13;
				}else{
				
					ban = false;
				}
				
			break;
			
			case Estado::q3:
				
				if(c == '0'){
					
					actual = Estado::q4;
				}
				
				else if(isdigit(c)){
					
					actual = Estado::q6;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q4:
				
				if(c == 1 || c == 'k'){
					
					actual = Estado::q5;
				}
				
				else if(c == '0'){
					
					
					actual = Estado::q4;
				}
				
				else if(isdigit(c)){
					
					actual = Estado::q6;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q5:
				
				if(c == '9'){
					
					actual = Estado::q5;
				}
				
				else if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					actual = Estado::q2;
				}
				
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q6:
				
				if(isdigit(c)){
					
					actual = Estado::q6;
				}
				
				else if(c == 'a'){
					
					actual = Estado::q7;
				}
				
				else if(c == 'e'){
					
					actual = Estado::q8;
				}
				
				else if(c == 'i'){
					
					actual = Estado::q9;
				}
				
				else if(c == 'o'){
					
					actual = Estado::q10;
				}
				
				else if(c == 'u'){
					
					actual = Estado::q11;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q7:
				
				if(isdigit(c) || c == '=' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					actual = Estado::q7;
				}
				
				else if(c == 1){
					
					actual = Estado::q12;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q8:
				
				if(isdigit(c) || c == '=' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					actual = Estado::q8;
				}
				
				else if(c == 1){
					
					actual = Estado::q12;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q9:
				
				if(isdigit(c) || c == '=' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					actual = Estado::q9;
				}
				
				else if(c == 1){
					
					actual = Estado::q12;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q10:
				
				if(isdigit(c) || c == '=' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					actual = Estado::q10;
				}
				
				else if(c == 1){
					
					actual = Estado::q12;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q11:
				
				if(isdigit(c) || c == '=' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					actual = Estado::q11;
				}
				
				else if(c == 1){
					
					actual = Estado::q12;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q12:
				
				if(isdigit(c) || c == '=' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					actual = Estado::q12;
				}
				
				else if(c == 1 || c == 'k'){
					
					actual = Estado::q2;
				}else{
					
					ban = false;
				}
				
			break;
				
			case Estado::q13:
				
				ban = false;
				
			break;
			
		}
	}
	
	if(ban == false || (actual != Estado::q13)){
		
		actual = Estado::WA;
	}
	
	return actual;
}
