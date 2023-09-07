#include "gyro.hpp"

void BMX055::init(void)
{
    //------------------------------------------------------------//
    i2c.beginTransmission(ACC_ID);
    i2c.write(0x0F); // Select PMU_Range register
    i2c.write(0x03); // Range = +/- 2g
    i2c.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    i2c.beginTransmission(ACC_ID);
    i2c.write(0x10); // Select PMU_BW register
    i2c.write(0x08); // Bandwidth = 7.81 Hz
    i2c.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    i2c.beginTransmission(ACC_ID);
    i2c.write(0x11); // Select PMU_LPW register
    i2c.write(0x00); // Normal mode, Sleep duration = 0.5ms
    i2c.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    i2c.beginTransmission(GYRO_ID);
    i2c.write(0x0F); // Select Range register
    i2c.write(0x04); // Full scale = +/- 125 degree/s
    i2c.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    i2c.beginTransmission(GYRO_ID);
    i2c.write(0x10); // Select Bandwidth register
    i2c.write(0x07); // ODR = 100 Hz
    i2c.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    i2c.beginTransmission(GYRO_ID);
    i2c.write(0x11); // Select LPM1 register
    i2c.write(0x00); // Normal mode, Sleep duration = 2ms
    i2c.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    i2c.beginTransmission(MAG_ID);
    i2c.write(0x4B); // Select Mag register
    i2c.write(0x83); // Soft reset
    i2c.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    i2c.beginTransmission(MAG_ID);
    i2c.write(0x4B); // Select Mag register
    i2c.write(0x01); // Soft reset
    i2c.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    i2c.beginTransmission(MAG_ID);
    i2c.write(0x4C); // Select Mag register
    i2c.write(0x00); // Normal Mode, ODR = 10 Hz
    i2c.endTransmission();
    //------------------------------------------------------------//
    i2c.beginTransmission(MAG_ID);
    i2c.write(0x4E); // Select Mag register
    i2c.write(0x84); // X, Y, Z-Axis enabled
    i2c.endTransmission();
    //------------------------------------------------------------//
    i2c.beginTransmission(MAG_ID);
    i2c.write(0x51); // Select Mag register
    i2c.write(0x04); // No. of Repetitions for X-Y Axis = 9
    i2c.endTransmission();
    //------------------------------------------------------------//
    i2c.beginTransmission(MAG_ID);
    i2c.write(0x52); // Select Mag register
    i2c.write(0x16); // No. of Repetitions for Z-Axis = 15
    i2c.endTransmission();
}

xyz_t BMX055::read_acc(void){
    xyz_t xyz;
    uint8_t data[6];
    for (int i = 0; i < 6; i++)
    {
        i2c.beginTransmission(ACC_ID);
        i2c.write((2 + i)); // Select data register
        i2c.endTransmission();
        i2c.requestFrom(ACC_ID, (size_t)1); // Request 1 byte of data
        // Read 6 bytes of data
        // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
        if (i2c.available() == 1){
            data[i] = i2c.read();
        }
    }
    // Convert the data to 12-bits
    xyz.x = (float)(((data[1] << 8) + (data[0] & 0xF0)) >> 4);
    if (xyz.x > 2047.0f) xyz.x -= 4096.0f;

    xyz.y = (float)(((data[3] << 8) + (data[2] & 0xF0)) >> 4);
    if (xyz.y > 2047.0f) xyz.y -= 4096.0f;

    xyz.z = (float)(((data[5] << 8) + (data[4] & 0xF0)) >> 4);
    if (xyz.z > 2047.0f) xyz.z -= 4096.0f;

    xyz.x *= 0.0098; // range = +/-2g
    xyz.y *= 0.0098; // range = +/-2g
    xyz.z *= 0.0098; // range = +/-2g
    return xyz;
}

xyz_t BMX055::read_gyro(void){
    xyz_t xyz;
    uint8_t data[6];
  for (int i = 0; i < 6; i++)
  {
    i2c.beginTransmission(GYRO_ID);
    i2c.write((2 + i));    // Select data register
    i2c.endTransmission();
    i2c.requestFrom(GYRO_ID, (size_t)1);    // Request 1 byte of data
    // Read 6 bytes of data
    // xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
    if (i2c.available() == 1)
      data[i] = i2c.read();
  }
  // Convert the data
  xyz.x = (data[1] << 8) + data[0];
  if (xyz.x > 32767)  xyz.x -= 65536;
  xyz.y = (data[3] << 8) + data[2];
  if (xyz.y > 32767)  xyz.y -= 65536;
  xyz.z = (data[5] << 8) + data[4];
  if (xyz.z > 32767)  xyz.z -= 65536;

  xyz.x *= 0.0038; //  Full scale = +/- 125 degree/s
  xyz.y *= 0.0038; //  Full scale = +/- 125 degree/s
  xyz.z *= 0.0038; //  Full scale = +/- 125 degree/s

  return xyz;
}
xyz_t BMX055::read_mag(void)
{
    xyz_t xyz;
    uint8_t data[8];
  for (int i = 0; i < 8; i++)
  {
    i2c.beginTransmission(MAG_ID);
    i2c.write((0x42 + i));    // Select data register
    i2c.endTransmission();
    i2c.requestFrom(MAG_ID, (size_t)1);    // Request 1 byte of data
    // Read 6 bytes of data
    // xMag lsb, xMag msb, yMag lsb, yMag msb, zMag lsb, zMag msb
    if (i2c.available() == 1)
      data[i] = i2c.read();
  }
// Convert the data
  xyz.x = ((data[1] <<5) | (data[0]>>3));
  if (xyz.x > 4095)  xyz.x -= 8192;
  xyz.y = ((data[3] <<5) | (data[2]>>3));
  if (xyz.y > 4095)  xyz.y -= 8192;
  xyz.z = ((data[5] <<7) | (data[4]>>1));
  if (xyz.z > 16383)  xyz.z -= 32768;

  return xyz;
}