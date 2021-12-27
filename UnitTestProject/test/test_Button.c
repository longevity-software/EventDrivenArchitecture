#ifdef TEST

#include "unity.h"

#include "Button.h"
#include "mock_EventQueue.h"
#include "mock_HardwareGpio.h"

#include <time.h>
#include <stdlib.h>

#define MAX_DEBOUNCE_COUNT     5

void setUp(void)
{
    BTN_Init();
    
    srand(time(NULL));   // Seed the random number generator
}

void tearDown(void)
{
}

void test_Button_ButtonOnePressedEventPostedAfter50MilliSeconds(void)
{
    sEvent event;

    event.id = Timer10MilliSecondsEvent;

    tu8 i;

    for (i = 0; i < (MAX_DEBOUNCE_COUNT - 1); ++i)
    { 
        HALG_GetButtonOneState_ExpectAndReturn(Active);

        BTN_EventProcessor(event);
    }

    sEvent expectedEvent;
    expectedEvent.id = ButtonPressedEvent;

    // one more, should post the event
    HALG_GetButtonOneState_ExpectAndReturn(Active);
    EVTQ_PostEvent_ExpectAndReturn(expectedEvent, True);

    BTN_EventProcessor(event);
}

void test_Button_ButtonOneReleasedEventPostedAfter50MilliSeconds(void)
{
    // call the button one pressed test to simulate the button being pressed.
    test_Button_ButtonOnePressedEventPostedAfter50MilliSeconds();

    sEvent event;

    event.id = Timer10MilliSecondsEvent;

    tu8 i;

    for (i = 0; i < (MAX_DEBOUNCE_COUNT - 1); ++i)
    { 
        HALG_GetButtonOneState_ExpectAndReturn(Inactive);

        BTN_EventProcessor(event);
    }

    sEvent expectedEvent;
    expectedEvent.id = ButtonReleasedEvent;

    // one more, should post the event
    HALG_GetButtonOneState_ExpectAndReturn(Inactive);
    EVTQ_PostEvent_ExpectAndReturn(expectedEvent, True);

    BTN_EventProcessor(event);
}

void test_Button_ButtonOnePressedEventPostedAfter50MilliSecondsWithReleaseMidDebounce(void)
{
    sEvent event;

    event.id = Timer10MilliSecondsEvent;

    const tu8 MIN_INITIAL_COUNT = 2;
    const tu8 INITIAL_COUNT_RANGE = (MAX_DEBOUNCE_COUNT - MIN_INITIAL_COUNT);
    const tu8 INITIAL_COUNT = (tu8)(MIN_INITIAL_COUNT + (rand() % INITIAL_COUNT_RANGE));
    tu8 i;

    for (i = 0; i < INITIAL_COUNT; ++i)
    { 
        HALG_GetButtonOneState_ExpectAndReturn(Active);

        BTN_EventProcessor(event);
    }

    // now set one instance where the button is not pressed.
    HALG_GetButtonOneState_ExpectAndReturn(Inactive);

    BTN_EventProcessor(event);

    // call the normal button debounce test to confirm that it is 50mS following this inactive state
    test_Button_ButtonOnePressedEventPostedAfter50MilliSeconds();    
}

void test_Button_ButtonOneReleasedEventPostedAfter50MilliSecondsWithPressMidDebounce(void)
{    
    // call the button one pressed test to simulate the button being pressed.
    test_Button_ButtonOnePressedEventPostedAfter50MilliSeconds();

    sEvent event;

    event.id = Timer10MilliSecondsEvent;

    const tu8 MIN_INITIAL_COUNT = 2;
    const tu8 INITIAL_COUNT_RANGE = (MAX_DEBOUNCE_COUNT - MIN_INITIAL_COUNT);
    const tu8 INITIAL_COUNT = (tu8)(MIN_INITIAL_COUNT + (rand() % INITIAL_COUNT_RANGE));
    tu8 i;

    for (i = 0; i < INITIAL_COUNT; ++i)
    { 
        HALG_GetButtonOneState_ExpectAndReturn(Inactive);

        BTN_EventProcessor(event);
    }

    // now set one instance where the button is pressed.
    HALG_GetButtonOneState_ExpectAndReturn(Active);

    BTN_EventProcessor(event);

    // Now confirm that it takes MAX_DEBOUNCE_COUNT times to raise the Button Released event
    for (i = 0; i < (MAX_DEBOUNCE_COUNT - 1); ++i)
    { 
        HALG_GetButtonOneState_ExpectAndReturn(Inactive);

        BTN_EventProcessor(event);
    }

    sEvent expectedEvent;
    expectedEvent.id = ButtonReleasedEvent;

    // one more, should post the event
    HALG_GetButtonOneState_ExpectAndReturn(Inactive);
    EVTQ_PostEvent_ExpectAndReturn(expectedEvent, True);

    BTN_EventProcessor(event);  
}

#endif // TEST
