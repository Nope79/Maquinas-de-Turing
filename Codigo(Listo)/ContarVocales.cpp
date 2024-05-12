#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <string>

// Nope79

using namespace std;

enum class Estado {q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15, q16, q17, q18, q19, q20, q21, q22, q23, q24, q25, WA};

Estado analisis(vector <char>& v, ofstream& out);

int main(){
	
	vector <char> v;
	ifstream in;
	in.open("in.txt", ios::in);
	
	if(in.fail()){
		
		cout << "Error al abrir el archivo.\n";
		exit(1);
	}
	
	int n = 0;
	std::string prefix = "out";
	
	while(!in.eof()){
		
		std::string filename = prefix + std::to_string(n) + ".txt";
        std::ofstream out(filename);
        
        out << "Es posible que se desfase la siguiente \"tabla\" si pone muchos datos, so, si pone muchos datos suerte interprentándolo porque yo no voy a investigar como evitarlo.";
        out << "\n\nCINTA                    ORIGEN     C_LEÍDO     C_ESCRITO     FIN     DIRECCIÓN\n";
        
        string texto;
        getline(in, texto);
        
        v.push_back(1);
		v.push_back(1);
		v.push_back(1);
		
		for(auto c : texto){
		
			v.push_back(c);
		}
		
		v.push_back(1);
		v.push_back(1);
		v.push_back(1);
		
		Estado x = analisis(v, out);
	
		if(x == Estado::q13){
		
			out << "AC\n";
		}else{
			
			out << "WA\n";
		}
		
		n++;
		v.clear();
		out.close();
	}
	
	in.close();
	
	return 0;
}

Estado analisis(vector <char>& v, ofstream& out){
	
	Estado actual = Estado::q0;
	int pos = 3;
	bool ban = true;
	
	while(ban && actual != Estado::q13){
		
		char c = v[pos];
		
		for(int i = 0; i < v.size(); i++){
		
			if(i == pos){
			
				out << "<" << v[pos] << ">";
			}else{
			
				out << v[i];
			}
		}
		
		out << "          ";
		
		switch(actual){
			
			case Estado::q0:
				
				out << "Q0          " << v[pos] << "          ";
				
				if(isdigit(c) || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					out << v[pos] << "          " << "Q0          " << "R\n";
					actual = Estado::q0;
					pos++;
				}
			
				else if(c == '='){
					
					out << v[pos] << "          " << "Q1          " << "L\n";
					actual = Estado::q1;
					pos--;
				}else{
				
					ban = false;
				}
			
			break;
			
			case Estado::q1:
				
				out << "Q1          " << v[pos] << "          ";
				
				if(isdigit(c) || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
				
					out << v[pos] << "          " << "Q1          " << "L\n";
					actual = Estado::q1;
					pos--;
				}
			
				else if(c == 1){
				
					out << v[pos] << "          " << "Q2          " << "R\n";
					actual = Estado::q2;
					pos++;
				}else{
				
					ban = false;
				}
				
			break;
			
			case Estado::q2:
				
				out << "Q2          " << v[pos] << "          ";
				
				if(isdigit(c)){
					
					out << v[pos] << "          " << "Q2          " << "R\n";
					actual = Estado::q2;
					pos++;
				}
				
				else if(c == '='){
					
					out << v[pos] << "          " << "Q13          " << "S\n";
					actual = Estado::q13;
				}
			
				else if(c == 'a' || c == 'e' || c == 'i' || c || 'o' || c == 'u'){
					
					out << v[pos] << "          " << "Q3          " << "L\n";
					actual = Estado::q3;
					pos--;
				}else{
				
					ban = false;
				}
				
			break;
			
			case Estado::q3:
				
				out << "Q3          " << v[pos] << "          ";
				
				if(c == '0'){
					
					out << '9' << "          " << "Q4          " << "L\n";
					actual = Estado::q4;
					v[pos] = '9';
					pos--;
				}
				
				else if(isdigit(c)){
					
					out << v[pos]-1 << "          " << "Q6          " << "R\n";
					actual = Estado::q6;
					v[pos] = v[pos]-1;
					pos++;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q4:
				
				out << "Q4          " << v[pos] << "          ";
				
				if(c == 1 || c == 'k'){
					
					out << v[pos] << "          " << "Q5          " << "R\n";
					actual = Estado::q5;
					pos++;
				}
				
				else if(c == '0'){
					
					out << '9' << "          " << "Q4          " << "L\n";
					actual = Estado::q4;
					v[pos] = '9';
					pos--;
				}
				
				else if(isdigit(c)){
					
					out << v[pos]-1 << "          " << "Q6          " << "R\n";
					actual = Estado::q6;
					v[pos] = v[pos]-1;
					pos++;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q5:
				
				out << "Q5          " << v[pos] << "          ";
				
				if(c == '9'){
					
					out << '9' << "          " << "Q5          " << "R\n";
					actual = Estado::q5;
					v[pos] = 'x';
					pos++;
				}
				
				else if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					out << 'k' << "          " << "Q2          " << "R\n";
					actual = Estado::q2;
					v[pos] = 'k';
					pos++;
				}
				
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q6:
				
				out << "Q6          " << v[pos] << "          ";
				
				if(isdigit(c)){
					
					out << v[pos] << "          " << "Q6          " << "R\n";
					actual = Estado::q6;
					pos++;
				}
				
				else if(c == 'a'){
					
					out << v[pos] << "          " << "Q7          " << "R\n";
					actual = Estado::q7;
					pos++;
				}
				
				else if(c == 'e'){
					
					out << v[pos] << "          " << "Q8          " << "R\n";
					actual = Estado::q8;
					pos++;
				}
				
				else if(c == 'i'){
					
					out << v[pos] << "          " << "Q9          " << "R\n";
					actual = Estado::q9;
					pos++;
				}
				
				else if(c == 'o'){
					
					out << v[pos] << "          " << "Q10          " << "R\n";
					actual = Estado::q10;
					pos++;
				}
				
				else if(c == 'u'){
					
					out << v[pos] << "          " << "Q11          " << "R\n";
					actual = Estado::q11;
					pos++;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q7:
				
				out << "Q7          " << v[pos] << "          ";
				
				if(isdigit(c) || c == '=' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					out << v[pos] << "          " << "Q7          " << "R\n";
					actual = Estado::q7;
					pos++;
				}
				
				else if(c == 1){
					
					out << 'a' << "          " << "Q12          " << "L\n";
					actual = Estado::q12;
					v[pos] = 'a';
					v.push_back(1);
					pos--;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q8:
				
				out << "Q8          " << v[pos] << "          ";
				
				if(isdigit(c) || c == '=' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					out << v[pos] << "          " << "Q8          " << "R\n";
					actual = Estado::q8;
					pos++;
				}
				
				else if(c == 1){
					
					out << 'e' << "          " << "Q12          " << "L\n";
					actual = Estado::q12;
					v[pos] = 'e';
					v.push_back(1);
					pos--;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q9:
				
				out << "Q9          " << v[pos] << "          ";
				
				if(isdigit(c) || c == '=' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					out << v[pos] << "          " << "Q9          " << "R\n";
					actual = Estado::q9;
					pos++;
				}
				
				else if(c == 1){
					
					out << 'i' << "          " << "Q12          " << "L\n";
					actual = Estado::q12;
					v[pos] = 'i';
					v.push_back(1);
					pos--;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q10:
				
				out << "Q10          " << v[pos] << "          ";
				
				if(isdigit(c) || c == '=' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					out << v[pos] << "          " << "Q10          " << "R\n";
					actual = Estado::q10;
					pos++;
				}
				
				else if(c == 1){
					
					out << 'o' << "          " << "Q12          " << "L\n";
					actual = Estado::q12;
					v[pos] = 'o';
					v.push_back(1);
					pos--;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q11:
				
				out << "Q11          " << v[pos] << "          ";
				
				if(isdigit(c) || c == '=' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					out << v[pos] << "          " << "Q11          " << "R\n";
					actual = Estado::q11;
					pos++;
				}
				
				else if(c == 1){
					
					out << 'u' << "          " << "Q12          " << "L\n";
					actual = Estado::q12;
					v[pos] = 'u';
					v.push_back(1);
					pos--;
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q12:
				
				out << "Q12          " << v[pos] << "          ";
				
				if(isdigit(c) || c == '=' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
					
					out << v[pos] << "          " << "Q12          " << "L\n";
					actual = Estado::q12;
					pos--;
				}
				
				else if(c == 1 || c == 'k'){
					
					out << v[pos] << "          " << "Q2          " << "R\n";
					actual = Estado::q2;
					pos++;
				}else{
					
					ban = false;
				}
				
			break;
		}
		
		out << "\n";
	}
	
	return actual;
}
