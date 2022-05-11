/*=======================================================================================
=========================================================================================
	=                                                                              =
	=            Proyect:       Text Classifier                                    =
	=            File name:     Chrono.cpp                                         =
	=            Author:        Gabriel Melián Hernández		                   =
	=																			   =
=========================================================================================
=======================================================================================*/
/*------------  DECLARACIÓN DE FUNCIONES  ------------*/

#include "../include/Chrono.hpp"

/*-------------------------------------------------*/


/**
 * @brief      Construye un nuevo chrono.
 */
Chrono::Chrono () {
}

/**
 * @brief      Destruye el chrono.
 */
Chrono::~Chrono () {
}

/**
 * @brief      Consigue el start del reloj.
 *
 * @return     El start del reloj.
 */
std::chrono::time_point<std::chrono::system_clock> Chrono::get_StartClock (void) const {
	return startClock_;
}

/**
 * @brief      Consigue el final del reloj.
 *
 * @return     El final del reloj.
 */
std::chrono::time_point<std::chrono::system_clock> Chrono::get_EndClock (void) const {
	return endClock_;
}

/**
 * @brief      Consigue el tiempo total.
 *
 * @return     El tiempo total.
 */
int Chrono::get_TotalTime (void) const {
	return totalTime_;
}

/**
 * @brief      Consigue el tiempo inicial.
 *
 * @return     El tiempo inicial.
 */
std::string Chrono::get_StartTime (void) const {
	return ctime(&startTime_);

}

/**
 * @brief      Cosnigue el tiempo final.
 *
 * @return     El tiempo final.
 */
std::string Chrono::get_EndTime (void) const {
	return ctime(&endTime_);
}

/**
 * @brief      Establece el tiempo inicial.
 *
 * @param[in]  startClock  El tiempo inicial.
 */
void Chrono::set_StartClock (std::chrono::time_point<std::chrono::system_clock> startClock) {
	startClock_ = startClock;
}

/**
 * @brief      Establece el tiempo final.
 *
 * @param[in]  endClock  El tiempo final
 */
void Chrono::set_EndClock (std::chrono::time_point<std::chrono::system_clock> endClock) {
	endClock_ = endClock;
}

/**
 * @brief      Establece el tiempo total.
 *
 * @param[in]  totalTime  El tiempo total.
 */
void Chrono::set_TotalTime (int totalTime) {
	totalTime_ = totalTime;
}

/**
 * @brief      Establece el tiempo inicial.
 */
void Chrono::set_StartTime (void) {
    startTime_ = time(NULL);
}

/**
 * @brief      Establece el tiempo final.
 */
void Chrono::set_EndTime (void) {
	endTime_ = time(NULL);
}

/**
 * @brief      Reinicia el reloj.
 */
void Chrono::restartChrono (void) {
	set_TotalTime(0);
}

/**
 * @brief      Incia el chrono.
 */
void Chrono::startChrono (void) {
	restartChrono();
	set_StartTime();
	startClock_ = std::chrono::system_clock::now();
}

/**
 * @brief      Para el chrono.
 */
void Chrono::stopChrono (void) {
	set_EndTime();
	endClock_ = std::chrono::system_clock::now();
	totalTime_ += std::chrono::duration_cast<std::chrono::microseconds>(endClock_ - startClock_).count();
}

/**
 * @brief      Pausa el chrono.
 */
void Chrono::pauseChrono (void) {
	stopChrono();
	totalTime_ += std::chrono::duration_cast<std::chrono::microseconds>(endClock_ - startClock_).count();
}

/**
 * @brief      Vuelve a poner en marcha el reloj.
 */
void Chrono::resumeChrono (void) {
	startClock_ = std::chrono::system_clock::now();
}

/**
 * @brief      Consigue el tiempo en segundos.
 *
 * @return     Los segundos.
 */
float Chrono::get_Seconds (void) {
	float time = totalTime_ / 1000000;
	return time;
}

/**
 * @brief      Consigue el tiempo en segundos con decimales.
 *
 * @param[in]  decimalAmmount  La cantidad de decimales.
 *
 * @return     Los segundos.
 */
float Chrono::get_Seconds (int decimalAmmount) {
	float time = totalTime_;
	time /= 1000000;
	std::string aux = std::to_string(time);
	std::string copy = "";
	int counter = 0;
	bool decimals = false;
	for (unsigned i = 0; i < aux.size(); i++) {
		if (aux[i] == '.') {
			decimals = true;
			copy[i] = aux[i];
		}
		else if (counter < decimalAmmount) {
			if (decimals == true) {
				counter++;
			}
			copy[i] = aux[i];
		}
		else {
			break;
		}
	}	
	time = stof(copy);
	return time;
}

/**
 * @brief      Consigue el tiempo en milisegundos.
 *
 * @return     Los milisegundos.
 */
float Chrono::get_MilliSeconds (void) {
	float time = totalTime_ / 1000;
	return time;
}

/**
 * @brief      Consigue el tiempo el milisegundos con decimales.
 *
 * @param[in]  decimalAmmount  La cantidad de decimales.
 *
 * @return     Los milisegundos.
 */
float Chrono::get_MilliSeconds (int decimalAmmount) {
	float time = totalTime_;
	time /= 1000;
	std::string aux = std::to_string(time);
	std::string copy = "";
	int counter = 0;
	bool decimals = false;
	for (unsigned i = 0; i < aux.size(); i++) {
		if (aux[i] == '.') {
			decimals = true;
			copy[i] = aux[i];
		}
		else if (counter < decimalAmmount) {
			if (decimals == true) {
				counter++;
			}
			copy[i] = aux[i];
		}
		else {
			break;
		}
	}	
	time = stof(copy);
	return time;
}

/**
 * @brief      Consigue el tiempo en microsegundos.
 *
 * @return     Los microsegundos.
 */
float Chrono::get_MicroSeconds (void) {
	return totalTime_;
}
