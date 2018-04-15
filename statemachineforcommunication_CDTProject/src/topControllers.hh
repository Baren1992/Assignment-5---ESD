
#ifndef TOPCONTROLLERS_HH
#define TOPCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_top,
    InstId_top_client_D2,
    InstId_top_server_D1
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_top_client_D2[];
extern UMLRTCommsPort internalports_top_client_D2[];
extern UMLRTCommsPort borderports_top_server_D1[];
extern UMLRTCommsPort internalports_top_server_D1[];
extern UMLRTSlot top_slots[];

#endif

