/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     classifier.cpp                                     =
	=            Author:        Gabriel Melián Hernández		                   =
	=																			   =
=========================================================================================
=======================================================================================*/
/*------------  DECLARACIÓN DE FUNCIONES  ------------*/

#include "../include/classifier.hpp"

/*------------------------------------------------*/

/**
 * @brief      Construye una nueva instancia.
 */
Classifier::Classifier (void) {
	set_Data("");
}

/**
 * @brief      Construye una nueva instancia.
 *
 * @param      argv  El array de argumentos.
 * @param      argc  La cantidad de argumentos.
 */
Classifier::Classifier (char* argv[], int& argc) {
	set_Data("");
	readInputFiles(argv, argc);
	generateClassProbability();
	std::string input = argv[2];
	std::string stopWords = argv[3];
	classifyFile(input, stopWords);
	std::string outputFile = "../outputs/clasificacion_alu0100819786.csv";
	std::string resume = "../outputs/resumen_alu0100819786.csv";
	storeFile(outputFile, resume);
}

/**
 * @brief      Destruye el objeto.
 */
Classifier::~Classifier (void) {
}

/**
 * @brief      Consigue el fichero de entrada.
 *
 * @return     EL fichero de entrada.
 */
std::vector<std::string> Classifier::get_InputFiles (void) const {
	return inputFiles_;
}

/**
 * @brief      Consigue los datos de aprendizaje.
 *
 * @return     Los datos de aprendizaje.
 */
std::vector<Vocabulary> Classifier::get_Class (void) const {
	return class_;
}

/**
 * @brief      Consigue los datos.
 *
 * @return     Los datos.
 */
std::string Classifier::get_Data (void) const {
	return data_;
}

/**
 * @brief      Establece el fichero de entrada.
 *
 * @param[in]  newInputFiles  El fichero de entrada.
 */
void Classifier::set_InputFiles (std::vector<std::string> newInputFiles) {
	inputFiles_ = newInputFiles;
}

/**
 * @brief      Establece los datos de aprendizaje.
 *
 * @param[in]  newClass  Los datos de aprendizaje.
 */
void Classifier::set_Class (std::vector<Vocabulary> newClass) {
	class_ = newClass;
}

/**
 * @brief      Establece los datos.
 *
 * @param[in]  newData  Los datos.
 */
void Classifier::set_Data (std::string newData) {
	data_ = newData;
}

/**
 * @brief      Preprocesa, calcula la probabilidad y clasifica el fichero de entrada.
 *
 * @param      inputFile      El fichero con del Corpus de Test.
 * @param      stopWordsFile  El fichero con las stopWords.
 */
void Classifier::classifyFile (std::string& inputFile, std::string& stopWordsFile) {
	Vocabulary voc;
	std::vector<std::string> stopWord;
	stopWord = voc.loadStopWord(stopWordsFile);
	std::string tmp;
	preProcess(stopWord, inputFile);
	std::string helper = "../outputs/preProcesserHelper.txt";
	std::ifstream file(helper, std::ios::in);
	std::ifstream originalFile(inputFile, std::ios::in);
	Chrono myChrono;
	myChrono.startChrono();
	if (file.fail() || originalFile.fail()) {
		std::cout << std::endl << "Error 404, preProcesserHelper.txt file not found in /outputs." << std::endl;
		exit(1);
	}
	std::string originalReader = "";
	while (!file.eof()) {
		std::vector<std::string> sentence; 
		std::string tmp = "";
		while (!file.eof()) {
			file >> tmp;
			if (tmp == "preprocesserendl") {
				break;
			}
			sentence.push_back(tmp);
		}
		std::getline(originalFile, originalReader);
		if (originalReader[originalReader.length() -1] == '\r') {
			originalReader[originalReader.length() -1] = ' ';
		}
		data_ += originalReader;
		classify(sentence);
	}
	file.close();
	originalFile.close();
	myChrono.stopChrono();
	std::cout << std::endl << "Elapsed Classifying time: " << myChrono.get_Seconds(5) << " seconds." << std::endl;
}

/**
 * @brief      Clasifica un tweet.
 *
 * @param[in]  sentence  El tweet que va a ser clasificado.
 */
void Classifier::classify (std::vector<std::string> sentence) {
	std::vector<float> prob;
	prob.resize(inputFiles_.size());
	for (unsigned i = 0; i < prob.size(); i++) {
		prob[i] = 0.0;
	}
	std::set<Token>::iterator it;
	for (unsigned i = 0; i < sentence.size(); i++) {
		it = learnedData_.find(sentence[i]);
		for (unsigned j = 0; j < prob.size(); j++) {
			prob[j] += it -> get_MultiClass(j);
		}
	}
	data_ += ", ";
	unsigned selection = 0;
	for (unsigned i = 0; i < prob.size(); i++) {
		prob[i] += class_[i].get_ClassProbability();
		if (prob[selection] < prob[i]) {
			selection = i;
		}
		data_ += std::to_string(prob[i]);
		data_ += ", ";
	}
	resume_.push_back(class_[selection].get_Type());
	data_ += class_[selection].get_Type();
	data_ += ".\r";
}

/**
 * @brief      Genera y añade la probabilidad de clase de cada clase.
 */
void Classifier::generateClassProbability (void) {
	int totalLines = 0;
	for (unsigned i = 0; i < class_.size(); i++) {
		totalLines += class_[i].get_NLines();
	}
	for (unsigned i = 0; i < class_.size(); i++) {
		class_[i].addClassProbability(totalLines);
	}
}

/**
 * @brief      Preprocesa un determinado Tweet.
 *
 * @param      preprocesser  El preProcesser.
 * @param      stopWords     Las stopWords.
 * @param      sentence      El tweet.
 */
void Classifier::preProcess (std::vector<std::string>& stopWords, std::string& fileName) {
	PreProcesser preprocesser;
	std::string helper = "../outputs/preProcesserHelper.txt";
	preprocesser.loadTestData(fileName);
	preprocesser.convertLowerCase();
	preprocesser.erasePunctuationSigns();
	preprocesser.eraseAllNumbers();
	preprocesser.storeData(helper, 0);
	preprocesser.eraseReservedWords(stopWords, helper);
}

/**
 * @brief      Lee los datos de aprendizaje y los guarda.
 *
 * @param      argv  El array de argumentos.
 * @param      argc  La cantidad de argumentos.
 */
void Classifier::readInputFiles (char* argv[], int& argc) {
	std::vector<Token> tmpVector;
	for (int k = 4; k < argc; k++) {
		std::string fileName = argv[k];
		inputFiles_.push_back(fileName);
		std::string type = "";
		type += fileName[fileName.length() - 5];
		std::ifstream file(fileName, std::ios::in);
		if (file.fail()) {
			std::cout << std::endl << "Error 404," << fileName << " file not found." << std::endl;
			exit(1);
		}
		else if (k == 4) {
			std::string reader = "";
			file >> reader >> reader >> reader >> reader >> reader >> reader;
			Vocabulary newVoc;
			newVoc.set_NLines(std::stoi(reader));
			newVoc.set_Type(type);
			class_.push_back(newVoc);
			std::getline(file, reader);
			while (!file.eof()) {
				file >> reader >> reader;
				Token newToken(reader);
				file >> reader >> reader >> reader >> reader;
				newToken.addClassProb(std::stof(reader), type);
				newToken.set_Type(type);
				tmpVector.push_back(newToken);
			}
		}
		else {
			int i = 0;
			std::string reader = "";
			file >> reader >> reader >> reader >> reader >> reader >> reader;
			Vocabulary newVoc;
			newVoc.set_NLines(std::stoi(reader));
			newVoc.set_Type(type);
			class_.push_back(newVoc);
			std::getline(file, reader);
			while (!file.eof()) {
				file >> reader >> reader >> reader >> reader >> reader >> reader;
				tmpVector[i].addClassProb(std::stof(reader), type);
				i++;
			}
		}
		file.close();
	}
	for (unsigned i = 0; i < tmpVector.size(); i++) {
		learnedData_.insert(tmpVector[i]);
	}
}

/**
 * @brief      Guarda los datos en los ficheros de salida finales.
 *
 * @param      outputFile  El fichero de salida.
 * @param      resumeFile  El fichero de resume.
 */
void Classifier::storeFile (std::string& outputFile, std::string& resumeFile) {
	std::fstream file(outputFile, std::ios::out | std::ios::trunc);
	if (file.fail()) {
		std::cout << "Error while storing data \"" << outputFile << "\" is not valid document." << std::endl;
		exit(1);
	} 
	else { 
		bool isDecimal = false;
		for (unsigned i = 0; i < data_.length(); i++) {
			
			if (isDecimal && std::isdigit(data_[i]) && std::isdigit(data_[i - 2])) {
				if (data_[i] != ',') {
					file << data_[i];
					i++;
				}
				if (data_[i] != ',') {
					file << data_[i];
					i++;
				}
				while (data_[i] != ',' && data_[i] != '.') {
					i++;
				}
				file << data_[i];
				isDecimal = false;
			}
			else {
				isDecimal = false;
				file << data_[i];
				if (data_[i] == '.') {
					isDecimal = true;
				}
			}
		}
	}
	file.close();
	std::fstream resume(resumeFile, std::ios::out | std::ios::trunc);
	if (resume.fail()) {
		std::cout << "Error while storing data \"" << resumeFile << "\" is not valid document." << std::endl;
		exit(1);
	} 
	else {
		resume << "codigo: " << std::endl;
		for (unsigned i = 0; i < resume_.size(); i++) {
			resume << resume_[i] << std::endl;
		}
		resume.close();
	}
}
