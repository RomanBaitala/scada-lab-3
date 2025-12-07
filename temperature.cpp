#include "temperature.h"

// --- Calibration coefficients ---
static int16_t AC1, AC2, AC3;
static uint16_t AC4, AC5, AC6;
static int16_t BMP_B1, BMP_B2, BMP_MB, BMP_MC, BMP_MD;

// === Helper functions ===
static uint16_t bmp180_read16u(uint8_t reg) 
{
    Wire.beginTransmission(BMP180_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom((int)BMP180_ADDR, 2);  // Use int to avoid overload ambiguity
    uint16_t val = (Wire.read() << 8) | Wire.read();
    return val;
}

static int16_t bmp180_read16s(uint8_t reg) 
{
    return (int16_t)bmp180_read16u(reg);
}

static void bmp180_write8(uint8_t reg, uint8_t value) 
{
    Wire.beginTransmission(BMP180_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

static uint16_t bmp180_readRawTemperature() 
{
    bmp180_write8(0xF4, 0x2E);  // Start temperature conversion
    delay(5);                   // Wait 4.5 ms
    return bmp180_read16u(0xF6);
}

// === Initialization ===
bool bmp180_begin() 
{
    Wire.begin();

    Wire.beginTransmission(BMP180_ADDR);
    if (Wire.endTransmission() != 0) 
    {
        return false;
    }

    AC1 = bmp180_read16s(0xAA);
    AC2 = bmp180_read16s(0xAC);
    AC3 = bmp180_read16s(0xAE);
    AC4 = bmp180_read16u(0xB0);
    AC5 = bmp180_read16u(0xB2);
    AC6 = bmp180_read16u(0xB4);
    BMP_B1 = bmp180_read16s(0xB6);
    BMP_B2 = bmp180_read16s(0xB8);
    BMP_MB = bmp180_read16s(0xBA);
    BMP_MC = bmp180_read16s(0xBC);
    BMP_MD = bmp180_read16s(0xBE);

    return true;
}

// === Read temperature in Celsius ===
float bmp180_readTemperature() 
{
    int32_t UT = bmp180_readRawTemperature();

    int32_t X1 = ((UT - (int32_t)AC6) * (int32_t)AC5) >> 15;
    int32_t X2 = ((int32_t)BMP_MC << 11) / (X1 + BMP_MD);
    int32_t B5 = X1 + X2;

    float temp = ((B5 + 8) >> 4) / 10.0f;
    return temp;
}
