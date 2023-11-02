#include <arduino.h>
#include <XPLDirect.h>
#include <Rotary.h>

Rotary r1 = Rotary(22, 23);
Rotary r2 = Rotary(24, 25);
Rotary r3 = Rotary(26, 27);
Rotary r4 = Rotary(28, 29);
Rotary r5 = Rotary(30, 31);
Rotary r6 = Rotary(32, 33);
Rotary r7 = Rotary(34, 35);
XPLDirect Xinterface(&Serial);      // create an instance of it

float readOBS1;
float writeOBS1;
float readOBS2;
float writeOBS2;
float readADF;
float writeADF;
float readHead;
float writeHead;
float readDrift;
float writeDrift;
float readBaro;
float writeBaro;
float readTAS;
float writeTAS;

void setup() {
  r1.begin(true);
  r2.begin(true);
  r3.begin(true);
  r4.begin(true);
  r5.begin(true);
  r6.begin(true);
  r7.begin(true);
  Serial.begin(XPLDIRECT_BAUDRATE);   
  Xinterface.begin("XPLDirect Cessna 6 Pack");
  while (!Serial){
    delay(30);
  }
  Xinterface.registerDataRef(F("sim/cockpit/radios/nav1_obs_degm"), XPL_READ, 100, 0, &readOBS1);
  Xinterface.registerDataRef(F("sim/cockpit/radios/nav1_obs_degm"), XPL_WRITE, 100, 0, &writeOBS1);
  
  Xinterface.registerDataRef(F("sim/cockpit/radios/nav2_obs_degm"), XPL_READ, 100, 0, &readOBS2);
  Xinterface.registerDataRef(F("sim/cockpit/radios/nav2_obs_degm"), XPL_WRITE, 100, 0, &writeOBS2);

  Xinterface.registerDataRef(F("sim/cockpit/radios/adf1_cardinal_dir"), XPL_READ, 100, 0, &readADF);
  Xinterface.registerDataRef(F("sim/cockpit/radios/adf1_cardinal_dir"), XPL_WRITE, 100, 0, &writeADF);

  Xinterface.registerDataRef(F("sim/cockpit/autopilot/heading_mag"), XPL_READ, 100, 0, &readHead);
  Xinterface.registerDataRef(F("sim/cockpit/autopilot/heading_mag"), XPL_WRITE, 100, 0, &writeHead);
  
  Xinterface.registerDataRef(F("sim/cockpit/gyros/dg_drift_vac_deg"), XPL_READ, 100, 0, &readDrift);
  Xinterface.registerDataRef(F("sim/cockpit/gyros/dg_drift_vac_deg"), XPL_WRITE, 100, 0, &writeDrift);

  Xinterface.registerDataRef(F("sim/cockpit/misc/barometer_setting"), XPL_READ, 100, 0, &readBaro);
  Xinterface.registerDataRef(F("sim/cockpit/misc/barometer_setting"), XPL_WRITE, 100, 0, &writeBaro);

  Xinterface.registerDataRef(F("laminar/c172/knob_TAS"), XPL_READ, 100, 0, &readTAS);
  Xinterface.registerDataRef(F("laminar/c172/knob_TAS"), XPL_WRITE, 100, 0, &writeTAS);
}

void loop() {
  Xinterface.xloop();
  
  int val_OBS1 = processInt(r1.process());
  int val_OBS2 = processInt(r2.process());
  int val_ADF = processInt(r3.process());
  int val_Head = processInt(r4.process());
  float val_Drift = processFloat(r5.process(), 1.0);
  float val_Baro = processFloat(r6.process(), 0.05);
  float val_TAS = processFloat(r7.process(), 0.5);
  
  if(val_OBS1){
    int ref_OBS1 = readOBS1;
    writeOBS1 = ref_OBS1 + val_OBS1;
  }
  else if(val_OBS2){
    int ref_OBS2 = readOBS2;
    writeOBS2 = ref_OBS2 + val_OBS2;
  }
  else if(val_ADF){
    int ref_ADF = readADF;
    writeADF = ref_ADF + val_ADF;
  }
  else if(val_Head){
    int ref_Head = readHead;
    writeHead = ref_Head + val_Head;
  }
  else if(val_Drift){
    float ref_Drift = readDrift;
    writeDrift = ref_Drift + val_Drift;
  }
  else if(val_Baro){
    float ref_Baro = readBaro;
    writeBaro = ref_Baro + val_Baro;
  }
  else if(val_TAS){
    double ref_TAS = readTAS;
    writeTAS = ref_TAS + 0.5;
  }
}

float processFloat(int val, float result){
  float output;
  if (val == 16){
    output = result;
  }
  else if (val == 32){
    output = -result;
  }
  else{
    output = 0;
  }
  return output;
}

int processInt(int val){
  int output;
  if (val == 16){
    output = 1;
  }
  else if (val == 32){
    output = -1;
  }
  else{
    output = 0;
  }
  return output;
}
