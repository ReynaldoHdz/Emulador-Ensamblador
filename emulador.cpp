#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string.h>
#include <cmath>

using namespace std;

int AC=0, MAR, MDR, PC=0, IR, FR=10;

//FR
//100: AC < 0, 
//010: AC = 0, 
//001: AC > 999999, 
//si no es ninguno, FR=000

//Construyendo el array de memoria
const int memorySize=100;
int Memory[memorySize];
//Obteniendo el lado de la matriz
int side = sqrt(memorySize);

//Estructura para guardar instrucción
struct Instruction {
  string instruction;
  int address;
};

//Array de instrucciones, para visualización en terminal
Instruction Memory_Instructions[memorySize];

//Convierte la instrucción a int. Muchos terminan en 0 porque no tienen direccionamiento
int instructionToInt(string ins){
  if (ins=="NOP") return 000;
  if (ins=="NEG") return 001;
  if (ins=="CLA") return 002;

  if (ins=="LDAI") return 100; //lDA INMEDIATO
  if (ins=="LDAR") return 101; //LDA RELATIVO
  if (ins=="LDAA") return 102; //LDA ABSOLUTO
  if (ins=="LDAD") return 103; //LDA INDIRECTO
  
  if (ins=="STAI") return 110;
  if (ins=="STAR") return 111;
  if (ins=="STAA") return 112;
  if (ins=="STAD") return 113;

  if (ins=="ADDI") return 200;
  if (ins=="ADDR") return 201;
  if (ins=="ADDA") return 202;
  if (ins=="ADDD") return 203;

  if (ins=="SUBI") return 210;
  if (ins=="SUBR") return 211;
  if (ins=="SUBA") return 212;
  if (ins=="SUBD") return 213;

  if (ins=="JMP") return 300;
  if (ins=="JMZ") return 310;
  if (ins=="JMN") return 320;
  if (ins=="JMV") return 330;
  
  if (ins=="INPUTtoAC") return 500; //INPUT al Acumulador
  if (ins=="INPUTtoAD") return 502; //INPUT a una dirección

  if (ins=="HLT") return 990;
  if (ins=="ORG") return 910;
  if (ins=="DEF") return 920; //No implementado


  else return 0;
}

//Codifica la instrucción al formato de 6 bits del IR.
int codifyInstruction(Instruction ins){
  int codified;
  codified+=ins.address;
  codified+=instructionToInt(ins.instruction)*1000;
  return codified;
}

//Corre una instrucción, aumenta PC en 1 cada vez (fetch).
bool runInstruction(int ins){
  IR=ins;
  int instruction, address;
  instruction = ins/1000;
  address = ins%1000;
  
  cout<<"Running Operation: "<<Memory_Instructions[PC].instruction<<" "<<Memory_Instructions[PC].address<<endl;

  switch(instruction){
    case 0: //NOP
    break;

    case 1: //NEG
      AC = -AC;
    break;

    case 2: //CLA
      AC = 0;
    break;

    case 100: //LOAD Inmediate
      AC = address;
    break;

    case 101: //LOAD Relative
      MAR = PC+address;
      MDR = Memory[MAR];
      AC = MDR;
    break;

    case 102: //LOAD Absolute
      MAR = address;
      MDR = Memory[MAR];
      AC = MDR;
    break;

    case 103: //LOAD Indirect
      MAR = Memory[address];
      MDR = Memory[MAR];
      AC = MDR;
    break;

    case 110: //STA Inmediate //NULL
      
    break;

    case 111: //STA Relative 
      MAR = PC+address;
      MDR = AC;
      Memory[MAR] = MDR;
    break;

    case 112: //STA Absolute
      MAR = address;
      MDR = AC;
      Memory[MAR] = MDR;
    break; 

    case 113: //STA Indirect
      MAR = Memory[address];
      MDR = AC;
      Memory[MAR] = MDR;
    break;

    case 200: //ADD Inmediate
      AC += address;
    break;

    case 201: //ADD Relative
      MAR = PC+address;
      MDR = Memory[MAR];
      AC += MDR;
    break;

    case 202: //ADD Absolute
      MAR = address;
      MDR = Memory[MAR];
      AC += MDR;
    break;

    case 203: //ADD Indirect
      MAR = Memory[address];
      MDR = Memory[MAR];
      AC += MDR;
    break; 

    case 210: //SUB Inmediate
      AC -= address;
    break;

    case 211: //SUB Relative
      MAR = PC+address;
      MDR = Memory[MAR];
      AC -= MDR;
    break;

    case 212: //SUB Absolute
      MAR = address;
      MDR = Memory[MAR];
      AC -= MDR;
    break;

    case 213: //SUB Indirect
      MAR = Memory[address];
      MDR = Memory[MAR];
      AC -= MDR;
    break; 

    case 300: //JMP
      PC = address-1;
    break;

    case 310: //JMZ
      if (AC==0) PC=address-1;
    break;

    case 320: //JMN
      if (AC<0) PC=address-1;
    break;

    case 330: //JMV
      if (AC>999999) PC=address-1;
    break;

    case 500: //INPUT TO AC
      int inputtoAC;
      cout<<"INPUT to AC = ";
      cin>>inputtoAC;
      AC=inputtoAC;
    break;

    case 502: //INPUT TO ADDRESS
      int input;
      cout<<"INPUT to address "<<address<<" = ";
      cin>>input;
      MAR = address;
      MDR = input;
      Memory[MAR] = MDR;
    break;

    case 910: //ORG
      PC=address;
    break;

    case 990: //HALT
      cout<<"Programa Terminado con HALT"<<endl;
      return false;
    
    default:
      cout<<"No existe la operación"<<endl;
      return false;
  }
  if (AC > 999999) //FR V
    FR = 1;
  else if (AC == 0) //FR Z
    FR = 10;
  else if (AC < 0) //FR N
    FR = 100;
  else
    FR = 0;
  
  PC++;
  return true;
}

//Para leer el programa de un archivo de texto
bool readProgram(string filename){
  ifstream bitacora;
  bitacora.open(filename);
  if (!bitacora) {
      cerr << "Error: el archivo " << filename << " no se encontro" << endl;
      return false;
  }

  int i=0;
  while (!bitacora.eof()){
    //Guardando instrucciones en el array
      Instruction ins;
      bitacora>>ins.instruction;
      cout<<"Read "<<ins.instruction<<endl;
      if(ins.instruction=="CLA" || ins.instruction=="HLT"){
        ins.address = 0;
      }
      else{
        bitacora>>ins.address;
      }
      Memory_Instructions[i]=ins;
      Memory[i]=codifyInstruction(ins);
      i++;
  }

  bitacora.close();
  return true;
}

void printMemory(){
  //Imprime la memoria con las instrucciones ya ensambladas.
  cout<<"----------------------------------------------------MEMORIA-------------------------------------------------------"<<endl;
  for (int i=0; i<side; i++){
    cout<<"          "<<i;
  }
  cout<<endl<<"________________________________________________________________________________________________________________"<<endl;

  for (int i=0; i<side; i++){
    cout<<i;
    for (int j=0; j<side; j++){
      cout<<"  |  "<<setw(6)<<setfill('0')<<Memory[i*10+j];
    }
    cout<<endl;
  }
}

int main(){
  
  //Llenando con ceros
  for (int i=0;i<memorySize;i++){
    Memory[i]=0;
  }

  //Corre el programa de example.txt por default.
  string filename = "example.txt";
  cout<<"Enter name of your program: ";
  cin>>filename;

  //Leyendo el programa
  if(!readProgram(filename)){
    return 1;
  }

  cout<<"Programa leido, ensamblado"<<endl;

  printMemory();

  int option;
  cout<<"ENTER: 1) Run all program. 2) Run step by step"<<endl;
  cin>>option;

  while (option!=1 && option!=2){
    cout<<"REENTER: 1) Run all program. 2) Run step by step"<<endl;
    cin>>option;
  }

  if (option==1){
    cout<<endl<<"Enter to run program"<<endl;
    cin.ignore();
    //Corre el programa completo
    while(runInstruction(Memory[PC])){
        cout<<"AC = "<<setw(6)<<setfill('0')<<AC<<endl;
        cout<<"PC = "<<setw(6)<<setfill('0')<<PC<<endl;
        cout<<"IR = "<<setw(6)<<setfill('0')<<IR<<endl;
        cout<<"MAR = "<<setw(6)<<setfill('0')<<MAR<<endl;
        cout<<"MDR = "<<setw(6)<<setfill('0')<<MDR<<endl;
        cout<<"FR = "<<setw(3)<<setfill('0')<<FR<<endl;
    };
  }
  else if (option == 2){
    cout<<endl<<"Enter to run instruction"<<endl;
    cin.ignore();

    //Corre la instrucción cada que se da enter.
    //Imprime los registros cada vez.

    while(runInstruction(Memory[PC])){
        cout<<"AC = "<<setw(6)<<setfill('0')<<AC<<endl;
        cout<<"PC = "<<setw(6)<<setfill('0')<<PC<<endl;
        cout<<"IR = "<<setw(6)<<setfill('0')<<IR<<endl;
        cout<<"MAR = "<<setw(6)<<setfill('0')<<MAR<<endl;
        cout<<"MDR = "<<setw(6)<<setfill('0')<<MDR<<endl;
        cout<<"FR = "<<setw(3)<<setfill('0')<<FR<<endl;
        
        cout<<endl<<"Enter to run instruction"<<endl;
        cin.ignore();
    };
  }

  else{
    cout<<"Opción inválida"<<endl;
    return 1;
  }

  //Imprime la matriz de la memoria al final
  printMemory();
  
  return 0;
}