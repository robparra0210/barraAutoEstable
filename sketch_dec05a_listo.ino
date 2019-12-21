double kp=1.2, ki=.0001, kd=01 ;


unsigned long currentTime,previousTime; 
double elapsedTime;
double error;
double lastError;
double input, output, Setpoint=50;
double cumError, rateError;
double SalidaDer, SalidaIzq;

void setup() {        //SEPUP SEPUP SEPUP SEPUP SEPUP SEPUP SEPUP SEPUP SEPUP SEPUP SEPUP SEPUP SEPUP SEPUP SEPUP SEPUP 
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
}

void loop() {   // LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP 
   kp=map(analogRead(A2),0,1024,0,30);
   
   
       double  input=map(analogRead(A0),430,630,0,100);
   double  output=computePID(input);
   
  if(output>=0){ //ERROR POSITIVO+ ERROR POSITIVO+ ERROR POSITIVO+ ERROR POSITIVO+ ERROR POSITIVO+ ERROR POSITIVO+ ERROR POSITIVO+ ERROR POSITIVO+ ERROR POSITIVO+
     
     double SalidaDer=map(abs(output),0,110,90,255);  
         if(SalidaDer>=256){
               SalidaDer=255;
               analogWrite(10, SalidaDer);
          }
  
           analogWrite(10, SalidaDer); //Salida motor derecho
        
    double SalidaIzq=map(SalidaDer,90,255,100,65);  // Freno
            analogWrite(9, SalidaIzq);     

    Serial.print("posReal= ");
    Serial.print(analogRead(A0));
    Serial.print(" posMap= ");
    Serial.print(input);
    Serial.print(" ouput =");
    Serial.print(output);
    Serial.print(" Error =");
    Serial.print(error);
    Serial.print(" SalidaDer= ");
    Serial.print( SalidaDer);
    Serial.print(" SalidaIzq  ");
    Serial.print( SalidaIzq);
    Serial.print(" kp= ");
    Serial.println( kp);    
    
  }
    
    if(output<0){ //ERROR NEGATIVO- ERROR NEGATIVO- ERROR NEGATIVO- ERROR NEGATIVO- ERROR NEGATIVO- ERROR NEGATIVO- ERROR NEGATIVO- ERROR NEGATIVO- ERROR NEGATIVO-  
      
      double SalidaIzq=map(abs(output),0,100,90,255);
             analogWrite(9, SalidaIzq);
             
           if(SalidaIzq>=256){
             SalidaIzq=255;
             analogWrite(9, SalidaIzq);
              }
  
     double SalidaDer=map(SalidaIzq,90,255,100,65);//FRENO
     analogWrite(10,SalidaDer);

    Serial.print("posReal= ");
    Serial.print(analogRead(A0));
    Serial.print(" posMap= ");
    Serial.print(input);
    Serial.print(" ouput =");
    Serial.print(output);
    Serial.print(" Error =");
    Serial.print(error);
    Serial.print(" SalidaDer= ");
    Serial.print( SalidaDer);
    Serial.print(" SalidaIzq  ");
    Serial.print( SalidaIzq);
    Serial.print(" kp= ");
    Serial.println( kp);    
    
   }
}

double computePID(double input){         //Funcion PID Funcion PID Funcion PID Funcion PID Funcion PID Funcion PID Funcion PID Funcion PID Funcion PID Funcion PID 
  
        currentTime = millis(); //Tiempo trancurrido
        elapsedTime = (double)(currentTime - previousTime); //Tiempo transcurrido desde la ultima iteracion
        error = Setpoint - input; // determine error
        cumError +=error*elapsedTime; // Calculo integrativo
        rateError = (error -lastError)/elapsedTime;
        double output = kp*error+ki*cumError +kd*rateError; ;
        lastError = error; //remember current error
        previousTime = currentTime; //remember current time return out; //have function return the PID output 
        return(output);
}
