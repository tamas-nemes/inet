//
// Copyright (C) 2020 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef __INET_IEEE8021QSOCKETCOMMANDPROCESSOR_H
#define __INET_IEEE8021QSOCKETCOMMANDPROCESSOR_H

#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ModuleRefByPar.h"
#include "inet/common/packet/Message.h"
#include "inet/linklayer/ieee8021q/Ieee8021qSocketTable.h"
#include "inet/queueing/base/PacketFlowBase.h"

namespace inet {

class INET_API Ieee8021qSocketCommandProcessor : public queueing::PacketFlowBase, public TransparentProtocolRegistrationListener
{
  protected:
    ModuleRefByPar<Ieee8021qSocketTable> socketTable;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;
    virtual void handleCommand(Request *request);
    virtual void processPacket(Packet *packet) override {}

    virtual cGate *getRegistrationForwardingGate(cGate *gate) override;
};

} // namespace inet

#endif

