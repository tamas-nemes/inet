//
// Copyright (C) 2006 Andras Babos and Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "OSPFInterfaceStateDown.h"

#include "MessageHandler.h"
#include "OSPFArea.h"
#include "OSPFInterfaceStateLoopback.h"
#include "OSPFInterfaceStateNotDesignatedRouter.h"
#include "OSPFInterfaceStatePointToPoint.h"
#include "OSPFInterfaceStateWaiting.h"
#include "OSPFRouter.h"

namespace inet {

namespace ospf {

void InterfaceStateDown::processEvent(Interface *intf, Interface::InterfaceEventType event)
{
    if (event == Interface::INTERFACE_UP) {
        MessageHandler *messageHandler = intf->getArea()->getRouter()->getMessageHandler();
        messageHandler->startTimer(intf->getHelloTimer(), truncnormal(0.1, 0.01));    // add some deviation to avoid startup collisions
        messageHandler->startTimer(intf->getAcknowledgementTimer(), intf->getAcknowledgementDelay());
        switch (intf->getType()) {
            case Interface::POINTTOPOINT:
            case Interface::POINTTOMULTIPOINT:
            case Interface::VIRTUAL:
                changeState(intf, new InterfaceStatePointToPoint, this);
                break;

            case Interface::NBMA:
                if (intf->getRouterPriority() == 0) {
                    changeState(intf, new InterfaceStateNotDesignatedRouter, this);
                }
                else {
                    changeState(intf, new InterfaceStateWaiting, this);
                    messageHandler->startTimer(intf->getWaitTimer(), intf->getRouterDeadInterval());

                    long neighborCount = intf->getNeighborCount();
                    for (long i = 0; i < neighborCount; i++) {
                        Neighbor *neighbor = intf->getNeighbor(i);
                        if (neighbor->getPriority() > 0) {
                            neighbor->processEvent(Neighbor::START);
                        }
                    }
                }
                break;

            case Interface::BROADCAST:
                if (intf->getRouterPriority() == 0) {
                    changeState(intf, new InterfaceStateNotDesignatedRouter, this);
                }
                else {
                    changeState(intf, new InterfaceStateWaiting, this);
                    messageHandler->startTimer(intf->getWaitTimer(), intf->getRouterDeadInterval());
                }
                break;

            default:
                break;
        }
    }
    if (event == Interface::LOOP_INDICATION) {
        intf->reset();
        changeState(intf, new InterfaceStateLoopback, this);
    }
}

} // namespace ospf

} // namespace inet

