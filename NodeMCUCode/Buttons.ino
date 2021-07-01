// Attach interrupts to buttons
void initButtons()
{
  pinMode(WIFI_R_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WIFI_R_PIN), pressedWiFiR, FALLING);

  delay(1000);

  pinMode(LOC_MS_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LOC_MS_PIN), pressedLocMS, FALLING);
}

// Actions for reset button press
void ICACHE_RAM_ATTR pressedWiFiR()
{
  wifiReset();
}

// Attach for location mode switch button
void ICACHE_RAM_ATTR pressedLocMS()
{
  switchLocationMode();
}
