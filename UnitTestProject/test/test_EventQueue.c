#ifdef TEST

#include "unity.h"
#include <time.h>
#include <stdlib.h>

#include "EventQueue.h"

#include "mock_HardwareInterrupt.h"

#define MAX_TEST_QUEUE_SIZE     10

void setUp(void)
{
    EVTQ_Init();
    
    srand(time(NULL));   // Seed the random number generator
}

void tearDown(void)
{
}

//
//	Tests that if No Events have been added, that no events 
//  are returned from the queue.
//
void test_EventQueue_NoEventsInQueueNoEventsReturned(void)
{
    HALI_PauseInterrupts_Expect();
    HALI_ResumeInterrupts_Expect();

    const sEventRequestResult res = EVTQ_GetEvent();

    TEST_ASSERT_EQUAL(False, res.eventPresent);
}

//
//	Tests that if a single Event has been added, that the events
//  is returned from the queue.
//
void test_EventQueue_OneEventInQueueEventIsReturned(void)
{
    sEvent input;

    input.id = TestEvent;

    HALI_PauseInterrupts_Expect();
    HALI_ResumeInterrupts_Expect();

    eBoolean postResult = EVTQ_PostEvent(input);

    HALI_PauseInterrupts_Expect();
    HALI_ResumeInterrupts_Expect();

    const sEventRequestResult res = EVTQ_GetEvent();

    TEST_ASSERT_EQUAL(True, postResult);
    TEST_ASSERT_EQUAL(True, res.eventPresent);
    TEST_ASSERT(input.id == res.event.id);
}

//
//	Tests that if too many events are added, that the post event function.
//  returns False.
//
void test_EventQueue_EventQueueFullAddingNextReturnsFalse(void)
{
    sEvent input;

    input.id = TestEvent;

    int i;
    eBoolean postResult = True;

    for (i = 0; i < MAX_TEST_QUEUE_SIZE; ++i)
    {
        HALI_PauseInterrupts_Expect();
        HALI_ResumeInterrupts_Expect();

        if (False == EVTQ_PostEvent(input))
        {
            postResult = False;
        }
    }
    
    // assert that the result is still true
    TEST_ASSERT_EQUAL(True, postResult);

    HALI_PauseInterrupts_Expect();
    HALI_ResumeInterrupts_Expect();

    // this next one should fail as queue is full. 
    postResult = EVTQ_PostEvent(input);

    TEST_ASSERT_EQUAL(False, postResult);
}

//
//	Tests that if X Events have been added, that the high water level matches.
//
void test_EventQueue_XEventsInQueueHighWaterLevelMatches(void)
{
    sEvent input;

    input.id = TestEvent;

    int i;
    eBoolean postResult = True;

    const tu8 MIN_TEST_LEVEL = 3;
    const tu8 TEST_LEVEL_RANGE = (MAX_TEST_QUEUE_SIZE - MIN_TEST_LEVEL); 
    const tu8 TEST_LEVEL = (tu8)(MIN_TEST_LEVEL + (rand() % TEST_LEVEL_RANGE));

    for (i = 0; i < TEST_LEVEL; ++i)
    {            
        HALI_PauseInterrupts_Expect();
        HALI_ResumeInterrupts_Expect();

        if (False == EVTQ_PostEvent(input))
        {
            postResult = False;
        }
    }
    
    // assert that the result is still true
    TEST_ASSERT_EQUAL(True, postResult);

    HALI_PauseInterrupts_Expect();
    HALI_ResumeInterrupts_Expect();

    // and that the hight water level matches
    TEST_ASSERT_EQUAL(TEST_LEVEL, EVTQ_GetHighWaterLevel());

}

//
//	Tests that if X Events have been added, Y events are removed and then Z events are added, 
//  that the high water level matches.
//
void test_EventQueue_X_Y_ZEventsInQueueHighWaterLevelMatches(void)
{
    sEvent input;

    input.id = TestEvent;

    int i;
    eBoolean result = True;

    const tu8 MIN_ADDITION_LEVEL = 3;
    const tu8 BUFFER = 3;
    const tu8 ADDITION_RANGE = (MAX_TEST_QUEUE_SIZE - MIN_ADDITION_LEVEL - BUFFER); 
    const tu8 ADDITION_LEVEL = (tu8)(MIN_ADDITION_LEVEL + (rand() % ADDITION_RANGE));

    // add the initial range of events
    for (i = 0; i < ADDITION_LEVEL; ++i)
    {        
        HALI_PauseInterrupts_Expect();
        HALI_ResumeInterrupts_Expect();

        if (False == EVTQ_PostEvent(input))
        {
            result = False;
        }
    }
    
    // assert that the result is still true
    TEST_ASSERT_EQUAL(True, result);

    HALI_PauseInterrupts_Expect();
    HALI_ResumeInterrupts_Expect();

    // and that the hight water level matches
    TEST_ASSERT_EQUAL(ADDITION_LEVEL, EVTQ_GetHighWaterLevel());

    // subtract a few
    const tu8 MIN_SUBTRACTION_LEVEL = 1;
    const tu8 SUBTRACTION_RANGE = (ADDITION_LEVEL - MIN_SUBTRACTION_LEVEL);
    const tu8 SUBTRACTION_LEVEL = (tu8)(MIN_SUBTRACTION_LEVEL + (rand() % SUBTRACTION_RANGE));
    
    // add the initial range of events
    for (i = 0; i < SUBTRACTION_LEVEL; ++i)
    {
        HALI_PauseInterrupts_Expect();
        HALI_ResumeInterrupts_Expect();

        if (False == EVTQ_GetEvent().eventPresent)
        {
            result = False;
        }
    }
    
    // assert that the result is still true
    TEST_ASSERT_EQUAL(True, result);

    HALI_PauseInterrupts_Expect();
    HALI_ResumeInterrupts_Expect();

    // and that the hight water level matches
    TEST_ASSERT_EQUAL(ADDITION_LEVEL, EVTQ_GetHighWaterLevel());

    // now add a few more to extend the high water level
    const tu8 MIN_ADDITION_LEVEL_2 = SUBTRACTION_LEVEL; // we need to add at least as many as we subtracted.
    const tu8 ADDITION_LEVEL_2 = (tu8)(MIN_ADDITION_LEVEL_2 + (rand() % BUFFER));
    
    // add the initial range of events
    for (i = 0; i < ADDITION_LEVEL_2; ++i)
    {
        HALI_PauseInterrupts_Expect();
        HALI_ResumeInterrupts_Expect();

        if (False == EVTQ_PostEvent(input))
        {
            result = False;
        }
    }
    
    // assert that the result is still true
    TEST_ASSERT_EQUAL(True, result);

    // and that the hight water level matches
    const tu8 FINAL_LEVEL = (ADDITION_LEVEL - SUBTRACTION_LEVEL + ADDITION_LEVEL_2);
    
    HALI_PauseInterrupts_Expect();
    HALI_ResumeInterrupts_Expect();

    TEST_ASSERT_EQUAL(FINAL_LEVEL, EVTQ_GetHighWaterLevel());
}

//
//	Tests that if Events have been added, and subsequently removed, 
//  that the next request for events returns False.
//
void test_EventQueue_AllEventsRemovedFromQueueNextReturnsFalse(void)
{
    sEvent input;

    input.id = TestEvent;

    int i;
    eBoolean result = True;

    const tu8 MIN_ADDITION_LEVEL = 3;
    const tu8 ADDITION_RANGE = (MAX_TEST_QUEUE_SIZE - MIN_ADDITION_LEVEL); 
    const tu8 ADDITION_LEVEL = (tu8)(MIN_ADDITION_LEVEL + (rand() % ADDITION_RANGE));

    // add the initial range of events
    for (i = 0; i < ADDITION_LEVEL; ++i)
    {
        HALI_PauseInterrupts_Expect();
        HALI_ResumeInterrupts_Expect();

        if (False == EVTQ_PostEvent(input))
        {
            result = False;
        }
    }
    
    // assert that the result is still true
    TEST_ASSERT_EQUAL(True, result);

    HALI_PauseInterrupts_Expect();
    HALI_ResumeInterrupts_Expect();

    // and that the hight water level matches
    TEST_ASSERT_EQUAL(ADDITION_LEVEL, EVTQ_GetHighWaterLevel());

    tu8 removedCount = 0;

    HALI_PauseInterrupts_Expect();
    HALI_ResumeInterrupts_Expect();

    // count how many times an event is successfully removed from the queue
    while (True == EVTQ_GetEvent().eventPresent)
    {
        removedCount++;
        
        HALI_PauseInterrupts_Expect();
        HALI_ResumeInterrupts_Expect();
    }

    TEST_ASSERT_EQUAL(ADDITION_LEVEL, removedCount);
}

#endif // TEST
