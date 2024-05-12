#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <string>

// Nope79

// Si está leyendo esto, ni se moleste en comprobar si sirve XD

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
	
	while(ban && (actual != Estado::q25 && actual != Estado::q25) ){
		
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
			// out << 'u' << "          " << "Q12          " << "L\n";
			case Estado::q0:
				
				out << "Q0          " << v[pos] << "          ";
				
				if(c == '1'){
					
					out << "x         Q1     R\n";
					v[pos] = 'x';
					pos++;
					actual = Estado::q1;
				}
				else{
				
					ban = false;
				}
			
			break;
			
			case Estado::q1:
				
				out << "Q1          " << v[pos] << "          ";
				
				if(c == '1' || c == '-'){
					
					out << v[pos] << "         Q1     R\n";
					pos++;
				}
				
				else if(c == '='){
					
					out << v[pos] << "         Q2     R\n";
					pos++;
					actual = Estado::q2;
				}
				else{
				
					ban = false;
				}
				
			break;
			
			case Estado::q2:
				
				out << "Q2          " << v[pos] << "          ";
				
				if(c == '-' || c == 1){
					
					if(c == 1){
						
						out << v[pos] << "         Q3     L\n";	
						v[pos] = '1';
						pos--;
						actual = Estado::q3;
					}
					
					
					
					
				}else if(isdigit(c)){
					out << v[pos] << "         Q4     R\n";
					pos++;
					actual = Estado::q4;
				}
				else{
				
					ban = false;
				}
				
			break;
			
			case Estado::q3:
				
				out << "Q3          " << v[pos] << "          ";
				
				if(isdigit(c) || c == '=' || c == '-'){
					
					out << v[pos] << "         Q3     L\n";
					pos--;
					actual = Estado::q3;
				}
				
				else if(c == 'x'){
					
					out << v[pos] << "         Q0     R\n";
					pos++;
					actual = Estado::q3;
				}
				
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q4:
				
				out << "Q4          " << v[pos] << "          ";
				
				if(isdigit(c)){
					
					out << v[pos] << "         Q4     R\n";
					pos++;
					actual = Estado::q4;
				}
				
				else if(c == '-'){
					
					out << v[pos] << "         Q2     R\n";
					pos++;
					actual = Estado::q2;
				}
				
				else if(c == 1){
					
					out << v[pos] << "         Q5     L\n";
					pos++;
					actual = Estado::q5;
				}
				
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q5:
				
				out << "Q5          " << v[pos] << "          ";
				
				if(c == '9'){
					
					out << '0' << "         Q7     L\n";
					pos--;
					actual = Estado::q7;
				}
				
				else if(isdigit(c)){
					
					out << v[pos]+1 << "         Q6     L\n";
					pos--;
					actual = Estado::q6;
				}
				
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q6:
				
				out << "Q6          " << v[pos] << "          ";
				
				if(isdigit(c) || c == '=' || c == '-'){
					
					out << v[pos] << "         Q6     L\n";
					pos++;
					actual = Estado::q6;
				}
				
				else if(c == 'x'){
					
					out << v[pos] << "         Q0     R\n";
					pos++;
					actual = Estado::q0;
				}
				
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q7:
				
				out << "Q7          " << v[pos] << "          ";
				
				if(c == '9'){
					
					out << v[pos] << "         Q7     L\n";
					pos--;
					actual = Estado::q7;
					v[pos] = '0';
				}
				
				else if(isdigit(c)){
					
					out << v[pos] << "         Q6     L\n";
					pos--;
					actual = Estado::q7;
					v[pos] = v[pos]-1;
				}
				
				else if(c == '=' || c == '-'){
					
					out << v[pos] << "         Q8     R\n";
					pos--;
					actual = Estado::q8;
					v[pos] = '0';
				}
				
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q8:
				
				out << "Q8          " << v[pos] << "          ";
				
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q9:
				
				out << "Q9          " << v[pos] << "          ";
				
				if(1){
					
				}else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q10:
				
				out << "Q10          " << v[pos] << "          ";
				
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q11:
				
				out << "Q11          " << v[pos] << "          ";
				
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q12:
				
				out << "Q12          " << v[pos] << "          ";
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q13:
				
				out << "Q13          " << v[pos] << "          ";
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q14:
				
				out << "Q14          " << v[pos] << "          ";
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q15:
				
				out << "Q15          " << v[pos] << "          ";
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q16:
				
				out << "Q16          " << v[pos] << "          ";
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q17:
				
				out << "Q17          " << v[pos] << "          ";
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q18:
				
				out << "Q18          " << v[pos] << "          ";
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q19:
				
				out << "Q19          " << v[pos] << "          ";
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q20:
				
				out << "Q20          " << v[pos] << "          ";
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q21:
				
				out << "Q21          " << v[pos] << "          ";
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q22:
				
				out << "Q22          " << v[pos] << "          ";
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
			
			case Estado::q24:
				
				out << "Q24          " << v[pos] << "          ";
				if(1){
					
				}
				else{
					
					ban = false;
				}
				
			break;
		}
		
		out << "\n";
	}
	
	return actual;
}
