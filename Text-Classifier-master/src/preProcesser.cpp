/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     preProcesser.cpp                                   =
	=            Author:        Gabriel Melián Hernández		                   =
	=																			   =
=========================================================================================
=======================================================================================*/
/*------------------  FUNCTIONS  -----------------*/

#include "../include/preProcesser.hpp"

/*------------------------------------------------*/

/**
 * @brief      Construye una nueva instancia.
 */
PreProcesser::PreProcesser (void) {
	set_InputFile("");
	set_OutputFile("");
	set_Data("");
}

/**
 * @brief      Construye una nueva instancia.
 *
 * @param[in]  inputFile  El fichero de entrada.
 * @param[in]  outpuFile  El fichero de salida.
 */
PreProcesser::PreProcesser (std::string inputFile, std::string outpuFile) {
	set_InputFile(inputFile);
	set_OutputFile(outpuFile);
	set_Data("");
}

/**
 * @brief      Destruye el objeto.
 */
PreProcesser::~PreProcesser (void) {
}

/**
 * @brief      Consigue el fichero de entrada.
 *
 * @return     El fichero de entrada.
 */
std::string PreProcesser::get_InputFile (void) const {
	return inputFile_;
}

/**
 * @brief      Consigue el fichero de salida.
 *
 * @return     El fichero de salida.
 */
std::string PreProcesser::get_OutputFile (void) const {
	return outputFile_;
}

/**
 * @brief      Consigue los datos.
 *
 * @return     Los datos.
 */
std::string PreProcesser::get_Data (void) const {
	return data_;
}

/**
 * @brief      Establece el fichero de entrada.
 *
 * @param[in]  newInputFile  El fichero de entrada.
 */
void PreProcesser::set_InputFile (std::string newInputFile) {
	inputFile_ = newInputFile;
}

/**
 * @brief      Establece el fichero de salida.
 *
 * @param[in]  newOutputFile  El fichero de salida.
 */
void PreProcesser::set_OutputFile (std::string newOutputFile) {
	outputFile_ = newOutputFile;
}

/**
 * @brief      Establece los datos.
 *
 * @param[in]  newData  Los datos.
 */
void PreProcesser::set_Data (std::string newData) {
	data_ = newData;
}

/**
 * @brief      Operador de asignación.
 *
 * @param[in]  newPreProcesser  El nuevo PreProcesser.
 *
 * @return     El resultado de la asignación.
 */
PreProcesser& PreProcesser::operator= (const PreProcesser& newPreProcesser) {
	this -> set_Data(newPreProcesser.get_Data());
	this -> set_OutputFile(newPreProcesser.get_OutputFile());
	this -> set_InputFile(newPreProcesser.get_InputFile());
	return *this;
}

/**
 * @brief      Convierte todo el str a minuscula.
 *
 * @param      str   El String.
 */
void PreProcesser::convertLowerCase (std::string& str) {
	set_Data(str);
	convertLowerCase();
	str = get_Data();
}

/**
 * @brief      Convierte todos los datos a minúscula.
 */
void PreProcesser::convertLowerCase (void) {
	std::transform(data_.begin(), data_.end(),data_.begin(), ::tolower);
}

/**
 * @brief      Convierte todo el string a mayúscula.
 *
 * @param      str   El String.
 */
void PreProcesser::convertUpperCase (std::string& str) {
	set_Data(str);
	convertUpperCase();
	str = get_Data();
}

/**
 * @brief      Convierte todos los datos a mayúscula.
 */
void PreProcesser::convertUpperCase (void) {
	std::transform(data_.begin(), data_.end(),data_.begin(), ::toupper);
}

/**
 * @brief      Borra todas las reservedWords.
 *             
 *
 * @param[in]  reservedWords  El vector de palabras reservadas.
 * @param[in]  fileName       El fichero de entrada.
 */
void PreProcesser::eraseReservedWords (std::vector<std::string>& reservedWords, std::string& fileName) {
	std::ifstream file(fileName, std::ios::in);
	data_ = "";
	if (file.fail()) {
		std::cout << std::endl << "Error 404, file not found in eraseReservedWords function." << std::endl;
		exit(1);
	}
	std::string aux = "";
	while (!file.eof()) {
		file >> aux;
		bool push = true;
		for (unsigned i = 0; i < reservedWords.size(); i++) {
			if (aux == reservedWords[i]) {
				push = false;
				break;
			}
		}
		if (push) {
			data_ += ' ' + aux;
		}
	}
	file.close();
	storeData(fileName, 0);
}

/**
 * @brief      Borra todas las reservedWords.
 *             
 *
 * @param[in]  reservedWords  El vector de palabras reservadas.
 * @param[in]  sentence       La sentencia.
 *
 * @return     El string sin las palabras reservadas.
 */
std::string PreProcesser::eraseReservedWords (std::string& sentence, std::vector<std::string>& reservedWords) {
	std::string result = "";
	std::string tmp = "";
	for (unsigned j = 0; j < sentence.length(); j++) {
		if (sentence[j] != ' ' && sentence[j] != '\t') {
			tmp += sentence[j];
		}
		else {
			bool push = true;
			for (unsigned i = 0; i < reservedWords.size(); i++) {
				if (tmp == reservedWords[i]) {
					push = false;
					break;
				}
			}
			if (push) {
				result += tmp + " ";
			}
			tmp = "";
		}
	}
	return result;
}

/**
 * @brief      Borra todos los signos de puntuación.
 *
 * @param      str   El string.
 */
void PreProcesser::erasePunctuationSigns (std::string& str) {
	set_Data(str);
	erasePunctuationSigns();
	str = get_Data();
}

/**
 * @brief      Borra todos los signos de puntuación.
 */
void PreProcesser::erasePunctuationSigns (void) {
	for (unsigned i = 0; i < data_.length(); i++) {
		if (!isalpha(data_[i]) && !isdigit(data_[i]) && data_[i] != '\n' && data_[i] != '\r') {
			data_[i] = ' ';
		}
	}
}

/**
 * @brief      Borra todas las URLs.
 *             
 *
 * @param      str   El String.
 */
void PreProcesser::eraseURLs (std::string& str) {
	set_Data(str);
	eraseURLs();
	str = get_Data();
}

/**
 * @brief      Borra todas las URLs.
 *             
 */
void PreProcesser::eraseURLs (void) {
	for (unsigned i = 0; i < data_.length(); i++) {
		if (data_[i] == '.' && data_[i + 1] != ' ') {
			unsigned k = i;
			while (data_[k] != ' ') {
				data_[k] = ' ';
				k--;
			}
			while (data_[i] != ' ') {
				data_[i] = ' ';
				i++;
			}
		}
	}
}

/**
 * @brief      Borra todos los Hashtags.
 *
 * @param      str   El String.
 */
void PreProcesser::eraseHashtags (std::string& str) {
	set_Data(str);
	eraseHashtags();
	str = get_Data();
}

/**
 * @brief      Borra todos los hashtags.
 *
 */
void PreProcesser::eraseHashtags (void) {
	for (unsigned i = 0; i < data_.length(); i++) {
		if (data_[i] == '#') {
			data_[i] = ' ';
			while (data_[i] != ' ') {
				data_[i] = ' ';
				i++;
			}
		}
	}
}

/**
 * @brief      Borra todos los números.
 *             
 *
 * @param      str   El String.
 */
void PreProcesser::eraseNumbers (std::string& str) {
	set_Data(str);
	eraseNumbers();
	str = get_Data();
}

/**
 * @brief      Borra todos los números.
 *             
 */
void PreProcesser::eraseNumbers (void) {
	if (isdigit(data_[0])) {
		unsigned i = 0;
		while (data_[i] != ' ') {
			data_[i] = ' ';
			i++;
		}
	}
	for (unsigned i = 1; i < data_.length(); i++) {
		if (isdigit(data_[i]) && data_[i - 1] == ' ') {
			while (data_[i] != ' ') {
				data_[i] = ' ';
				i++;
			}
		}
	}
}

/**
 * @brief      Borra todos los números y las palabras que contengan números.
 */
void PreProcesser::eraseAllNumbers (void) {
	if (isdigit(data_[0])) {
		unsigned i = 0;
		while (data_[i] != ' ') {
			data_[i] = ' ';
			i++;
		}
	}
	for (unsigned i = 1; i < data_.length(); i++) {
		if (isdigit(data_[i])) {
			if (data_[i - 1] != ' ') {
				unsigned k = i - 1;
				while (data_[k] != ' ' && k > 0) {
					data_[k] = ' ';
					k--;
				}
			}
			while (data_[i] != ' ' && i < data_.size()) {
				data_[i] = ' ';
				i++;
			}
		}
	}
}

/**
 * @brief      Borra todos los números y las palabras que contienen números.
 *             
 *
 * @param      str   El String.
 */
void PreProcesser::eraseAllNumbers (std::string& str) {
	set_Data(str);
	eraseAllNumbers();
	str = get_Data();
}

/**
 * @brief      Carga los datos de determinado tipo.
 *             
 *
 * @param      inputFile  El fichero de entrada.
 * @param[in]  dataType   El tipo.
 *                        
 *
 * @return     Las líneas de datos incluidas.
 */
int PreProcesser::loadData (std::string& inputFile, std::string dataType) {
	data_ = "";
	int dataLines = 0;
	std::ifstream file(inputFile, std::ios::in);
	if (file.fail()) {
		std::cout << std::endl << "Error 404, file not found in loadData function." << std::endl;
		exit(1);
	}
	std::string aux = "";
	while (!file.eof()) {
		file >> aux;
		if (dataType == "" ) {
			data_ += aux + " ";
			std::getline(file, aux);
			data_ += aux;
			dataLines++;
		}
		else {
			if (aux.length() < dataType.length()) {
				std::string spacedName = "";
				while (aux.length() < dataType.length()) {
					file >> spacedName;
					aux += " " + spacedName;
				}
			}
			std::string readedType = aux.substr(0, dataType.length());
			aux = aux.substr(dataType.length(), aux.length());
			std::getline(file, aux);
			if (readedType == dataType) {				
				data_ += aux;
				dataLines++;
			}
		}
		
	}
	file.close();
	return dataLines;
}

/**
 * @brief      Carga los datos de testeo.
 *
 * @param      inputFile  El fichero de entrada.
 */
void PreProcesser::loadTestData (std::string& inputFile) {
	data_ = "";
	const std::string ENDL = " PREPROCESSERENDL "; // Var that is going to be used in classifier to detects the end of a line
	std::ifstream file(inputFile, std::ios::in);
	if (file.fail()) {
		std::cout << std::endl << "Error 404, file not found in loadTestData function." << std::endl;
		exit(1);
	}
	std::string aux = "";
	while (!file.eof()) {
		std::getline(file, aux);
		data_ += aux + ENDL;	
	}
	file.close();
}

/**
 * @brief      Muestra los datos..
 */
void PreProcesser::printData  (void) {
	std::cout << data_;
}

/**
 * @brief      Guarda los datos en determinado fichero.
 *
 * @param      outputFile  El fichero de salida.
 * @param[in]  dataLines   Las líneas de datos.
 */
void PreProcesser::storeData(std::string& outputFile, int dataLines) {
	std::fstream file(outputFile, std::ios::out | std::ios::trunc);
	
	if (file.fail()) {
		std::cout << "Error while storing data \"" << outputFile << "\" is not valid document" << std::endl;
		exit(1);
	} 
	else { 
		if (dataLines != 0) {
			file << dataLines << std::endl;
		}
		file << data_;
	}
	file.close();
}