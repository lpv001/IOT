#ifndef TELEMETRY_H
#define TELEMETRY_H

#define tlm_h0 0
#define tlm_length 65
typedef union 
{
  float value;
  uint8_t bytes[4];
} STRIKE_t;

void telemetryInitialise(void);
void telemetryUpdate(void);
void telemetryOutputSerial(void);
#endif
