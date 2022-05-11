/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     token.hpp                                          =
	=            Author:        Gabriel Melián Hernández		                   =
	=																			   =
=========================================================================================
=======================================================================================*/
/*------------------  FUNCIONES  -----------------*/

#pragma once

/*------------------------------------------------*/
/*------------------  LIBRERÍAS  -----------------*/

#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

/*------------------------------------------------*/

/**
 * @brief      Esta clase describe un token.
 */
class Token {

	private:
		// Atributos
		std::string name_;				// El nombre del token.
		unsigned ammount_;				// La cantidad de veces que aparece el token en el corpus.
		float probability_;				// La probabilidad.
		std::string type_; 				// El tipo del token en las clases especificadas.
		std::vector<float> multiClass_;	// La probabilidad del vector para la clasificación.

	public:
		// Constructores y Destructor.
		Token (void);
		Token (std::string name);
		~Token (void);

		// Setters y Getters.
		std::string get_Name(void) const;
		unsigned get_Ammount (void) const;
		float get_Probability (void) const;
		float get_MultiClass (unsigned pos) const;
		std::vector<float> get_MultiClass (void) const;
		std::string get_Type (void) const;

		void set_Name (std::string name);
		void set_Ammount (unsigned ammount);
		void set_Probability (float newProbability);
		void set_MultiClass (std::vector<float> newMultiClass);
		void set_Type (std::string newType);

		// Sobrecarga de Operadores
		bool operator< (const Token& otherToken) const;
		bool operator<= (const Token& otherToken) const;
		bool operator< (const std::string& str) const;
		bool operator<= (const std::string& str) const;
		bool operator> (const Token& otherToken) const;
		bool operator>= (const Token& otherToken) const;
		bool operator> (const std::string& str) const;
		bool operator>= (const std::string& str) const;
		bool operator== (const Token& otherToken) const;
		bool operator== (const std::string& str) const;
		Token& operator++ (void);
		Token& operator= (const Token& otherToken);

		// Funciones.
		void incrementate (void);
		void addClassProb (float prob, std::string newClass);
		float generateLogProb (const unsigned& vocSize, const unsigned& tokenAmmount);

		// Escritura.
		void printToken (void) const;
};