#include<fstream>
#include<iostream>
using std::cout;
#include<string>
using std::string;


std::string deleteWhiteSpacesSurround(std::string str);

int main(void){
    string reempN = "Negative,";
    string reempN_con = "\nNegative,";
    string reempP = "Positive,";
    string reempP_con = "\nPositive,";
    string line;
    size_t lenN = reempN.length();
    size_t lenP = reempP.length();

    std::ifstream archivo_in{ "entrada.txt" };//archivo de entrada
    std::ofstream archivo_out{ "temp.txt" };//archivo de salida

    if (archivo_in && archivo_out) {
        
       int contador = 0;
  std::string line;
  std::string tweet = "";
  while (std::getline(archivo_in, line)) {
    line = deleteWhiteSpacesSurround(line);
    if (line.empty()) {
      continue;
    }
    if(contador != 0){
        size_t pos;
        if((pos = line.find(reempN) != string::npos)){
                line.replace(pos, lenN, reempN_con);
        }
        else if((pos = line.find(reempP) != string::npos)){
            line.replace(pos, lenP, reempP_con);
        }
    }
      tweet += line + " ";
      contador = 1;
    }
    archivo_out << tweet << '\n';   
    }
    else
        cout << "No se pueden abrir los archivos";
}


std::string deleteWhiteSpacesSurround(std::string str) {
  while (!str.empty()) {
    if ((str[0] == ' ') || (str[0] == '\t') || ((int)str[0] == 13) || (str[0] == '"')) {
      str.erase(str.begin());
    } else if ((str[str.size() - 1] == ' ')  || (str[str.size() - 1] == '\t') || ((int)str[str.size() - 1] == 13) || (str[str.size() - 1] == '"')) {
      str.erase(str.size() - 1);
    } else {
      break;
    }
  }
  return str;
}