/**
 * Rete neurale con Arduino
 * Ingressi su A0 e A1
 * 
 * LINK da cui ho recuperato informazioni e codice
 * https://enlight.nyc/projects/neural-network/
 * https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6
 * https://towardsdatascience.com/back-propagation-demystified-in-7-minutes-4294d71a04d7
 * https://towardsdatascience.com/simple-neural-network-implementation-in-c-663f51447547
 */

//nodi d'ingresso
static const int numInputs = 2;
//neuroni hidden layer
static const int numHiddenNodes = 2;
//numero neuroni d'uscita
static const int numOutputs = 1;

//gli array con i valori di uscita e i pesi
float hiddenLayer[numHiddenNodes];
float hiddenLayerBias[numHiddenNodes];
float hiddenWeights[numInputs][numHiddenNodes];
float outputLayer[numOutputs];
float outputLayerBias[numOutputs];
float outputWeights[numHiddenNodes][numOutputs];

//learning rate (per non applicare le correzioni ai pesi, "intere" - darebbe instabilità)
float lr = 0.1;

//cosa vogliamo fare apprendere alla rete?
static const int numTrainingSets = 4;
static const long learning_cycles = 40000;
float training_inputs[numTrainingSets][numInputs] = { 
  {0.0f,0.0f},
  {1.0f,0.0f},
  {0.0f,1.0f},
  {1.0f,1.0f} 
};
float training_outputs[numTrainingSets][numOutputs] = { 
  {0.0f},
  {1.0f},
  {1.0f},
  {0.0f} 
};

//la signoide e la sua derivata
float sigmoid(float x) {
  return (1/(1 + exp(-x)));
}
float dSigmoid(float x) {
  return (x*(1-x));
}

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  
  //init pesi
  initw();
  
  Serial.println("Siate pazienti... ci vuole molto!");  
  //Fase di ISTRUZIONE della RETE
  for (long n = 0; n < learning_cycles; n++) { 
      //sorteggio un set di apprendimento
      int idSet = random(0, 4);
      //lo propago
      propagate(idSet);
      //backpropagation
      learn(idSet);     
  }
  Serial.println("Ready!");
}

void loop() {
  if (digitalRead(2)){
    float a = (float)map(analogRead(A0), 0, 1023, 0, 1000);
    a = a/1000.0;
    float b = (float)map(analogRead(A1), 0, 1023, 0, 1000);
    b = b/1000.0;

    //prendo i training set e modifico il primo per 
    //passargli i valori da elaborare
    training_inputs[0][0] = a;
    training_inputs[0][1] = b;
    
    Serial.print("IN:\t");
    Serial.print(a);
    Serial.print("\t");
    Serial.println(b);    
    
    propagate(0);
    for (int j=0; j<numOutputs; j++) {
      Serial.print("Y = ");
      Serial.println(outputLayer[j]);
      int pwm = outputLayer[j] * 255;
      analogWrite(11, pwm);
    }
    delay(1000);
  }
}

//inizializza i pesi e i bias con numeri casuali (tra 0 e 1)
void initw(){
  randomSeed(analogRead(A3));
  //livello hidden
  for (int j = 0; j < numHiddenNodes; j++) {
    hiddenLayerBias[j] = ((float)random(0,1000))/1000.0;
    for (int k = 0; k < numInputs; k++) {
      hiddenWeights[k][j] = ((float)random(0,1000))/1000.0;
    }
  }
  //livello di uscita
  for (int j = 0; j < numOutputs; j++) {
    outputLayerBias[j] = ((float)random(0,1000))/1000.0;
    for (int k = 0; k < numHiddenNodes; k++) {
      outputWeights[k][j] = ((float)random(0,1000))/1000.0;
    }
  }
}

void propagate(int i){ 
  // scelto il pattern i-esimo, lo propago 
  // Per tutti i nodi Hidden:
  for (int j = 0; j < numHiddenNodes; j++) {
    float activation = hiddenLayerBias[j];
    for (int k = 0; k < numInputs; k++){
      //sommatoria degli ingressi * i pesi
      activation += training_inputs[i][k] * hiddenWeights[k][j];
    }
    //applico la sigmoide
    hiddenLayer[j] = sigmoid(activation);
  }
      
  // per l'uscita (o le uscite)
  for (int j=0; j<numOutputs; j++) {
    float activation=outputLayerBias[j];
    for (int k=0; k<numHiddenNodes; k++) {
      activation += hiddenLayer[k] * outputWeights[k][j];
    }
    outputLayer[j] = sigmoid(activation);
  }
}

void learn(int i) {
  // scelto il pattern i, applico la backpropagation
  
  // 1. parto dall'uscita e propago all'indietro l'errore
  // array con gli errori sulle uscite
  float deltaOutput[numOutputs];
  for (int j = 0; j < numOutputs; j++) {
    //errore preso pari alla diff tra valore ottenuto nella propagazione e 
    //valore desiderato
    float error = (training_outputs[i][j] - outputLayer[j]);
    //questo è il valore da usare per correggere i pesi.
    //l'errore portato all'ingresso del nodo di uscita
    deltaOutput[j] = error * dSigmoid(outputLayer[j]);
  } 
  
  // propago sui nodi hidden
  // array con gli errori sui nodi hidden
  float deltaHidden[numHiddenNodes];
  for (int j=0; j<numHiddenNodes; j++) {
    float error = 0.0f;
    for (int k=0; k<numOutputs; k++) {
      //lo moltiplico per il peso per metterlo allo stesso livello
      //dell'uscita hidden
      error += deltaOutput[k] * outputWeights[j][k];
    }
    //qui riporto l'errore sul nodo hidden all'ingresso del nodo hidden
    deltaHidden[j] = error * dSigmoid(hiddenLayer[j]);
  }

  // 2. ora modifico i pesi
  // per le uscite
  for (int j=0; j<numOutputs; j++) {
    outputLayerBias[j] += deltaOutput[j] * lr;
    for (int k=0; k<numHiddenNodes; k++) {
      //il nuovo peso è pari al valore di uscita del nodo H moltiplicato per 
      //l'errore portato all'ingresso del nodo di uscita
      outputWeights[k][j] += hiddenLayer[k] * deltaOutput[j] * lr;
    }
  }
  // per i pesi H
  for (int j=0; j<numHiddenNodes; j++) {
    hiddenLayerBias[j] += deltaHidden[j]*lr;
    for(int k=0; k<numInputs; k++) {
      //il nuovo peso è pari al valore presentato all'ingresso moltiplicato per 
      //l'errore H portato all'ingresso del nodo di ingresso
      hiddenWeights[k][j] += training_inputs[i][k] * deltaHidden[j]*lr;
    }
  }
}
