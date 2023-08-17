#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>


#include <esp8266channel3lib.h>
#include "pong_geometry.h"

#define POTI_L_PIN 4
#define POTI_R_PIN 5
int16_t paddlePos[2] = {0,0};

#define MAX_SCORE 10
int scorePaddle[2] = {0,0};

#define ADCVAL_TO_Y_POS(ADC) ((ADC)/6.4f)
int adcIdx = 0;

float ballTotalVel = 2.0f;

float ballPosX = 0;
float ballPosY = 0;
float ballVelX = 1;
float ballVelY = 2;
uint32_t frameCount = 0;
uint8_t showallowadvance = 1;
int framessostate = 0;
int framestempcount = 0;
int showtemp = 0;

void SetupMatrix( )
{
  int16_t lmatrix[16];
  tdIdentity( ProjectionMatrix );
  tdIdentity( ModelviewMatrix );

  Perspective( 600, 250, 50, 8192, ProjectionMatrix );
}

void Draw3DSegmentTranslate( int16_t * c1, int16_t * c2, int dx, int dy)
{
  int16_t sx0, sy0, sx1, sy1;
  LocalToScreenspace( c1, &sx0, &sy0 );
  LocalToScreenspace( c2, &sx1, &sy1 );
  CNFGTackSegment( sx0+dx, sy0+dy, sx1+dx, sy1+dy );
}

void Draw3DModelTranslate(int16_t *verts, uint16_t *indices, int lenIndices, int dx,int dy){
  int i;
  int nrv = lenIndices/sizeof(uint16_t);
  for( i = 0; i < nrv; i+=2 )
  {
    int16_t * c1 = &verts[indices[i]];
    int16_t * c2 = &verts[indices[i+1]];
    Draw3DSegmentTranslate( c1, c2, dx,dy );
  }
}

void LeftPaddle(int posy){
  int16_t ftmp[16];
  memcpy(ftmp, ModelviewMatrix, sizeof(ModelviewMatrix));
  MakeTranslate(PADDLE_CENTER_X(138),PADDLE_CENTER_Y(0),512, ModelviewMatrix);
  ModelviewMatrix[0] = PADDLE_X;
  ModelviewMatrix[5] = PADDLE_Y;
  ModelviewMatrix[10] = PADDLE_Z;
  Draw3DModelTranslate(cubeVerts, cubeIndices, sizeof(cubeIndices) ,-64,posy+1);
  memcpy(ModelviewMatrix, ftmp, sizeof(ModelviewMatrix));
}


void RightPaddle(int posy){
  int16_t ftmp[16];
  memcpy(ftmp, ModelviewMatrix, sizeof(ModelviewMatrix));
  MakeTranslate(PADDLE_CENTER_X(-138),PADDLE_CENTER_Y(0),512, ModelviewMatrix);
  ModelviewMatrix[0] = PADDLE_X;
  ModelviewMatrix[5] = PADDLE_Y;
  ModelviewMatrix[10] = PADDLE_Z;
  Draw3DModelTranslate(cubeVerts, cubeIndices, sizeof(cubeIndices) ,64,posy+1);
  memcpy(ModelviewMatrix, ftmp, sizeof(ModelviewMatrix));
}

void Outline(){
  CNFGColor( 5 );
  int16_t ftmp[16];
  memcpy(ftmp, ModelviewMatrix, sizeof(ModelviewMatrix));
  MakeTranslate(-460,-425,512, ModelviewMatrix);
  ModelviewMatrix[0] = 920;
  ModelviewMatrix[5] = 850;
  ModelviewMatrix[10] = 200;
  Draw3DModelTranslate(cubeVerts, cubeIndices, sizeof(cubeIndices) ,0,0);
  memcpy(ModelviewMatrix, ftmp, sizeof(ModelviewMatrix));
  CNFGColor( 17 );
}

void Ball(){
  int16_t ftmp[16];
  memcpy(ftmp, ModelviewMatrix, sizeof(ModelviewMatrix));
  tdIdentity( ModelviewMatrix );
  tdScale(ModelviewMatrix, BALL_X, BALL_Y, BALL_Z);
  tdRotateEA(ModelviewMatrix, framessostate*3,framessostate*5,2*framessostate);
  ModelviewMatrix[11] = 768;
  ModelviewMatrix[3] = BALL_CENTER_X(0);
  ModelviewMatrix[7] = BALL_CENTER_Y(0);
  Draw3DModelTranslate(dodecahedronVerts, dodecahedronIndices, sizeof(dodecahedronIndices) ,((int)ballPosX)-5,((int)ballPosY)-5);
  memcpy(ModelviewMatrix, ftmp, sizeof(ModelviewMatrix));
}

int calcPaddlePos(uint16_t adcVal){
  /*
  if(adcVal<50)
    return -70;
  if(adcVal>450)
    return 70;

  return ((adcVal-50)/2.9f)-70;
  */

  if(adcVal < 50)
    return -70;
  if(adcVal > 975)
    return 70;

  return (adcVal-512)/7.4;
}

void resetBall(){
  ballPosX = 0;
  ballPosY = 0;
  ballVelX = (os_random() & 1)? -ballTotalVel:ballTotalVel;
  ballVelY = (tdSIN(os_random())/256.0f) * ballTotalVel;
}

void calcNewBallPos(){
  ballPosX += ballVelX;
  ballPosY += ballVelY;
  if(ballPosY < BALL_Y_POS_MIN || ballPosY > BALL_Y_POS_MAX){
    ballVelY = -ballVelY;
  }

  if(ballPosX < BALL_X_POS_PADDLE_MIN){
    int ballYDelta = (paddlePos[0]-ballPosY);
    if(ballYDelta <= 0 && ballYDelta >= -PADDLE_RADIUS){
      ballVelX = -ballVelX;
      ballVelY = (tdSIN(3*ballYDelta)/256.0f) * ballTotalVel;
      ballPosX = BALL_X_POS_PADDLE_MIN;
    } else if(ballYDelta > 0 && ballYDelta < PADDLE_RADIUS){
      ballVelX = -ballVelX;
      ballVelY = -(tdSIN(3*ballYDelta)/256.0f) * ballTotalVel;
      ballPosX = BALL_X_POS_PADDLE_MIN;
    } 
  } 
  if (ballPosX < BALL_X_POS_MIN){
      scorePaddle[1]+=1;
      resetBall();
  } 

  if (ballPosX > BALL_X_POS_PADDLE_MAX){
    int ballYDelta = (paddlePos[1]-ballPosY);
    if(ballYDelta <= 0 && ballYDelta >= -PADDLE_RADIUS){
      ballVelX = -ballVelX;
      ballVelY = (tdSIN(3*ballYDelta)/256.0f) * ballTotalVel;
      ballPosX = BALL_X_POS_PADDLE_MAX;
    } else if(ballYDelta > 0 && ballYDelta < PADDLE_RADIUS){
      ballVelX = -ballVelX;
      ballVelY = -(tdSIN(3*ballYDelta)/256.0f) * ballTotalVel;
      ballPosX = BALL_X_POS_PADDLE_MAX;
    }
  } 
  if (ballPosX > BALL_X_POS_MAX){
      scorePaddle[0]+=1;
      resetBall();
  } 
}

int16_t Height( int x, int y, int l )
{
  return tdCOS( (x*x + y*y) + l );
}

// This callback gets called automatically every frame
void loadFrame()
{
    video_broadcast_clear_frame();
    CNFGPenX = 14;
    CNFGPenY = 20;
    int16_t rt[16];
    tdIdentity( ModelviewMatrix );
    tdIdentity( ProjectionMatrix );
    CNFGColor( 17 );

    
    adcIdx = (!adcIdx) & 1;
    if(adcIdx){
      pinMode(POTI_L_PIN, INPUT);
      pinMode(POTI_R_PIN, OUTPUT);
      digitalWrite(POTI_R_PIN, LOW);
    } else {
      pinMode(POTI_R_PIN, INPUT);
      pinMode(POTI_L_PIN, OUTPUT);
      digitalWrite(POTI_L_PIN, LOW);
    }
    
  
    if(scorePaddle[0] >= MAX_SCORE || scorePaddle[1] >= MAX_SCORE){
      // Show win screen
      if(framestempcount == 0)
        framestempcount = framessostate;
      CNFGColor( 17 );
      CNFGTackRectangle( 70, 110, 180+200, 150 );   
      CNFGColor( 16 );
      CNFGPenY += 14*6+10;
      CNFGPenX += 25;
      char buf[256];
      ets_sprintf(buf, "Player %c has won!", (scorePaddle[0] >= MAX_SCORE)?'1':'2' );
      CNFGDrawText(buf, 3);
      CNFGPenY += 16;
      CNFGPenX += 25;
      ets_sprintf(buf, "Score: %d:%d", scorePaddle[0], scorePaddle[1]);
      CNFGDrawText(buf, 3);
  
      if(framessostate-framestempcount == 5*25){
        scorePaddle[0] = 0;
        scorePaddle[1] = 0;
        resetBall();
        framestempcount = 0;
      }
    } else {
      // Game logic
      CNFGPenY += 24;
      CNFGPenX += 80;
      char buf[256];
      ets_sprintf(buf, "%d:%d", scorePaddle[0], scorePaddle[1]);
      CNFGDrawText(buf, 4);
  
      SetupMatrix();
      if(adcIdx)
        paddlePos[adcIdx] = calcPaddlePos(analogRead(A0));
      else 
        paddlePos[adcIdx] = calcPaddlePos(1024-analogRead(A0));
      Outline();
      LeftPaddle(paddlePos[0]);
      RightPaddle(paddlePos[1]);
      calcNewBallPos();
      Ball();
    }
    framessostate++;
}

void setup() {
  system_update_cpu_freq( SYS_CPU_160MHZ );
  Serial.begin(115200);
  Serial.println("Starting ESPong3D!");
  WiFi.softAP("ESPong3D", "ESPong3D");

  // Port defaults to 8266
  ArduinoOTA.setPort(8266);
  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("ESPong3D");

  ArduinoOTA.onStart([]() {
    channel3Deinit();
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {   
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {    
    Serial.printf("Progress: %u%%\r\n", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  
  channel3Init(PAL, &loadFrame);
  Serial.printf("Update via %s:8266\n", WiFi.softAPIP().toString().c_str());
}

void loop() {
  // put your main code here, to run repeatedly:
  // Handle OTA requests
  ArduinoOTA.handle();
}
