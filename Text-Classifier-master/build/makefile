# Variables
TIME =$(LOGPATH)$(shell date)
# Object Vars
OBJECTS = main.o vocabulary.o preProcesser.o Chrono.o token.o corpus.o learner.o classifier.o
# Compilation flags
CFLAGS = -c -std=c++17 -Wall

textClassifier: $(OBJECTS)
	g++ $(OBJECTS) -o textClassifier
	mv textClassifier ../bin

main.o: ../src/main.cpp
	g++ $(CFLAGS) ../src/main.cpp

vocabulary.o: ../src/vocabulary.cpp ../include/vocabulary.hpp
	g++ $(CFLAGS) ../src/vocabulary.cpp

preProcesser.o: ../src/preProcesser.cpp ../include/preProcesser.hpp
	g++ $(CFLAGS) ../src/preProcesser.cpp

Chrono.o: ../src/Chrono.cpp ../include/Chrono.hpp
	g++ $(CFLAGS) ../src/Chrono.cpp

token.o: ../src/token.cpp ../include/token.hpp
	g++ $(CFLAGS) ../src/token.cpp

corpus.o: ../src/corpus.cpp ../include/corpus.hpp
	g++ $(CFLAGS) ../src/corpus.cpp

learner.o: ../src/learner.cpp ../include/learner.hpp
	g++ $(CFLAGS) ../src/learner.cpp

classifier.o: ../src/classifier.cpp ../include/classifier.hpp
	g++ $(CFLAGS) ../src/classifier.cpp



.PHONY: clean
clean:
	rm -rf ../build/*.o
	rm -rf ../bin/*

help:
	../bin/textClassifier --help

fullRun:
	make clean
	make
	make runVocabulary
	make runCorpus
	make runLearner
	make runClassifier
	make runTestPercentage

runTestPercentage:
	../bin/textClassifier --error ../outputs/resumen_alu0100819786.csv ../inputs/resumeExpected.csv

runClassifier:
	../bin/textClassifier --classify ../inputs/COV-test.csv ../inputs/stopWords.txt ../outputs/aprendizajeN.txt ../outputs/aprendizajeP.txt

runLearner:
	../bin/textClassifier --learner ../outputs/vocabulary.txt Negative Positive

runCorpus:
	../bin/textClassifier --corpus ../inputs/COV_train.csv ../inputs/stopWords.txt Negative Positive

runVocabulary:
	../bin/textClassifier --vocabulary ../inputs/COV_train.csv ../outputs/vocabulary.txt ../inputs/stopWords.txt