#include<iostream>
#include<Windows.h>
#include<conio.h> 
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
using namespace std;
//jugador izquierda
#define Up 119
#define Low 115

//jugador derecha
#define ArroyUp 72
#define ArroyDown 80

void gotoxy(int x, int y);
void printContorno();
void borrarContorno();
void cursor(bool);
void menu(class Jugador1 &, class Jugador2 &, class pelota &, class pelota&, int &);
void printTitulo();
void ganador(class Jugador1, class Jugador2);

class base{
	private:
		int x, y, vidas;
		string nombre;
		bool automatic = false;
	public:
		base(){
			x = 0;
			y = 0;
			vidas = 3;
			nombre = "***";
		}
		
		void printBase() {
			
			if(automatic == false){
				gotoxy(x, y); printf("%c", 178);
				gotoxy(x, y + 1); printf("%c", 178);
				gotoxy(x, y + 2); printf("%c", 178);
				gotoxy(x, y + 3); printf("%c", 178);
			}else{
				if(y > 1){
					gotoxy(x, y ); printf("%c", 178);
					gotoxy(x, y + 1); printf("%c", 178);
					gotoxy(x, y + 2); printf("%c", 178);
					gotoxy(x, y + 3); printf("%c", 178);
				}
			
			}
		}
		
		void setAuto(bool _automatic){
			automatic = _automatic;
		}
	
		void borrarBase(){
			if(automatic == false){
				gotoxy(x, y); cout << " ";
				gotoxy(x, y + 1); cout << " ";
				gotoxy(x, y + 2); cout << " ";
				gotoxy(x, y + 3); cout << " ";
			}else{
				if(y > 1){
					gotoxy(x, y); cout << " ";
					gotoxy(x, y + 1); cout << " ";
					gotoxy(x, y + 2); cout << " ";
					gotoxy(x, y + 3); cout << " ";
				}
			}
		}
	
		void setX(int _x) {
			x = _x;
		}
		int getX() {
			return x;
		}
	
		void setY(int _y) {
			y = _y;
		}
		int getY() {
			return y;
		}
	
		void setVidas(int _vidas) {
			vidas = _vidas;
		}
	
		int getVidas() {
			return vidas;
		}
		
		void setNombre(string n){
			nombre = n;
		}
		
		string getNombre(){
			return nombre;
		}
	

};
 
class Jugador1 : public base {
	public:
		Jugador1(){
			setY(12);
			setX(4);
			setVidas(3);
		}
	
		void moverBase() {
			char tecla;

			if (_kbhit()) {
	
				tecla = _getch();
	
				borrarBase();
				
				if (tecla == Up and getY() > 2){
					setY(getY() - 2);
				}
				
				if (tecla == Low and getY() < 23){
					setY(getY() + 2);
				}
				
				printBase();
			}
		
		}
	
		void printVidas() {
			gotoxy(3, 29);
			cout << getNombre() << ":             ";
	
			for (int i = 0; i < getVidas(); i++) {
				gotoxy(9 + 2 * i, 29);
				cout << "<3 ";
			}
		}

};
 
class Jugador2 : public base {
	public:
		Jugador2(){
			setX(115);
			setY(12);
			setVidas(3);
		}
		
		void moverBase(){
			char tecla;
		
			if (_kbhit()) {
		
				tecla = _getch();
		
				borrarBase();
				
				if (tecla == ArroyUp and getY() > 2) setY(getY() - 2);
				
				if (tecla == ArroyDown and getY() < 23) setY(getY() + 2);
				printBase();
			}
	
		}
		
		void printVidas(){
			gotoxy(105, 29);
			cout << getNombre() << ":           ";
		
			for (int i = 0; i < getVidas(); i++) {
				gotoxy(111 + 2 * i, 29);
				cout << "<3 ";
			}
		}
};


class pelota {
	private:
		int x, y, velocidad;
		bool der, izq, arriba, abajo;
public:
	pelota() {
		srand (time(NULL));
		x = 60;
		y = 15;
		velocidad = 35;
		
		izq = rand() % 2; //0, 1
		arriba = rand() % 2; //0, 1
		
		if(izq == 0){
			der = 1;
		}else if(izq == 1){
			der = 0;
		}
		
		if(arriba == 0){
			abajo = 1;
		}else if(arriba == 1){
			abajo = 0;
		}
	}

	void setX(int _x) {
		x = _x;
	}
	int getX() {
		return x;
	}

	void setY(int _y) {
		y = _y;
	}
	int getY() {
		return y;
	}
	
	void setDer(bool _der){
		der = _der;
	}
	
	bool getDer(){
		return der;
	}
	
	void setIzq(bool _izq){
		izq = _izq;
	}
	
	bool getIzq(){
		return izq;
	}
	
	void setArriba(bool a){
		arriba = a;
	}
	
	bool getArriba(){
		return arriba;
	}
	
	void setAbajo(bool a){
		abajo = a;
	}
	
	bool getAbajo(){
		return abajo;
	}
	
	void setVelocidad(int vel){
		velocidad = vel;
	}

	void impacto(class Jugador1 &jugador1, class Jugador2 &jugador2) {
		if (x == 2){
			jugador1.setVidas(jugador1.getVidas() - 1);
			jugador1.printVidas();
			setX(60);
			setY(15);
			gotoxy(x, y);cout << "o";
		}
		else if (x == 117) {
			jugador2.setVidas(jugador2.getVidas() - 1);
			jugador2.printVidas();
			setX(60);
			setY(15);
			gotoxy(x, y);cout << "o";
		}
	}
	
	void printPelota(){
		
		if(der and !izq and abajo and !arriba){
			gotoxy(x, y); cout << "o";
			Sleep(velocidad);
			gotoxy(x, y); cout << " ";
			x += 1;	
			y += 1;
		}else if(der and !izq and !abajo and arriba){
			gotoxy(x, y); cout << "o";
			Sleep(velocidad);
			gotoxy(x, y); cout << " ";
			x += 1;
			y -= 1;
		}else if(!der and izq and arriba and !abajo){
			gotoxy(x, y); cout << "o";
			Sleep(velocidad);
			gotoxy(x, y); cout << " ";
			x -= 1;
			y -= 1;
		}else if(!der and izq and abajo and !arriba){
			gotoxy(x, y); cout << "o";
			Sleep(velocidad);
			gotoxy(x, y); cout << " ";
			x -= 1;
			y += 1;
		}
	}

	void rebote(class Jugador1 jugador1, class Jugador2 jugador2){
		if(getY() == 2){ // si la pelota toca el borde superior
			setAbajo(true);
			setArriba(false);
		}
		
		if(getY() == 27){ // si toca el borde inferior
			setArriba(true);
			setAbajo(false);
		}

		
		if(getX() == 114 and getY() >= jugador2.getY() and getY() <= jugador2.getY() + 6){ //si toca la barra del jugador derecho o la pared derecha
			setIzq(true);
			setDer(false);
		}

		if(getX() == 5 and getY() >= jugador1.getY() and getY() <= jugador1.getY() + 5){ // si toca la barra del jugador izquierdo o la pared izquierda
			setDer(true);
			setIzq(false);
		}
	}
	
};

int main(){
 	bool gameOver = false;
 	bool menuOp = false;
 	int op;
	cursor(false);
	
	Jugador1 jugador1;
	Jugador2 jugador2;
	pelota ball, ball2;
	
	menu(jugador1, jugador2, ball, ball2, op);
	
	while (gameOver != true){
		
		if(jugador1.getVidas() == 0 or jugador2.getVidas() == 0){
			ganador(jugador1, jugador2);
			menuOp = true;
		}
		if(menuOp == true){
			menu(jugador1, jugador2, ball, ball2, op);
			jugador1.setVidas(3);
			jugador2.setVidas(3);
			menuOp = false;
			
			ball.setX(60);
			ball.setY(15);
			
			ball2.setX(60);
			ball2.setY(15);
		}


		if(op == 5){
			gameOver = true;
		}else{
			if(op == 2 or op == 3){		
				ball2.printPelota();
				ball2.impacto(jugador1, jugador2);
				ball2.rebote(jugador1, jugador2);
			}else if(op == 4){
				
				jugador1.moverBase();
				
				jugador1.printBase();
				
				
				jugador1.printVidas();
				
				if(ball.getY() > 2){
					jugador2.borrarBase();
					jugador2.setY(ball.getY() - 3);
					jugador2.printBase();
				}
				
	                                
				ball.impacto(jugador1, jugador2);
				ball.printPelota();
				ball.rebote(jugador1, jugador2);
			}
			
			
			if(op != 4){
				
				jugador1.moverBase();
				jugador2.moverBase();
				
				jugador1.printBase();
				jugador2.printBase();
				
				jugador1.printVidas();
				jugador2.printVidas();
				
				ball.impacto(jugador1, jugador2);
				ball.printPelota();
				ball.rebote(jugador1, jugador2);	
			}
		}
		
	}
	
	gotoxy(51, 10); cout << "GRACIAS POR JUGAR :) \n\n\n\n\n\n";
	return 0;
}

void printContorno() {
	//dimension de la pantalla: 116x26
	
	gotoxy(1, 1); printf("%c", 201);
	gotoxy(118, 1); printf("%c", 187);
	gotoxy(1, 28); printf("%c", 200);
	gotoxy(118, 28); printf("%c", 188);
	
	//horizontales
	for (int i = 2; i < 118; i++){
		gotoxy(i, 1); printf("%c", 205);
		gotoxy(i, 28); printf("%c", 205);
	}
	
	//verticales
	for (int i = 2; i < 28; i++){
		gotoxy(1, i); printf("%c", 186);
		gotoxy(118, i); printf("%c", 186);
	}
}

void borrarContorno(){
	

	for (int i = 0; i < 119; i++){
		for(int j = 0; j < 30; j++){
			gotoxy(i, j); cout << " ";
		}
	}
	
}

void gotoxy(int x, int y) {

	HANDLE hCon; //objeto tipo ventana, identificador de nuestra ventana

	hCon = GetStdHandle(STD_OUTPUT_HANDLE); //tomando el control de la salida de consola

	COORD Pos; //creando objeto tipo coordenada. 

	Pos.X = x;
	Pos.Y = y;

	SetConsoleCursorPosition(hCon, Pos);//perimte dar una posicion al cursor

}

void cursor(bool x) {
	HANDLE hCon; //objeto tipo ventana, identificador de nuestra ventana

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);


	CONSOLE_CURSOR_INFO cci; //objeto de tipo cursor con la informacion

	cci.dwSize = 1;
	cci.bVisible = x;

	SetConsoleCursorInfo(hCon, &cci); //metodo para modificar el cursor
}

void printTitulo(){
	gotoxy(52, 1);cout << "C R A Z Y  P O N G"; //titulo
	gotoxy(51, 0); printf("%c", 218); //esquina arriba izq titulo
	gotoxy(51, 3); printf("%c", 192); //esquina abajo izq titulo
	
	gotoxy(70, 0);printf("%c", 191); //esquina arriba der titulo
	gotoxy(70, 3);printf("%c", 217); //esquina abajo der titulo
	
	
	for(int i = 0; i < 18; i++){ //contorno superior e inferior titulo
		gotoxy(52 + i, 0);
		printf("%c", 196);
		
		gotoxy(52 + i, 3);
		printf("%c", 196);
	}
	
	for(int i = 0; i < 2; i++){ //contorno laterales titulo
		gotoxy(51, i+1);
		printf("%c", 179);
		
		gotoxy(70, i+1);
		printf("%c", 179);
	}
}

void menu(class Jugador1 &jugador1, class Jugador2 &jugador2, class pelota &ball, class pelota &ball2, int &op){
	borrarContorno();
	string nombre;
	printTitulo();
	
	gotoxy(47,5);
	cout << "Nivel 1 -> 1 bolita, velocidad intermedio" << endl;
	gotoxy(47,6);
	cout << "Nivel 2 -> 2 bolitas, velocidad intermedio" << endl;
	gotoxy(47,7);
	cout << "Nivel 3 -> 2 bolitas, velocidad alta" << endl;
	gotoxy(47,8);
	cout << "Nivel 4 -> Un jugador";
	gotoxy(47, 9);
	cout << "5.- Salir" << endl;
	gotoxy(47,10);
	cout << "Nivel: ";
	cin >> op;
	
	
	for(int i = 0; i < 50; i++){
		for(int j = 0; j < 7; j++){
			gotoxy(i + 47, j + 5);
			cout << " ";
		}
	}
	
	if(op == 2 or op == 3){
		
		if(ball.getDer()){
			ball2.setDer(false);
			ball2.setIzq(true);
		}else{
			ball2.setDer(true);
			ball2.setIzq(false);
		}
	}
	
	if(op == 1 or op == 4){
		ball.setVelocidad(35);
		ball.setVelocidad(35);
		if(op == 4){
			jugador2.setAuto(true);
		}
	}else if(op == 2){
		ball2.setVelocidad(10);
		ball2.setVelocidad(10);
		
		ball.setVelocidad(10);
		ball.setVelocidad(10);
	}else if(op == 3){
		ball2.setVelocidad(1);
		ball2.setVelocidad(1);
		
		ball.setVelocidad(1);
		ball.setVelocidad(1);
	}
	
	
	if(op != 5){
		
	
		gotoxy(47,5);
		cout << "Ingrese el nombre del jugador 1: ";
		cin >> nombre;
		jugador1.setNombre(nombre);
		gotoxy(47,6);
		cout << "Ingrese el nombre del jugador 2: ";
		cin >> nombre;
		jugador2.setNombre(nombre);
		borrarContorno();
		
		
		gotoxy(47, 15);
		cout << "Cargando";	
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 3; j++){
				gotoxy(55 + j, 15);
				cout << ".";
				Sleep(500);
			}
			for(int k = 0; k < 3; k++){
				gotoxy(55 + k, 15);
				cout << " ";
			}
			Sleep(500);
		}
		
		for(int i = 0; i < 8; i++){
			gotoxy(47 + i, 15); cout << " ";
		}
		

		printContorno();
	}
	
}

void ganador(class Jugador1 jugador1, class Jugador2 jugador2){
	borrarContorno();
	printTitulo();
	string frase = "El ganador es: ";
	
	for(int i = 0; i < 15; i++){
		gotoxy(52 + i, 5); cout << frase[i];
		Sleep(20);
	}
	
	gotoxy(67, 5);
	if(jugador1.getVidas() == 0){
		cout << jugador2.getNombre();
	}else{
		cout << jugador1.getNombre();
	}
	Sleep(2000);
}