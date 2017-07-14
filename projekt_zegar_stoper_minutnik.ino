/*
Zegar binarny wykorzystujący 12 diod LED, z możliwością ręcznego ustawiania godziny za pomocą przycisków 1(A3) i 2(A2). W celu wybrania parametru do zmiany (godziny/minuty) wciśnij przycisk 3(A1).
 */

// the setup routine runs once when you press reset:

void setup() {                
  // initialize the digital pin as an output.
  for (int i = 2; i<=11; ++i)
    pinMode(i, OUTPUT);
  for (int i = 8; i<=11; ++i) 
    pinMode(i, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A3, INPUT);
  digitalWrite(A3, HIGH);
  pinMode(A2, INPUT);
  digitalWrite(A2, HIGH);
  pinMode(A1, INPUT);
  digitalWrite(A1, HIGH);
  pinMode(A0, INPUT);
  digitalWrite(A0, HIGH);
  Serial.begin(9600);
}

int funkcja = 0;
int glos=1200;

//zegar
int minuty=0;
int sekundy=0;
int i=0;
int j=0;
int x=12;
int mode=0;
int p=11;
int l=7;
static unsigned long tyk = 0;

int minutyPin[]={2, 3, 4, 5, 6, 7};
int godzinyPin[]={8, 9, 10, 11};
int godziny[]={12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

//stoper
int mili_sek=0;
int stoper_sek=0;
int stoper_min=0;
int modest=0;
static unsigned long tykstop = 0; 

//minutnik
int minutys=0;
int sekundys=0;
int modes=0;
static unsigned long tyks = 0;

int sekundysPin[]={2, 3, 4, 5, 6, 7};
int minutysPin[]={8, 9, 10, 11};

void loop() {
  
  //przycisk 4 (zmiania funkcji 0 - 1)
      if (digitalRead(A0) == LOW  && funkcja == 0) {
        while (digitalRead(A0) == LOW) delay(1);
        {
        for (int i=2; i<=13; ++i) {
          digitalWrite(i, LOW);
        }  
        funkcja=1;
        stoper_sek=0;
        stoper_min=0;
        }
      }
      
  //przycisk 4 (zmiania funkcji 1 - 2)
      if (digitalRead(A0) == LOW  && funkcja == 1) {
        while (digitalRead(A0) == LOW) delay(1);
        {
        for (int i=2; i<=13; ++i) {
          digitalWrite(i, LOW);
        }  
        funkcja=2;
        }
      }
      
  //przycisk 4 (zmiania funkcji 2 - 0)
      if (digitalRead(A0) == LOW  && funkcja == 2) {
        while (digitalRead(A0) == LOW) delay(1);
        {
        for (int i=2; i<=13; ++i) {
          digitalWrite(i, LOW);
        }  
        funkcja=0;
        }
      }    
  
  //-----------------------------------------------------------
  //                        ZEGAR
  //-----------------------------------------------------------
  if (funkcja == 0) {

      //przycisk 1 (- godziny)
      if (digitalRead(A3) == LOW  &&  mode == 1  &&  x>=1) {
        while (digitalRead(A3) == LOW) delay(1); 
        {           
          --x;
          sekundy=0;
        }
      }
      
      //przycisk 2 (+ godziny)  
      if (digitalRead(A2) == LOW &&  mode == 1) { 
        while (digitalRead(A2) == LOW) delay(1); 
        {           
          ++x;
          sekundy=0;
        }
      }
      
      //przycisk 1 (- minuty)
      if (digitalRead(A3) == LOW  && mode == 2) {
        while (digitalRead(A3) == LOW) delay(1); 
        {           
          --minuty;
          sekundy=0;
        }
      }
    
      //przycisk 2 (+ minuty)  
      if (digitalRead(A2) == LOW && mode == 2) { 
        while (digitalRead(A2) == LOW) delay(1); 
        {           
          ++minuty;
          sekundy=0;
        }
      }
      
      //przycisk 3 (ON ustawianie godziny)  
      if (digitalRead(A1) == LOW  &&  mode == 0) { 
        while (digitalRead(A1) == LOW) delay(1); 
        {           
          mode=1;
          setgodziny();
        }
      }
      
      //przycisk 3 (ON ustawianie minut)  
      if (digitalRead(A1) == LOW  &&  mode == 1) { 
        while (digitalRead(A1) == LOW) delay(1); 
        {           
          mode=2;
          setminuty();
        }
      }
      
      //przycisk 3 (OFF ustawianie)  
      if (digitalRead(A1) == LOW  &&  mode == 2) { 
        while (digitalRead(A1) == LOW) delay(1); 
        {           
          mode=0;
        }
      }
        
      //diody (minuty) 
      for (int i=0; i<=5; ++i) {
        if (bitRead(minuty, i) == 1) {
          digitalWrite(minutyPin[i], HIGH);
        }
        else {
          digitalWrite(minutyPin[i], LOW);
        }
      }
    
      //diody (godziny)
      for (int j=0; j<=3; ++j) {
        if (bitRead(godziny[x], j) == 1) {
          digitalWrite(godzinyPin[j], HIGH);
        }
        else {
          digitalWrite(godzinyPin[j], LOW);
        }
      }
      
      //sekundnik (dioda pod pinem 12)
      if (sekundy % 2 == 0)
        digitalWrite(12, HIGH);
      else 
        digitalWrite(12, LOW);
      
      //dioda (AM/PM)  
      if (x>=12  &&  x<=24)
        digitalWrite(13, HIGH);
      else 
        digitalWrite(13, LOW);
        
      //zegar
      if (millis() - tyk >= 1000) {
        tyk = millis();
        ++sekundy;
      }
      
      if (sekundy >=60) {
        ++minuty;
        sekundy=0;
      }
      
      if (minuty >= 60) {
        minuty=0;
        ++x;
      }
      
      if (minuty < 0) {
        minuty=59;
        --x;
      }
      
      if (x>=24) {
        x=0;
      }
      
      if (digitalRead(A3) == LOW  &&  x == 0) {
        x=24;
      }
      
      //wypisanie
      Serial.print(godziny[x]);
      Serial.print(":");
      if (minuty>=0  &&  minuty<=9)
        Serial.print("0");
      Serial.print(minuty);
      Serial.print(":");
      if (sekundy>=0  &&  sekundy<=9)
        Serial.print("0");
      Serial.print(sekundy);
      if (x >= 0 &&  x<=11)
        Serial.println(" AM");
      else
        Serial.println(" PM");    
  }
  
  //-----------------------------------------------------------
  //                        STOPER
  //-----------------------------------------------------------
  
  if (funkcja == 1) {
    
    //przycisk 1 (start)
    if (digitalRead(A3) == LOW  &&  modest == 0) {
      while (digitalRead(A3) == LOW) delay(1); 
      {           
        modest=1;
      }
    }
    
    //przycisk 1 (ponowny start)
    if (digitalRead(A3) == LOW  &&  modest == 2) {
      while (digitalRead(A3) == LOW) delay(1); 
      {           
        modest=1;
      }
    }
    
    //przycisk 2 (stop)
    if (digitalRead(A2) == LOW  &&  modest == 1) {
      while (digitalRead(A2) == LOW) delay(1); 
      {           
        modest=2;  
      }
    }
    
    //przycisk 3 (reset)
    if (digitalRead(A1) == LOW  &&  modest == 2) {
      while (digitalRead(A1) == LOW) delay(1); 
      {           
        modest=0;
        stoper_sek=0;
        stoper_min=0;
        mili_sek=0;  
      }
    }
    
    //diody(sekundy)
    for (int e=0; e<=5; ++e) {
      if (bitRead(stoper_sek, e) == 1) {
        digitalWrite(sekundysPin[e], HIGH);
      }
      else {
        digitalWrite(sekundysPin[e], LOW);
      }
    }
  
    //diody(minuty)
    for (int r=0; r<=3; ++r) {
      if (bitRead(stoper_min, r) == 1) {
        digitalWrite(minutysPin[r], HIGH);
      }
      else {
        digitalWrite(minutysPin[r], LOW);
      }
    }
    
    //stoper
    if (modest == 1) { 
      
      delay(9);
      ++mili_sek;
      
      if (mili_sek>=100) {
        ++stoper_sek;
        mili_sek=0;
      }
      
      if (stoper_sek>=60) {
        ++stoper_min;
        stoper_sek=0;
      }
    }
    //wypisanie
    Serial.print(stoper_min);
    Serial.print(":");
    if (stoper_sek>=0  &&  stoper_sek<=9)
      Serial.print("0");  
    Serial.print(stoper_sek);
    Serial.print(":");
    if (mili_sek>=0  &&  mili_sek<=9)
      Serial.print("0");
    Serial.println(mili_sek);
  }
  
  //-----------------------------------------------------------
  //                        MINUTNIK
  //-----------------------------------------------------------
  
  if (funkcja == 2) {
    //przycisk 3 (tryb 0 - 1)
    if (digitalRead(A1) == LOW  &&  modes == 0) {
      while (digitalRead(A1) == LOW) delay(1); 
      {           
        modes=1;
        minutys=0;
        sekundys=0;  
        setgodziny();
      }
    }
    
    //przycisk 3 (tryb 1 - 2)
    if (digitalRead(A1) == LOW  &&  modes == 1) {
      while (digitalRead(A1) == LOW) delay(1); 
      {           
        modes=2;
        setminuty();  
      }
    }
    
    //przycisk 3 (tryb 2 - 3)
    if (digitalRead(A1) == LOW  &&  modes == 2) {
      while (digitalRead(A1) == LOW) delay(1); 
      {           
        modes=3;  
      }
    }
    
    //przycisk 3 (tryb 3 - 0)
    if (digitalRead(A1) == LOW  &&  modes == 3) {
      while (digitalRead(A1) == LOW) delay(1); 
      {           
        modes=0;  
      }
    }
    
    //przycisk 1 (- minuty w trybie 1)
    if (digitalRead(A3) == LOW  &&  modes == 1  &&  minutys >= 1) {
      while (digitalRead(A3) == LOW) delay(1); 
      {           
        --minutys;  
      }
    }
    
    //przycisk 1 (zapetlenie minut na 0)
    if (digitalRead(A3) == LOW  &&  modes == 1  &&  minutys == 0) {
      while (digitalRead(A3) == LOW) delay(1); 
      {           
        minutys=15;  
      }
    }
    
    //przycisk 2 (+ minuty w trybie 1)
    if (digitalRead(A2) == LOW  &&  modes == 1  &&  minutys <15) {
      while (digitalRead(A2) == LOW) delay(1); 
      {           
        ++minutys;  
      }
    }
    
    //przycisk 2 (zapetlenie minut na 15)
    if (digitalRead(A2) == LOW  &&  modes == 1  &&  minutys == 15) {
      while (digitalRead(A2) == LOW) delay(1); 
      {           
        minutys=0;  
      }
    }
    
    //przycisk 1 (- sekundy w trybie 2)
    if (digitalRead(A3) == LOW  &&  modes == 2  &&  sekundys >= 10) {
      while (digitalRead(A3) == LOW) delay(1); 
      {           
        sekundys-=10;  
      }
    }
    
    //przycisk 1 (zapetlenie sekund na 0)
    if (digitalRead(A3) == LOW  &&  modes == 2  &&  sekundys == 0) {
      while (digitalRead(A3) == LOW) delay(1); 
      {           
        sekundys=50;  
      }
    }
    
    //przycisk 2 (+ sekundy w trybie 2)
    if (digitalRead(A2) == LOW  &&  modes == 2  &&  sekundys < 50) {
      while (digitalRead(A2) == LOW) delay(1); 
      {           
        sekundys+=10;  
      }
    }
    
    //przycisk 2 (zapetlenie sekund na 60)
    if (digitalRead(A2) == LOW  &&  modes == 2  &&  sekundys == 50) {
      while (digitalRead(A2) == LOW) delay(1); 
      {           
        sekundys=0;  
      }
    }
    
    //przycisk 1 (pauza w trybie 3)
    if (digitalRead(A3) == LOW  &&  modes == 3) {
      while (digitalRead(A3) == LOW) delay(1); 
      {           
        modes=0;  
      }
    }
    
    //przycisk 1 (OFF pauza w trybie 3)
    if (digitalRead(A3) == LOW  &&  modes == 0) {
      while (digitalRead(A3) == LOW) delay(1); 
      {           
        modes=3;  
      }
    }
    
    //diody(sekundy)
    for (int q=0; q<=5; ++q) {
      if (bitRead(sekundys, q) == 1) {
        digitalWrite(sekundysPin[q], HIGH);
      }
      else {
        digitalWrite(sekundysPin[q], LOW);
      }
    }
  
    //diody(minuty)
    for (int w=0; w<=3; ++w) {
      if (bitRead(minutys, w) == 1) {
        digitalWrite(minutysPin[w], HIGH);
      }
      else {
        digitalWrite(minutysPin[w], LOW);
      }
    }
    
   
    
    //koniec odliczania
    if (minutys == 0  &&  sekundys == 0 &&  modes == 3) 
    {
      for (int i=2; i<=11; i++)
        {
        digitalWrite (i, HIGH);
        delay(50);
        digitalWrite (i, LOW);
        }   
      modes=0;
    }
    
   //dioda na pinie 12 (pauza)
    if (modes == 0) 
      digitalWrite(12, HIGH);
    else
      digitalWrite(12, LOW);
    
    if (modes == 3) { 
      if (sekundys % 2 != 0)
        digitalWrite(12, HIGH);
      else 
        digitalWrite(12, LOW);
    }  
  
    //minutnik
    if(modes == 3) {
      if (millis() - tyks >= 1000) {
        tyks = millis();
        --sekundys;
      }
      
      if (sekundys >=60) {
        ++minutys;
        sekundys=0;
      }
      
      if (sekundys < 0) {
        --minutys;
        sekundys=59;
      }
      
    }
   
    //wypisanie
    Serial.print(minutys);
    Serial.print(":");
    if(sekundys>=0  &&  sekundys<=9)
      Serial.print("0");
    Serial.println(sekundys);  
  }

}//KONIEC
  

void setgodziny() {
  for (p=11; p>=8; --p)
    digitalWrite(p, LOW);
  p=11;
  if (p>=8) {
    for (p=11; p>=8; --p) {
      digitalWrite(p, HIGH);
      delay(100);
      digitalWrite(p, LOW);
    }
  }
}

void setminuty() {
  for (l=7; l>=2; --l)
    digitalWrite(l, LOW);
  l=7;
  if (l>=2) {
    for (l=7; l>=2; --l) {
      digitalWrite(l, HIGH);
      delay(100);
      digitalWrite(l, LOW);
    }
  }
}
