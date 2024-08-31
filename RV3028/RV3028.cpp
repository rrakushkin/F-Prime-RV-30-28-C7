#include "RV3028.hpp"
#include <hardware/i2c.h>
#include <pico/stdlib.h>

RV3028::RV3028() : i2cAddress(0) {}

RV3028::~RV3028() {}

bool RV3028::init(uint8_t i2c_address) {
    this->i2cAddress = i2c_address;
    // Assume i2c is already initialized elsewhere in the CubeSat firmware
    return true;
}

bool RV3028::setTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t weekday, uint8_t date, uint8_t month, uint16_t year) {
    _time[0] = decToBcd(sec);
    _time[1] = decToBcd(min);
    _time[2] = decToBcd(hour);
    _time[3] = decToBcd(weekday);
    _time[4] = decToBcd(date);
    _time[5] = decToBcd(month);
    _time[6] = decToBcd(year - 2000); // Assuming year input as YYYY

    return writeMultipleRegisters(0x00, _time, 7); // Assuming registers start at 0x00
}

bool RV3028::getTime(uint8_t &sec, uint8_t &min, uint8_t &hour, uint8_t &weekday, uint8_t &date, uint8_t &month, uint16_t &year) {
    if (!readMultipleRegisters(0x00, _time, 7)) {
        return false;
    }

    sec = bcdToDec(_time[0]);
    min = bcdToDec(_time[1]);
    hour = bcdToDec(_time[2]);
    weekday = bcdToDec(_time[3]);
    date = bcdToDec(_time[4]);
    month = bcdToDec(_time[5]);
    year = bcdToDec(_time[6]) + 2000;

    return true;
}

bool RV3028::setUnixTime(uint32_t unixTime) {
    uint8_t unix_reg[4];
    unix_reg[0] = unixTime;
    unix_reg[1] = unixTime >> 8;
    unix_reg[2] = unixTime >> 16;
    unix_reg[3] = unixTime >> 24;

    return writeMultipleRegisters(0x1B, unix_reg, 4); // Assuming UNIX time registers start at 0x1B
}

uint32_t RV3028::getUnixTime() {
    uint8_t unix_reg[4];
    if (!readMultipleRegisters(0x1B, unix_reg, 4)) {
        return 0;
    }
    return (uint32_t)unix_reg[3] << 24 | (uint32_t)unix_reg[2] << 16 | (uint32_t)unix_reg[1] << 8 | unix_reg[0];
}

bool RV3028::setAlarm(uint8_t min, uint8_t hour, uint8_t date_or_weekday, bool setWeekdayAlarm_not_Date, uint8_t mode) {
    // Implementation of alarm setting
    return true;
}

bool RV3028::enableAlarmInterrupt() {
    return true;
}

bool RV3028::disableAlarmInterrupt() {
    return true;
}

bool RV3028::clearAlarmInterruptFlag() {
    return true;
}

bool RV3028::readAlarmInterruptFlag() {
    return true;
}

bool RV3028::enableTrickleCharge(uint8_t resistor_value) {
    return true;
}

bool RV3028::disableTrickleCharge() {
    return true;
}

void RV3028::reset() {
    writeRegister(0x10, 0x80); // Assuming reset bit is in register 0x10, bit 7
}

bool RV3028::writeRegister(uint8_t reg, uint8_t data) {
    uint8_t buf[2] = {reg, data};
    return i2c_write_blocking(i2c_default, i2cAddress, buf, 2, false) >= 0;
}

uint8_t RV3028::readRegister(uint8_t reg) {
    uint8_t data;
    i2c_write_blocking(i2c_default, i2cAddress, &reg, 1, true);
    i2c_read_blocking(i2c_default, i2cAddress, &data, 1, false);
    return data;
}

bool RV3028::writeMultipleRegisters(uint8_t reg, uint8_t *data, uint8_t length) {
    uint8_t buf[length + 1];
    buf[0] = reg;
    for (uint8_t i = 0; i < length; i++) {
        buf[i + 1] = data[i];
    }
    return i2c_write_blocking(i2c_default, i2cAddress, buf, length + 1, false) >= 0;
}

bool RV3028::readMultipleRegisters(uint8_t reg, uint8_t *data, uint8_t length) {
    if (i2c_write_blocking(i2c_default, i2cAddress, &reg, 1, true) < 0) {
        return false;
    }
    return i2c_read_blocking(i2c_default, i2cAddress, data, length, false) >= 0;
}

uint8_t RV3028::bcdToDec(uint8_t val) {
    return (val / 16 * 10) + (val % 16);
}

uint8_t RV3028::decToBcd(uint8_t val) {
    return (val / 10 * 16) + (val % 10);
}
