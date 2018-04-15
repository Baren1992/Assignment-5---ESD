
#include "Server_D1.hh"

#include "communication.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtsignal.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Server_D1::Capsule_Server_D1( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, serverPort( borderPorts[borderport_serverPort] )
, timer( internalPorts[internalport_timer] )
, Data( "FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF" )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Connected] = "Connected";
    stateNames[Data_send] = "Data_send";
    stateNames[Disconnected] = "Disconnected";
    stateNames[Exit] = "Exit";
    stateNames[time_out] = "time_out";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}








void Capsule_Server_D1::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_serverPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_serverPort, index, true );
            break;
        }
}

void Capsule_Server_D1::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_serverPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_serverPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_serverPort], index );
            break;
        }
}



void Capsule_Server_D1::inject( const UMLRTMessage & message )
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
    case Data_send:
        currentState = state_____Data_send( &message );
        break;
    case Exit:
        currentState = state_____Exit( &message );
        break;
    case time_out:
        currentState = state_____time_out( &message );
        break;
    default:
        break;
    }
}

void Capsule_Server_D1::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = Disconnected;
}

const char * Capsule_Server_D1::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Server_D1::update_state( Capsule_Server_D1::State newState )
{
    currentState = newState;
}

void Capsule_Server_D1::entryaction_____Connected( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1::Connected entry  */
    timer.cancelTimer(timerID); //stop timer so it is not sending messages any more
    timerID=timer.informEvery(UMLRTTimespec(60,0)); //wait 60s
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::entryaction_____Data_send( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1::Data_send entry  */
    timer.cancelTimer(timerID);
    timerID=timer.informEvery(UMLRTTimespec(10,0)); //wait 10s
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::entryaction_____Disconnected( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1::Disconnected entry  */
    timerID=timer.informEvery(UMLRTTimespec(60,0)); //wait 60s
    if ( serverPort.connect_req().send() ) {
    log.log( "Server is requesting connection...");
    } else {
    log.log( "Connection Error");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::entryaction_____Exit( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1::Exit entry  */
    timer.cancelTimer(timerID);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::entryaction_____time_out( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1::time out entry  */
    timer.cancelTimer(timerID); //stop timer so it is not sending messages any more
    log.log( "Timeout!");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1 transition subvertex0,Disconnected */
    log.log("initializing server...");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::transitionaction_____timeout( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1 transition Disconnected,time out,timeout:timer/rtUnbound:serverPort/ack_data:serverPort/disconnect_ok:serverPort/reset:serverPort/rtBound:serverPort */
    if ( serverPort.over_time().send() ) {
    log.log( "Unsuccessful transfer!");
    } else {
    log.log( "Unsuccessful transfer Error");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::transitionaction_____transition1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1 transition Disconnected,Connected,connection_ok:serverPort */
    // Reply to a connection message by client
    if (serverPort.send_data(Data).send()) {
    log.log( "Server is sending data...");
    } else {
    log.log( "Error sending data!");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::transitionaction_____transition2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1 transition Connected,Data_send,ack_data:serverPort */
    // Reply to a ack_data message by sending a disconnect request.
    log.log("Data successfully received...");
    if ( serverPort.disconnect_req().send() ) {
    log.log( "Server is requesting disconnection...");
    } else {
    log.log( "Error in disconnection request!");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::transitionaction_____transition3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1 transition Data_send,Exit,disconnect_ok:serverPort */
    // Reply to a  sucessful disconnection 
    log.log("Successful transfer!");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::transitionaction_____transition5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1 transition Connected,time out,timeout:timer/rtUnbound:serverPort/connection_ok:serverPort/disconnect_ok:serverPort/reset:serverPort/rtBound:serverPort */
    //timer.cancelTimer(timerID);
    if ( serverPort.over_time().send() ) {
    log.log( "Unsuccessful transfer!");
    } else {
    log.log( "Unsuccessful transfer Error");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::transitionaction_____transition6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1 transition Data_send,time out,timeout:timer/rtUnbound:serverPort/connection_ok:serverPort/ack_data:serverPort/reset:serverPort/rtBound:serverPort */
    //timer.cancelTimer(timerID);
    if ( serverPort.over_time().send() ) {
    log.log( "Unsuccessful transfer!");
    } else {
    log.log( "Unsuccessful transfer Error");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::transitionaction_____transition7( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/statemachineforcommunication/statemachineforcommunication.uml statemachineforcommunication::Server_D1 transition time out,Disconnected,reset:serverPort */
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server_D1::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( Disconnected );
    entryaction_____Disconnected( msg );
}

void Capsule_Server_D1::actionchain_____timeout( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____timeout( msg );
    update_state( time_out );
    entryaction_____time_out( msg );
}

void Capsule_Server_D1::actionchain_____transition1( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition1( msg );
    update_state( Connected );
    entryaction_____Connected( msg );
}

void Capsule_Server_D1::actionchain_____transition2( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition2( msg );
    update_state( Data_send );
    entryaction_____Data_send( msg );
}

void Capsule_Server_D1::actionchain_____transition3( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition3( msg );
    update_state( Exit );
    entryaction_____Exit( msg );
}

void Capsule_Server_D1::actionchain_____transition5( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition5( msg );
    update_state( time_out );
    entryaction_____time_out( msg );
}

void Capsule_Server_D1::actionchain_____transition6( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition6( msg );
    update_state( time_out );
    entryaction_____time_out( msg );
}

void Capsule_Server_D1::actionchain_____transition7( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition7( msg );
    update_state( Disconnected );
    entryaction_____Disconnected( msg );
}

Capsule_Server_D1::State Capsule_Server_D1::state_____Connected( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_serverPort:
        switch( msg->getSignalId() )
        {
        case communication::signal_ack_data:
            actionchain_____transition2( msg );
            return Data_send;
        case UMLRTSignal::rtUnbound:
            actionchain_____transition5( msg );
            return time_out;
        case communication::signal_connection_ok:
            actionchain_____transition5( msg );
            return time_out;
        case communication::signal_disconnect_ok:
            actionchain_____transition5( msg );
            return time_out;
        case communication::signal_reset:
            actionchain_____transition5( msg );
            return time_out;
        case UMLRTSignal::rtBound:
            actionchain_____transition5( msg );
            return time_out;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition5( msg );
            return time_out;
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

Capsule_Server_D1::State Capsule_Server_D1::state_____Data_send( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_serverPort:
        switch( msg->getSignalId() )
        {
        case communication::signal_disconnect_ok:
            actionchain_____transition3( msg );
            return Exit;
        case UMLRTSignal::rtUnbound:
            actionchain_____transition6( msg );
            return time_out;
        case communication::signal_connection_ok:
            actionchain_____transition6( msg );
            return time_out;
        case communication::signal_ack_data:
            actionchain_____transition6( msg );
            return time_out;
        case communication::signal_reset:
            actionchain_____transition6( msg );
            return time_out;
        case UMLRTSignal::rtBound:
            actionchain_____transition6( msg );
            return time_out;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition6( msg );
            return time_out;
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

Capsule_Server_D1::State Capsule_Server_D1::state_____Disconnected( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_serverPort:
        switch( msg->getSignalId() )
        {
        case communication::signal_connection_ok:
            actionchain_____transition1( msg );
            return Connected;
        case UMLRTSignal::rtUnbound:
            actionchain_____timeout( msg );
            return time_out;
        case communication::signal_ack_data:
            actionchain_____timeout( msg );
            return time_out;
        case communication::signal_disconnect_ok:
            actionchain_____timeout( msg );
            return time_out;
        case communication::signal_reset:
            actionchain_____timeout( msg );
            return time_out;
        case UMLRTSignal::rtBound:
            actionchain_____timeout( msg );
            return time_out;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____timeout( msg );
            return time_out;
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

Capsule_Server_D1::State Capsule_Server_D1::state_____Exit( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Server_D1::State Capsule_Server_D1::state_____time_out( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_serverPort:
        switch( msg->getSignalId() )
        {
        case communication::signal_reset:
            actionchain_____transition7( msg );
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
        Capsule_Server_D1::port_serverPort,
        "communication",
        "serverPort",
        "",
        1,
        true,
        true,
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
        Capsule_Server_D1::port_timer,
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
        Capsule_Server_D1::port_log,
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

static void instantiate_Server_D1( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &Server_D1 );
    slot->capsule = new Capsule_Server_D1( &Server_D1, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass Server_D1 = 
{
    "Server_D1",
    NULL,
    instantiate_Server_D1,
    0,
    NULL,
    1,
    portroles_border,
    2,
    portroles_internal
};

