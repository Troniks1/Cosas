/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     corpus.hpp                                         =
	=            Author:        Gabriel Melián Hernández		                   =
	=																			   =
=========================================================================================
=======================================================================================*/
/*------------  DECLARACIÓN DE FUNCIONES  ------------*/

#pragma once
#include "vocabulary.hpp"
#include "Chrono.hpp"

/*------------------------------------------------*/
/*------------------  LIBRERÍAS  -----------------*/

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <algorithm>

/*------------------------------------------------*/

/**
 * @brief      Esta clase describe un corpus.
 */
class Corpus {

	private:
		// Atributos
		std::string name_;				// El nombre del corpus o tipo de dato
		std::string outputFileName_;	// El nombre del fichero de salida.
		std::string inputFile_;			// El nombre del fichero de entrada.

	public:
		// Constructores y Destructor
		Corpus (void);
		Corpus (std::string name, std::string inputFile);
		~Corpus (void);

		// Setters y Getters
		std::string get_Name (void) const;
		std::string get_OutputFileName (void) const;
		std::string get_InputFile (void) const;

		void set_Name (std::string newName);
		void set_OutputFileName (std::string newOutputFileName);
		void set_InputFile (std::string newInputFile);

		// Funciones
		void generateCorpus (std::vector<std::string>& stopWords, PreProcesser& preProcesser);

};