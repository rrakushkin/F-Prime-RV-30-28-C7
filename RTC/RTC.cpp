// ======================================================================
// RTC.cpp
// ======================================================================

#include "RTC.hpp"
#include "RV3028.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  RV3028 ::
    RV3028(const char* const compName) :
      RV3028ComponentBase(compName),
      i2cAddress(0x52)  // Default I2C address
  {

  }

  RV3028 ::
    ~RV3028()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void RV3028 ::
    SET_TIME_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq,
        U32 year,
        U32 month,
        U32 day,
        U32 hour,
        U32 minute,
        U32 second
    )
  {
    if (this->rtcDriver.setTime(second, minute, hour, 0, day, month, year)) {
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
    } else {
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
    }
  }

  void RV3028 ::
    GET_TIME_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    uint8_t sec, min, hour, weekday, date, month;
    uint16_t year;
    if (this->rtcDriver.getTime(sec, min, hour, weekday, date, month, year)) {
      this->tlmWrite_TIME_UPDATED(year, month, date, hour, min, sec);
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
    } else {
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
    }
  }

  void RV3028 ::
    SET_ALARM_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq,
        U8 minute,
        U8 hour,
        U8 date_or_weekday,
        bool weekday_alarm,
        U8 mode
    )
  {
    if (this->rtcDriver.setAlarm(minute, hour, date_or_weekday, weekday_alarm, mode)) {
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
    } else {
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
    }
  }

  void RV3028 ::
    RESET_RTC_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    this->rtcDriver.reset();
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
    this->log_ACTIVITY_HI_RTC_RESET();
  }

  void RV3028 ::
    ENABLE_ALARM_INTERRUPT_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    if (this->rtcDriver.enableAlarmInterrupt()) {
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
    } else {
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
    }
  }

  void RV3028 ::
    DISABLE_ALARM_INTERRUPT_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    if (this->rtcDriver.disableAlarmInterrupt()) {
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
    } else {
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
    }
  }

  void RV3028 ::
    CLEAR_ALARM_INTERRUPT_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    if (this->rtcDriver.clearAlarmInterruptFlag()) {
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
    } else {
      this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
    }
  }

}
