#ifdef TEST

#include "unity.h"

#include "EventQueue.h"

void setUp(void)
{
    EVTQ_Init();
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
    EVTQ_PostEvent(TestEvent);

    const sEventRequestResult res = EVTQ_GetEvent();

    TEST_ASSERT_EQUAL(True, res.eventPresent);
    TEST_ASSERT(TestEvent == res.event.id);
}

#endif // TEST
