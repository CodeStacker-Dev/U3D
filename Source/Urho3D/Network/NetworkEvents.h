//
// Copyright (c) 2008-2025 the U3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

/// Server connection established.
URHO3D_EVENT(E_SERVERCONNECTED, ServerConnected)
{
}

/// Server connection disconnected.
URHO3D_EVENT(E_SERVERDISCONNECTED, ServerDisconnected)
{
}

/// Server connection failed.
URHO3D_EVENT(E_CONNECTFAILED, ConnectFailed)
{
}

/// Server connection failed because its already connected or tries to connect already.
URHO3D_EVENT(E_CONNECTIONINPROGRESS, ConnectionInProgress)
{
}

/// New client connection established.
URHO3D_EVENT(E_CLIENTCONNECTED, ClientConnected)
{
    URHO3D_PARAM(P_CONNECTION, Connection);        // Connection pointer
}

/// Client connection disconnected.
URHO3D_EVENT(E_CLIENTDISCONNECTED, ClientDisconnected)
{
    URHO3D_PARAM(P_CONNECTION, Connection);        // Connection pointer
}

/// Client has sent identity: identity map is in the event data.
URHO3D_EVENT(E_CLIENTIDENTITY, ClientIdentity)
{
    URHO3D_PARAM(P_CONNECTION, Connection);        // Connection pointer
    URHO3D_PARAM(P_ALLOW, Allow);                  // bool
}

/// Client has informed to have loaded the scene.
URHO3D_EVENT(E_CLIENTSCENELOADED, ClientSceneLoaded)
{
    URHO3D_PARAM(P_CONNECTION, Connection);        // Connection pointer
}

/// Unhandled network message received.
URHO3D_EVENT(E_NETWORKMESSAGE, NetworkMessage)
{
    URHO3D_PARAM(P_CONNECTION, Connection);        // Connection pointer
    URHO3D_PARAM(P_MESSAGEID, MessageID);          // int
    URHO3D_PARAM(P_DATA, Data);                    // Buffer
}

/// About to send network update on the client or server.
URHO3D_EVENT(E_NETWORKUPDATE, NetworkUpdate)
{
}

/// Network update has been sent on the client or server.
URHO3D_EVENT(E_NETWORKUPDATESENT, NetworkUpdateSent)
{
}

/// Scene load failed, either due to file not found or checksum error.
URHO3D_EVENT(E_NETWORKSCENELOADFAILED, NetworkSceneLoadFailed)
{
    URHO3D_PARAM(P_CONNECTION, Connection);      // Connection pointer
}

/// Remote event: adds Connection parameter to the event data.
URHO3D_EVENT(E_REMOTEEVENTDATA, RemoteEventData)
{
    URHO3D_PARAM(P_CONNECTION, Connection);      // Connection pointer
}

/// Server refuses client connection because of the ban.
URHO3D_EVENT(E_NETWORKBANNED, NetworkBanned)
{
}

/// Server refuses connection because of invalid password.
URHO3D_EVENT(E_NETWORKINVALIDPASSWORD, NetworkInvalidPassword)
{
}

/// When LAN discovery found hosted server.
URHO3D_EVENT(E_NETWORKHOSTDISCOVERED, NetworkHostDiscovered)
{
    URHO3D_PARAM(P_ADDRESS, Address);   // String
    URHO3D_PARAM(P_PORT, Port);         // int
    URHO3D_PARAM(P_BEACON, Beacon);     // VariantMap
}

/// NAT punchtrough succeeds.
URHO3D_EVENT(E_NETWORKNATPUNCHTROUGHSUCCEEDED, NetworkNatPunchtroughSucceeded)
{
    URHO3D_PARAM(P_ADDRESS, Address);   // String
    URHO3D_PARAM(P_PORT, Port);         // int
}

/// NAT punchtrough fails.
URHO3D_EVENT(E_NETWORKNATPUNCHTROUGHFAILED, NetworkNatPunchtroughFailed)
{
    URHO3D_PARAM(P_ADDRESS, Address);   // String
    URHO3D_PARAM(P_PORT, Port);         // int
}

/// Connecting to NAT master server failed.
URHO3D_EVENT(E_NATMASTERCONNECTIONFAILED, NetworkNatMasterConnectionFailed)
{
}

/// Connecting to NAT master server succeeded.
URHO3D_EVENT(E_NATMASTERCONNECTIONSUCCEEDED, NetworkNatMasterConnectionSucceeded)
{
}

/// Disconnected from NAT master server.
URHO3D_EVENT(E_NATMASTERDISCONNECTED, NetworkNatMasterDisconnected)
{
}

}
