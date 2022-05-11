/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     learner.hpp                                        =
	=            Author:        Gabriel Melián Hernández		                   =
	=																			   =
=========================================================================================
=======================================================================================*/
/*------------  DECLARACIÓN DE FUNCIONES  ------------*/

#pragma once
#include "corpus.hpp"
#include "token.hpp"

/*------------------------------------------------*/
/*------------------  LIBRERÍAS  -----------------*/

#include <cstring>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>

/*------------------------------------------------*/

/**
 * @brief      Esta clase describe un learner.
 */
class Learner {

	private:
		// Atributos.
		std::vector<Vocabulary> learners_;			// El learner para cada tipo de dato.
		std::vector<std::string> inputCorpusFiles_;	// El fichero de entrada del corpus.
		std::string vocabularyFile_;				// El fichero del vocabulario.

	public:
		// Constructores y Destructor
		Learner (void);
		Learner (char* argv[], int& argc);
		~Learner (void);

		// Setters y Getters
		std::vector<Vocabulary> get_Learners (void) const;
		std::vector<std::string> get_InputCorpusFiles (void) const;
		std::string get_VocabularyFile (void) const;

		void set_Learners (std::vector<Vocabulary> newLearners);
		void set_InputCorpusFiles (std::vector<std::string> newInputCorpusFiles);
		void set_VocabularyFile (std::string newVocabularyFile);

		// Funciones.
		void learnAndStoreData (void);

};