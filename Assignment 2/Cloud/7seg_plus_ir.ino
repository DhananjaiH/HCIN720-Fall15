int a = D0;
int b = D1;
int c = D2;
int d = D3;
int e = D4;
int f = D5;
int g = D6;

int handThresh, def, z2, z3, z5, dist;
int t1,t2; //variables for holding millis() for timing
bool flag = false; //flag for checking that events are not published consecutively

void countdown(int secs) {
    int ctr = secs; //converting to ms
    while(ctr!=-1) {
        //a is HIGH for 1,4
        (ctr==1 || ctr==4)?digitalWrite(a,HIGH):digitalWrite(a,LOW);

        //b is HIGH for 5,6
        (ctr==5 || ctr==6)?digitalWrite(b,HIGH):digitalWrite(b,LOW);

        //c is HIGH for 2
        (ctr==2)?digitalWrite(c,HIGH):digitalWrite(c,LOW);

        //d is HIGH for 1,4,7,9
        (ctr==1 || ctr==4 || ctr==7 || ctr==9)?digitalWrite(d,HIGH):digitalWrite(d,LOW);

        //e is HIGH for 1,3,4,5,7,9
        (ctr==1 || ctr==3 || ctr==4 || ctr==5 || ctr==7 || ctr==9)?digitalWrite(e,HIGH):digitalWrite(e,LOW);

        //f is HIGH for 1,2,3,7
        (ctr==1 || ctr==2 || ctr==3 || ctr==7)?digitalWrite(f,HIGH):digitalWrite(f,LOW);

        //g is HIGH for 0,1,7
        (ctr==0 || ctr==1 || ctr==7)?digitalWrite(g,HIGH):digitalWrite(g,LOW);

        Serial.println(ctr);
        ctr--;
        delay(800);
    }
}

void checkZone(int reading) {
    if(reading<=def) {
        //zone 1
        Serial.println("Z1 - no hand detected");
        flag = false;
        //input to 7seg
        levels(2);
    }
    else if(reading>def && reading<z2) {
        //zone 2
        Serial.println("Zone 2");
        flag = false;
        //input to 7seg
        levels(3);
    }
    else if(reading>=z2 && reading<z3) {
        //zone 3
        Serial.println("Zone 3");
        flag = false;
        //input to 7seg
        levels(4);
    }
    else if(reading>=z3 && reading<handThresh) {
        //zone 4
        Serial.println("zone 4 - input registered");
        //to add - check if publish is being done consecutively or not
        if(flag==false) {
            Spark.publish("IRsensor","input",60,PRIVATE);
            flag = true;
        }
        //input to 7seg
        levels(5);
    }
    else {
        //zone 5
        Serial.println("zone 5 - input registered");
        //to add - check if publish is being done consecutively or not
        if(flag==false) {
            Spark.publish("IRsensor","input",60,PRIVATE);
            flag = true;
        }
        //input to 7seg
        levels(6);
    }
}

void levels(int l) {
    //Serial.println(l);
    //Serial.println(t2-t1);
    //a is LOW for level 6
    (l==6)?digitalWrite(a,LOW):digitalWrite(a,HIGH);

    //b is LOW for 5,6
    (l==5 || l==6)?digitalWrite(b,LOW):digitalWrite(b,HIGH);

    //c is HIGH for 1,2
    (l==1 || l==2)?digitalWrite(c,HIGH):digitalWrite(c,LOW);

    //d is HIGH for 1
    (l==1)?digitalWrite(d,HIGH):digitalWrite(d,LOW);

    //e is HIGH for 1,2
    (l==1 || l==2)?digitalWrite(e,HIGH):digitalWrite(e,LOW);

    //f is LOW for 5,6
    (l==5 || l==6)?digitalWrite(f,LOW):digitalWrite(f,HIGH);

    //g is HIGH for 1,2,3
    (l==1 || l==2 || l==3)?digitalWrite(g,HIGH):digitalWrite(g,LOW);
}

void setup() {
    //setting up pin modes
    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    pinMode(d, OUTPUT);
    pinMode(e, OUTPUT);
    pinMode(f, OUTPUT);
    pinMode(g, OUTPUT);
    pinMode(A0, INPUT);

    //initializing the 7seg
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);

    Serial.begin(9600);

    //code for setting the threshold for the IR proximity sensor
    //- count down the 7seg from 5 with 1sec delays - indication to the user to put their hand on top on the IR sensor
    //- collect 3 readings and then take the avg. This will be the threshold value for registering input for the game
    //- count down 7seg from 3 with 1sec delays - indicate to the user that the readings have been collected and the hand can be taken away
    //- collect 3 readings and then take the avg. This will be the value range for no input
    // based on the collected values - we can distribute sensor value ranges into 5 'zones' - this will be used for display on the 7seg
    // indicate that all readings havve been tken
    // loop function will categorize each reading into the zones - to be used for trials
    Serial.println("Starting calibration for hand distance - place your hand above the sensor");
    countdown(5);

    //collecting readings with hand
    handThresh = analogRead(A0);
    delay(250);
    handThresh += analogRead(A0);
    handThresh /= 2;
    delay(250);
    handThresh += analogRead(A0);
    handThresh /= 2;
    delay(100);

    //indicating that hand readings are done
    Serial.println("Readings have been taken - please remove hand");
    countdown(5);

    //collecting readings without hand (or default state)
    def = analogRead(A0);
    delay(250);
    def += analogRead(A0);
    def /= 2;
    delay(250);
    def += analogRead(A0);
    def /= 2;
    delay(100);

    /*

    dividing the ranges into zones

    def is zone 1 - _

    zone 2 - |_|
              _
    zone 3 - |_|
                                                                   |_|
    zone 4 - threshold - detect input at this level for the game - |_|
              _
             |_|
    zone 5 - |_|

    */

    int d = (handThresh - def)/3;
    z2 = def + d;
    z3 = def + 2*d;
    z5 = handThresh + 500; //arbitrary value - to be changed after trial

    Serial.println( "(z1) Default state value>>");
    Serial.println(def);
    Serial.println( "(z2) Zone 2>>");
    Serial.println(z2);
    Serial.println( "(z3) Zone 3>>");
    Serial.println(z3);
    Serial.println( "Threshold value>>");
    Serial.println(handThresh);
    Serial.println( "(z5) Zone 5>>");
    Serial.println(z5);

    t1 = millis();
}

void loop() {
    t2 = millis();
    if(t2-t1 >= 200) {
        //reading the value from the analog port
        dist = analogRead(A0);

        //sending info to the computer over the serial port
        Serial.println(dist);
        checkZone(dist);

        t1 = t2;
    }
    //delay(500);
}
