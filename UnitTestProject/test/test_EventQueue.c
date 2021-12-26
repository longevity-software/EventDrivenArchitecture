#ifdef TEST

#include "unity.h"
#include <time.h>
#include <stdlib.h>

#include "EventQueue.h"

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

    eBoolean postResult = EVTQ_PostEvent(input);

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
        if (False == EVTQ_PostEvent(input))
        {
            postResult = False;
        }
    }
    
    // assert that the result is still true
    TEST_ASSERT_EQUAL(True, postResult);

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
        if (False == EVTQ_PostEvent(input))
        {
            postResult = False;
        }
    }
    
    // assert that the result is still true
    TEST_ASSERT_EQUAL(True, postResult);

    // and that the hight water level matches
    TEST_ASSERT_EQUAL(TEST_LEVEL, EVTQ_GetHighWaterLevel());

}

#endif // TEST
