package inet.examples.test.issue509;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.AdhocHost;
import inet.node.inet.WirelessHost;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.wireless.common.medium.RadioMedium;
import inet.visualizer.common.IntegratedVisualizer;


network WlanAndWpanCoexistenceTopology
{
    parameters:
        int nbrWlanTransmitters;
        int nbrWpanTransmitters;

    submodules:

        visualizer: IntegratedVisualizer {
            @display("p=44,43");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=47,114");
        }
        radioMedium: RadioMedium {
            @display("p=47,180");
        }

        wlanHost[nbrWlanTransmitters]: WirelessHost {
            @display("r=,,#707070;p=151.57034,211.65227");
            wlan[*].mgmt.typename = "Ieee80211MgmtStaSimplified";
            wlan[*].agent.typename = "";
        }
        wlanAP: AccessPoint {
            @display("p=151.57034,149.29451;r=,,#707070");
            wlan[*].mgmt.typename = "Ieee80211MgmtApSimplified";
        }
        wlanSink: WirelessHost {
            @display("r=,,#707070;p=145.65318,83.75058");
            wlan[*].mgmt.typename = "Ieee80211MgmtStaSimplified";
            wlan[*].agent.typename = "";
        }

        wpanHost[nbrWpanTransmitters]: AdhocHost {
            @display("r=,,#707070;p=206.64545,126.99136;i=misc/sensor2");
        }

        wpanSink: AdhocHost {
            @display("p=201.18346,180.2458;r=,,#707070;i=misc/sensor2");
        }
}
