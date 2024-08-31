module Components {
    @ Real time clock for time keeping, alerts, and backup voltages
    active component RV3028 {

        ######################################################################
        # Commands                                                           #
        ######################################################################

        # Command to set the RTC time
        async command SET_TIME(year: U32, month: U32, day: U32, hour: U32, minute: U32, second: U32) {
            opcode 1
        }

        # Command to get the current RTC time
        sync command GET_TIME {
            opcode 2
            return year: U32, month: U32, day: U32, hour: U32, minute: U32, second: U32
        }

        # Command to set the RTC alarm
        async command SET_ALARM(minute: U8, hour: U8, date_or_weekday: U8, weekday_alarm: bool, mode: U8) {
            opcode 3
        }

        # Command to reset the RTC
        async command RESET_RTC {
            opcode 4
        }

        # Command to enable the RTC alarm interrupt
        async command ENABLE_ALARM_INTERRUPT {
            opcode 5
        }

        # Command to disable the RTC alarm interrupt
        async command DISABLE_ALARM_INTERRUPT {
            opcode 6
        }

        # Command to clear the RTC alarm interrupt flag
        async command CLEAR_ALARM_INTERRUPT {
            opcode 7
        }

        ######################################################################
        # Events                                                             #
        ######################################################################

        event ALARM_TRIGGERED {
            severity activity high
            id 0
            format "Alarm triggered"
        }

        event RTC_RESET {
            severity activity high
            id 1
            format "RTC reset"
        }

        ######################################################################
        # Telemetry                                                          #
        ######################################################################

        telemetry TIME_UPDATED {
            year: U32
            month: U32
            day: U32
            hour: U32
            minute: U32
            second: U32
        }

        ######################################################################
        # Ports                                                              #
        ######################################################################

        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @ Port to set the value of a parameter
        param set port prmSetOut

        ######################################################################
        # Parameters                                                         #
        ######################################################################

        param I2C_Address: U8 default 0x52
    }
}
