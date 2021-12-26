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

void test_EventQueue_NoEventsInQueueNoEventsReturned(void)
{
    const sEventRequestResult res = EVTQ_GetEvent();

    TEST_ASSERT_EQUAL(False, res.eventPresent);
}

#endif // TEST
