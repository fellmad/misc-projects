#include "WexTestClass.h"

class TestFlipPrintTicketHandlers : public WEX::TestClass<TestFlipPrintTicketHandlers> {
public:

    TEST_CLASS(TestFlipPrintTicketHandlers);
    TEST_CLASS_SETUP(Setup);
    TEST_CLASS_CLEANUP(Cleanup);

    TEST_METHOD(TestGetFromEmptyTicketReturnsNotFound);
    TEST_METHOD(TestGetDataWithNullPointer);
    TEST_METHOD(TestSetDataWithNullPointer);
    TEST_METHOD(TestReturnedFlipped);
    TEST_METHOD(TestGet_BadData);
    TEST_METHOD(TestSet_BadData);

private:

    _CrtMemState _start_mem_state {};
    byte* _pbyte {nullptr};
};