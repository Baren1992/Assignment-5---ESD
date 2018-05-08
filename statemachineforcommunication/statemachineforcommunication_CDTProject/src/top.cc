
#include "top.hh"

#include "Client_D2.hh"
#include "Server_D1.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsulerole.hh"
#include "umlrtcommsport.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;

Capsule_top::Capsule_top( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, client_D2( &slot->parts[part_client_D2] )
, server_D1( &slot->parts[part_server_D1] )
{
}




void Capsule_top::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_top::unbindPort( bool isBorder, int portId, int index )
{
}

void Capsule_top::initialize( const UMLRTMessage & msg )
{
}

void Capsule_top::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "client_D2",
        &Client_D2,
        1,
        1,
        false,
        false
    },
    {
        "server_D1",
        &Server_D1,
        1,
        1,
        false,
        false
    }
};

static void instantiate_top( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_top::part_client_D2].slots[0]->ports[Capsule_Client_D2::borderport_clientPort], 0, &slot->parts[Capsule_top::part_server_D1].slots[0]->ports[Capsule_Server_D1::borderport_serverPort], 0 );
    Client_D2.instantiate( NULL, slot->parts[Capsule_top::part_client_D2].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_top::part_client_D2].slots[0], Client_D2.numPortRolesBorder ) );
    Server_D1.instantiate( NULL, slot->parts[Capsule_top::part_server_D1].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_top::part_server_D1].slots[0], Server_D1.numPortRolesBorder ) );
    slot->capsule = new Capsule_top( &top, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass top = 
{
    "top",
    NULL,
    instantiate_top,
    2,
    roles,
    0,
    NULL,
    0,
    NULL
};

