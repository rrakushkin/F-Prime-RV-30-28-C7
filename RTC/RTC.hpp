// ======================================================================
// RTC.hpp
// ======================================================================


#ifndef Components_RTC_HPP
#define Components_RTC_HPP

#include "Components/RTC/RTCComponentAc.hpp"
#include "RV3028.hpp"

namespace Components {

  class RTC :
    public RTCComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction + destruction
      // ----------------------------------------------------------------------

      //! Construct RTC object
      RTC(
          const char* const compName 
      );

      //! Destroy RTC object
      ~RTC();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

      //! Handler implementation for command SET_TIME
      void SET_TIME_cmdHandler(
          FwOpcodeType opCode, 
          U32 cmdSeq, 
          U32 year,
          U32 month,
          U32 day,
          U32 hour,
          U32 minute,
          U32 second
      ) override;

      //! Handler implementation for command GET_TIME
      void GET_TIME_cmdHandler(
          FwOpcodeType opCode, 
          U32 cmdSeq 
      ) override;

      //! Handler implementation for command SET_ALARM
      void SET_ALARM_cmdHandler(
          FwOpcodeType opCode, 
          U32 cmdSeq,
          U8 minute,
          U8 hour,
          U8 date_or_weekday,
          bool weekday_alarm,
          U8 mode
      ) override;

      //! Handler implementation for command RESET_RTC
      void RESET_RTC_cmdHandler(
          FwOpcodeType opCode,
          U32 cmdSeq 
      ) override;

      //! Handler implementation for command ENABLE_ALARM_INTERRUPT
      void ENABLE_ALARM_INTERRUPT_cmdHandler(
          FwOpcodeType opCode, 
          U32 cmdSeq 
      ) override;

      //! Handler implementation for command DISABLE_ALARM_INTERRUPT
      void DISABLE_ALARM_INTERRUPT_cmdHandler(
          FwOpcodeType opCode, 
          U32 cmdSeq 
      ) override;

      //! Handler implementation for command CLEAR_ALARM_INTERRUPT
      void CLEAR_ALARM_INTERRUPT_cmdHandler(
          FwOpcodeType opCode, 
          U32 cmdSeq 
      ) override;

  };

}

#endif
