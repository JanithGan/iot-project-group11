// Attach interrupts to buttons
void initButtons()
{
  // pinMode(WIFI_R_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WIFI_R_PIN), pressedWiFiR, RISING);

  // pinMode(LOC_MS_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LOC_MS_PIN), pressedLocMS, RISING);
}

// Actions for reset button press
ICACHE_RAM_ATTR void pressedWiFiR()
{
  wifiReset();
}

// Attach for location mode switch button
ICACHE_RAM_ATTR void pressedLocMS()
{
  switchLocationMode();
}
