/*
Speeduino - Simple engine management for the Arduino Mega 2560 platform
Copyright (C) Josh Stewart
A full copy of the license may be found in the projects root directory
*/

/*
 * Sets the next available error
 * Returns the error number or 0 if there is no more room for errors
 */
byte setError(byte errorID)
{
  if(errorCount < MAX_ERRORS)
  {
    errorCodes[errorCount] = errorID;
    errorCount++;
    if(errorCount == 1) { BIT_SET(currentStatus.engine, BIT_SPARK_ERROR); } //Enable the error indicator
    return errorCount;
  }
  return 0;
}

void clearError(byte errorID)
{
  byte clearedError;
  
  if (errorID == errorCodes[0]) { clearedError = 0; }
  else if(errorID == errorCodes[1]) { clearedError = 1; }
  else if(errorID == errorCodes[2]) { clearedError = 2; }
  else if(errorID == errorCodes[3]) { clearedError = 3; }
  else return; //Occurs when the error we're being asked to clear is not currently one of the active errors

  errorCodes[clearedError] = ERR_NONE;
  //Clear the required error and move any from above it 'down' in the error array
  for (byte x=clearedError; x < (errorCount-1); x++)
  {
    errorCodes[x] = errorCodes[x+1];
    errorCodes[x+1] = ERR_NONE;
  }

  errorCount--;
  if(errorCount == 0) { BIT_CLEAR(currentStatus.engine, BIT_SPARK_ERROR); } //Enable the error indicator
  
}

byte getNextError()
{
  packedError currentError;
  
  //We alternate through the errors once per second
  byte currentErrorNum = currentStatus.secl % MAX_ERRORS; //Which error number will be returned. This changes once per second. Note that as long as MAX_ERRORS is a power of 2, this % operation is performed very quickly. 
  
  currentError.errorNum = currentErrorNum;
  currentError.errorID = errorCodes[currentErrorNum];

  return *(byte*)&currentError; //Ugly, but this forces the cast of the currentError struct to a byte. 
}

