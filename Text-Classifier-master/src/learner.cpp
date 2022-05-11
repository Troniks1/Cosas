/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     learner.cpp                                        =
	=            Author:        Gabriel Melián Hernández		                   =
	=																			   =
=========================================================================================
=======================================================================================*/
/*------------------  DECLARACIÓN DE FUNCIONES  -----------------*/

#include "../include/learner.hpp"

/*------------------------------------------------*/

/**
 * @brief      Construye una nueva instancia.
 */
Learner::Learner (void) {
	set_VocabularyFile("");
}

/**
 * @brief      Construye una nueva instancia.
 *
 * @param      argv  El array de argumentos.
 * @param      argc  La cantidad de argumentos.
 */
Learner::Learner (char* argv[], int& argc) {
	set_VocabularyFile(argv[2]);
	for (int i = 3; i < argc; i++) {
		Chrono chrono;
		chrono.startChrono();
		std::string tmp = "../outputs/corpus_";
		tmp += argv[i];
		tmp += ".txt";
		Vocabulary newVoc;
		newVoc.readVocabulary(vocabularyFile_);
		newVoc.generateVocabulary(tmp, true);
		learners_.push_back(newVoc);
		inputCorpusFiles_.push_back(argv[i]);
		chrono.stopChrono();
		std::cout << std::endl << "Elapsed generating tokens and vocabulary time: " << chrono.get_Seconds(5) << " seconds for " << argv[i] << " data type." << std::endl;
	}
	learnAndStoreData();
}

/**
 * @brief      Destruye el objeto.
 */
Learner::~Learner (void) {
}

/**
 * @brief      Consigue el aprendizaje.
 *
 * @return     El aprendizaje.
 */
std::vector<Vocabulary> Learner::get_Learners (void) const {
	return learners_;
}

/**
 * @brief      Consigue el fichero de entrada del corpus.
 *
 * @return     El fichero de entrada del corpus.
 */
std::vector<std::string> Learner::get_InputCorpusFiles (void) const {
	return inputCorpusFiles_;
}

/**
 * @brief      Consigue el fichero del vocabulario.
 *
 * @return     El fichero de entrada del vocabulario.
 */
std::string Learner::get_VocabularyFile (void) const {
	return vocabularyFile_;
}

/**
 * @brief      Establece el aprendizaje.
 *
 * @param[in]  newLearners  Los nuevos aprendizajes.
 */
void Learner::set_Learners (std::vector<Vocabulary> newLearners) {
	learners_ = newLearners;
}

/**
 * @brief      Establece el fichero de entrada del corpus.
 *
 * @param[in]  newInputCorpusFiles  El nuevo fichero de entrada del corpus.
 */
void Learner::set_InputCorpusFiles (std::vector<std::string> newInputCorpusFiles) {
	inputCorpusFiles_ = newInputCorpusFiles;
}

/**
 * @brief      Establece el fichero de vocabulario.
 *
 * @param[in]  newVocabularyFile  El nuevo fichero de vocabulario.
 */
void Learner::set_VocabularyFile (std::string newVocabularyFile) {
	vocabularyFile_ = newVocabularyFile;
}

/**
 * @brief      Genera las probabilidades para todos los tokens del vocabulario
 *             y los almacena en un fichero.
 */
void Learner::learnAndStoreData (void) {
	for (unsigned i = 0; i < learners_.size(); i++) {
		Chrono chrono;
		chrono.startChrono();
		std::string fileName = "../outputs/aprendizaje";
		fileName += inputCorpusFiles_[i][0];
		fileName += ".txt";
		std::fstream file(fileName, std::ios::out);
		if (file.fail()) {
			std::cout << "Error while storing learned data \"" << fileName << "\" is not valid document" << std::endl;
			exit(1);
		} 
		else {
			int tokenAmmount = learners_[i].get_NTokens();
			int vocSize = learners_[i].get_VocabularyCounter();
			std::string data = "Numero de documentos del corpus: " + std::to_string(learners_[i].get_NLines());
			data += "\nNumero de palabras del corpus: " + std::to_string(tokenAmmount);
			for (auto tmp : learners_[i].get_Vocabulary()) {
				std::string line =  "\nPalabra: " + tmp.get_Name();
				data += line + " Frec: " + std::to_string(tmp.get_Ammount()) + " LogProb: " + std::to_string(tmp.generateLogProb(vocSize, tokenAmmount));
			}
			file << data;
			file.close();
		}
		chrono.stopChrono();
		std::cout << std::endl << "Elapsed time for calculating probabilities: " << chrono.get_Seconds(5) << " seconds for " << inputCorpusFiles_[i] << " data type." << std::endl;
	}
}
