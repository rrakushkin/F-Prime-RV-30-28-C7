component RTC {

  // Define the input command port
  sync input CmdInput {
    opcode SET_TIME(u32 year, u32 month, u32 day, u32 hour, u32 minute, u32 second)
    opcode GET_TIME()
    opcode SET_ALARM(u8 minute, u8 hour, u8 date_or_weekday, bool weekday_alarm, u8 mode)
    opcode RESET_RTC()
    opcode ENABLE_ALARM_INTERRUPT()
    opcode DISABLE_ALARM_INTERRUPT()
    opcode CLEAR_ALARM_INTERRUPT()
  }

  // Define the output command response port
  async output CmdResponse {
    opcode SUCCESS()
    opcode FAILURE()
    opcode TIME(u32 year, u32 month, u32 day, u32 hour, u32 minute, u32 second)
  }

  // Define the event output port
  async output EventOutput {
    event ALARM_TRIGGERED()
    event RTC_RESET()
    event TIME_UPDATED(u32 year, u32 month, u32 day, u32 hour, u32 minute, u32 second)
  }

  // Define the parameter
  param I2C_Address(u8) default(0x52)

  // Define the commands
  command SET_TIME(u32 year, u32 month, u32 day, u32 hour, u32 minute, u32 second)
  command GET_TIME()
  command SET_ALARM(u8 minute, u8 hour, u8 date_or_weekday, bool weekday_alarm, u8 mode)
  command RESET_RTC()
  command ENABLE_ALARM_INTERRUPT()
  command DISABLE_ALARM_INTERRUPT()
  command CLEAR_ALARM_INTERRUPT()

  // Define telemetry
  telemetry TIME_UPDATED(u32 year, u32 month, u32 day, u32 hour, u32 minute, u32 second)

  // Define events
  event ALARM_TRIGGERED()
  event RTC_RESET()
}
