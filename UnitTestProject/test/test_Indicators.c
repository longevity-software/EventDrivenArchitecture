#ifdef TEST

#include "unity.h"

#include "Indicators.h"

#include "mock_HardwareGpio.h"

void setUp(void)
{
    HALG_SetLedOneState_Expect(Inactive);

    INDC_Init();
}

void tearDown(void)
{
}

void test_Indicators_ButtonPressedEventTurnsOnLED(void)
{
    sEvent event;

    event.id = ButtonPressedEvent;

    HALG_SetLedOneState_Expect(Active);

    INDC_EventProcessor(event);
}

void test_Indicators_LEDTurnsOffAfter200MilliSeconds(void)
{
    // set to the on state
    test_Indicators_ButtonPressedEventTurnsOnLED();

    sEvent event;

    event.id = Timer10MilliSecondsEvent;

    tu8 i;

    // perform the first 190mS of events
    for (i = 0; i < 19; ++i)
    {
        INDC_EventProcessor(event);
    }

    // the 200mS event should set the LED off.
    HALG_SetLedOneState_Expect(Inactive);

    INDC_EventProcessor(event);
}

void test_Indicators_LEDTurnsBackOnAfter800MilliSeconds(void)
{
    // Continue on from the LED turning off
    test_Indicators_LEDTurnsOffAfter200MilliSeconds();

    sEvent event;

    event.id = Timer10MilliSecondsEvent;

    tu8 i;

    // perform the first 790mS of events
    for (i = 0; i < 79; ++i)
    {
        INDC_EventProcessor(event);
    }

    // the 800mS event should set the LED on.
    HALG_SetLedOneState_Expect(Active);
    
    INDC_EventProcessor(event);
}

void test_Indicators_ButtonReleasedEventTurnsOffLED(void)
{
    test_Indicators_ButtonPressedEventTurnsOnLED();

    sEvent event;

    event.id = ButtonReleasedEvent;

    HALG_SetLedOneState_Expect(Inactive);

    INDC_EventProcessor(event);
}

#endif // TEST
