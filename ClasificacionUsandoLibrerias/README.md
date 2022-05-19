Para instalar el autokeras:
    1-  Para comprobar si esta instalado:
            python3 --version
            pip3 --version
        Si no:
            sudo apt update
            sudo apt install python3-dev python3-pip python3-venv
    
    2- Instala tensorflow y comprobar que funciona:
        pip install --upgrade tensorflow
        python -c "import tensorflow as tf;print(tf.reduce_sum(tf.random.normal([1000, 1000])))"
        Si funciona debe devolver un tensor
    
    3- Instalar autokeras
        python3 -m pip install git+https://github.com/keras-team/keras-tuner.git
        python3 -m pip install autokeras

        o

        !pip install autokeras

    4- SKLEARN
        
        pip3 install -U scikit-learn scipy matplotlib

To run: python3 -W ignore text_classifier.py