const int ledSpkr = PA0; // Output 1 = LED on
const int ledOT = PA1; // Output 1 = LED on
const int ledDC = PA2; // Output 1 = LED on
const int ledOC = PA3; // Output 1 = LED on
const int SpkrON = PA4; // Output 1 = Speaker SSR on
const int inOT = PA7; // Input 1 = Overtemperature
const int inDC = 10; // Input 1 = DC detected
const int inOC = 9; // Input 1 = Overcurrent
const int inPWR = 8; // Input 0 = Power on (SMPS)
int State = 0; // Status 0 = INIT, 1 = WAIT, 2 = START, 3 = RUN, 4 = ERROR, 5 = WAITOFF
int lastState = 0;
unsigned long lastDebounceTime = 0;  // the last time the inPWR changed
unsigned long debounceDelay = 200;

void setup() {
  // set port modes
  pinMode(ledSpkr, OUTPUT);
  pinMode (ledOT, OUTPUT);
  pinMode (ledDC, OUTPUT);
  pinMode (ledOC, OUTPUT);
  pinMode (SpkrON, OUTPUT);
  pinMode (inOT, INPUT);
  pinMode (inDC, INPUT);
  pinMode (inOC, INPUT);
  pinMode (inPWR, INPUT);
  digitalWrite(SpkrON, LOW);
  digitalWrite(ledOC, HIGH);
  delay(100);
  digitalWrite(ledDC, HIGH);
  delay(100);
  digitalWrite(ledOT, HIGH);
  delay(100);
  digitalWrite(ledSpkr, HIGH);
  delay(100);
}

void StartDelay() {
  for (int i = 0; i <= 10; i++) {
    digitalWrite(ledSpkr, HIGH);
    delay(200);
    digitalWrite(ledSpkr, LOW);
    delay(200);
  }
}

int CheckError() {
  if (digitalRead(inOC) == HIGH) { // Overcurrent
    digitalWrite(SpkrON, LOW);
    digitalWrite(ledSpkr, LOW);
    digitalWrite(ledOC, HIGH);
    return HIGH;
  }
  if (digitalRead(inDC) == HIGH) { // DC detected
    delay(50); // Wait 50mS and check again
    if (digitalRead(inDC) == HIGH) {
      digitalWrite(SpkrON, LOW);
      digitalWrite(ledSpkr, LOW);
      digitalWrite(ledDC, HIGH);
      return HIGH;
    }
  }
  if (digitalRead(inOT) == HIGH) { // Overtemperature
    digitalWrite(SpkrON, LOW);
    digitalWrite(ledSpkr, LOW);
    digitalWrite(ledOT, HIGH);
    return HIGH;
  }
  return LOW;
}
void loop() {
  // put your main code here, to run repeatedly:
  switch (State) {
    case 0: // INIT
      digitalWrite(SpkrON, LOW);
      digitalWrite(ledSpkr, LOW);
      digitalWrite(ledDC, LOW);
      digitalWrite(ledOC, LOW);
      digitalWrite(ledOT, LOW);
      State = 1;
      break;
    case 1: // WAIT for Power ON
      delay(100);
      if (digitalRead(inPWR) == LOW) {
        State = 2;
      }
      break;
    case 2: // START
      if (CheckError() == HIGH) {
        State = 4;
      } else {
        StartDelay();
        digitalWrite(SpkrON, HIGH);
        digitalWrite(ledSpkr, HIGH);
        State = 3;
      }
      break;
    case 3: // RUN
      if (CheckError() == HIGH) {
        State = 4;
      }
      if (digitalRead(inPWR) == HIGH) { // Power OFF
        lastDebounceTime = millis();
        lastState = 3;
        State = 5;
      }
      break;
    case 4: // ERROR (keep Error LED on until switch off)
      if (digitalRead(inPWR) == HIGH) { // Power OFF
        lastDebounceTime = millis();
        lastState = 4;
        State = 5;
      }
      break;
    case 5: // WAIT OFF
      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (digitalRead(inPWR) == HIGH) { // still Power OFF
          digitalWrite(SpkrON, LOW);
          digitalWrite(ledSpkr, LOW);
          State = 0;
        } else {
          State = lastState;
        }
      }
      break;
  }
}
