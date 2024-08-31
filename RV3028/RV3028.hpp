#ifndef RV3028_HPP
#define RV3028_HPP

#include <cstdint>

class RV3028 {
public:
    RV3028();
    ~RV3028();

    bool init(uint8_t i2c_address);
    bool setTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t weekday, uint8_t date, uint8_t month, uint16_t year);
    bool getTime(uint8_t &sec, uint8_t &min, uint8_t &hour, uint8_t &weekday, uint8_t &date, uint8_t &month, uint16_t &year);
    
    bool setUnixTime(uint32_t unixTime);
    uint32_t getUnixTime();
    
    bool setAlarm(uint8_t min, uint8_t hour, uint8_t date_or_weekday, bool setWeekdayAlarm_not_Date, uint8_t mode);
    bool enableAlarmInterrupt();
    bool disableAlarmInterrupt();
    bool clearAlarmInterruptFlag();
    bool readAlarmInterruptFlag();

    bool enableTrickleCharge(uint8_t resistor_value);
    bool disableTrickleCharge();

    void reset();

private:
    uint8_t i2cAddress;
    uint8_t _time[7]; // Time storage (sec, min, hr, weekday, date, month, year)

    bool writeRegister(uint8_t reg, uint8_t data);
    uint8_t readRegister(uint8_t reg);
    bool writeMultipleRegisters(uint8_t reg, uint8_t *data, uint8_t length);
    bool readMultipleRegisters(uint8_t reg, uint8_t *data, uint8_t length);

    uint8_t bcdToDec(uint8_t val);
    uint8_t decToBcd(uint8_t val);
};

#endif // RV3028_HPP
