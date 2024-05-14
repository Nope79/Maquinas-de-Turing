#include <iostream>
#include <fstream>
#include <vector>
// Nope79

/*
MÁQUINA DE TURING QUE PUEDE REALIZAR OPERACIONES BÁSICAS.
SOLO RECIBE SECUENCIAS DE 1'S.
LAS DIVISIONES DESPRECIAN DECIMALES.
SON OPERACIONES SECUENCIALES, NO TOMA EN CUENTA LA JERARQUÍA DE OPERACIONES.

EJEMPLOS DE CADENAS VALIDAS:
111+111-111-111=
1/1/1/1=
1*111/11/111111111*1-1+1-1+1-1+1=

EJEMPLOS DE CADENAS NO VALIDAS
KADFSF=
18*32+8329=
11111
1+1+1*1-1/1=1

PARA REPRESENTAR LOS NODOS SE USA UN ENUMERADO.
PARA REPRESENTAR LA CINTA SE USA UN VECTOR.
TENEMOS UNA FUNCIÓN A LA QUE SE LE PASA LA CADENA A REVISAR Y SE REALIZA TODO EL PROCESO EN ESA ÚNICA FUNCIÓN.

EXPLICACIÓN BÁSICA DEL ALGORITMO:
AL INICIAR, SE REVISARÁ  QUE SE CUMPLA QUE LUEGO DEL SIGNO DE IGUAL NO HAYA NADA MÁS.
Al TERMINAR, SE REVISARÁ QUE SE CUMPLA EL FORMATO: término, operación, término, operación, término, operación... término, signo_igual.

SE CALCULA EL RESULTADO LUEGO DEL SIGNO DE IGUAL, POR LO TANTO, ES NECESARIO PASAR EL PRIMER TÉRMINO A LA DERECHA DEL MISMO, ESTO SE HACE SIEMPRE.
CON TODAS LAS OPERACIONES SE HACE ESTO, EN LAS DIVISIONES SE NECESITA HACER UN REACOMODO DEBIDO A QUE EL RESULTADO SE COLOCA SEGUIDO EL RESULTADO ANTERIOR.

LA SUMA Y RESTA SON MUY SIMILARES, POR SU PARTE, LA SUMA AÑADEN 1'S CUANDO SE HACE ADICIÓN A UN NÚMERO POSITIVO Y SE ELIMINAN CUANDO ESTE ES NEGATIVO.
POR OTRO LADO, LA RESTA HACE ADICIÓN A UN NÚMERO NEGATIVO Y UNA EXTRACCIÓN CUANDO ES UN NÚMERO POSITIVO.
¿PODRÍAN USARSE LOS MISMOS NODOS ENTONCES? NO. ☺

LA MULTIPLICACIÓN ES UNA SECUENCIA DE SUMAS, ENTONCES, SOLO HACEMOS DICHAS ADICIONES, VAMOS MARCANDO LOS 1'S 
DEL RESULTADO Y AÑADIENDO A LA VEZ MÁS EN RELACIÓN A LOS PRIMEROS, ESTO EN UN CICLO, N-1 VECES, DONDE
N ES EL NÚMERO SEGUIDO DEL SIGNO *, ESTO PORQUE YA TENEMOS LA PRIMERA ADICIÓN HECHA SIEMPRE.

LA DIVISIÓN ES ALGO MÁS COMPLEJA YA QUE REALIZA UN PROCESO PARECIDO AL DE LA MULTIPLICACIÓN, PERO DE FORMA INVERSA,
EN ESTE CASO VERIFICAMOS CUANTAS VECES CABE X EN Y, SIENDO X EL NÚMERO SEGUIDO POR EL SIGNO /, Y SIENDO
EL RESULTADO CALCULADO ANTES DE LA DIVISIÓN. VAMOS MARCANDO TANTO LOS VALORES DE X COMO LOS DE Y.
AL INICIAR LO PRIMERO QUE SE HACE ES COLOCAR UN CARACTER CUALQUIERA AL FINAL DE TODA LA EXPRESIÓN PARA 
GUARDAR EL RESULTADO LUEGO DE DICHO CARACTER.
FINALMENTE, CUANDO SE TERMINA EL PROCESO PRINCIPAL, SE PROCEDE A RECORRERSE TODO EL RESULTADO HASTA EL SIGNO = 
O - EN CASO DE TENER UN RESULTADO NEGATIVO.

PARA HACER PRUEBAS DIFERENTES A LAS PROPUESTAS PUEDE MODIFICAR EL ARCHIVO TXT LLAMADO "in.txt".
CADA LÍNEA ORIGINARÁ OTRO ARCHIVO TXT CON TODO EL PROCESO REALIZADO, AL FINAL TIENE EL VEREDICTO,
AC PARA UNA CADENA QUE FUE ACEPTADA Y WA PARA UNA CADENA QUE FUE RECHAZADA.

EN CASO DE ENCONTRAR ALGÚN ERROR CONTACTAR AL SIGUIENTE CORREO: nopesep@gmail.com
TOME DE BASE EL ARCHIVO JFLAP ADJUNTO Y REALICE LAS MISMAS PRUEBAS QUE AL CÓDIGO PARA SABER SI ES UN PROBLEMA 
ÚNICO DEL CÓDIGO O ES ALGO QUE REQUIERE CORREGIR TODO.
*/

using namespace std;

enum class Estado {q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15, q16, q17, q18, q19, q20, 
q21, q22, q23, q24, q25, q26, q27, q28, q29, q30, q31, q32, q33, q34, q35, q36, q37, q38, q39, q40, 
q41, q42, q43, q44, q45, q46, q47, q48, q49, q50, q51, q52, q53, q54, q55, q56, q57, q58, WA, qa, qb, qc};

Estado analisis(vector <char>& v, ofstream& out);

int main(){
	
	char lk = 1;
	cout << lk;
	
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
        out << "\n\nCINTA                                     ORIGEN          C_LEÍDO FIN          C_ESCRITO          DIRECCIÓN\n";
        
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
	
		if(x == Estado::q56){
		
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
	
	Estado actual = Estado::qa;
	int pos = 3;
	bool ban = true;
	
	while(ban && actual != Estado::q56){
		
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
			
			case Estado::qa:
				
				out << "QA          " << v[pos] << "          ";
				
				if(c == '1' || c == '*' || c == '/' || c == '+'  || c == '-'){
			
					out << "QA          " << v[pos] << "           R\n";
					pos++;
				}
				
				else if(c == '='){
					
					out << "QB          " << v[pos] << "           R\n";
					actual = Estado::qb;
					pos++;
				}else{
					
					out << "Rompe en QA con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::qb:
				
				if(c == 1){
					
					out << "QC          " << v[pos] << "           L\n";
					pos--;
					actual = Estado::qc;
				}else{
					
					out << "Rompe en QB con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::qc:
				
				if(c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '1'){
					
					out << "QC          " << v[pos] << "           L\n";
					pos--;
				}
				
				else if(c == 1){
					
					out << "Q0          " << v[pos] << "           L\n";
					actual = Estado::q0;
					pos++;
				}else{
					
					out << "Rompe en QC con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q0:
				
				out << "Q0          " << v[pos] << "          ";
				
				if(c == '1'){
			
					v[pos] = 'x';
					out << "Q1          " << v[pos] << "           R\n";
					pos++;
					actual = Estado::q1;
				}
				
				else if(c == '-'){
					
					out << "Q4          " << v[pos] << "           R\n";
					pos++;
					actual = Estado::q4;
				}
				
				else if(c == '+'){
					
					
					out << "Q5          " << v[pos] << "           R\n";
					pos++;
					actual = Estado::q5;
				}
				
				else if(c == '*'){
					
					out << "Q6          " << v[pos] << "           R\n";
					pos++;
					actual = Estado::q6;
				}
				
				else if(c == '/'){
					
					out << "Q7          " << v[pos] << "           R\n";
					pos++;
					actual = Estado::q7;
				}else{
					
					out << "Rompe en Q0 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
			
			break;
			
			case Estado::q1:
				
				out << "Q1          " << v[pos] << "          ";
				
				if(c == '1' || c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
					
					out << "Q1          " << v[pos] << "           R\n";
					pos++;
				}
					
				else if(c == 1){
					
					v[pos] = '1';
					v.push_back(1);
					out << "Q2          " << v[pos] << "           L\n";
					pos--;
					actual = Estado::q2;
				}else{
				
					out << "Rompe en Q1 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q2:
				
				out << "Q2          " << v[pos] << "          ";
				
				if(c == 'x'){
					
					out << "Q0          " << v[pos] << "           R\n";
					pos++;
					actual = Estado::q0;
				}
				
				else if(c == '1' || c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
					
					out << "Q2          " << v[pos] << "           L\n";
					pos--;
				}else{
				
					out << "Rompe en Q2 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q3:
				
				out << "Q3          " << v[pos] << "          ";
				
				if(c == 'x'){
					
					out << "Q8          " << v[pos] << "           L\n";
					pos--;
					actual = Estado::q8;
				}else{
					
					out << "Rompe en Q3 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q4:
				
				out << "Q4          " << v[pos] << "          ";
				
				if(c == '-'){
					
					out << "Q4          " << v[pos] << "           R\n";
					pos++;
				}
				
				else if(c == '+'){
					
					out << "Q5          " << v[pos] << "           R\n";
					actual = Estado::q5;
					pos++;
				}
				
				else if(c == '*'){
					
					
					out << "Q6          " << v[pos] << "           R\n";
					actual = Estado::q6;
					pos++;
				}
				
				else if(c == '/'){
					
					out << "Q7          " << v[pos] << "           R\n";
					actual = Estado::q7;
					pos++;
				}
				
				else if(c == '='){
					
					out << "Q3          " << v[pos] << "           L\n";
					actual = Estado::q3;
					pos--;
				}
				
				else if(c == '1'){
					
					out << "Q9          " << 'x' << "           R\n";
					actual = Estado::q9;
					v[pos] = 'x';
					pos++;
				}else{
					
					out << "Rompe en Q4 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q5:
				
				out << "Q5          " << v[pos] << "          ";
				
				if(c == '-'){
					
					out << "Q4          " << v[pos] << "           R\n";
					pos++;
					actual = Estado::q4;
				}
				
				else if(c == '+'){
					
					out << "Q5          " << v[pos] << "           R\n";
					pos++;
				}
				
				else if(c == '*'){
					
					
					out << "Q6          " << v[pos] << "           R\n";
					actual = Estado::q6;
					pos++;
				}
				
				else if(c == '/'){
					
					out << "Q7          " << v[pos] << "           R\n";
					actual = Estado::q7;
					pos++;
				}
				
				else if(c == '='){
					
					out << "Q3          " << v[pos] << "           L\n";
					actual = Estado::q3;
					pos--;
				}
				
				else if(c == '1'){
					
					v[pos] = 'x';
					out << "Q15          " << v[pos] << "           R\n";
					actual = Estado::q15;
					pos++;
				}else{
					
					out << "Rompe en Q5 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q6:
				
				out << "Q6          " << v[pos] << "          ";
				
				if(c == '-'){
					
					out << "Q4          " << v[pos] << "           R\n";
					actual = Estado::q4;
					pos++;
				}
				
				else if(c == '+'){
					
					out << "Q5          " << v[pos] << "           R\n";
					actual = Estado::q5;
					pos++;
				}
				
				else if(c == '*'){
					
					
					out << "Q6          " << v[pos] << "           R\n";
					pos++;
				}
				
				else if(c == '/'){
					
					out << "Q7          " << v[pos] << "           R\n";
					actual = Estado::q7;
					pos++;
				}
				
				else if(c == '='){
					
					out << "Q3          " << v[pos] << "           L\n";
					actual = Estado::q3;
					pos--;
				}
				
				else if(c == '1'){
					
					v[pos] = 'x';
					out << "Q23          " << v[pos] << "           R\n";
					actual = Estado::q23;
					pos++;
				}else{
					
					out << "Rompe en Q6 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q7:
				
				out << "Q7          " << v[pos] << "          ";
				
				if(c == '-'){
					
					out << "Q4          " << v[pos] << "           R\n";
					actual = Estado::q4;
					pos++;
				}
				
				else if(c == '+'){
					
					out << "Q5          " << v[pos] << "           R\n";
					actual = Estado::q5;
					pos++;
				}
				
				else if(c == '*'){
					
					
					out << "Q6          " << v[pos] << "           R\n";
					actual = Estado::q6;
					pos++;
				}
				
				else if(c == '/'){
					
					out << "Q7          " << v[pos] << "           R\n";
					pos++;
				}
				
				else if(c == '='){
					
					out << "Q3          " << v[pos] << "           L\n";
					actual = Estado::q3;
					pos--;
				}
				
				else if(c == '1'){
					
					out << "Q33          " << v[pos] << "           R\n";
					actual = Estado::q33;
					pos++;
				}
				
				else{
					
					out << "Rompe en Q7 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q8:
				
				out << "Q8          " << v[pos] << "          ";
				
				if(c == 'x'){
					
					out << "Q8          " << v[pos] << "          L\n";
					pos--;
				}
				
				else if(c == '+' || c == '-' || c == '*' || c == '/'){
					
					out << "Q55          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q55;
				}
				
				else if(c == 1){
					
					out << "Q56          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q56;
				}else{
					
					out << "Rompe en Q8 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q9:
				
				out << "Q9          " << v[pos] << "          ";
				
				if(c == '1' || c == '+' || c == '-' || c == '*' || c == '/'){
					
					out << "Q9          " << v[pos] << "           R\n";
					pos++;
				}
				
				else if(c == '='){
					
					out << "Q10          " << v[pos] << "           R\n";
					pos++;
					actual = Estado::q10;
				}else{
					
					out << "Rompe en Q9 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q10:
				
				out << "Q10          " << v[pos] << "          ";
				
				if(c == '1'){
					
					out << "Q11          " << v[pos] << "           R\n";
					actual = Estado::q11;
					pos++;
				}
				
				else if(c == '-' || c == 1){
					
					if(c == 1){
						
						v[pos] = '-';
						v.push_back(1);
					}
					
					out << "Q14          " << v[pos] << "           R\n";
					actual = Estado::q14;
					pos++;
				}else{
					
					out << "Rompe en Q10 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q11:
				
				out << "Q11          " << v[pos] << "          ";
				
				if(c == '1'){
					
					out << "Q11          " << v[pos] << "           R\n";
					pos++;
				}
				
				else if(c == 1){
					
					out << "Q12          " << v[pos] << "           L\n";
					pos--;
					actual = Estado::q12;
				}else{
					
					out << "Rompe en Q11 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q12:
				
				out << "Q12          " << v[pos] << "          ";
				
				if(c == '1'){
					
					v[pos] = 1;
					v.pop_back();
					out << "Q13          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q13;
				}else{
					
					out << "Rompe en Q12 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q13:
				
				out << "Q13          " << v[pos] << "          ";
				
				if(c == '1' || c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
					
					out << "Q13          " << v[pos] << "          L\n";
					pos--;
				}
				
				else if(c == 'x'){
					
					out << "Q4          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q4;
				}else{
					
					out << "Rompe en Q13 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q14:
				
				out << "Q14           " << v[pos] << "          ";
				
				if(c == '1'){
					
					out << "Q14          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == 1){
					
					v[pos] = '1';
					out << "Q13          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q13;	
				}else{
					
					out << "Rompe en Q14 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q15:
				
				out << "Q15          " << v[pos] << "          ";
				
				if(c == '*' || c == '/' || c == '+' || c == '-' || c == '1'){
					
					out << "Q15          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == '='){
					
					out << "Q16          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q16;
				}else{
					
					out << "Rompe en Q15 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q16:
				
				out << "Q16          " << v[pos] << "          ";
				
				if(c == '1'){
					
					out << "Q17          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q17;
				}else if(c == 1){
					
					out << "Q17          " << v[pos] << "          S\n";
					actual  = Estado::q17;
				}
				
				else if(c == '-'){
					
					out << "Q18          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q18;
				}else{
					
					out << "Rompe en Q16 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q17:
				
				out << "Q17          " << v[pos] << "          ";
				
				if(c == '1'){
					
					out << "Q17          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == 1){
					
					v[pos] = '1';
					v.push_back(1);
					out << "Q22          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q22;
				}else{
					
					out << "Rompe en Q17 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q18:
				
				out << "Q18          " << v[pos] << "          ";
				
				if(c == '1'){
					
					out << "Q18          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == 1){
					
					out << "Q19          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q19;
				}else{
					
					out << "Rompe en Q18 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q19:
				
				out << "Q19          " << v[pos] << "          ";
				
				if(c == '1'){
					
					v[pos] = 1;
					out << "Q20          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q20;
				}else{
					
					out << "Rompe en Q19 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q20:
				
				out << "Q20          " << v[pos] << "          ";
				
				if(c == '-'){
					
					v[pos] = 1;
					out << "Q21          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q21;
				}else if(c == '1'){
					
					out << "Q22          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q22;
				}else{
					
					out << "Rompe en Q20 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q21:
				
				out << "Q21          " << v[pos] << "          ";
				
				if(c == '='){
					
					out << "Q22          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q22;
				}else{
				
					out << "Rompe en Q21 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q22:
				
				out << "Q22           " << v[pos] << "          ";
				
				if(c == '+' || c == '-'  || c == '*' || c == '/' || c == '=' || c == '1'){
					
					out << "Q22          " << v[pos] << "          L\n";
					pos--;
				}else if(c == 'x'){
					
					out << "Q5          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q5;
				}else{
					
					out << "Rompe en Q22 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q23:
				
				out << "Q23          " << v[pos] << "          ";
				
				if(c == '+'  || c == '-' || c == '*' || c == '/' || c == '='){
					
					out << "Q30          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q30;
				}else if(c == '1'){
					
					v[pos] = 'x';
					out << "Q24          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q24;
				}else{
					
					out << "Rompe en Q23 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q24:
				
				out << "Q24          " << v[pos] << "          ";
				
				if(c == '1' || c == 'k' || c == '*' || c == '/' || c == '+' || c == '-' || c == '='){
					
					out << "Q24          " << v[pos] << "          R\n";
					pos++;
				}else if(c == 1){
					
					out << "Q25          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q25;
				}else{
					
					out << "Rompe en Q24 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q25:
				
				out << "Q25          " << v[pos] << "          ";
				
				if(c == '1'){
					
					v[pos] = 'k';
					out << "Q26          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q26;
				}else if(c == '='){
					
					out << "Q29          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q29;
				}else{
					
					out << "Rompe en Q25 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q26:
				
				out << "Q26          " << v[pos] << "          ";
				
				if(c == '1' || c == 'k'){
					
					out << "Q26          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == 1){
					
					v[pos] = '1';
					v.push_back(1);
					out << "Q27          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q27;
				}else{
					
					out << "Rompe en Q26 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q27:
				
				out << "Q27          " << v[pos] << "          ";
				
				if(c == '1'){
					
					out << "Q27          " << v[pos] << "          L\n";
					pos--;
				}else if(c == 'k'){
					
					out << "Q28          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q28;
				}else{
					
					out << "Rompe en Q27 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q28:
				
				out << "Q28          " << v[pos] << "          ";
				
				if(c == 'k'){
					
					out << "Q28          " << v[pos] << "          L\n";
					pos--;
				}else if(c == '1'){
					
					v[pos] = 'k';
					out << "Q26          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q26;
				}else if(c == '-' || c == '='){
					
					out << "Q29          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q29;
				}else{
					
					out << "Rompe en Q28 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q29:
				
				out << "Q29          " << v[pos] << "          ";
				
				if(c == '1' || c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
					
					out << "Q29          " << v[pos] << "          L\n";
					pos--;
				}else if(c == 'x'){
					
					out << "Q23          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q23;
				}else{
					
					out << "Rompe en Q29 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q30:
				
				out << "Q30           " << v[pos] << "          ";
				
				if(c == '1' || c == '=' || c == '+' || c == '-' || c == '*' || c == '/'){
					
					out << "Q30          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == 'k'){
					
					v[pos] = '1';
					out << "Q31          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q31;
				}
				
				else if(c == 1){
					
					out << "Q32          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q32;
				}else{
					
					out << "Rompe en Q30 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q31:
				
				out << "Q31          " << v[pos] << "          ";
				
				if(c == 'k'){
					
					v[pos] = '1';
					out << "Q31          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == '1'){
					
					out << "Q32          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q32;
				}else{
					
					out << "Rompe en Q31 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q32:
				
				out << "Q32          " << v[pos] << "          ";
				
				if(c == '1' || c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
					
					out << "Q32          " << v[pos] << "          L\n";
					pos--;
				}
				
				else if(c == 'x'){
					
					out << "Q6          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q6;
				}else{
					
					out << "Rompe en Q32 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q33:
				
				out << "Q33          " << v[pos] << "          ";
				
				if(c == '1' || c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
					
					out << "Q33          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == 1){
					
					v[pos] = '.';
					out << "Q34          " << v[pos] << "          L\n";
					v.push_back(1);
					pos--;
					actual = Estado::q34;
				}else{
					
					out << "Rompe en Q33 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q34:
				
				out << "Q34          " << v[pos] << "          ";
				
				if(c == '1' || c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
					
					out << "Q34          " << v[pos] << "          L\n";
					pos--;
				}
				
				else if(c == 'x'){
					
					out << "Q35          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q35;
				}else{
					
					out << "Rompe en Q34 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q35:
				
				out << "Q35          " << v[pos] << "          ";
				
				if(c == '/'){
					
					out << "Q36          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q36;
				}else{
					
					out << "Rompe en Q35 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q36:
				
				out << "Q36          " << v[pos] << "          ";
				
				if(c == '=' || c == '+' || c == '-' || c == '*' || c == '/'){
					
					out << "Q41          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q41;
				}
				
				else if(c == '1'){
					
					v[pos] = 'x';
					out << "Q37          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q37;
				}else{
					
					out << "Rompe en Q36 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q37:
				
				out << "Q37          " << v[pos] << "          ";
				
				if(c == '1' || c == '+' || c == '-' || c == '*' || c == '/'){
					
					out << "Q37          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == '='){
					
					out << "Q37          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q38;
				}else{
					
					out << "Rompe en Q37 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q38:
				
				out << "Q38           " << v[pos] << "          ";
				
				if(c == 'k'){
					
					out << "Q38          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == '-'){
					
					out << "Q39          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q39;
				}
				
				else if(c == '1'){
					
					v[pos] = 'k';
					out << "Q40          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q40;
				}
				
				else if(c == '.'){
					
					out << "Q45          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q45;
				}else{
					
					out << "Rompe en Q38 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q39:
				
				out << "Q39          " << v[pos] << "          ";
				
				if(c == 'k'){
					
					out << "Q39          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == '1'){
					
					v[pos] = 'k';
					out << "Q40          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q40;
				}
				
				else if(c == '.'){
					
					out << "Q45          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q45;
				}else{
					
					out << "Rompe en Q39 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q40:
				
				out << "Q40          " << v[pos] << "          ";
				
				if(c == '1' || c == 'k' || c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
					
					out << "Q40          " << v[pos] << "          L\n";
					pos--;
				}
				
				else if(c == 'x'){
					
					out << "Q36          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q36;
				}else{
					
					out << "Rompe en Q40 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q41:
				
				out << "Q41          " << v[pos] << "          ";
				
				if(c == 'x'){
					
					v[pos] = '1';
					out << "Q41          " << v[pos] << "          L\n";
					pos--;
				}
				
				else if(c == '/'){
					
					out << "Q42          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q42;
				}else{
					
					out << "Rompe en Q41 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q42:
				
				out << "Q42          " << v[pos] << "          ";
				
				if(c == '1' || c == 'k' || c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
					
					out << "Q42          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == '.'){
					
					out << "Q43          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q43;
				}else{
					
					out << "Rompe en Q42 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q43:
				
				out << "Q43          " << v[pos] << "          ";
				
				if(c == '1'){
					
					out << "Q43          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == 1){
					
					v[pos] = '1';
					v.push_back(1);
					out << "Q44          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q44;
				}else{
					
					out << "Rompe en Q43 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q44:
				
				out << "Q44          " << v[pos] << "          ";
				
				if(c == '.' || c == '1' || c == 'k' || c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
					
					out << "Q44          " << v[pos] << "          L\n";
					pos--;
				}
				
				else if(c == 'x'){
					
					out << "Q35          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q35;
				}else{
					
					out << "Rompe en Q44 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q45:
				
				out << "Q45          " << v[pos] << "          ";
				
				if(c == '1'){
					
					out << "Q46          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q46;
				}
				
				else if(c == 1){
					
					out << "Q53          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q53;
				}else{
					
					out << "Rompe en Q45 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q46:
				
				out << "Q46           " << v[pos] << "          ";
				
				if(c == '1'){
					
					out << "Q46          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == 1){
					
					v[pos] = '.';
					v.push_back(1);
					out << "Q47          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q47;
				}else{
					
					out << "Rompe en Q46 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q47:
				
				out << "Q47          " << v[pos] << "          ";
				
				if(c == '.' || c == 'k' || c == '1'){
					
					if(c != '1'){
						
						v[pos] = 1;
					}
					
					out << "Q48          " << v[pos] << "          L\n";
					pos--;
				}
				
				else if(c == '-' || c == '='){
					
					out << "Q48          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q48;
				}else{
					
					out << "Rompe en Q47 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q48:
				
				out << "Q48          " << v[pos] << "          ";
				
				if(c == 1){
					
					out << "Q48          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == '1'){
					
					v[pos] = 1;
					out << "Q49          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q49;
				}
				
				else if(c == '.'){
					
					v[pos] = 1;
					out << "Q52          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q52;
				}else{
					
					out << "Rompe en Q48 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q49:
				
				out << "Q49          " << v[pos] << "          ";
				
				if(c == 1){
					
					out << "Q49          " << v[pos] << "          L\n";
					pos--;
				}
				
				else if(c == '=' || c == '1' || c == '-'){
					
					out << "Q50          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q50;
				}else{
					
					out << "Rompe en Q49 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q50:
				
				out << "Q50          " << v[pos] << "          ";
				
				if(c == 1){
					
					v[pos] = '1';
					v.push_back(1);
					out << "Q51          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q51;
				}else{
					
					out << "Rompe en Q50 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q51:
				
				out << "Q51          " << v[pos] << "          ";
				
				if(c == 1){
					
					out << "Q48          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q48;
				}else{
					
					out << "Rompe en Q51 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q52:
				
				out << "Q52          " << v[pos] << "          ";
				
				if(c == 1 || c == '1' || c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
					
					out << "Q52          " << v[pos] << "          L\n";
					pos--;
				}
				
				else if(c == 'x'){
					
					out << "Q57          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q57;
				}else{
					
					out << "Rompe en Q52 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q53:
				
				out << "Q53          " << v[pos] << "          ";
				
				if(c == 'k' || c == '-' || c == '.'){
					
					v[pos] = 1;
					out << "Q53          " << v[pos] << "          L\n";
					pos--;
				}
				
				else if(c == '='){
					
					out << "Q54          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q54;
				}else{
					
					out << "Rompe en Q53 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q54:
				
				out << "Q54           " << v[pos] << "          ";
				
				if(c == '1' || c == '+' || c == '-' || c == '*' || c == '/'){
					
					out << "Q54          " << v[pos] << "          L\n";
					pos--;
				}
				
				else if(c == 'x'){
					
					out << "Q58          " << v[pos] << "          R\n";
					pos++;
					actual = Estado::q58;
				}else{
					
					out << "Rompe en Q55 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q55:
				
				out << "Q55          " << v[pos] << "          ";
				
				if(c == 'x'){
					
					out << "Q8          " << v[pos] << "          L\n";
					pos--;
					actual = Estado::q8;
				}else{
					
					out << "Rompe en Q55 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q57:
				
				out << "Q57          " << v[pos] << "          ";
				
				if(c == '1'){
					
					v[pos] = 'x';
					out << "Q57          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == '=' || c == '+' || c == '-' || c == '*' || c == '/'){
					
					out << "Q7          " << v[pos] << "          S\n";
					actual = Estado::q7;
				}else{
					
					out << "Rompe en Q57 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;
			
			case Estado::q58:
				
				out << "Q58          " << v[pos] << "          ";
				
				if(c == '1'){
					
					v[pos] = 'x';
					out << "Q58          " << v[pos] << "          R\n";
					pos++;
				}
				
				else if(c == '=' || c == '+' || c == '-' || c == '*' || c == '/'){
					
					out << "Q7          " << v[pos] << "          S\n";
					actual = Estado::q7;
				}else{
					
					out << "Rompe en Q58 con el caracter " << v[pos] << " :(\n";
					ban = false;
				}
				
			break;	
		}
		out << "\n";
	}
	
	if(!ban){
		
		actual = Estado::WA;
	}
	
	return actual;
}
