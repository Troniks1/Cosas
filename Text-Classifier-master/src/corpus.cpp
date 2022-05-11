/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     corpus.cpp                                         =
	=            Author:        Gabriel Melián Hernández		                   =
	=																			   =
=========================================================================================
=======================================================================================*/

/*------------------  DECLARACION DE FUNCIONES -----------------*/

#include "../include/corpus.hpp"

/*------------------------------------------------*/

/**
 * @brief      Construye una nueva instancia.
 */
Corpus::Corpus (void) {
	set_Name("");
	set_OutputFileName("");
	set_InputFile("");
}

/**
 * @brief      Construye una nueva instancia.
 *
 * @param[in]  name       El nombre.
 * @param[in]  inputFile  El fichero de entrada.
 */
Corpus::Corpus (std::string name, std::string inputFile) {
	set_Name(name);
	set_OutputFileName("../outputs/corpus_" + name + ".txt");
	set_InputFile(inputFile);
}

/**
 * @brief      Destruye el objeto.
 */
Corpus::~Corpus (void) {
}

/**
 * @brief      Consigue el nombre.
 *
 * @return     El nombre.
 */
std::string Corpus::get_Name (void) const {
	return name_;
}

/**
 * @brief      Consigue el nombre del fichero de salida.
 *
 * @return     El nombre del fichero de salida.
 */
std::string Corpus::get_OutputFileName (void) const {
	return outputFileName_;
}

/**
 * @brief      COnsigue el fichero de entrada.
 *
 * @return     El fichero de entrada.
 */
std::string Corpus::get_InputFile (void) const {
	return inputFile_;
}

/**
 * @brief      Establece el nombre.
 *
 * @param[in]  newName  El nombre.
 */
void Corpus::set_Name (std::string newName) {
	name_ = newName;
}

/**
 * @brief      Establece el nombre del fichero de salida.
 *
 * @param[in]  newOutputFileName  El nombre del fichero de salida.
 */
void Corpus::set_OutputFileName (std::string newOutputFileName) {
	outputFileName_ = newOutputFileName;
}

/**
 * @brief      Establece el nombre del fichero de entrada.
 *
 * @param[in]  newInputFile  El nombre del fichero de entrada.
 */
void Corpus::set_InputFile (std::string newInputFile) {
	inputFile_ = newInputFile;
}

/**
 * @brief      Genera y almacena los datos del corpus.
 *
 * @param      stopWords     Las StopWords.
 * @param[in]  preProcesser  El preprocesado.
 */
void Corpus::generateCorpus (std::vector<std::string>& stopWords, PreProcesser& preProcesser) {
	Chrono myChrono;
	int dataLines;
	myChrono.startChrono();
	std::string outputFile = "../outputs/preProcesserHelper.txt";
	std::string dataType = get_Name() + ",";
	dataLines = preProcesser.loadData(inputFile_, dataType);
	preProcesser.convertLowerCase();
	preProcesser.erasePunctuationSigns();
	preProcesser.eraseAllNumbers();
	preProcesser.storeData(outputFile, 0);
	preProcesser.eraseReservedWords(stopWords, outputFile);
	preProcesser.storeData(outputFileName_, dataLines);
	myChrono.stopChrono();
	std::cout << std::endl << "Elapsed time for corpus " << name_ << ": " << myChrono.get_Seconds(5) << " seconds." << std::endl;
}


