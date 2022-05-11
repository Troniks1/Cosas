/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     vocabulary.cpp                                     =
	=            Author:        Gabriel Melián Hernández		                   =
	=																			   =
=========================================================================================
=======================================================================================*/

/*------------------  DECLARACIÓN DE FUNCIONES  -----------------*/

#include "../include/vocabulary.hpp"

/*------------------------------------------------*/

/**
 * @brief      Construye una nueva instancia.
 */
Vocabulary::Vocabulary (void) {
	set_InputFile("");
	set_OutpuFile("");
	set_VocabularyCounter(0);
	set_Type("");	
	set_NTokens(0);
	set_NLines(0);
	set_ClassProbability(0.0);
}

/**
 * @brief      Construye una nueva instancia.
 *
 * @param[in]  inputFile  El fichero de entrada.
 * @param[in]  outpuFile  El fichero de salida.
 */
Vocabulary::Vocabulary (std::string inputFile, std::string outpuFile) {
	set_InputFile(inputFile);
	set_OutpuFile(outpuFile);
	set_VocabularyCounter(0);
	set_Type("");
	set_NTokens(0);
	set_NLines(0);
	set_ClassProbability(0.0);
}

/**
 * @brief      Destruye el objeto.
 */
Vocabulary::~Vocabulary (void) {
}

/**
 * @brief      Consigue el fichero de entrada.
 *
 * @return     El fichero de entrada.
 */
std::string Vocabulary::get_InputFile (void) const {
	return inputFile_;
}

/**
 * @brief      Consigue el fichero de salida.
 *
 * @return     El fichero de salida.
 */
std::string Vocabulary::get_OutpuFile (void) const {
	return outpuFile_;
}

/**
 * @brief      Consigue el VocabularyCounter.
 *
 * @return     El VocabularyCounter.
 */
int Vocabulary::get_VocabularyCounter (void) const {
	return vocabularyCounter_;
}

/**
 * @brief      Consigue el número de tokens.
 *
 * @return     El número de tokens.
 */
int Vocabulary::get_NTokens (void) const {
	return nTokens_;
}

/**
 * @brief      Consigue el número de líneas.
 *
 * @return     El número de líneas.
 */
int Vocabulary::get_NLines (void) const {
	return nLines_;
}

/**
 * @brief      Conssigue la probabilidad de clase.
 *
 * @return     La probabilidad de clase.
 */
float Vocabulary::get_ClassProbability (void) const {
	return classProbability_;
}

/**
 * @brief      Consigue el vocabulario.
 *
 * @return     El vocabulario.
 */
std::set<Token> Vocabulary::get_Vocabulary (void) const {
	return vocabulary_;
}

/**
 * @brief      Consigue el tipo.
 *
 * @return     El tipo.
 */
std::string Vocabulary::get_Type (void) const {
	return type_;
}

/**
 * @brief      Establece el fichero de entrada.
 *
 * @param[in]  newInputFile  El fichero de entrada.
 */
void Vocabulary::set_InputFile (std::string newInputFile) {
	inputFile_ = newInputFile;
}

/**
 * @brief      Establece el fichero de salida.
 *
 * @param[in]  newOutpuFile  El fichero de salida.
 */
void Vocabulary::set_OutpuFile (std::string newOutpuFile) {
	outpuFile_ = newOutpuFile;
}

/**
 * @brief      Establece el contador.
 *
 * @param[in]  newVocabularyCounter  El contador.
 */
void Vocabulary::set_VocabularyCounter (int newVocabularyCounter) {
	vocabularyCounter_ = newVocabularyCounter;
}

/**
 * @brief      Establece el número de tokens.
 *
 * @param[in]  newTokens  El número de tokens
 */
void Vocabulary::set_NTokens (int newTokens) {
	nTokens_ = newTokens;
}

/**
 * @brief      Establece el número de lineas
 *
 * @param[in]  newLines  El número de líneas.
 */
void Vocabulary::set_NLines (int newLines) {
	nLines_ = newLines;
}

/**
 * @brief      Establece el vocabulario.
 *
 * @param[in]  newVocabulary  El vocabulario.
 */
void Vocabulary::set_Vocabulary (std::set<Token> newVocabulary) {
	vocabulary_ = newVocabulary;
}

/**
 * @brief      Establece el tipo.
 *
 * @param[in]  newType  El tipo.
 */
void Vocabulary::set_Type (std::string newType) {
	type_ = newType;
}

/**
 * @brief      Establece la probabilidad de clase.
 *
 * @param[in]  newClassProbability  La probabilidad de clase.
 */
void Vocabulary::set_ClassProbability (float newClassProbability) {
	classProbability_ = newClassProbability;
}

/**
 * @brief      Operador =
 *
 * @param[in]  newVocabulary  El vocabulario.
 *
 * @return     El resultado de la asignación.
 */
Vocabulary& Vocabulary::operator= (const Vocabulary& newVocabulary) {
	this -> set_Vocabulary(newVocabulary.get_Vocabulary());
	this -> set_VocabularyCounter(newVocabulary.get_VocabularyCounter());
	this -> set_OutpuFile(newVocabulary.get_OutpuFile());
	this -> set_InputFile(newVocabulary.get_InputFile());
	this -> set_NTokens(newVocabulary.get_NTokens());
	this -> set_NLines(newVocabulary.get_NLines());
	this -> set_Type(newVocabulary.get_Type());
	this -> set_ClassProbability(newVocabulary.get_ClassProbability());
	return *this;
}

/**
 * @brief      Preprocesa los datos del programa.
 *
 * @param[in]  stopWordFile  El fichero de StopWords.
 */
void Vocabulary::preProcessData (std::string& stopWordFile) {
	PreProcesser preProcesser;
	std::string outputFile = "../outputs/preProcesserHelper.txt";
	std::vector<std::string> stopWords = loadStopWord(stopWordFile);
	std::string empty = "";
	preProcesser.loadData(inputFile_, empty);
	preProcesser.convertLowerCase();
	preProcesser.erasePunctuationSigns();
	preProcesser.eraseAllNumbers();
	preProcesser.storeData(outputFile, 0);
	preProcesser.eraseReservedWords(stopWords, outputFile);
	return;
}

/**
 * @brief      Carga las stopWords.
 *
 * @param[in]  inputFile  El fichero de entrada.
 *
 * @return     El vector de StopWords.
 */
std::vector<std::string> Vocabulary::loadStopWord (std::string& inputFile) {
	std::vector<std::string> stopWords;
	std::ifstream file(inputFile, std::ios::in);
	if (file.fail()) {
		std::cout << std::endl << "Error 404, stopWords file not found." << std::endl;
		exit(1);
	}
	std::string word = "";
	while (!file.eof()) {
		file >> word;
		stopWords.push_back(word);
	}
	file.close();
	return stopWords;
}

/**
 * @brief      Genera el fichero de Vocabulario.
 *
 * @param      inputFile  El fichero de entrada.
 * @param[in]  tokenize   Si quieres que las palabras se tokenizen o no.
 */
void Vocabulary::generateVocabulary (std::string& inputFile, bool tokenize) {
	std::ifstream file(inputFile, std::ios::in);
	if (file.fail()) {
		std::cout << std::endl << "Error 404, generateVocabulary file not found. (" << inputFile << ")" << std::endl;
		exit(1);
	}
	set_NTokens(0);
	set_VocabularyCounter(0);
	std::string word;
	std::set<Token>::iterator it;
	while (!file.eof()) {
		file >> word;
		if (isdigit(word[0])) {
			nLines_ = stoi(word);
		}
		else {
			if (!vocabulary_.count(word)) {
				Token newToken(word);
				vocabulary_.insert(newToken);
			}
			else if (tokenize){
				it = vocabulary_.find(word);
				Token newToken = *it;
				newToken.incrementate();
				vocabulary_.erase(word);
				vocabulary_.insert(newToken);
			}
			nTokens_++;
		}
	}
	file.close();
	set_VocabularyCounter(vocabulary_.size());
}

/**
 * @brief      Calcula y añade la probabilidad de clase.
 *
 * @param[in]  size  El tamaño
 */
void Vocabulary::addClassProbability (int size) {

	float prob = nLines_;
	prob /= size;
	prob = std::log(prob);
	set_ClassProbability(prob);
}

/**
 * @brief      Lee un Vocabulario creado desde el fichero.
 *
 * @param      inputFile  El fichero de entrada.
 */
void Vocabulary::readVocabulary (std::string& inputFile) {
	std::ifstream file(inputFile, std::ios::in);
	if (file.fail()) {
		std::cout << std::endl << "Error 404, readVocabulary file not found. (" << inputFile << ")" << std::endl;
		exit(1);
	}
	set_NTokens(0);
	set_VocabularyCounter(0);
	std::string word;
	std::getline(file, word);
	while (!file.eof()) {
		file >> word;
		Token newToken(word);
		newToken.set_Ammount(0);
		vocabulary_.insert(newToken);
		nTokens_++;
	}
	file.close();
	set_VocabularyCounter(vocabulary_.size());
}

/**
 * @brief      Almacena el vocabulario en un fichero de salida.
 *
 * @param      outputFile  El fichero de salida.
 */
void Vocabulary::storeVocabulary (std::string& outputFile) {
	std::fstream file(outputFile, std::ios::out | std::ios::trunc);
	if (file.fail()) {
		std::cout << "Error while storing data \"" << outputFile << "\" is not valid document" << std::endl;
		exit(1);
	} 
	else { 
		file << "Numero de palabras: " << get_VocabularyCounter();
		for (auto i : vocabulary_) {
			file << std::endl << i.get_Name();
		}
		// This represents unkown words
		file << std::endl << "<UNK>";
	}
	file.close();
}

/**
 * @brief      Lee los datos de aprendiza yt los guarda con sus respectivas
 *             probabilidades y frecuencias.
 *
 * @param      inputFile  El fichero de entrada.
 */
void Vocabulary::readLearnedData (std::string& inputFile) {
	std::ifstream file(inputFile, std::ios::in);
	std::string type = "";
	type += inputFile[inputFile.length() - 5];
	set_Type(type);
	if (file.fail()) {
		std::cout << std::endl << "Error 404, readVocabulary file not found. (" << inputFile << ")" << std::endl;
		exit(1);
	}
	set_NTokens(0);
	set_VocabularyCounter(0);
	std::string word;
	std::getline(file, word);
	std::string tmp = "";
	for (unsigned i = 0; i < word.length(); i++) {
		if (isdigit(word[i])) {
			tmp += word[i];
		}
	}
	set_NLines(std::stoi(tmp));
	std::getline(file, word);
	while (!file.eof()) {
		file >> word >> word;
		Token newToken(word);
		newToken.set_Type(type);
		file >> word >> word;
		newToken.set_Ammount(std::stoi(word));
		file >> word >> word;
		newToken.set_Probability(std::stof(word));
		vocabulary_.insert(newToken);
		nTokens_++;
	}
	file.close();
	set_VocabularyCounter(vocabulary_.size());
}