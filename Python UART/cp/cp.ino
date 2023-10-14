
#define ll long long


int pin = 0;
uint8_t container[128];
int currentIndex ;
int tlm_length = 9;
boolean test = false;

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {

  processReadingData();
  if ( test == true ){
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }
}

void processReadingData() {
  uint8_t data;
  boolean start;
  while ( Serial.available() ) {
    data = Serial.read();
    start = addData((uint8_t)data);
  }
  if ( start ) {
    processData();
  }
}

boolean addData(byte nextChar) {
  
  if (pin == 1)
  {
    container[currentIndex] = nextChar;
    currentIndex++;

    if (currentIndex == tlm_length)
    {
      currentIndex = 0;
      pin = 0;
      return true;
    }
  }

  if (nextChar == 'H' && pin == 0)
  {
    container[currentIndex] = nextChar;
    pin = 1;
    currentIndex++;
  }
  return false;
}

void processData() {
  long m0 = (ll)container[4] << 24 | (ll)container[3] << 16 | (ll)container[2] << 8 | (ll)container[1];
  long m1 = (ll)container[8] << 24 | (ll)container[7] << 16 | (ll)container[6] << 8 | (ll)container[5];
 
  
  union
  {
    long y;
    float z;
  } data0,data1;
  data0.y = m0;
  data1.y = m1;

  if (data0.z == 3.14){
    test = true;
  }
  
  Serial.print(data0.z);
  Serial.print("\t");
  Serial.println(data1.z);

  
}
