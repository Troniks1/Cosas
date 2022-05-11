/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     preProcesser.hpp                                   =
	=            Author:        Gabriel Melián Hernández		                   =
	=																			   =
=========================================================================================
=======================================================================================*/
/*------------------  FUNCIONES  -----------------*/

#pragma once

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
 * @brief      Esta clase describe un pre procesador para llevar a cabo dichas tareas
 *             en el fichero de entrada, antes de usarlo.
 */
class PreProcesser {

	private:
		// Atributos.
		std::string inputFile_;						// Fichero de entrada
		std::string outputFile_;					// Fichero de salida donde se guarda el preProceso.
		std::string data_;							// datos leidos del fichero de entrada.

	public:
		// Constructores & Destructor.
		PreProcesser (void);
		PreProcesser (std::string inputFile, std::string outpuFile);
		~PreProcesser (void);

		// Getters & Setters
		std::string get_InputFile (void) const;
		std::string get_OutputFile (void) const;
		std::string get_Data (void) const;

		void set_InputFile (std::string newInputFile);
		void set_OutputFile (std::string newOutputFile);
		void set_Data (std::string newData);

		// Sobrecarga de Operadores.
		PreProcesser& operator= (const PreProcesser& newPreProcesser);

		// Funciones.
		void convertLowerCase (std::string& str);
		void convertLowerCase (void);
		void convertUpperCase (std::string& str);
		void convertUpperCase (void);
		void eraseReservedWords (std::vector<std::string>& reservedWords, std::string& fileName);
		std::string eraseReservedWords (std::string& sentence, std::vector<std::string>& reservedWords);
		void erasePunctuationSigns (std::string& str);
		void erasePunctuationSigns (void);
		void eraseURLs (std::string& str);
		void eraseURLs (void);
		void eraseHashtags (std::string& str);
		void eraseHashtags (void);
		void eraseNumbers (std::string& str);
		void eraseNumbers (void);
		void eraseAllNumbers (void);
		void eraseAllNumbers (std::string& str);

		// Lectura & Escritura.
		int loadData (std::string& inputFile, std::string dataType);
		void loadTestData (std::string& inputFile);
		void printData (void);
		void storeData(std::string& outputFile, int dataLines);

};