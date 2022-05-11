/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     vocabulary.hpp                                     =
	=            Author:        Gabriel Melián Hernández		                   =
	=																			   =
=========================================================================================
=======================================================================================*/
/*------------------  DECLARACIÓN DE FUNCIONES  -----------------*/

#pragma once
#include "preProcesser.hpp"
#include "Chrono.hpp"
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
 * @brief      Esta clase describe un vocabulario. 
 */
class Vocabulary {

	private:
		// Atributos.
		std::string inputFile_;			// Fichero de entrada.
		std::string outpuFile_;			// Fichero de salida donde será guardado el vocabulario.
		int vocabularyCounter_;			// Numero de diferentes palabras en el vocabulario.
		int nTokens_;					// Número de palabras en el texto.
		int nLines_;					// Numero de líneas leído
		std::set<Token> vocabulary_;	// Set con todo el vocabulario.
		std::string type_;				// El tipo del vocabulario.
		float classProbability_;		// La probabilidad de clase

	public:
		// Constructores y Destructor.
		Vocabulary (void);
		Vocabulary (std::string inputFile, std::string outpuFile);
		~Vocabulary (void);

		// Getters & Setters
		std::string get_InputFile (void) const;
		std::string get_OutpuFile (void) const;
		int get_VocabularyCounter (void) const;
		int get_NTokens (void) const;
		int get_NLines (void) const;
		std::set<Token> get_Vocabulary (void) const;
		std::string get_Type (void) const;
		float get_ClassProbability (void) const;

		void set_InputFile (std::string newInputFile);
		void set_OutpuFile (std::string newOutpuFile);
		void set_VocabularyCounter (int newVocabularyCounter);
		void set_NTokens (int newNTokens);
		void set_NLines (int newNLines);
		void set_Vocabulary (std::set<Token> newVocabulary);
		void set_Type (std::string newType);
		void set_ClassProbability (float newClassProbability);

		// Sobrecarga de Operadores.
		Vocabulary& operator= (const Vocabulary& newVocabulary);

		// Funciones.
		void preProcessData (std::string& stopWordFile);
		std::vector<std::string> loadStopWord (std::string& inputFile);
		void generateVocabulary (std::string& inputFile, bool tokenized);
		void calculateProbabilities (void);
		void addClassProbability (int size);

		// Escritura.
		void readVocabulary (std::string& inputFile);
		void storeVocabulary (std::string& outputFile);
		void readLearnedData (std::string& inputFile);
};