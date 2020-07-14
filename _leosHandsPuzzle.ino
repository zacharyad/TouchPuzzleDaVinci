#include <DFPlayerMini_Fast.h>
#include <SoftwareSerial.h>
DFPlayerMini_Fast myMP3;
SoftwareSerial mySerial(10, 11); // RX 11, TX 10


// Pins Assignment
int readPin0 = A0;
int readPin1 = A1;
int readPin2 = A2;
int readPin3 = A3;
int readPin4 = A4;
int readPin5 = A5;
int readPin6 = A6;
int readPin7 = A7;
int toggleSwitch = 2;

//Puzzle data
int arrayLength = 6;
int arraySize = 7;
int correctOrder[] = {1, 2, 3, 2, 4, 5, 6};
int inputs[] = {100, 200, 300, 400, 500, 600, 700};

// Audio config
const int volume = 20;

//Helper Funcs
void showInputsArr(){
        Serial.println(inputs[0]);
        Serial.println(inputs[1]);
        Serial.println(inputs[2]);
        Serial.println(inputs[3]);
        Serial.println(inputs[4]);
        Serial.println(inputs[5]);
        Serial.println(inputs[6]);
}

void push(int numberPushed){
  for(int k = 1; k < arraySize; k++){
    int temp = inputs[k];
    inputs[k - 1] = temp;
  }
  inputs[arraySize - 1] = numberPushed;
}

void inputsReset(){
  for(int j = 0; j < arrayLength; j++){
    correctOrder[j] = 100;
  }
}

int checkAnswer() {
  for(int i = 0; i < arrayLength; i++){
    if(correctOrder[i] != inputs[i]){
      return 0;
    }
  }
  return 1;
  audio(1);
}

void audio(int number){
  // play number
  myMP3.play(number);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(9600);

  pinMode(readPin0, INPUT);
  pinMode(readPin1, INPUT);
  pinMode(readPin2, INPUT);
  pinMode(readPin3, INPUT);
  pinMode(readPin4, INPUT);
  pinMode(readPin5, INPUT);
  pinMode(readPin6, INPUT);
  pinMode(readPin7, INPUT);
  pinMode(toggleSwitch, INPUT_PULLUP);

  myMP3.begin(mySerial);
  myMP3.volume(volume);
  delay(1000);
  Serial.println("Sleeping for 1 sec");
  myMP3.sleep();
  delay(1000);
  Serial.println("Waking up");
  myMP3.wakeUp();
  delay(1000);

  //testing for correct sound file orde
  Serial.println("Playing track 4 for 5 sec");
  audio(1);
  delay(2000);

}

void loop() {
  int readVal1 = analogRead(readPin1);
  int readVal2 = analogRead(readPin2);
  int readVal3 = analogRead(readPin3);
  int readVal4 = analogRead(readPin4);
  int readVal5 = analogRead(readPin5);
  int readVal6 = analogRead(readPin6);
  int readVal7 = analogRead(readPin7);
  int readVal0 = analogRead(readPin0);
  int toggleState = digitalRead(toggleSwitch);
//
  //  Checking to see what is been pressed
//

  if(!toggleState){
    // TOggle is in the puzzle state
       if(readVal1 < 200){
          Serial.println(readVal1);
          if(inputs[arraySize - 1] == 2){
            //PLAY AUDIO AGAIN
            audio(7);
            delay(3000);
          } else {
            //PLAY AUDIO
            audio(7);
            push(2);
            delay(3000);
          }

          Serial.println("TWO");
          delay(2000);

    } else if (readVal7 < 200){
      //INFO MESSAGE
       audio(3);
       Serial.println("SEVEN");
       delay(3000);

    } else if (readVal2 < 200){
      Serial.println(readVal2);
      if(inputs[arraySize - 1] == 3){
        //PLAY AUDIO AGAIN
        audio(9);
        delay(3000);
      } else {
        //PLAY AUDIO
        audio(9);
        push(3);
        delay(3000);
      }

      Serial.println("THREE");
      delay(2000);

    } else if (readVal3 < 200){
      Serial.println(readVal3);
       if(inputs[arraySize - 1] == 4){
        //PLAY AUDIO AGAIN
        audio(11);
        delay(3000);
      } else {
        //PLAY AUDIO
        audio(11);

        push(4);
        delay(3000);
      }

      Serial.println("FOUR");
      delay(2000);

    } else if (readVal4 < 200){
      Serial.println(readVal4);
      if(inputs[arraySize - 1] == 5){
        //PLAY AUDIO AGAIN
        audio(13);
        delay(3000);
      } else {
        //PLAY AUDIO
        audio(13);
        push(5);
        delay(3000);
      }

      Serial.println("FIVE");
      delay(2000);

    } else if (readVal0 < 200){
      Serial.println(readVal0);
      if(inputs[arraySize - 1] == 1){
        //PLAY AUDIO AGAIN
        audio(5);
        delay(3000);
      } else {
        //PLAY AUDIO
        audio(5);
        delay(100);
        push(1);
        delay(3000);
      }

      Serial.println("ONE");
      delay(2000);

    } else if (readVal5 < 200){
        push(6);
        Serial.println(readVal5);
        if(checkAnswer()){
        //CORRECT ANSWER
        Serial.println("YOU WIN!!");
        // PLAY CORRECT WINNING SOUND
        audio(1);
        delay(2000);
        audio(17);
        delay(30000);
        } else {
          //WRONG ANWSER
        if(inputs[arraySize - 1] == 5){
          //PLAY AUDIO AGAIN
          audio(15);
          delay(3000);
        } else {
          //PLAY AUDIO
          audio(15);
          push(6);
          delay(3000);
        }

      Serial.println("SIX");
      delay(2000);
     }
    }
  }
}
