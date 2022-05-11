/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     token.cpp                                          =
	=            Author:        Gabriel Melián Hernández		                   =
	=																			   =
=========================================================================================
=======================================================================================*/
/*------------------  FUNCTIONS  -----------------*/

#include "../include/token.hpp"

/*------------------------------------------------*/

/**
 * @brief      Construye una nueva instancia.
 */
Token::Token (void) {
	set_Name("");
	set_Ammount(0);
	set_Probability(0);
	set_Type("");
}

/**
 * @brief      Construye una nueva instancia.
 *
 * @param[in]  name  El nombre.
 */
Token::Token (std::string name) {
	set_Name(name);
	set_Ammount(1);
	set_Probability(-9999999999999.99);
	set_Type("");
}

/**
 * @brief      Destruye el objeto.
 */
Token::~Token (void) {
}

/**
 * @brief      Consigue el nombre.
 *
 * @return     El nombre.
 */
std::string Token::get_Name(void) const {
	return name_;
}

/**
 * @brief      Consigue la cantidad.
 *
 * @return     La cantidad.
 */
unsigned Token::get_Ammount (void) const {
	return ammount_;
}

/**
 * @brief      Consigue la probabilidad.
 *
 * @return     La Probabilidad.
 */
float Token::get_Probability (void) const {
	return probability_;
}

/**
 * @brief      COnsigue la multi clase.
 *
 * @param[in]  pos   La posición.
 *
 * @return     La multi clase.
 */
float Token::get_MultiClass (unsigned pos) const {
	if (pos < multiClass_.size()) 
		return multiClass_[pos];
	else {
		std::cout << std::endl << "Error, pos must be lower than multiClass_ size." << std::endl;
		exit(1);
	}
}

/**
 * @brief      Consigue la multiclase.
 *
 * @return     La multiclase.
 */
std::vector<float> Token::get_MultiClass (void) const {
	return multiClass_;
}

/**
 * @brief      Consigue el tipo.
 *
 * @return     El tipo.
 */
std::string Token::get_Type (void) const {
	return type_;
}

/**
 * @brief      Establece el nombre.
 *
 * @param[in]  name  El nombre.
 */
void Token::set_Name (std::string name) {
	name_ = name;
}

/**
 * @brief      Establece la cantidad.
 *
 * @param[in]  ammount  La cantidad.
 */
void Token::set_Ammount (unsigned ammount) {
	ammount_ = ammount;
}

/**
 * @brief      Establece la probabilidad.
 *
 * @param[in]  newProbability  La nueva probabilidad.
 */
void Token::set_Probability (float newProbability) {
	probability_ = newProbability;
}

/**
 * @brief      Establece la multiclase.
 *
 * @param[in]  newMultiClass  La multiclase.
 */
void Token::set_MultiClass (std::vector<float> newMultiClass) {
	multiClass_ = newMultiClass;
}

/**
 * @brief      Establece el tipo.
 *
 * @param[in]  newType  El tipo.
 */
void Token::set_Type (std::string newType) {
	type_ = newType;
}

/**
 * @brief      Operador <.
 *
 * @param[in]  otherToken  El otro token.
 *
 * @return     El resultado de la comparación.
 */
bool Token::operator< (const Token& otherToken) const {
	return (get_Name() < otherToken.get_Name());
}

/**
 * @brief      Operador <=.
 *
 * @param[in]  otherToken  El otro token.
 *
 * @return     El resultado de la comparación.
 */
bool Token::operator<= (const Token& otherToken) const {
	return (get_Name() <= otherToken.get_Name());
}

/**
 * @brief      Operador <.
 *
 * @param[in]  otherToken  El otro token.
 *
 * @return     El resultado de la comparación.
 */
bool Token::operator< (const std::string& str) const {
	return (get_Name() < str);
}

/**
 * @brief      Operador <=.
 *
 * @param[in]  otherToken  El otro token.
 *
 * @return     El resultado de la comparación.
 */
bool Token::operator<= (const std::string& str) const {
	return (get_Name() <= str);
}

/**
 * @brief      Operador >.
 *
 * @param[in]  otherToken  El otro token.
 *
 * @return     El resultado de la comparación.
 */
bool Token::operator> (const Token& otherToken) const {
	return (get_Name() > otherToken.get_Name());
}

/**
 * @brief      Operador >=.
 *
 * @param[in]  otherToken  El otro token.
 *
 * @return     El resultado de la comparación.
 */
bool Token::operator>= (const Token& otherToken) const {
	return (get_Name() >= otherToken.get_Name());
}

/**
 * @brief      Operador >.
 *
 * @param[in]  otherToken  El otro token.
 *
 * @return     El resultado de la comparación.
 */
bool Token::operator> (const std::string& str) const {
	return (get_Name() > str);
}

/**
 * @brief      Operador >=.
 *
 * @param[in]  otherToken  El otro token.
 *
 * @return     El resultado de la comparación.
 */
bool Token::operator>= (const std::string& str) const {
	return (get_Name() >= str);
}

/**
 * @brief      Operador ==.
 *
 * @param[in]  otherToken  El otro token.
 *
 * @return     El resultado de la comparación.
 */
bool Token::operator== (const Token& otherToken) const {
	return (get_Name() == otherToken.get_Name());
}

/**
 * @brief      Operador ==.
 *
 * @param[in]  otherToken  El otro token.
 *
 * @return     El resultado de la comparación.
 */
bool Token::operator== (const std::string& str) const {
	return (get_Name() == str);
}

/**
 * @brief      Operador ++.
 *
 * @return     El resultado del incremento.
 */
Token& Token::operator++ (void) {
	this -> set_Ammount(get_Ammount() + 1);
	return *this;
}

/**
 * @brief      Operador =.
 *
 * @param[in]  otherToken  El otro token.
 *
 * @return     El resultado de la asignación.
 */
Token& Token::operator= (const Token& otherToken) {
	this -> set_Name(otherToken.get_Name());
	this -> set_Ammount(otherToken.get_Ammount());
	this -> set_Probability(otherToken.get_Probability());
	this -> set_Type(otherToken.get_Type());
	this -> set_MultiClass(otherToken.get_MultiClass());
	return *this;
}

/**
 * @brief      Incrementa la cantidad en 1.
 */
void Token::incrementate (void) {
	ammount_++;
}

/**
 * @brief      Añade la probablidad de clase.
 *
 * @param[in]  prob      La probabilidad.
 * @param[in]  newClass  La clase.
 */
void Token::addClassProb (float prob, std::string newClass) {
	multiClass_.push_back(prob);
	if (prob > probability_) {
		probability_ = prob;
		type_ = newClass;
	}
}

/**
 * @brief      Genera la probabilidad de un token.
 *
 * @param[in]  vocSize       Tamaño del vocabulario.
 * @param[in]  tokenAmmount  Cantidad de veces que aparece un token
 *
 * @return     El Log de la probabilidad.
 */
float Token::generateLogProb (const unsigned& vocSize, const unsigned& tokenAmmount) {
	probability_ = (ammount_ + 1);
	int divider = (vocSize + tokenAmmount);
	probability_ /= divider;
	return std::log(probability_);
}

/**
 * @brief      Escribe un token.
 */
void Token::printToken (void) const {
	std::cout << std::endl << "Token Info:" << std::endl << "\t - Name: " << get_Name() << std::endl << "\t - Ammount: " << get_Ammount() << std::endl << "\t - Type: " << get_Type() << std::endl << "\t - Prob: " << get_Probability();
}
