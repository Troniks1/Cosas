/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     classifier.hpp                                     =
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
 * @brief      Esta clase describe al clasificador.
 */
class Classifier {

	private:
		// Atributos.
		std::vector<std::string> inputFiles_;	// Vector de fichero de entrada.
		std::vector<Vocabulary> class_;			// Vector de la Clase/Vocabulario.
		std::string data_;						// Aqui almacenaremos los datos de salida.
		std::set<Token> learnedData_;			// Diccionario con todo el aprendizaje.
		std::vector<std::string> resume_;		// Vector donde será almacenado el resume.

	public:
		// Cnstructores y Destrcutor.
		Classifier (void);
		Classifier (char* argv[], int& argc);
		~Classifier (void);

		// Setters y Getters.
		std::vector<std::string> get_InputFiles (void) const;
		std::vector<Vocabulary> get_Class (void) const;
		std::string get_Data (void) const;

		void set_InputFiles (std::vector<std::string> newInputFiles);
		void set_Class (std::vector<Vocabulary> newClass);
		void set_Data (std::string newData);

		// Funciones.
		void classifyFile (std::string& inputFile, std::string& stopWords);
		void classify (std::vector<std::string> sentence);
		void generateClassProbability (void);
		void preProcess (std::vector<std::string>& stopWords, std::string& sentence);

		// Lectura y Escritura.
		void readInputFiles (char* argv[], int& argc);
		void storeFile (std::string& outputFile, std::string& resumeFile);
};