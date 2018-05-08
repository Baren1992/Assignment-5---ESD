
#include "Client_D2.hh"

#include "communication.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Client_D2::Capsule_Client_D2( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, clientPort( borderPorts[borderport_clientPort] )
, timer( internalPorts[internalport_timer] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Connected] = "Connected";
    stateNames[Data_Recieved] = "Data_Recieved";
    stateNames[Disconnected] = "Disconnected";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}








void Capsule_Client_D2::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_clientPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_clientPort, index, true );
            break;
        }
}

void Capsule_Client_D2::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_clientPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_clientPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_clientPort], index );
            break;
        }
}

void Capsule_Client_D2::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case Disconnected:
        currentState = state_____Disconnected( &message );
        break;
    case Connected:
        currentState = state_____Connected( &message );
        break;
    case Data_Recieved:
        currentState = state_____Data_Recieved( &message );
        break;
    default:
        break;
    }
}

void Capsule_Client_D2::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = Disconnected;
}

const char * Capsule_Client_D2::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Client_D2::update_state( Capsule_Client_D2::State newState )
{
    currentState = newState;
}

void Capsule_Client_D2::entryaction_____Disconnected( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Client_D2::Disconnected entry  */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client_D2::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Client_D2 transition subvertex0,Disconnected */
    log.log("Client is ready...");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client_D2::transitionaction_____transition1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Client_D2 transition Disconnected,Connected,connect_req:clientPort */
    // Reply to a connection message by server
    log.log("Client received connection request...");
    if ( clientPort.connection_ok().send() ) {
    log.log( "Connection established!");
    } else {
    log.log( "Connection failed!");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client_D2::transitionaction_____transition2( const UMLRTMessage * msg )
{
    #define data ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Client_D2 transition Connected,Data_Recieved,send_data:clientPort */
    // Reply to a send data message by server
    log.log("Data is sending...");
    if ( clientPort.ack_data().send() ) {
    log.log( "Client acknowleged data:");
    log.log(data);
    } else {
    log.log( "Error acknowledging data!");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef data
}

void Capsule_Client_D2::transitionaction_____transition3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Client_D2 transition Data_Recieved,Disconnected,disconnect_req:clientPort */
    // Reply to a disconnection message by server
    log.log("Client receive disconnection request...");
    if ( clientPort.disconnect_ok().send() ) {
    log.log( "Server and client are disconnected!");
    } else {
    log.log( "Disconnection failed!");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client_D2::transitionaction_____transition4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Client_D2 transition Connected,Disconnected,over_time:clientPort */
    clientPort.reset().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client_D2::transitionaction_____transition5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Client_D2 transition Data_Recieved,Disconnected,over_time:clientPort */
    clientPort.reset().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client_D2::transitionaction_____transition6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Client_D2 transition Disconnected,Disconnected,over_time:clientPort */
    clientPort.reset().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client_D2::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( Disconnected );
    entryaction_____Disconnected( msg );
}

void Capsule_Client_D2::actionchain_____transition1( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition1( msg );
    update_state( Connected );
}

void Capsule_Client_D2::actionchain_____transition2( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition2( msg );
    update_state( Data_Recieved );
}

void Capsule_Client_D2::actionchain_____transition3( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition3( msg );
    update_state( Disconnected );
    entryaction_____Disconnected( msg );
}

void Capsule_Client_D2::actionchain_____transition4( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition4( msg );
    update_state( Disconnected );
    entryaction_____Disconnected( msg );
}

void Capsule_Client_D2::actionchain_____transition5( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition5( msg );
    update_state( Disconnected );
    entryaction_____Disconnected( msg );
}

void Capsule_Client_D2::actionchain_____transition6( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition6( msg );
    update_state( Disconnected );
    entryaction_____Disconnected( msg );
}

Capsule_Client_D2::State Capsule_Client_D2::state_____Connected( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_clientPort:
        switch( msg->getSignalId() )
        {
        case communication::signal_send_data:
            actionchain_____transition2( msg );
            return Data_Recieved;
        case communication::signal_over_time:
            actionchain_____transition4( msg );
            return Disconnected;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Client_D2::State Capsule_Client_D2::state_____Data_Recieved( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_clientPort:
        switch( msg->getSignalId() )
        {
        case communication::signal_disconnect_req:
            actionchain_____transition3( msg );
            return Disconnected;
        case communication::signal_over_time:
            actionchain_____transition5( msg );
            return Disconnected;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Client_D2::State Capsule_Client_D2::state_____Disconnected( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_clientPort:
        switch( msg->getSignalId() )
        {
        case communication::signal_connect_req:
            actionchain_____transition1( msg );
            return Connected;
        case communication::signal_over_time:
            actionchain_____transition6( msg );
            return Disconnected;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}


static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_Client_D2::port_clientPort,
        "communication",
        "clientPort",
        "",
        1,
        true,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPortRole portroles_internal[] = 
{
    {
        Capsule_Client_D2::port_timer,
        "Timing",
        "timer",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_Client_D2::port_log,
        "Log",
        "log",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    }
};

static void instantiate_Client_D2( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &Client_D2 );
    slot->capsule = new Capsule_Client_D2( &Client_D2, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass Client_D2 = 
{
    "Client_D2",
    NULL,
    instantiate_Client_D2,
    0,
    NULL,
    1,
    portroles_border,
    2,
    portroles_internal
};

