
#include "topControllers.hh"

#include "Client_D2.hh"
#include "Server_D1.hh"
#include "top.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcommsport.hh"
#include "umlrtcommsportfarend.hh"
#include "umlrtcontroller.hh"
#include "umlrtslot.hh"
#include <cstddef>


static UMLRTController DefaultController_( "DefaultController" );

UMLRTController * DefaultController = &DefaultController_;

static Capsule_top top_( &top, &top_slots[InstId_top], NULL, NULL, true );

static UMLRTSlot * slots_top[] = 
{
    &top_slots[InstId_top_client_D2],
    &top_slots[InstId_top_server_D1]
};

static UMLRTCapsulePart parts_top[] = 
{
    {
        &top,
        Capsule_top::part_client_D2,
        1,
        &slots_top[0]
    },
    {
        &top,
        Capsule_top::part_server_D1,
        1,
        &slots_top[1]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_top_client_D2[] = 
{
    {
        0,
        &borderports_top_server_D1[Capsule_Server_D1::borderport_serverPort]
    }
};

UMLRTCommsPort borderports_top_client_D2[] = 
{
    {
        &Client_D2,
        Capsule_Client_D2::borderport_clientPort,
        &top_slots[InstId_top_client_D2],
        1,
        borderfarEndList_top_client_D2,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_top_client_D2_ptrs[] = 
{
    &borderports_top_client_D2[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_top_client_D2[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_top_client_D2[] = 
{
    {
        &Client_D2,
        Capsule_Client_D2::internalport_timer,
        &top_slots[InstId_top_client_D2],
        1,
        &internalfarEndList_top_client_D2[1],
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    },
    {
        &Client_D2,
        Capsule_Client_D2::internalport_log,
        &top_slots[InstId_top_client_D2],
        1,
        internalfarEndList_top_client_D2,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_top_client_D2_ptrs[] = 
{
    &internalports_top_client_D2[0],
    &internalports_top_client_D2[1]
};

static Capsule_Client_D2 top_client_D2_( &Client_D2, &top_slots[InstId_top_client_D2], borderports_top_client_D2_ptrs, internalports_top_client_D2_ptrs, true );

static UMLRTCommsPortFarEnd borderfarEndList_top_server_D1[] = 
{
    {
        0,
        &borderports_top_client_D2[Capsule_Client_D2::borderport_clientPort]
    }
};

UMLRTCommsPort borderports_top_server_D1[] = 
{
    {
        &Server_D1,
        Capsule_Server_D1::borderport_serverPort,
        &top_slots[InstId_top_server_D1],
        1,
        borderfarEndList_top_server_D1,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_top_server_D1_ptrs[] = 
{
    &borderports_top_server_D1[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_top_server_D1[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_top_server_D1[] = 
{
    {
        &Server_D1,
        Capsule_Server_D1::internalport_log,
        &top_slots[InstId_top_server_D1],
        1,
        internalfarEndList_top_server_D1,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    },
    {
        &Server_D1,
        Capsule_Server_D1::internalport_timer,
        &top_slots[InstId_top_server_D1],
        1,
        &internalfarEndList_top_server_D1[1],
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_top_server_D1_ptrs[] = 
{
    &internalports_top_server_D1[0],
    &internalports_top_server_D1[1]
};

static Capsule_Server_D1 top_server_D1_( &Server_D1, &top_slots[InstId_top_server_D1], borderports_top_server_D1_ptrs, internalports_top_server_D1_ptrs, true );

UMLRTSlot top_slots[] = 
{
    {
        "top",
        0,
        &top,
        NULL,
        0,
        &top_,
        &DefaultController_,
        2,
        parts_top,
        0,
        NULL,
        NULL,
        true,
        false
    },
    {
        "top.client_D2",
        0,
        &Client_D2,
        &top,
        Capsule_top::part_client_D2,
        &top_client_D2_,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_top_client_D2,
        NULL,
        true,
        false
    },
    {
        "top.server_D1",
        0,
        &Server_D1,
        &top,
        Capsule_top::part_server_D1,
        &top_server_D1_,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_top_server_D1,
        NULL,
        true,
        false
    }
};

